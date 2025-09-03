/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _HLP_H
#define _HLP_H
#include "cfg.h"
#include "log.h"
#include "str.h"

/* Help string */
#define HLP_STR\
  CFG_NAME " " CFG_VERSION "\n"\
  CFG_COPYRIGHT\
  CFG_DISCLAIMER "\n"\
  "Usage:\n"\
  "    " CFG_NAME " [OPTION]... DIR SPACE\n\n"\
  "    DIR     target directory\n"\
  "    SPACE   requested minimal free disk space "\
  	"(or maximal total size with -t)\n"\
  "            in bytes (supports suffixes K/M/G/T/P/E for "\
  	"KiB/MiB/GiB/TiB/PiB/EiB)\n\n"\
  "Options:\n"\
  "    -a A    minimal age of empty files for -z in seconds (default: "\
  	STR(CFG_EAGE_DFL) ")\n"\
  "    -b B    remove only files with names beginning with B\n"\
  "    -c      output build-in constraints\n"\
  "    -d D    warn if execution time exceeds D seconds\n"\
  "    -e E    remove only files with names ending in E\n"\
  "    -h      output usage information\n"\
  "    -i      case-insensitive name handling with -b/-e/-r and -n\n"\
  "    -l L    set log level to L (value " STR(LOG_PRI_ALR) "-"\
  	STR(LOG_PRI_DBG) " for levels\n"\
  "            " LOG_PFX_ALR "/" LOG_PFX_CRT "/" LOG_PFX_ERR "/" LOG_PFX_WRN\
  	"/" LOG_PFX_NTC "/" LOG_PFX_INF "/" LOG_PFX_DBG ")\n"\
  "    -m M    remove at most M files "\
  	"(default: " STR(CFG_FCNT_DFL) ", maximum: " STR(CFG_FCNT_MAX) ");\n"\
  "            not applied to empty files removed with -z\n"\
  "    -n      name-based file ordering\n"\
  "    -p      consider free space for privileged users\n"\
  "    -q      disable logging to stderr\n"\
  "    -r R    remove only files with names matching extended regex R\n"\
  "    -s F    log to syslog with facility F (implies -q)\n"\
  "    -t      remove files until their total size is equal to or less than "\
  	"SPACE\n"\
  "    -u      use actual disk usage (size of occupied blocks) as file size\n"\
  "    -v      increase log verbosity (use twice for debug output)\n"\
  "    -z      remove also all empty files older than A seconds (see -a)\n\n"\
  "WARNING: this program IRREVERSIBLY TRUNCATES AND REMOVES the oldest files\n"\
  "under the target directory unless and until the free disk space (or total\n"\
  "file size) goal is met. Use with caution."

#define LMT_STR\
  "Built-in limits:\n"\
  "Maximal filesystem size: %juB\n"\
  "Maximal path length: %zuB\n"\
  "Maximal number of non-empty removed files: %zu\n"
#endif
