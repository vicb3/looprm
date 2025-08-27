/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define _OPT_C
#include "cfg.h"
#include "opt.h"

opts opt = {
	.a = CFG_EAGE_DFL,
	.b = NULL,
	.c = 0,
	.d = 0,
	.e = NULL,
	.h = 0,
	.i = 0,
	.l = 0,
	.m = CFG_FCNT_DFL,
	.p = 0,
	.q = 0,
	.r = NULL,
	.s = NULL,
	.t = 0,
	.u = 0,
	.v = 0,
	.z = 0
};

/* convert optarg to ulong in opt.OPT & check bounds */
#define OPTARG_ULONG(OPT, MIN, MAX)\
	errno = 0;\
	while (isspace(*optarg))\
		optarg++;\
	if (*optarg == '-') {\
		logalr("invalid argument for -" STR(OPT) ": %s", optarg);\
		return -1;\
	}\
	opt.OPT = strtoul(optarg, &e, 10);\
	if (errno || (e == optarg) || *e) {\
		logalr("invalid argument for -" STR(OPT) ": %s", optarg);\
		return -1;\
	}\
	if (MIN && (opt.OPT < MIN)) {\
		logalr("argument for -" STR(OPT) " too low (min "\
			STR(MIN) "): %s", optarg);\
		return -1;\
	}\
	if (MAX && (opt.OPT > MAX)) {\
		logalr("argument for -" STR(OPT) " too high (max "\
			STR(MAX) "): %s", optarg);\
		return -1;\
	}

/* additional check for time values */
#define OPTARG_TIME(OPT)\
	if ((time_t) opt.OPT < 0) {\
		logalr("time argument for -" STR(OPT) " too high: %s", optarg);\
		return -1;\
	}

int opt_init(int argc, char *argv[])
{
	int o;
	char *e;

	opterr = 0;
	while ((o = getopt(argc, argv, OPT_STR)) > 0) {
		switch(o) {
		case 'a':
			OPTARG_ULONG(a, 1, 0);
			OPTARG_TIME(a);
			break;
		case 'b':
			opt.b = optarg;
			break;
		case 'c':
			opt.c = 1;
			break;
		case 'd':
			OPTARG_ULONG(d, 1, 0);
			OPTARG_TIME(d);
			break;
		case 'e':
			opt.e = optarg;
			break;
		case 'h':
			opt.h = 1;
			break;
		case 'i':
			opt.i = 1;
			break;
		case 'l':
			OPTARG_ULONG(l, LOG_PRI_ALR, LOG_PRI_DBG);
			break;
		case 'm':
			OPTARG_ULONG(m, 1, CFG_FCNT_MAX);
			break;
		case 'p':
			opt.p = 1;
			break;
		case 'q':
			opt.q = 1;
			break;
		case 'r':
			opt.r = optarg;
			break;
		case 's':
			opt.s = optarg;
			if (log_sl_open(opt.s)) {
				logalr("unknown syslog facility %s", opt.s);
				return -1;
			}
			log_stderr = 0;
			break;
		case 't':
			opt.t = 1;
			break;
		case 'u':
			opt.u = 1;
			break;
		case 'v':
			opt.v++;
			break;
		case 'z':
			opt.z = 1;
			break;
		case ':':
			logalr("missing option argument for -%c", optopt);
			return -1;
		default:
			logalr("unknown option -%c", optopt);
			return -1;
		}
	}
	return 0;
}
