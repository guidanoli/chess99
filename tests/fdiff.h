#ifndef FDIFF_H
#define FDIFF_H

#include <stdio.h>

// Compare two files, and if they are identical,
// fdiff returns 0, otherwise, it returns 1
// The function does not take ownership of the file pointers
// The comparison ends on EOF
int fdiff(FILE* fp1, FILE* fp2);

#endif
