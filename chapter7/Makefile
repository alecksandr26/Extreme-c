C = clang -pendamic -std=c11

BINS = test.out
OBJS = back.o

all: $(BINS)

back.o: back.c back.h
	$(C) -c $< -o $@

test.out: test.c $(OBJS)
	$(C) $(OBJS) $< -o $@
