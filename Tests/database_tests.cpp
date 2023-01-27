#include "database_tests.h"

void DatabaseTests::create_tag_table(){
	printf("Create table tags.\t");
	assert(TagDb::create_table() == 0);
	printf("OK\n");
}

void DatabaseTests::create_tag(){
	printf("Create tag.\t\t");
	Tag *t = new Tag(1, "TEST");
	//*DatabaseTest::t = new Tag(1, "TEST");
	assert(TagDb::create(t) == 0);
	printf("OK\n");
}

void DatabaseTests::read_tag(){
	printf("Read Tag.\t\t");
	Tag *t = TagDb::read(1);
	assert(t->get_id() == 1);
	printf("OK\n");
}

void DatabaseTests::set_tag(){
	printf("Update tag.\t\t");
	Tag *t = TagDb::read(1);
	t->set_tag("TEST2");
	assert(TagDb::update(t) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::read_all_tags(){
	printf("Read all tags.\t\t");
	assert(TagDb::read_all_tags().size() > 0);
	printf("OK\n");
}

void DatabaseTests::create_table_questions(){
	printf("Create table questions.\t");
	assert(QuestionDb::create_table() == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::create_question(){
	printf("Create question.\t");
	Question *q = new Question(1, "TEST", "TESTS", {});
	assert(QuestionDb::create(q) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::read_question(){
	printf("Read Question.\t\t");
	Question *q = QuestionDb::read(1);
	assert(q->get_id() == 1);
	printf("OK\n");
}

void DatabaseTests::update_question(){
	printf("Update Question.\t");
	Question *q = new Question(1, "TEST1", "TEST2", {});
	assert(QuestionDb::update(q) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::create_table_questions_tags(){
	printf("Create table questions tags.\t");
	assert(Database::create_table_questions_tags() == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::add_realation_question_and_tags(){
	printf("Added relation questions and tag.\t");
	Tag *t = new Tag(1, "");
	Question *q = new Question(1, "", "", {});
	assert(Database::create_relation(t, q) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::read_related_tags(){
	printf("Read related tags.\t");
	Question *q = new Question(1, "", "", {});
	assert(QuestionDb::read_related_tags(q) == SQLITE_OK);
	assert(q->get_tags().size() == 1);
	printf("OK\n");
}

void DatabaseTests::read_all_questions(){
	printf("Read all questions.\t");
	assert(QuestionDb::read_all_questions().size() > 0);
	printf("OK\n");
}

void DatabaseTests::remove_tag_from_question(){
	printf("Remove tag from question.\t");
	Question *q = new Question(1, "", "", {});
	Tag *t = new Tag(1, "");
	assert(QuestionDb::remove_tag(q, t) == SQLITE_OK);
	q->get_tags().clear();
	QuestionDb::read_related_tags(q);
	assert(q->get_tags().size() == 0);
	printf("OK\n");
}

void DatabaseTests::remove_tag(){
	printf("Remove tag.\t\t");
	assert(TagDb::remove(1) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::remove_question(){
	printf("Remove question.\t");
	assert(QuestionDb::remove(1) == SQLITE_OK);
	printf("OK\n");
}

void DatabaseTests::database_tests(){
	printf("Database tests start...\n");

	create_tag_table();
	create_tag();
	read_tag();
	set_tag();
	read_all_tags();
	create_table_questions();
	create_question();
	read_question();
	update_question();
	create_table_questions_tags();
	add_realation_question_and_tags();
	read_related_tags();
	read_all_questions();
	remove_tag_from_question();
	remove_tag();
	remove_question();

	printf("Database tests end.\n");
}
