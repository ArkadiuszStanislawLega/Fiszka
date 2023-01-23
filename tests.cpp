#include "tests.h"
#include <vector>

using std::vector;

void model_tag_test();
void model_question_test();

int main(){
	printf("Start testing.\n"); 
	model_tag_test();
	model_question_test();
	printf("Koniec testow.\n");
	return 0;
}

//SQLITE_OK = 0, every other values means error.
void model_tag_test(){
	Model *m = new Model();
	Tag *tag = new Tag(NULL, 1, "");

	printf("Tag model testing.\n"); 

	assert(tag->create() == 0);
	assert(tag->read() == 0);
	assert(tag->update() == 0);
	assert(tag->del() == 0);

	sqlite3 *db = m->get_database()->get_access();
	tag->set_db(db);
	tag->set_id(0);

	assert(tag->read() == 0);
	assert(tag->update() == 0);
	assert(tag->del() == 0);
	printf("Tag model tests complited successfull.\n");
}

void model_question_test(){
	Model *m = new Model();
	Question *q = new Question();
	Tag t = Tag(m->get_database()->get_access(), 1, "test");
	Tag t2 = Tag(m->get_database()->get_access(), 2, "test2");
	q->set_tags({t});

	printf("Question model testing.\n"); 
	assert(Question::create(NULL, q) == 0);
	assert(Question::read(NULL, 1) == 0);
	assert(Question::update(NULL, q) == 0);
	assert(Question::del(NULL, 1) == 0);


	sqlite3 *db = m->get_database()->get_access();
	assert(Question::create(db, NULL) == 0);
	assert(Question::read(db, 0) == 0);
	assert(Question::update(db, NULL) == 0);
	assert(Question::del(db, 0) == 0);

	assert(q->is_have_tag(&t));
	assert(!q->is_have_tag(&t2));

	printf("Tag model tests complited successfull.\n");
}
