C = clang -pedantic -std=c11

OBJS = student.o person.o
BINS = test test1

all: $(BINS)

person.o: person.c person.h
	$(C) -c $< -o $@

student.o: student.c student.h person.o
	$(C) -c $< -o s.o
	ld -relocatable s.o person.o -o $@
	rm s.o

test1: test1.c student.h student.o
	$(C) $< student.o -o $@

test: test.c person.h person.o
	$(C) $< person.o -o $@

clean:
	rm $(OBJS) $(BINS)


