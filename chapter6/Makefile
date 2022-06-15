C = clang -pedantic -std=c11

OBJS = car.o
BINS = test

all: $(BINS)

car.o: car.c car.h
	$(C) -c $< -o $@

test: test.c car.h $(OBJS)
	$(C) $< $(OBJS) -o $@
