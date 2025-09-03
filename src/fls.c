/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <stdlib.h>

#include "fls.h"
#include "log.h"
#include "str.h"

/* files are kept in bidirectional sorted (oldest to newest) linked list
 * with at most fls_cnt_max items, with fls_end pointing to the last last one */
fls_ent *fls, *fls_end;
size_t fls_cnt;
size_t fls_cnt_max;

/* compare two timespecs */
#define TSCMP(t1, t2) ((t1.tv_sec == t2.tv_sec) ?\
	((t1.tv_nsec == t2.tv_nsec) ?\
		0 : (t1.tv_nsec > t2.tv_nsec) ? 1 : -1) :\
	((t1.tv_sec > t2.tv_sec) ? 1 : -1))

/* compare nm/tm with fls entry in name (nbo!=0) or time (nbo==0) mode */
#define FLSCMP(nm, tm, fls, nbo)\
	(nbo ? str_cmp(nm, fls->nm) : TSCMP(tm, fls->tm))

int fls_init(size_t max)
{
	fls_cnt_max = max;
	return 0;
}

void fls_ent_free(fls_ent *e)
{
	if (e->nm)
		free(e->nm);
	free(e);
}

void fls_free(void)
{
	fls_ent *nxt;
	while (fls) {
		nxt = fls->nxt;
		fls_ent_free(fls);
		fls = nxt;
	}
}

int fls_add(const char *nm, size_t lnm,
	off_t sz, struct timespec tm, nlink_t hl, int nbo)
{
	fls_ent *e, *tmp;

	if (fls_cnt >= fls_cnt_max) {
		/* trust fls_cnt that fls_end isn't NULL */
		if (FLSCMP(nm, tm, fls_end, nbo) >= 0)
			/* already have fls_cnt_max older files */
			return 0;

		/* dismiss newest file at fls_end */
		tmp = fls_end->prv;
		fls_ent_free(fls_end);
		/* fls_end->prv may be NULL if fls_cnt_max is 1 */
		if (tmp)
			tmp->nxt = NULL;
		fls_end = tmp;
		/* fls_end equals fls if fls_cnt_max is 1 */
		if (!(--fls_cnt))
			fls = NULL;
	}

	/* new entry */
	if (!(e = calloc(1, sizeof(fls_ent)))) {
		logcrt("unable to allocate entry for %s", nm);
		return -1;
	}
	if (!(e->nm = malloc(lnm + 1))) {
		logcrt("unable to allocate name for %s", nm);
		free(e);
		return -1;
	}
	memcpy(e->nm, nm, lnm + 1);
	e->tm.tv_sec = tm.tv_sec;
	e->tm.tv_nsec = tm.tv_nsec;
	e->sz = sz;
	e->hl = hl;

	if (!fls) {
		/* first one */
		fls = fls_end = e;
		goto stored;
	}
	if (FLSCMP(nm, tm, fls, nbo) <= 0) {
		/* prepend */
		fls->prv = e;
		e->nxt = fls;
		fls = e;
		goto stored;
	}
	if (FLSCMP(nm, tm, fls_end, nbo) > 0) {
		/* append */
		tmp = fls_end;
		goto append;
	}
	/* insert */
	tmp = fls;
	while(tmp->nxt && (FLSCMP(nm, tm, tmp->nxt, nbo) > 0))
		tmp = tmp->nxt;
append:
	e->prv = tmp;
	if (!(e->nxt = tmp->nxt))
		fls_end = e;
	else
		e->nxt->prv = e;
	tmp->nxt = e;
stored:
	fls_cnt++;
	return 0;
}
