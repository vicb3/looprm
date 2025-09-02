/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <errno.h>
#include <inttypes.h>
#include <string.h>
#include <strings.h>

#include "str.h"

int (*str_cmp)(const char *s1, const char *s2) = strcmp;
int (*str_ncmp)(const char *s1, const char *s2, size_t n) = strncmp;

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

/* ignore case */
void str_ics(void)
{
	str_cmp = strcasecmp;
	str_ncmp = strncasecmp;
}

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
