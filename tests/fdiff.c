#include "fdiff.h"

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif

#ifndef ROOT
#define ROOT "."
#endif

static const char* groundtruth_path = ROOT SEP "tests" SEP "groundtruths" SEP;

int fdiff(FILE* fp1, FILE* fp2)
{
	char ch1 = getc(fp1);
	char ch2 = getc(fp2);

	while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}

	return ch1 == ch2;
}

static char* string_concat(const char* s1, const char* s2)
{
	char* s = malloc(strlen(s1) + strlen(s2) + 1);
	if (!s)
		return NULL;
	s[0] = '\0';
	strcpy(s, s1);
	strcat(s, s2);
	return s;
}

int gtdiff(gt_func f, void* arg, const char* filepath)
{
	int ret = -1;
	char* fp2path = string_concat(groundtruth_path, filepath);
	if (!fp2path)
		goto fail1;
	FILE* fp1 = fopen("temp", "w+");
	if (!fp1)
		goto fail2;
	FILE* fp2 = fopen(fp2path, "r");
	if (!fp2)
		goto fail3;
	f(arg, fp1);
	rewind(fp1);
	ret = fdiff(fp1, fp2);
	fclose(fp2);
fail3:
	fclose(fp1);
fail2:
	free(fp2path);
fail1:
	return ret;
}

void set_gtpath(const char* path)
{
	groundtruth_path = path;
}
