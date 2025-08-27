/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

#include "cfg.h"
#include "str.h"

typedef struct {
	const uchar sf;	/* unit suffix */
	const uchar ls;	/* left bit shift */
} unit_ls;

/* bit shifts for size units */
unit_ls units[] = {
	{'K', 10},
	{'M', 20},
	{'G', 30},
	{'T', 40},
	{'P', 50},
	{'E', 60},
	{0, 0}
};

/* multiply *dst by size unit suffix in sf */
int sz_unit(umax *dst, char sf)
{
	umax tmp;
	unit_ls *unit = units;

	while (unit->sf != sf) {
		if (!(++unit)->sf)	/* unknown suffix */
			return -1;
	}

	tmp = *dst << unit->ls;
	if ((tmp >> unit->ls) != *dst)	/* overflow */
		return -1;
	*dst = tmp;
	return 0;
}

int str_sz(umax *dst, const char *str)
{
	umax tmp;
	char *e;

	while (isspace(*str))
		str++;
	if (*str == '-')
		return -1;
	errno = 0;
	tmp = strtoumax(str, &e, 10);
	if (errno || (e == str))
		return -1;

	if (*e) {
		if (*(e + 1))
			return -1;
		if (sz_unit(&tmp, *e))
			return -1;
	}
	*dst = tmp;
	return 0;
}
