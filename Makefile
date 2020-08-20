all: heap_arrays
	@echo running...
	@./$<
	
heap_arrays: heap_arrays.c testing.h testing.c
	gcc $^ -o $@

clean:
	rm heap_arrays
