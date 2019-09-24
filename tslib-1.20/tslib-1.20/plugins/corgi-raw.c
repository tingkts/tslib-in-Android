/*
 * Copyright (C) 2004 Douglas Lowder
 *
 * SPDX-License-Identifier: LGPL-2.1
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "tslib-private.h"

struct corgi_ts_event { /* Used in the Sharp Zaurus SL-C700 */
	short pressure;
	short x;
	short y;
	short millisecs;
};

static int corgi_read(struct tslib_module_info *inf, struct ts_sample *samp, int nr)
{
	struct tsdev *ts = inf->dev;
	struct corgi_ts_event *corgi_evt;
	int ret;
	int nr_read;

	corgi_evt = alloca(sizeof(*corgi_evt) * nr);
	ret = read(ts->fd, corgi_evt, sizeof(*corgi_evt) * nr);
	if (ret > 0) {
		nr_read  = ret / sizeof(*corgi_evt);
		while (ret >= (int)sizeof(*corgi_evt)) {
			samp->x = corgi_evt->x;
			samp->y = corgi_evt->y;
			samp->pressure = corgi_evt->pressure;
#ifdef DEBUG
	fprintf(stderr, "RAW---------------------------> %d %d %d\n",
		samp->x, samp->y, samp->pressure);
#endif /*DEBUG*/
			samp->tv.tv_usec = (corgi_evt->millisecs % 1000) * 1000;
			samp->tv.tv_sec = corgi_evt->millisecs / 1000;
			samp++;
			corgi_evt++;
			ret -= sizeof(*corgi_evt);
		}
	} else {
		return -1;
	}
	ret = nr_read;
	return ret;
}

static const struct tslib_ops corgi_ops = {
	.read	= corgi_read,
};

TSAPI struct tslib_module_info *corgi_mod_init(__attribute__ ((unused)) struct tsdev *dev,
					       __attribute__ ((unused)) const char *params)
{
	struct tslib_module_info *m;

	m = malloc(sizeof(struct tslib_module_info));
	if (m == NULL)
		return NULL;

	m->ops = &corgi_ops;
	return m;
}

#ifndef TSLIB_STATIC_CORGI_MODULE
	TSLIB_MODULE_INIT(corgi_mod_init);
#endif
