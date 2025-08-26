/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _FLS_H
#define _FLS_H
#include <stddef.h>
#include <sys/types.h>
#include <time.h>

typedef struct fls_s {
	char *nm;		/* name */
	off_t sz;		/* size */
	struct timespec tm;	/* time */
	size_t hl;		/* hardlinks */
	struct fls_s *prv;	/* previous */
	struct fls_s *nxt;	/* next */
} fls_ent;

#ifndef _FLS_C
extern fls_ent *fls;
#endif

int fls_init(size_t cnt_max);
/* fls_ent_free and fls_free are for final cleanup only (these don't
 * update internal fls_cnt and fls_end) */
void fls_ent_free(fls_ent *e);
void fls_free(void);
int fls_add(const char *nm, size_t nml, off_t sz,  struct timespec tm, nlink_t hl);
#endif
