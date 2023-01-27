#include "tests.h"
#include <cassert>
#include <vector>

void database_tests();

int main(){
	printf("Start testing.\n"); 
	database_tests();
	printf("Koniec testow.\n");
	return 0;
}

//SQLITE_OK = 0, every other values means error.
void database_tests(){
	printf("Database tests start...\n");

	printf("Create table tags.\t");
	assert(TagDb::create_table() == 0);
	printf("OK\n");

	printf("Create tag.\t\t");
	Tag *t = new Tag(1, "TEST");
	assert(TagDb::create(t) == 0);
	printf("OK\n");

	printf("Read Tag. \"%s\"\t", t->get_tag().c_str());
	t = NULL;
	t = TagDb::read(1);
	assert(t != NULL);
	printf("OK\n");

	printf("Update tag.\t\t");
	t->set_tag("TEST2");
	assert(TagDb::update(t) == SQLITE_OK);
	printf("OK\n");

	printf("Read all tags.\t\t");
	assert(TagDb::read_all_tags().size() > 0);
	printf("OK\n");

	printf("Create table questions.\t");
	assert(QuestionDb::create_table() == SQLITE_OK);
	printf("OK\n");

	printf("Create question.\t");
	Question *q = new Question(1, "TEST", "TESTS", {});
	assert(QuestionDb::create(q) == SQLITE_OK);
	printf("OK\n");

	printf("Read Question.\t\t");
	q = NULL;
	q = QuestionDb::read(1);
	assert(q != NULL);
	assert(q->get_id() == 1);
	printf("OK\n");

	printf("Update Question.\t");
	q = new Question(1, "TEST1", "TEST2", {});
	assert(QuestionDb::update(q) == SQLITE_OK);
	printf("OK\n");

	printf("Create table questions tags.\t");
	assert(Database::create_table_questions_tags() == SQLITE_OK);
	printf("OK\n");

	printf("Added relation questions and tag.\t");
	assert(Database::create_relation(t, q) == SQLITE_OK);
	printf("OK\n");

	printf("Read related tags.\t");
	assert(QuestionDb::read_related_tags(q) == SQLITE_OK);
	assert(q->get_tags().size() == 1);
	printf("OK\n");
	
	printf("Read all questions.\t");
	assert(QuestionDb::read_all_questions().size() > 0);
	printf("OK\n");

	printf("Remove tag from question.\t");
	assert(QuestionDb::remove_tag(q, t) == SQLITE_OK);
	q->get_tags().clear();
	QuestionDb::read_related_tags(q);
	assert(q->get_tags().size() == 0);
	printf("OK\n");

	printf("Remove tag.\t\t");
	assert(TagDb::remove(1) == SQLITE_OK);
	printf("OK\n");

	printf("Remove question.\t");
	assert(QuestionDb::remove(1) == SQLITE_OK);
	printf("OK\n");

	printf("Database tests end.\n");
}
