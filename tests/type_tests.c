#include "tests.h"
#include "test_manager.h"
#include "types.h"

void run_type_tests()
{
	push_name("TypeTests");

	assert(getSquareRank(SQ_A1) == RK_1);	
	assert(getSquareRank(SQ_H1) == RK_1);	
	assert(getSquareRank(SQ_A8) == RK_8);	
	assert(getSquareRank(SQ_H8) == RK_8);	

	assert(getSquareFile(SQ_A1) == FL_A);	
	assert(getSquareFile(SQ_H1) == FL_H);	
	assert(getSquareFile(SQ_A8) == FL_A);	
	assert(getSquareFile(SQ_H8) == FL_H);	

	pop_name();
}
