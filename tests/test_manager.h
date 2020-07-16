#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

// Tell the manager that a test succeeded
void test_succeeded();

// Tell the manager that a test failed
void test_failed();

// Print the results to stdout
void print_results();

// Specify new scope
void push_name(const char* name);

// Exit last pushed scope
void pop_name();

// Tell the manager file and line
// After calling test_succeeded or test_failed,
// this information is not cleared.
void tell_file_and_line(const char* file, int line);

// Auxiliary macro for asserting boolean statements
#define assert_helper(statement, file, line) do { \
	tell_file_and_line(file, line); \
	if (statement) \
		test_succeeded(); \
	else \
		test_failed(); \
} while(0)

// Assert might be already defined from assert.h
#ifndef assert
#define assert(statement) \
	assert_helper(statement, __FILE__, __LINE__)
#endif

// Run test array
// f_v must be an array of functions
// ending with NULL
void run_tests(void(**f_v)(void));

#endif
