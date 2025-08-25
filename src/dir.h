/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _DIR_H
#define _DIR_H
#include <time.h>
#include "tps.h"


int dir_cln(const char *dir, size_t lnd, umax spc, uint tsm, uint usg,
	const char *bgn, const char *end, const char *reg, uint ics,
	size_t max, int prv, time_t emp, size_t *cnte, size_t *cntr);
#endif
