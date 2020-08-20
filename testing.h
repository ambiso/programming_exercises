#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32;1m" 
#define RED "\033[31;1m"
#define RESET "\033[0m"
#define YES GREEN "✔" RESET
#define NO RED "✘" RESET

extern int CONTINUE_AFTER_FAIL;

#define CHECK_EQ(A, B, FMT) do { \
  typeof (A) _a = A; \
  typeof (B) _b = B; \
  if (_a == _b) { \
    puts(YES); \
  } else { \
    printf(NO " " #A " (=" FMT ") != " #B " (=" FMT ") \n", _a, _b); \
    if (!CONTINUE_AFTER_FAIL) { exit(1); } \
  } \
} while(0)

#define CHECK_EQ_INT(A, B) CHECK_EQ(A, B, "%d")
#define CHECK_EQ_LD(A, B) CHECK_EQ(A, B, "%ld")
#define CHECK_EQ_PTR(A, B) CHECK_EQ(A, B, "%p")
#define CHECK_EQ_SIZE(A, B) CHECK_EQ(A, B, "%zu")
