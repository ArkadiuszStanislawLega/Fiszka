#include "tests.h"
#include "database_tests.cpp"
#include <cassert>
#include <vector>

int main(){
	printf("Start testing.\n"); 
	DatabaseTest::database_tests();
	printf("Koniec testow.\n");
	return 0;
}
