#include "fdiff.h"

int fdiff(FILE* fp1, FILE* fp2) {
	char ch1 = getc(fp1);
	char ch2 = getc(fp2);

	while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}

	return ch1 != ch2;
}
