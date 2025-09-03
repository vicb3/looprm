/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _OPT_H
#define _OPT_H

#include "tps.h"

#define OPT_STR ":a:b:cd:e:hil:m:npqr:s:tuvz"

typedef struct {
	ulong a;		/* minimal file age for -z */
	const char *b;		/* filename beginning */
	uint c;			/* compiled-in limits */
	ulong d;		/* max duration */
	const char *e;		/* filename ending */
	uint h;			/* help */
	uint i;			/* case-insensitive name handling */
	uint l;			/* log level */
	ulong m;		/* max # of non-empty files to remove */
	uint n;			/* name-based file ordering */
	uint p;			/* consider free space for privileged users */
	uint q;			/* quiet stderr */
	const char *r;		/* filename regex */
	const char *s;		/* syslog facility */
	uint t;			/* total size mode */
	uint u;			/* disk usage as file size */
	uint v;			/* verbose logging */
	uint z;			/* remove zero-sized files */
} opts;

extern opts opt;

int opt_init(int argc, char *argv[]);
#endif
