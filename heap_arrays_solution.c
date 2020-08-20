#include <stddef.h> // for size_t
#include "testing.h"

// A simple fixed size array
typedef struct {
	void **array; // array can hold pointers to "any" type
	size_t capacity; // number of slots in the array
} FixedSizeArray;

// typedef A B;
// means B refers to the type A;
//
// typedef struct {} Name;
// means Name refers to the type struct {};
//
// this is exactly opposite to #define B A, where B is defined as A

FixedSizeArray new_fixed(size_t capacity) {
	FixedSizeArray retval;
	// TODO


	retval.array = malloc(capacity * sizeof (void*));
	retval.capacity = capacity;

	return retval;
}

void free_fixed(FixedSizeArray *array) {
	// TODO
}

/**
 * Returns:  0 if successful
 *          -1 if index is out-of-range
 */
int set_fixed(FixedSizeArray *array, size_t idx, void *elem) {
	// TODO
	array->array[idx] = elem;
}

/**
 * Returns: the pointer at the provided index
 *          or NULL if the index is out-of-range
 */
void *get_fixed(FixedSizeArray *array, size_t idx) {
	// TODO
	return array->array[idx];
	return NULL;
}

void test_fixed() {
	FixedSizeArray arr = new_fixed(3);
	set_fixed(&arr, 0, (void*)1337);
	set_fixed(&arr, 1, (void*)1);
	set_fixed(&arr, 2, (void*)2);

	CHECK_EQ_INT(get_fixed(&arr, 0), (void*)1337);
	CHECK_EQ_INT(get_fixed(&arr, 1), (void*)1);
	CHECK_EQ_INT(get_fixed(&arr, 2), (void*)2);
	CHECK_EQ_INT(get_fixed(&arr, 1000), NULL);

	free_fixed(&arr);
}

///////////////////
// Growing Array //
///////////////////

typedef struct {
	void **array; // array can hold pointer to "any" type
	size_t capacity; // number of slots in the array
	size_t length; // number of occupied slots
} SimpleGrowingArray;

SimpleGrowingArray new_simple_growing(size_t capacity) {
	SimpleGrowingArray retval;

	// TODO
	retval.array = malloc(sizeof (void*) * capacity);
	retval.capacity = capacity;
	retval.length = 0;

	return retval;
}

void free_simple_growing(SimpleGrowingArray *array) {
	// TODO
}

/**
 * Adds an element at the end of the array.
 *
 * Returns:  0 if successful
 *          -1 if no space left
 */
int push_simple_growing(SimpleGrowingArray *array, void *elem) {
	// TODO
	if (array->length == array->capacity) {
	return -1;
	}
	array->array[array->length] = elem;
	++array->length;
	return 0;
}

/**
 * Returns: the pointer at the provided index
 *          or NULL if the index is out-of-range
 */
void *get_simple_growing(SimpleGrowingArray *array, size_t idx) {
	// TODO
	if (idx >= array->length) {
	return NULL;
	}
	return array->array[idx];
}

void test_simple_growing() {
	SimpleGrowingArray arr = new_simple_growing(3);
	CHECK_EQ_INT(arr.length, 0);
	CHECK_EQ_INT(arr.capacity, 3);

	CHECK_EQ_INT(push_simple_growing(&arr, (void*)1337), 0);
	CHECK_EQ_INT(arr.length, 1);
	CHECK_EQ_INT(get_simple_growing(&arr, 0), (void*)1337);

	CHECK_EQ_INT(push_simple_growing(&arr, (void*)1), 0);
	CHECK_EQ_INT(arr.length, 2);
	CHECK_EQ_INT(get_simple_growing(&arr, 1), (void*)1);

	CHECK_EQ_INT(push_simple_growing(&arr, (void*)2), 0);
	CHECK_EQ_INT(arr.length, 3);
	CHECK_EQ_INT(get_simple_growing(&arr, 2), (void*)2);

	CHECK_EQ_INT(push_simple_growing(&arr, (void*)3), -1);
	free_simple_growing(&arr);
}

////////////////////////
// Reallocating Array //
////////////////////////

typedef struct {
	void **array; // array can hold pointer to "any" type
	size_t capacity; // number of slots in the array
	size_t length; // number of occupied slots
} ReallocatingArray;

ReallocatingArray new_reallocating(size_t capacity) {
	SimpleGrowingArray arr = new_simple_growing(capacity);
	ReallocatingArray rv;
	rv.array = arr.array;
	rv.capacity = arr.capacity;
	rv.length = arr.length;
	return rv;
}

void free_reallocating(ReallocatingArray *array) {
	// Yikes :-)
	free_simple_growing((SimpleGrowingArray*) array);
}

/**
 * Adds an element at the end of the array.
 */
void push_reallocating(ReallocatingArray *array, void *elem) {
	// TODO

	if (array->length == array->capacity) {
		array->array = realloc(array->array, array->length * 2 * sizeof(void*));
	}

	array->array[array->length] = elem;
	++array->length;

}

/**
 * Returns: the pointer at the provided index
 *          or NULL if the index is out-of-range
 */
void *get_reallocating(ReallocatingArray *array, size_t idx) {
	// Yikes :-)
	return get_simple_growing((SimpleGrowingArray*) array, idx);
}

void test_reallocating() {
	ReallocatingArray arr = new_reallocating(3);

	for (size_t i = 0; i < 100; ++i) {
		push_reallocating(&arr, (void*)1337+i);
		CHECK_EQ_INT(get_reallocating(&arr, i), (void*)1337+i);
	}

	free_reallocating(&arr);
}

void main(int argc, char **argv) {
	if (argc > 1) {
		CONTINUE_AFTER_FAIL = 1;
	}
	test_fixed();
	test_simple_growing();
	test_reallocating();
}
