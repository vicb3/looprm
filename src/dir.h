/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _DIR_H
#define _DIR_H
#include <time.h>
#include "tps.h"

int dir_cln(const char *dir, size_t lnd, umax spc,
	const char *bgn, const char *end, const char *reg,
	size_t max, int noact, int prv, time_t empty,
	size_t *cnte, size_t *cntr);
#endif
