C = clang -pedantic -std=c11 -ggdb

OBJS = animal.o cat.o
BINS = test.out test1.out

all: $(BINS)

# The base class
animal.o: animal.c animal.h
	$(C) -c $< -o $@

test.out: test.c animal.o
	$(C) $< animal.o -o $@

# The polymorphic class
cat.o: cat.c cat.h animal.o animal.h
	$(C) -c $< -o c.o
	ld -relocatable c.o animal.o -o $@
	rm c.o

test1.out: test1.c cat.o
	$(C) $< cat.o -o $@


clean:
	rm $(OBJS) $(BINS)
