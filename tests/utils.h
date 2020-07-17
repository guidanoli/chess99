#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

typedef void (*utils_gt_func)(void*, FILE*);

// Concatenate two strings
// Returns the new string or 0 in case of bad malloc
char* utils_strcat(const char* s1, const char* s2);

// Compare two files
// The function does not take ownership of the file pointers
// Comparison ends when one of the two file pointers reach EOF
// Assumes both file pointers are valid
// If they are identical, returns a positive number
// If they are NOT identical, returns 0
// On error, returns a negative number.
int utils_file_diff(FILE* fp1, FILE* fp2);

// Run a groundtruth test
// The function f is called with:
// * the arbitrary argument 'arg'
// * a pointer to an empty temporary file pointer (FILE*)
// The function f does not own the pointer, i.e. should not close it.
// This file is then compared with the gt file using utils_file_diff.
// If they are identical, returns a positive number.
// If they are NOT identical, returns 0
// On error, returns a negative number.
int utils_gt(utils_gt_func f, void* arg, const char* gt);

// Overwrite groundtruth path prefix
// All gt files are concatenated with this preffix
void utils_set_gt_path(const char* path);

#endif
