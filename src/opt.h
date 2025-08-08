/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _OPT_H
#define _OPT_H

#include "tps.h"

#define OPT_STR ":b:d:e:hlm:npqs:vz::"

typedef struct {
	const char *b;		/* filename beginning */
	time_t d;		/* max duration */
	const char *e;		/* filename ending */
	uint h;			/* help */
	uint l;			/* limits */
	size_t m;		/* max # of non-empty files to remove */
	uint n;			/* no-act */
	uint p;			/* consider free space for privileged users */
	uint q;			/* quiet stderr */
	const char *s;		/* syslog facility */
	uint v;			/* verbose logging */
	time_t z;		/* remove zero-sized files (holds min age) */
} opts;

#ifndef _OPT_C
extern opts opt;
#endif
int opt_init(int argc, char *argv[]);
#endif
