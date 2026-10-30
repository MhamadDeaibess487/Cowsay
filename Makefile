CC ?= cc
CPPFLAGS ?=
CFLAGS ?= -O2 -g
WARNINGS = -std=c11 -Wall -Wextra -Wpedantic -Wformat=2 -Wstrict-prototypes
CPPFLAGS += -D_DEFAULT_SOURCE
PROGRAMS = newcow reading_cow wild_cow tamagoshi_cow

.PHONY: all clean test
all: $(PROGRAMS)

newcow: newcow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< $(LDFLAGS) $(LDLIBS) -o $@
reading_cow: reading_cow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< $(LDFLAGS) $(LDLIBS) -o $@
wild_cow: wild_cow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< $(LDFLAGS) $(LDLIBS) -o $@
tamagoshi_cow: tamagoshi\ cow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) "$<" $(LDFLAGS) $(LDLIBS) -o $@

tests/fail_alloc: tests/fail_alloc.c reading_cow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< $(LDFLAGS) $(LDLIBS) -o $@

tests/fast_tamagoshi: tests/fast_tamagoshi.c tamagoshi\ cow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< $(LDFLAGS) $(LDLIBS) -o $@

test: all tests/fail_alloc tests/fast_tamagoshi
	bash tests/test.sh

clean:
	$(RM) $(PROGRAMS) tests/fail_alloc tests/fast_tamagoshi
