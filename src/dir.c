/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright (c) 2025 Vic B <vic@4ever.vip> */

#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include "cfg.h"
#include "dir.h"
#include "fls.h"
#include "log.h"
#include "tps.h"

#define STRACT (noact) ? "not removing" : "removing"

/* scan directory for oldest files with specified name constraints
 * (beginning/ending/regex) and optionally also remove empty files) */
int dir_scn(const char *dir, size_t lnd,
	const char *bgn, const char *end, const char *reg,
	int noact, uint empty, size_t *cnte)
{
	DIR *d = NULL;
	struct dirent *de;
	size_t lnb, lne, lnf, lnp;	/* lenghts: bgn, end, file, path */
	char pn[CFG_PATH_MAX];		/* pathname */
	regex_t regp;
	struct stat st;
	time_t t = time(NULL);
	int r = -1;

	*cnte = 0;
	if (reg && regcomp(&regp, reg, REG_EXTENDED | REG_NOSUB)) {
		logerr("invalid regular expression %s", reg);
		return -1;
	}

	if ((lnd = strlen(dir)) >= CFG_PATH_MAX - 1) {
		logerr("directory name %s too long", dir);
		goto done;
	}

        if (!(d = opendir(dir))) {
                logerr("unable to open %s: %s", dir, STRERR);
                goto done;
        }

	memcpy(pn, dir, lnd);
	if (pn[lnd - 1] == '/')
		lnd--;
	else
		pn[lnd] = '/';

	if (bgn)
		lnb = strlen(bgn);
	if (end)
		lne = strlen(end);
	
	while ((de = readdir(d))) {
		if (de->d_type != DT_REG)
			continue;
		lnf = strlen(de->d_name);
		if (bgn && ((lnf < lnb) || strncmp(de->d_name, bgn, lnb))) {
			logdbg("ignoring %s (name start mismatch)",
				de->d_name);
			continue;
		}
		if (end && ((lnf < lne) ||
			strcmp(de->d_name + (lnf - lne), end))) {
			logdbg("ignoring %s (name end mismatch)",
				de->d_name);
			continue;
		}

		if (reg && regexec(&regp, de->d_name, 0, NULL, 0)) {
			logdbg("ignoring %s (regex mismatch)", de->d_name);
			continue;
		}

		lnp = lnd + lnf + 1;
		if (lnp >= CFG_PATH_MAX) {
			logerr("pathname %s/%s too long", dir, de->d_name);
			continue;
		}
		memcpy(pn + lnd + 1, de->d_name, lnf + 1);
		if (stat(pn, &st) < 0) {
			logerr("unable to stat %s: %s", pn, STRERR);
			continue;
		}

		logdbg("found %s (%lu.%09lu %juB)", pn,
			st.st_mtim.tv_sec, st.st_mtim.tv_nsec,
			(umax) st.st_size);

		if (empty && !st.st_size) {
			if ((t - st.st_mtim.tv_sec) < empty) {
				logdbg("ignoring %s (%lu.%09lu 0B)", pn,
					st.st_mtim.tv_sec, st.st_mtim.tv_nsec);
				continue;
			}
			logntc("%s %s (%lu.%09lu 0B)", STRACT, pn,
				st.st_mtim.tv_sec, st.st_mtim.tv_nsec);
			if(!noact) {
				if (unlink(pn) < 0)
					logerr("unable to remove %s: %s",
						pn, STRERR);
				else
					(*cnte)++;
			}
			continue;
		}
		if (fls_add(pn, lnp, st.st_size, st.st_mtim, st.st_nlink))
			goto done;
	}
	r = 0;
done:
	if (d)
		closedir(d);
	if (reg)
		regfree(&regp);
	return r;
}

/* get fs info (total/free/avail sizes) */
int dir_statfs(const char *dir, int prv, umax *t, umax *a)
{
	struct statvfs s;
	umax bsz;

	if (statvfs(dir, &s)) {
		logerr("unable to statvfs %s: %s", dir, STRERR);
		return -1;
	}

	bsz = (s.f_frsize) ? s.f_frsize : s.f_bsize;
	*t = bsz * s.f_blocks;
	*a = bsz * ((prv) ? s.f_bfree : s.f_bavail);
	return 0;
}

int dir_cln(const char *dir, size_t lnd, umax spc,
	const char *bgn, const char *end, const char *reg,
	size_t max, int noact, int prv, time_t empty,
	size_t *cnte, size_t *cntr)
{
	size_t cnts = 0;	/* # of spotted files */
	umax szt, sza, szr = 0; /* sizes: fs total, fs avail, removed */
	fls_ent *nxt;
	int r;

	*cnte = *cntr = 0;
	if (dir_statfs(dir, prv, &szt, &sza))
		return -1;
	loginf("%s: free=%juB required=%juB", dir, sza, spc);

	if (spc >= szt) {
		logerr("requested free space in %s is bigger than whole fs",
			dir);
		return -1;
	}
	if (spc <= sza)	/* nothing to do */
		return 0;

	r = -1;
	if (fls_init(max))
		return -1;
	if (dir_scn(dir, lnd, bgn, end, reg, noact, empty, cnte))
		goto done;
	while (fls) {
		cnts++;
		logntc("%s %s (%lu.%09lu %juB)", STRACT, fls->nm,
			fls->tm.tv_sec, fls->tm.tv_nsec, (umax) fls->sz);
		if(fls->hl > 1)
			logwrn("%s has %zu hardlinks",
				fls->nm, fls->hl);
		if (!noact) {
			if (truncate(fls->nm, 0) < 0)
				logerr("unable to truncate %s: %s",
					fls->nm, STRERR);
			if (unlink(fls->nm) < 0)
				logerr("unable to remove %s: %s",
					fls->nm, STRERR);
			else {
				(*cntr)++;
				szr += fls->sz;
			}
			if (dir_statfs(dir, prv, &szt, &sza))
				goto done;
			if (spc <=  sza)	/* freed enough */
				break;
		}
		nxt = fls->nxt;
		fls_ent_free(fls);
		fls = nxt;
	}
	loginf("%s: free=%juB, removed=%juB", dir, sza, szr);

	if (!cnts)	/* no files spotted */
		logerr("%s: not enough free space but no files to remove", dir);
	if (noact)
		logntc("no-action mode, files not removed");
	else if (cnts && (spc > sza)) {
		logerr("%s: not enough free space after file removal", dir);
		if (*cntr)
			r = 1;
		goto done;
	}
	r = 0;
done:
	fls_free();
	return r;
}
