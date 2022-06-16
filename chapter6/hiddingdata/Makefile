C = clang -pedantic -std=c11

OBJS = car.o
BINS = test.out

all: $(BINS)

car.o: car.c car.h
	$(C) -c $< -o $@

test.out: test.c car.h $(OBJS)
	$(C) $< $(OBJS) -o $@
