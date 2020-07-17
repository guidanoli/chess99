#ifndef FDIFF_H
#define FDIFF_H

#include <stdio.h>

// Compare two files, and if they are identical,
// fdiff returns a positive number, otherwise, it returns 0.
// The function does not take ownership of the file pointers
// The comparison ends on EOF
int fdiff(FILE* fp1, FILE* fp2);

typedef void (*gt_func)(void*, FILE*);

// Compare a function with a groudtruth
// The function calls f with a temporary file pointer (don't close it!)
// and the optional argument 'arg', that can be anything really...
// and opens another file pointer with the file whose path is filepath
// Then, compares both contents using fdiff.
// On error, returns a negative number.
int gtdiff(gt_func f, void* arg, const char* filepath);

// Overwrite default groundtruth path,
// which is ROOT/tests/groundtruts
void set_gtpath(const char* path);

#endif
