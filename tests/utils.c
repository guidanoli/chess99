#include "utils.h"

#include <stdlib.h>
#include <string.h>

static const char* gtpath;

int utils_file_diff(FILE* fp1, FILE* fp2)
{
	char ch1, ch2;

	do {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	} while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2));

	return ch1 == ch2;
}

char* utils_strcat(const char* s1, const char* s2)
{
	char* s = malloc(strlen(s1) + strlen(s2) + 1);
	if (!s)
		return NULL;
	s[0] = '\0';
	strcpy(s, s1);
	strcat(s, s2);
	return s;
}

int utils_gt(utils_gt_func f, void* arg, const char* filepath)
{
	int ret = -1;
	char* fp1path = utils_strcat(gtpath, filepath);
	if (!fp1path)
		goto fail1;
	FILE* fp1 = fopen(fp1path, "r");
	if (!fp1)
		goto fail2;
	FILE* fp2 = fopen("temp", "w+");
	if (!fp2)
		goto fail3;
	f(arg, fp2);
	rewind(fp2);
	ret = utils_file_diff(fp1, fp2);
	fclose(fp2);
fail3:
	fclose(fp1);
fail2:
	free(fp1path);
fail1:
	return ret;
}

void utils_set_gt_path(const char* path)
{
	gtpath = path;
}
