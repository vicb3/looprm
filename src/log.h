/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#ifndef _LOG_H
#define _LOG_H
#include <errno.h>
#include <string.h>

typedef enum {
	LOG_PRI_NONE = -1,
	LOG_PRI_EMG,
	LOG_PRI_ALR,
	LOG_PRI_CRT,
	LOG_PRI_ERR,
	LOG_PRI_WRN,
	LOG_PRI_NTC,
	LOG_PRI_INF,
	LOG_PRI_DBG
} log_pri;

#define LOG_PFX_EMG "emergency"
#define LOG_PFX_ALR "alert"
#define LOG_PFX_CRT "critical"
#define LOG_PFX_ERR "error"
#define LOG_PFX_WRN "warning"
#define LOG_PFX_NTC "notice"
#define LOG_PFX_INF "info"
#define LOG_PFX_DBG "debug"

#define LOG_SEP_PFX ": "

#define LOG_SL_PRI {\
	LOG_EMERG,\
	LOG_ALERT,\
	LOG_CRIT,\
	LOG_ERR,\
	LOG_WARNING,\
	LOG_NOTICE,\
	LOG_INFO,\
	LOG_DEBUG\
}

#define logemg(...) log_printf(LOG_PRI_EMG, LOG_PFX_EMG LOG_SEP_PFX __VA_ARGS__)
#define logalr(...) log_printf(LOG_PRI_ALR, LOG_PFX_ALR LOG_SEP_PFX __VA_ARGS__)
#define logcrt(...) log_printf(LOG_PRI_CRT, LOG_PFX_CRT LOG_SEP_PFX __VA_ARGS__)
#define logerr(...) log_printf(LOG_PRI_ERR, LOG_PFX_ERR LOG_SEP_PFX __VA_ARGS__)
#define logwrn(...) log_printf(LOG_PRI_WRN, LOG_PFX_WRN LOG_SEP_PFX __VA_ARGS__)
#define logntc(...) log_printf(LOG_PRI_NTC, LOG_PFX_NTC LOG_SEP_PFX __VA_ARGS__)
#define loginf(...) log_printf(LOG_PRI_INF, LOG_PFX_INF LOG_SEP_PFX __VA_ARGS__)
#define logdbg(...) log_printf(LOG_PRI_DBG, LOG_PFX_DBG LOG_SEP_PFX __VA_ARGS__)

#define STRERR strerror(errno)

#ifndef _LOG_C
extern log_pri log_level;
extern int log_stderr;
#endif

int log_sl_open(const char *fcl);
void log_sl_close(void);
void log_printf(log_pri pri, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
#endif
