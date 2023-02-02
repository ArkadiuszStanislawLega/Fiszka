#include "view.h"

View::View(Model * model){
	this->_model = model;
}

void View::print_menu(){
	if(this->_model->get_selected_tag() != NULL){
		printf("%s: %s\n", SELECTED_TAG.c_str(), this->_model->get_selected_tag()->get_tag().c_str());
	}

	printf("%s:\n", MAIN_MENU.c_str());
	printf("%d. %s.\n", (int)Views::tag_list, TAG_LIST.c_str());
	printf("%d. %s.\n", (int)Views::add_tag, ADD_TAG.c_str());
	printf("%d. %s.\n", (int)Views::remove_tag, REMOVE_TAG.c_str());
	printf("%d. %s.\n", (int)Views::select_tag, SELECTED_TAG.c_str());
	printf("%d. %s.\n", (int)Views::make_series, MAKE_SERIES.c_str());
	printf("%d. %s.\n", (int)Views::question_menu, "Questions menu");
	printf("10. Exit.\n");
	printf("%s:", CHOSE_NUMBER.c_str());
}

void View::print_wrong_value(){
	printf("%s.\n", WRONG_VALUE.c_str());
}

void View::print_wrong_value_try_again(){
	printf("%s", WRONG_VALUE_TRY_AGAIN.c_str());
}

void View::print_line(){
	printf("%s\n", string(40, '=').c_str());
}

void View::print_first_select_tag(){
	printf("%s.\n", SELECT_TAG_FIRST.c_str());
}

void View::print_tags_list(vector<Tag *> tags){
	int i {0};
	printf("%s:\n", TAGS_LIST.c_str());
	for(Tag *t : tags){
		printf("%d. %s\n", i, t->get_tag().c_str());
		i++;
	}
}

void View::print_questions_vector(vector<Question *> vector){
	int i {0};
	printf("List of questions:\n");
	for(Question *q : vector){
		printf("%d. %s, ", i, q->to_string().c_str());
		this->print_tags_vector(q->get_tags());
		printf("\n");
		i++;
	}
}

void View::print_tags_vector(vector<Tag *> vector){
	if(vector.size() > 0){
		printf("Tags: ");
		for(Tag *t: vector){
			printf("%s, ", t->get_tag().c_str());
		}
	} else {
		printf("No tags.");
	}
}

void View::print_select_question_number(){
	printf("Please select question, choose number:");
}

void View::print_create_tag(){
	printf("%s:\n", ADD_TAG.c_str());
}

void View::print_created_tag(Tag *t, int sql_answer){
	if(sql_answer == 0){
		printf("%s: %s\n", TAG_CREATED_CORRECTLY.c_str(),t->get_tag().c_str());
	} else {
		printf("%s.", DATABASE_ERROR.c_str());
	}
}

void View::print_select_question(){
	printf("Select question first.\n");
}

void View::print_create_question(){
	printf("%s\n", INFO_CREATING_QUESTION.c_str());
}

void View::print_created_question(Question *q, int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s: %lu\n", QUESTION_CREATED_CORRECTLY.c_str(),q->get_id());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void View::print_select_tag(){
	printf("%s:\n", CHOSE_TAG.c_str());
	//this->print_tag_list();
}

void View::print_add_tag_to_question(vector<Question *> questions){
	int i = 0;
	printf("%s (%s) %s:\n", ADD_THE_TAG.c_str(), this->_model->get_selected_tag()->get_tag().c_str(), TO_THE_QUESTION.c_str());
	for(Question *q: questions){ 
		printf("%d. %s: %s, %s: %s\n", i, VALUE.c_str() ,q->get_value().c_str(), ANSWER.c_str(), q->get_answer().c_str());
		i++;
	}
}

void View::print_selected_question(Question *q){
	printf("Currently selected question: %s\n", q->to_string().c_str());
}

void View::print_main_menu(){
	printf("%d. %s.\n", (int)Crud::create, "Create");
	printf("%d. %s.\n", (int)Crud::read, "Select question");
	printf("%d. %s.\n", (int)Crud::update, "Update selected question");
	printf("%d. %s.\n", (int)Crud::del, "Remove selected question");
	printf("%d. %s.\n", (int)Crud::tag_add, "Add tag to selected question");
	printf("%d. %s.\n", (int)Crud::tag_remove, "Remove tag from selected question");
	printf("10. Exit.\n");
	printf("Please select option:");
}

void View::print_remove_tag_from_question(Question *q){
	printf("Select tag from the list below to remove it from the question (%s).\n", q->to_string().c_str());
}

void View::print_removed_tag_from_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("Tag has been removed.\n");
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void View::print_add_tag_to_question(){
	printf("Select tag from the list below to add to the question.\n");
}

void View::print_added_tag_to_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", TAG_ADDED_SUCCESFULLY.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void View::print_delete_tag(){
	printf("%s: %s\n%s", REMOVE_TAG.c_str(), this->_model->get_selected_tag()->get_tag().c_str(), INFO_CONFIRM_REMOVE.c_str());
}

void View::print_deleted_tag(){
	printf("%s: %s - %s.\n", THE_TAG.c_str(), this->_model->get_selected_tag()->get_tag().c_str(), SUCCESFULLY_REMOVED.c_str());
}

void View::print_delete_question(Question *question){
	printf("Are you sure do you want to remove %s? If yes push (Y).", question->to_string().c_str());
}

void View::print_deleted_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", QUESTIONS_SUCCESFULLY_REMOVED.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void View::print_delete_tag_from_question(){
	printf("%s:", REMOVE_TAG_FROM_QUESTION.c_str());
}

void View::print_make_series(){
	printf("%s:", MAKE_SERIES.c_str());
}

void View::print_questions_number_in_series(long current_number, int max_number){
	printf("(%lu/%d) ", current_number, max_number);
}

void View::print_tags(){
	int i = 1;
	vector<Tag*> tags = TagDb::read_all_tags();
	printf("%s (%lu):\n", LIST_OF_TAGS.c_str(), tags.size());
	for(Tag *tag : tags){
		printf("%d. %s\n", i++, tag->get_tag().c_str());
	}
	printf("--\n");
}

void View::print_how_many_number_in_series(long size){
	printf("%s %lu:", INFO_QUESTIONS_NUMBER_IN_SERIES.c_str(), size);
}

void View::print_all_randomised_questions(){
	printf("%s (%lu):\n", RANDOM_QUESTION_LIST.c_str(), this->_model->get_randomised_questions().size());
	for(Question * q : this->_model->get_randomised_questions()){
		printf(" >> %s\n", q->to_string().c_str());
	}
}

void View::print_question_value(Question *q){
	printf("%s", q->get_value().c_str());
}

void View::print_question_answer(Question *q){
	printf("%s\n", q->get_answer().c_str());
}

void View::print_value(){
	printf("Value:");
}

void View::print_answer(){
	printf("Answer:");
}
