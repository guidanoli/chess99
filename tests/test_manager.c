#include "test_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct stack
{
	struct stack* next;
	const void* info;
};

size_t succeeded = 0;
size_t failed = 0;
struct stack* name_stack = NULL;

size_t get_test_id()
{
	return succeeded + failed;
}

void print_test_name()
{
	printf("Test ");
	for (struct stack* name = name_stack; name != NULL; name = name->next)
		printf("%s:", (const char*) name->info);
	printf("#%zu", get_test_id());
}

void test_succeeded()
{
	++succeeded;
	print_test_name();
	printf(" succeeded\n");
}

void test_failed()
{
	++failed;
	print_test_name();
	printf(" failed\n");
}

void push_name(const char* name)
{
	struct stack* new_name = malloc(sizeof(struct stack));
	new_name->next = name_stack;
	new_name->info = name;
	name_stack = new_name;
}

void pop_name()
{
	struct stack* top = name_stack;
	name_stack = top->next;
	free(top);
}

void print_results()
{
	if (failed == 0)
		printf("All %zu tests passed\n", succeeded);
	else
		printf("%zu from %zu tests failed\n", failed, succeeded + failed);
}

void run_tests(void(**f_v)(void))
{
	for (;*f_v;++f_v)
		(*f_v)();
}
