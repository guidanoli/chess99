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

#endif
