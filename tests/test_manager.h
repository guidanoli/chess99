#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

// Initialize test_manager
void test_manager_init();

// Tell the manager that a test has succeeded
void test_manager_test_succeeded();

// Tell the manager that a test has failed
void test_manager_test_failed();

// Tell the manager that a test has crashed
void test_manager_test_crashed();

// Print the results to stdout
void test_manager_print_results();

// Specify new scope
void test_manager_push_name(const char* name);

// Exit last pushed scope
void test_manager_pop_name();

// Tell the manager file and line
// After calling test_manager_test_succeeded or test_manager_test_failed,
// this information is not cleared.
void test_manager_tell_file_and_line(const char* file, int line);

// Auxiliary macro for asserting boolean statements
#define assert_helper(statement, file, line) do { \
	test_manager_tell_file_and_line(file, line); \
	int __val = statement; \
	if (__val > 0) \
		test_manager_test_succeeded(); \
	else if (__val < 0) \
		test_manager_test_crashed(); \
	else \
		test_manager_test_failed(); \
} while(0)

// Assert might be already defined from assert.h
#ifndef assert
#define assert(statement) \
	assert_helper(statement, __FILE__, __LINE__)
#endif

// Close test manager
void test_manager_close();

#endif
