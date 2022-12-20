# Makefile -- build script for the binomial distribution
# calculator.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Dec 16 19:58:18 EET 2022
# Copyright: (c) 2022 Luis Colorado.  All rights reserved.
# License: BSD

targets = bd
toclean = $(targets)

RM     ?= rm -f

bd_deps =
bd_objs = comb.o bin_dist.o input.o
bd_ldfl =
bd_libs = -lm
toclean += $(bd_objs)

all: $(targets)
clean:
	$(RM) $(toclean)

bd: $(bd_deps) $(bd_objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $($@_ldfl) $($@_objs) $($@_libs) $(LIBS)
