#include "model_tests.h"

void ModelTests::get_questions_id_related_with_tag(){
	printf("Get questions id related with tag.\t");
	string values = "TEST";

	Tag *t = new Tag(1, values);
	TagDb::create(t);

	Question *q = new Question(1, values, values, {});
	QuestionDb::create(q);

	Database::create_relation(t, q);
	Database::create_relation(t, q);

	Model *m = new Model();
	m->set_selected_tag(t);
	vector<long> ids = m->get_questions_id_related_with_tag(); 

	assert(ids.size() == 2);

	Database::delete_all_relation_with_tag(t);
	TagDb::remove(1);
	QuestionDb::remove(1);

	printf("OK\n");
}

void ModelTests::model_tests(){
	printf("Models tests start...\n");

	get_questions_id_related_with_tag();

	printf("Models tests end.\n");
}
