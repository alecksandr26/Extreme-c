
# This is an example of Aggregation

C = clang -pedantic -Wall -std=c11
OBJS = gun.o bullet.o
BINS = test.out

all: $(BINS)

bullet.o: bullet.c bullet.h
	$(C) -c $< -o $@

gun.o: gun.c gun.h
	$(C) -c $< -o $@


test.out: test.c $(OBJS)
	$(C) $(OBJS) $< -o $@

clean:
	rm	$(OBJS) $(BINS)

test:
	./test.out



