/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "cfg.h"
#include "log.h"
#define _OPT_C
#include "opt.h"
#include "str.h"

opts opt = {
	.b = NULL,
	.d = 0,
	.e = NULL,
	.h = 0,
	.i = 0,
	.m = CFG_FCNT_DFL,
	.n = 0,
	.p = 0,
	.q = 0,
	.r = NULL,
	.s = NULL,
	.v = 0,
	.z = 0
};

int opt_init(int argc, char *argv[])
{
	int o;
	char *e;

	opterr = 0;
	while ((o = getopt(argc, argv, OPT_STR)) > 0) {
		switch(o) {
		case 'b':
			opt.b = optarg;
			break;
		case 'd':
			e = NULL;
			opt.d = (time_t) strtoul(optarg, &e, 10);
			if (e && *e) {
				logerr("invalid argument for -d: %s", optarg);
				return -1;
			}
			if (opt.d < 1) {
				logerr("argument for -d must be at least 1");
				return -1;
			}
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
			opt.l = 1;
			break;
		case 'm':
			e = NULL;
			opt.m = (size_t) strtoul(optarg, &e, 10);
			if (e && *e) {
				logerr("invalid argument for -m: %s", optarg);
				return -1;
			}
			if (opt.m < 1) {
				logerr("argument for -m must be at least 1");
				return -1;
			}
			if (opt.m > CFG_FCNT_MAX) {
				logerr("argument for -m too high (max "\
					STR(CFG_FCNT_MAX)")");
				return -1;
			}
			break;
		case 'n':
			opt.n = 1;
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
				logerr("unknown syslog facility %s", opt.s);
				return -1;
			}
			log_stderr = 0;
			break;
		case 'v':
			opt.v++;
			break;
		case 'z':
			if (optarg) {
				opt.z = (time_t) strtoul(optarg, &e, 10);
				if (e && *e) {
					logerr("invalid argument for -z: %s",
						optarg);
					return -1;
				}
				if (opt.z < 1) {
					logerr("argument for -z must be"
					"at least 1");
					return -1;
				}
			} else
				opt.z = CFG_EAGE_DFL;
			break;
		case ':':
			logerr("missing option argument for -%c", optopt);
			return -1;
		default:
			logerr("unknown option -%c", optopt);
			return -1;
		}
	}
	return 0;
}
