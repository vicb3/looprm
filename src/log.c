/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#define _LOG_C
#include "cfg.h"
#include "log.h"

int log_level = LOG_PRI_NTC;
uint log_stderr = 1;
uint log_sl = 0;

int log_sl_pri[] = LOG_SL_PRI;

struct {
	char *name;
	int fcl;
} log_sl_fcls[] = {
	{"auth", LOG_AUTH},
	{"authpriv", LOG_AUTHPRIV},
	{"cron", LOG_CRON},
	{"daemon", LOG_DAEMON},
	{"ftp", LOG_FTP},
	{"local0", LOG_LOCAL0},
	{"local1", LOG_LOCAL1},
	{"local2", LOG_LOCAL2},
	{"local3", LOG_LOCAL3},
	{"local4", LOG_LOCAL4},
	{"local5", LOG_LOCAL5},
	{"local6", LOG_LOCAL6},
	{"local7", LOG_LOCAL7},
	{"lpr", LOG_LPR},
	{"mail", LOG_MAIL},
	{"news", LOG_NEWS},
	{"syslog", LOG_SYSLOG},
	{"user", LOG_USER},
	{"uucp", LOG_UUCP},
	{NULL, 0}
};

int log_sl_open(const char *fcl)
{
	size_t i = 0;

	while (log_sl_fcls[i].name) {
		if (!strcmp(fcl, log_sl_fcls[i].name)) {
			openlog(CFG_NAME, LOG_PID, log_sl_fcls[i].fcl);
			log_sl = 1;
			return 0;
		}
		i++;
	}
	/* facility not found */
	return -1;
}

void log_sl_close(void)
{
	if (log_sl) {
		closelog();
		log_sl = 0;
	}
}

void log_printf(int pri, const char *fmt, ...)
{
	va_list args;

	if (pri > log_level)
		return;

	if (log_stderr) {
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		fputc('\n', stderr);
		va_end(args);
	}
	if (log_sl) {
		va_start(args, fmt);
		vsyslog(log_sl_pri[pri], fmt, args);
		va_end(args);
	}
}
