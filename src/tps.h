/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _TPS_H
#define _TPS_H
#include <stdint.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

/* type to hold filesystem size (i.e. a multiple of block size and block count).
 * As statvfs() uses unsigned long for block size and fsblkcnt_t for block
 * count, uintmax_t seems to be the best choice here. Maximum value for this
 * type is also defined to be shown with -l. */
typedef uintmax_t umax;
#define UMAX_MAX UINTMAX_MAX
#endif
