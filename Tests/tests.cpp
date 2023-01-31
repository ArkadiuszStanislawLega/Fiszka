#include "tests.h"

int main(){
	printf("Start testing.\n"); 
	DatabaseTests::database_tests();
	ModelTests::model_tests();
	printf("Koniec testow.\n");
	return 0;
}
