/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "cfg.h"
#include "dir.h"
#include "log.h"
#include "opt.h"
#include "str.h"
#include "tps.h"

/* exit status codes for main */
#define EXIT_OK 	0	/* success */
#define EXIT_FAIL	1	/* failure (files removed but goal not met) */
#define EXIT_ERR	2	/* error (wrong usage or no files to remove) */

int main(int argc, char *argv[])
{
	char *dir;
	size_t lnd;
	umax spc;
	size_t cnte, cntr;
	int r;
	struct timespec t[3]; /* start, end, diff */

	clock_gettime(CLOCK_REALTIME, &t[0]);
	/* parse options */
	if (opt_init(argc, argv))
		return EXIT_ERR;

	/* setup logging (except syslog which is handled in opt_init) */
	if (opt.q)			/* quiet stderr */
		log_stderr = 0;
	if (opt.q && !opt.s)		/* no logging */
		log_level = LOG_PRI_NONE;
	else if (opt.v)			/* verbose debug */
		log_level = (log_level + opt.v <= LOG_PRI_DBG) ?
			log_level + opt.v : LOG_PRI_DBG;

	/* help & limits */
	if (opt.h) 			/* show help */
		puts(CFG_HLP_STR);
	if (opt.c) {			/* show limits */
		if (opt.h)
			putchar('\n');
		printf(CFG_LMT_STR,
			(umax) UMAX_MAX,
			(size_t) CFG_PATH_MAX - 1,
			(size_t) CFG_FCNT_MAX);
	}
	if (opt.h || opt.c) {
		if (argc > optind) {
			logalr("unexpected arguments with -h and/or -c");
			return EXIT_ERR;
		} else
			return EXIT_OK;
	}

	/* sanity checks */
	if (argc - optind <= 1) {	/* missing arguments */
		logalr("not enough arguments; try " CFG_NAME " -h");
		return EXIT_ERR;
	}
	if (argc - optind > 2) {	/* too many arguments */
		logalr("too many arguments; try " CFG_NAME " -h");
		return EXIT_ERR;
	}

	/* parse non-option arguments */
	dir = argv[optind];
	if (!(lnd = strlen(dir))) {
		logalr("empty directory name");
		return EXIT_ERR;
	}
	if (str_sz(&spc, argv[optind + 1])) {
			logalr("invalid size %s", argv[optind+1]);
			return EXIT_ERR;
	}
	/* strip trailing slashes (except first character for "/") */
	while ((lnd > 1) && (dir[lnd - 1] == '/')) {
		dir[--lnd] = 0;
	}

	r = dir_cln(dir, lnd, spc, opt.t, opt.u, opt.b, opt.e, opt.r, opt.i,
		opt.m, opt.p, opt.z, &cnte, &cntr);

	clock_gettime(CLOCK_REALTIME, &t[1]);
	t[2].tv_sec = t[1].tv_sec - t[0].tv_sec;
	t[2].tv_nsec = t[1].tv_nsec - t[0].tv_nsec;
	if (t[2].tv_nsec < 0) {
		t[2].tv_nsec += 1000000000UL;
		t[2].tv_sec--;
	}

	if (opt.z)
		loginf("%s: removed %zu empty and %zu non-empty file(s)"
			" in %lu.%03lus", dir, cnte, cntr,
			t[2].tv_sec, t[2].tv_nsec / 1000000);
	else
		loginf("%s: removed %zu file(s) in %lu.%03lus",
			dir, cntr, t[2].tv_sec, t[2].tv_nsec / 1000000);

	if (opt.d) {
		if ((t[2].tv_sec > opt.d) ||
			((t[2].tv_sec == opt.d) && t[2].tv_nsec > 0))
			logwrn("%s: execution time %lu.%03lus exceeds expected"
				" maximum of %lus", dir,
				t[2].tv_sec, t[2].tv_nsec / 1000000, opt.d);
	}
	log_sl_close();

	switch(r) {
	case 0:
		return EXIT_OK;
	case 1:
		return EXIT_FAIL;
	default:
		return EXIT_ERR;
	}
}
