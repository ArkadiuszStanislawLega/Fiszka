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
	printf("Tag model tests start...\n");

	assert(TagDb::create_table() == 0);
	printf("1. Create table.\n");

	Tag *t = new Tag(1, "TEST");
	assert(TagDb::create(t) == 0);
	printf("2. Create tag.\n");

	t = NULL;
	t = TagDb::read(1);
	assert(t != NULL);
	printf("3. Read Tag. \"%s\"\n", t->get_tag().c_str());

	t->set_tag("TEST2");
	assert(TagDb::update(t) == 0);
	printf("4. Update tag.\n");

	assert(TagDb::read_all_tags().size() > 0);
	printf("5. Read all tags.\n");

	assert(TagDb::remove(1) == 0);
	printf("6. Remove tag.\n");

	printf("Tag model tests end.\n");
}

void model_question_test(){
	printf("Question model tests start...\n");

	assert(QuestionDb::create_table() == 0);
	printf("1. Create table.\n");

	Question *q = new Question(1, "TEST", "TESTS", {});
	assert(QuestionDb::create(q) == 0);
	printf("2. Create question.\n");

	q = NULL;
	q = QuestionDb::read(1);
	assert(q != NULL);
	printf("3. Read Question.\n");

	q = new Question(1, "TEST1", "TEST2", {});
	assert(QuestionDb::update(q) == 0);
	printf("4. Update Question.\n");

	assert(QuestionDb::read_all_questions().size() > 0);
	printf("5. Read all questions.\n");

	printf("Question model test end.\n");
}
