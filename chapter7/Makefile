C = clang -pedantic -std=c11 -Wall

EN = ld -relocatable

BINS = test.out
OBJS = back.o

all: $(BINS)


item.o: item.c item.h
	$(C) -c $< -o $@

# Encampsulate
back.o: back.c item.o back.h
	$(C) -c $< -o obj.o
	$(EN) obj.o item.o -o $@
	rm obj.o

test.out: test.c $(OBJS)
	$(C) $(OBJS) $< -o $@

clean:
	rm $(OBJS) $(BINS)

# Run the test
test:
	./test.out
