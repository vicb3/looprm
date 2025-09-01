/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _CFG_H
#define _CFG_H

#if defined(NAME) && defined(VERSION)
#define CFG_NAME NAME
#define CFG_VERSION VERSION
#else
#error "NAME and VERSION must be defined"
#endif

#define CFG_COPYRIGHT "Copyright (c) 2025 Vic B <vic@4ever.vip>.\n"\
	"License GPLv3: GNU GPL version 3"\
	" <https://gnu.org/licenses/gpl.html>.\n"

#define CFG_DISCLAIMER \
	"This is free software: you are free to change and redistribute it.\n"\
	"There is NO WARRANTY, to the extent permitted by law.\n"

/* Number of non-empty files to remove */
#define CFG_FCNT_DFL	16		/* default value */
#define CFG_FCNT_MAX	16777216	/* maximal value */

/* Maximal path length */
#ifdef PATH_MAX
#define CFG_PATH_MAX	PATH_MAX
#else
#define CFG_PATH_MAX	4096
#endif

/* Minimal age of empty files in seconds */
#define CFG_EAGE_DFL	60
#endif
