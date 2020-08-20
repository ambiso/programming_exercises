all: heap_arrays
	@echo running...
	@./$<
	
heap_arrays: heap_arrays.c testing.h testing.c
	gcc -Wall -o $@ $^

clean:
	rm heap_arrays
