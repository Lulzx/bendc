# bendc: a self-hosting Bend -> C compiler.
#
#   make            build build/bendc from the committed C seed (needs only a C compiler)
#   make test       run the test suite with build/bendc
#   make selfcheck  compile bendc.bend with build/bendc and check it reproduces the seed
#   make bootstrap  full bootstrap from the official `bend` (stage0 -> stage1 -> stage2)
#   make seed       regenerate seed/bendc.c from bendc.bend
#
# base.bend comes with the official Bend install; override with BEND_BASE=...

ifeq ($(origin CC),default)
CC = clang
endif
CFLAGS    ?= -O2 -w
BEND_BASE ?= $(HOME)/.bend/bend2/base.bend
export CC BEND_BASE

all: build/bendc build/bendrt.o

build/bendc: seed/bendc.c rt/bendrt.h
	@mkdir -p build
	$(CC) $(CFLAGS) -I rt seed/bendc.c -o $@ -lm -lpthread

# The runtime compiled once, for programs built with -DBEND_RT_SPLIT (bendc -o
# does that, and builds it too when it is missing).
build/bendrt.o: rt/bendrt_impl.c rt/bendrt_split.h
	@mkdir -p build
	$(CC) $(CFLAGS) -I rt -c rt/bendrt_impl.c -o $@

# rt/bendrt_split.h and rt/bendrt_impl.c come from rt/bendrt.h.
rt/bendrt_split.h rt/bendrt_impl.c: rt/bendrt.h tools/rtsplit.py
	python3 tools/rtsplit.py

test: build/bendc build/bendrt.o
	./run_tests.sh build/bendc

selfcheck: build/bendc
	BEND_NO_FREE=1 ./build/bendc --no-check $(BEND_BASE) bendc.bend > build/self.c
	cmp build/self.c seed/bendc.c && echo "selfcheck: bendc.bend compiles to the seed byte for byte"

bootstrap:
	./bootstrap.sh

seed: build/bendc
	./tools/reseed.sh

clean:
	rm -rf build

.PHONY: all test selfcheck bootstrap seed clean
