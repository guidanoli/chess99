#include "test_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

struct stack
{
	struct stack* next;
	const void* info;
};

static size_t succeeded;
static size_t failed;
static size_t crashed;
static struct stack* name_stack;
static int line;
static const char* file;

static int test_manager_printf(const char* format, ...)
{
	va_list va;
	va_start(va, format);
	printf("[TEST] ");
	int ret = vprintf(format, va);
	printf("\n");
	va_end(va);
	return ret;
}

void test_manager_init()
{
	succeeded = 0;
	failed = 0;
	crashed = 0;
	name_stack = NULL;
	line = 0;
	file = NULL;
	test_manager_printf("Test Manager initialized");
}

static size_t get_test_id()
{
	return succeeded + failed + crashed;
}

static void print_test_name()
{
	for (struct stack* name = name_stack; name != NULL; name = name->next)
		printf("%s:", (const char*) name->info);
	printf("#%zu", get_test_id());
}

static void print_test_location()
{
	if (file && line)
		test_manager_printf("See %s:%d", file, line);
}

static void clear_test_location()
{
	file = NULL;
	line = 0;
}

void test_manager_test_succeeded()
{
	++succeeded;
	printf("[TEST] ");
	print_test_name();
	printf(" --- OK\n");
	clear_test_location();
}

void test_manager_test_failed()
{
	++failed;
	printf("[TEST] ");
	print_test_name();
	printf(" --- FAILED\n");
	print_test_location();
	clear_test_location();
}

void test_manager_test_crashed()
{
	++crashed;
	printf("[TEST] ");
	print_test_name();
	printf(" --- CRASHED\n");
	print_test_location();
	clear_test_location();
}

void test_manager_push_name(const char* name)
{
	struct stack* new_name = malloc(sizeof(struct stack));
	new_name->next = name_stack;
	new_name->info = name;
	name_stack = new_name;
}

void test_manager_pop_name()
{
	struct stack* top = name_stack;
	name_stack = top->next;
	free(top);
}

void test_manager_print_results()
{
	if (failed == 0 && crashed == 0) {
		if (succeeded != 0)
			test_manager_printf("All %zu tests passed", succeeded);
	} else {
		test_manager_printf("%zu test run", succeeded + failed + crashed);
		if (succeeded != 0)
			test_manager_printf("%zu tests succeeded", succeeded);
		if (failed != 0)
			test_manager_printf("%zu tests failed [!]", failed);
		if (crashed != 0)
			test_manager_printf("%zu tests crashed [!!]", crashed);
	}
}

void test_manager_tell_file_and_line(const char* _file, int _line)
{
	file = _file;
	line = _line;
}

void test_manager_close()
{
	while (name_stack)
		test_manager_pop_name();
	test_manager_printf("Test Manager closed");
}