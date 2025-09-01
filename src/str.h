/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _STR_H
#define _STR_H
#include "tps.h"

/* Stringify macro */
#define STR_I(m) #m
#define STR(m) STR_I(m)

int str_sz(umax *dst, const char *str);
#endif
