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

/* Stringify macro */
#define STR_I(m) #m
#define STR(m) STR_I(m)

/* Help string */
#define CFG_HLP_STR\
  CFG_NAME " " CFG_VERSION "\n"\
  CFG_COPYRIGHT\
  CFG_DISCLAIMER "\n"\
  "Usage:\n"\
  "    " CFG_NAME " [OPTION]... DIR SPACE\n\n"\
  "    DIR     target directory\n"\
  "    SPACE   requested minimal free disk space (or maximal total file size\n"\
  "            with -t) in bytes (supports suffixes K/M/G/T/P/E for\n"\
  "            KiB/MiB/GiB/TiB/PiB/EiB)\n\n"\
  "Options:\n"\
  "    -b B    remove only files with names beginning with B\n"\
  "    -c      output build-in limits\n"\
  "    -d D    warn if execution time exceeds D seconds\n"\
  "    -e E    remove only files with names ending in E\n"\
  "    -h      output usage information\n"\
  "    -i      case-insensitive name matching with -b/-e/-r\n"\
  "    -m M    remove at most M files "\
  	"(default: " STR(CFG_FCNT_DFL) ", maximum: " STR(CFG_FCNT_MAX) ");\n"\
  "            not applied to empty files removed with -z\n"\
  "    -p      consider free space for privileged users\n"\
  "    -q      disable logging to stderr\n"\
  "    -r R    remove only files with names matching extended regex R\n"\
  "    -s F    log to syslog with facility F (implies -q)\n"\
  "    -t      remove files until their total size drops below SPACE\n"\
  "    -u      use actual disk usage (size of occupied blocks) as file size\n"\
  "    -v      increase log verbosity (use twice for debug output)\n"\
  "    -z[A]   remove also all empty files older than A seconds\n"\
  "            (default: " STR(CFG_EAGE_DFL) " seconds when A is omitted)\n\n"\
  "WARNING: this program IRREVERSIBLY TRUNCATES AND REMOVES the oldest files\n"\
  "under the target directory unless and until the free disk space (or total\n"\
  "file size) goal is met. Use with caution."

#define CFG_LMT_STR\
  "Built-in limits:\n"\
  "Maximal filesystem size: %juB\n"\
  "Maximal path length: %zuB\n"\
  "Maximal number of non-empty removed files: %zu\n"
#endif
