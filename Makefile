CC = gcc
CPP = cpp
CFLAGS = -Wall -Wextra -pedantic --std=gnu99 -g
LDFLAGS = -lm -lrt

#CC = clang
#CFLAGS += -g -O0 -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined
#LDFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined

#CFLAGS += -g -O0 -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=thread
#LDFLAGS += -fsanitize=undefined -fsanitize=thread

OUTS = watsh tests
OBJS_watsh = main.o alias.o
OBJS_tests = tests.o alias.o
OBJS = $(OBJS_watsh) $(OBJS_tests)

DEPS = $(OBJS:.o=.d)

.PHONY: all clean format run-tests

all: watsh

-include $(DEPS)

watsh: $(OBJS_watsh)
	$(CC) $^ -o $@ $(LDFLAGS)

tests: $(OBJS_tests)
	$(CC) $^ -o $@ $(LDFLAGS)

%.d: %.c
	$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

clean:
	rm -f $(OBJS) $(OUTS) $(DEPS)

format:
	clang-format -i *.c *.h

run-tests: tests
	./tests
