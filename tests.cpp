#include "tests.h"
#include <vector>

using std::vector;

void model_tag_test();
void model_question_test();
void model_database_test();

int main(){
	printf("Start testing.\n"); 
	model_database_test();
	model_tag_test();
	model_question_test();
	printf("Koniec testow.\n");
	return 0;
}

void model_database_test(){
	assert(Database::create_table_questions_tags()==0);
}

//SQLITE_OK = 0, every other values means error.
void model_tag_test(){
	assert(TagDb::create_table() == 0);

}

void model_question_test(){
	assert(QuestionDb::create_table() == 0);

}
