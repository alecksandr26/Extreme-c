C = clang -pedantic -std=c11

OBJS = animal.o cat.o
BINS = test test1

all: $(BINS)

animal.o: animal.c animal.h
	$(C) -c $< -o $@

test: test.c animal.o
	$(C) $< animal.o -o $@

# Here we do inheritance animal
cat.o: cat.c cat_p.h animal.o
	$(C) -c $< -o c.o
	ld -relocatable animal.o c.o -o $@
	rm c.o

test1: test1.c cat.h cat.o
	$(C) $< cat.o -o $@

clean: 
	rm $(OBJS) $(BINS)
