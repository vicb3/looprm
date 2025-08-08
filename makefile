# SPDX-License-Identifier: GPL-3.0-only
# Copyright (c) 2025 Vic B <vic@4ever.vip>

SRCDIR = src
DESTDIR = $(abspath $(DESTDIR))
VERSION ?= $(shell sed -e 's/.*(\(.*\)).*/\1/;q' < debian/changelog)

.PHONY: $(SRCDIR) clean install

$(SRCDIR):
	$(MAKE) -C$(SRCDIR) VERSION=$(VERSION)

clean:
	$(MAKE) -C$(SRCDIR) clean

install: $(SRCDIR)
	$(MAKE) -C$(SRCDIR) install DESTDIR=$(DESTDIR)
