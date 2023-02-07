#include "view.h"

View::View(Model * model){
	this->_model = model;
	this->_question_view = new QuestionView();
	this->_tag_view = new TagView();
}

QuestionView *View::get_question_view(){
	return this->_question_view;
}

TagView *View::get_tag_view(){
	return this->_tag_view;
}

void View::print_menu(){
	if(this->_model->get_selected_tag() != NULL){
		printf("%s: %s\n", SELECTED_TAG.c_str(), this->_model->get_selected_tag()->get_tag().c_str());
	}

	printf("%s:\n", MAIN_MENU.c_str());
	printf("%d. %s.\n", (int)Views::select_tag, SELECTED_TAG.c_str());
	printf("%d. %s.\n", (int)Views::make_series, MAKE_SERIES);
	printf("%d. %s.\n", (int)Views::question_menu, QUESTIONS_MENU);
	printf("%d. %s.\n", (int)Views::tag_menu, TAGS_MENU);
	printf("10. %s.\n", EXIT);
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

void View::print_select_tag(){
	printf("%s:\n", CHOSE_TAG.c_str());
}

void View::print_selected_question(Question *q){
	printf("%s: %s\n", INFO_SELECTED_QUESTION, q->to_string().c_str());
}

void View::print_delete_tag_from_question(){
	printf("%s:", REMOVE_TAG_FROM_QUESTION);
}

void View::print_make_series(){
	printf("%s:", MAKE_SERIES);
}

void View::print_questions_number_in_series(long current_number, int max_number){
	printf("(%lu/%d) ", current_number, max_number);
}

void View::print_how_many_number_in_series(long size){
	printf("%s %lu:", INFO_QUESTIONS_NUMBER_IN_SERIES.c_str(), size);
}

void View::print_all_randomised_questions(){
	printf("%s (%lu):\n", RANDOM_QUESTION_LIST, this->_model->get_randomised_questions().size());
	for(Question * q : this->_model->get_randomised_questions()){
		printf(" >> %s\n", q->to_string().c_str());
	}
}
