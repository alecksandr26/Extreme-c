C = clang -pedantic -std=c11 -ggdb

OBJS = animal.o cat.o duck.o
BINS = test.out test1.out

all: $(BINS)

# The base class
animal.o: animal.c animal_p.h
	$(C) -c $< -o $@

test.out: test.c animal.o
	$(C) $< animal.o -o $@

# The polymorphic class
cat.o: cat.c cat_p.h 
	$(C) -c $< -o $@

# The polymorphic class
duck.o: duck.c duck_p.h 
	$(C) -c $< -o $@

module.o: duck.o cat.o animal.o
	ld -relocatable duck.o cat.o animal.o -o $@

test1.out: test1.c cat.h  duck.h module.o
	$(C) $< module.o -o $@


clean:
	rm $(OBJS) $(BINS)
