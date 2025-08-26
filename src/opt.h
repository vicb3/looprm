/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _OPT_H
#define _OPT_H

#include "tps.h"

#define OPT_STR ":b:cd:e:hil:m:pqr:s:tuvz::"

typedef struct {
	const char *b;		/* filename beginning */
	uint c;			/* compiled-in limits */
	time_t d;		/* max duration */
	const char *e;		/* filename ending */
	uint h;			/* help */
	uint i;			/* case-insensitive matching */
	uint l;			/* log level */
	size_t m;		/* max # of non-empty files to remove */
	uint p;			/* consider free space for privileged users */
	uint q;			/* quiet stderr */
	const char *r;		/* filename regex */
	const char *s;		/* syslog facility */
	uint t;			/* total size mode */
	uint u;			/* disk usage as file size */
	uint v;			/* verbose logging */
	time_t z;		/* remove zero-sized files (holds min age) */
} opts;

#ifndef _OPT_C
extern opts opt;
#endif
int opt_init(int argc, char *argv[]);
#endif
