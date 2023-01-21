#include "tests.h"

void model_tag_test();

int main(){
	printf("Start testing.\n"); 
	model_tag_test();
	printf("Koniec testow.");
	return 0;
}

void model_tag_test(){
	Model *m = new Model();
	Tag *tag = new Tag();

	printf("Tag model testing.\n"); 
	assert(Tag::create(NULL, tag) == 0);
	assert(Tag::read(NULL, 1) == 0);
	assert(Tag::update(NULL, tag) == 0);
	assert(Tag::del(NULL, 1) == 0);

	sqlite3 *db = m->get_database()->get_access();
	assert(Tag::create(db, NULL) == 0);
	assert(Tag::read(db, 0) == 0);
	assert(Tag::update(db, NULL) == 0);
	assert(Tag::del(db, 0) == 0);
	printf("Tag model tests complited successfull.\n");
}
