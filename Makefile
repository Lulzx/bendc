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

all: build/bendc

build/bendc: seed/bendc.c rt/bendrt.h
	@mkdir -p build
	$(CC) $(CFLAGS) -I rt seed/bendc.c -o $@ -lm -lpthread

test: build/bendc
	./run_tests.sh build/bendc

selfcheck: build/bendc
	./build/bendc $(BEND_BASE) bendc.bend > build/self.c
	cmp build/self.c seed/bendc.c && echo "selfcheck: bendc.bend compiles to the seed byte for byte"

bootstrap:
	./bootstrap.sh

seed: build/bendc
	./build/bendc $(BEND_BASE) bendc.bend > build/seed1.c
	$(CC) $(CFLAGS) -I rt build/seed1.c -o build/seed1 -lm -lpthread
	./build/seed1 $(BEND_BASE) bendc.bend > build/seed2.c
	cmp build/seed1.c build/seed2.c
	cp build/seed2.c seed/bendc.c
	@echo "seed/bendc.c updated"

clean:
	rm -rf build

.PHONY: all test selfcheck bootstrap seed clean
