# SPDX-License-Identifier: GPL-3.0-only
# Copyright (c) 2025 Vic B <vic@4ever.vip>

NAME = looprm
# VERSION comes from toplevel makefile (which reads it from packaging info
# to avoid multiple definitions). This provides a placeholder value when
# building in subdir.
VERSION = TEST.BUILD

CDEFS = -DNAME=\"$(NAME)\" -DVERSION=\"$(VERSION)\"
CFLAGS ?= -g -O2 -Wall -Wextra -Werror -pedantic
CPPFLAGS += $(CDEFS)

INSTALL ?= install
PREFIX ?= /usr

HDR := $(wildcard *.h)
SRC := $(wildcard *.c)
OBJ := $(SRC:c=o)

.PHONY: clean install

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(NAME) $(OBJ) makefile.dep

install:
	$(INSTALL) -s -m755 -D -t$(DESTDIR)$(PREFIX)/bin/ $(NAME)

makefile.dep: $(SRC) $(HDR)
	$(CC) -MM $(CDEFS) $(SRC) > $@

include makefile.dep
