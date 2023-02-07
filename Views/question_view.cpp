#include "question_view.h"

QuestionView::QuestionView(){

}

void QuestionView::print_main_menu(){
	printf("%s\n", QUESTION_MENU);
	printf("%d. %s.\n", (int)Crud::create, CREATE);
	printf("%d. %s.\n", (int)Crud::read, SELECT_QUESTION);
	printf("%d. %s.\n", (int)Crud::update, UPDATE_QUESTION);
	printf("%d. %s.\n", (int)Crud::del, REMOVE_QUESTION);
	printf("%d. %s.\n", (int)Crud::tag_add, ADD_TAG_TO_QUESTION);
	printf("%d. %s.\n", (int)Crud::tag_remove, REMOVE_TAG_FROM_QUESTION);
	printf("%d. %s.\n", MENU_EXIT_VALUE, EXIT);
	printf("%s:", PLEASE_SELECT_OPTION);
}

void QuestionView::print_selected_question(Question *q){
	printf("%s: %s", INFO_SELECT_QUESTION, q->to_string().c_str());
}

void QuestionView::print_create_question(){
	printf("%s\n", INFO_CREATING_QUESTION.c_str());
}

void QuestionView::print_created_question(Question *q, int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s: %lu\n", QUESTION_CREATED_CORRECTLY.c_str(),q->get_id());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void QuestionView::print_select_question_number(){
	printf("%s:", INFO_SELECT_QUESTION);
}

void QuestionView::print_select_question(){
	printf("%s.\n", INFO_FIRST_SELECT_QUESTION);
}

void QuestionView::print_delete_question(Question *question){
	printf("%s: %s", INFO_SELECTED_QUESTION, question->to_string().c_str());
	printf("%s", INFO_ARE_YOU_SURE_TO_REMOVE_QUESTION);
}

void QuestionView::print_deleted_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", QUESTIONS_SUCCESFULLY_REMOVED.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void QuestionView::print_question_value(Question *q){
	printf("%s: %s", VALUE, q->get_value().c_str());
}

void QuestionView::print_question_answer(Question *q){
	printf("%s: %s\n", ANSWER, q->get_answer().c_str());
}

void QuestionView::print_value(){
	printf("%s:", VALUE);
}

void QuestionView::print_answer(){
	printf("%s:", ANSWER);
}

void QuestionView::print_remove_tag_from_question(Question *q){
	printf("%s: %s", SELECT_QUESTION, q->to_string().c_str());
	printf("%s", INFO_SELECT_TAG_TO_REMOVE_FROM_QUESTION);
}

void QuestionView::print_removed_tag_from_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", TAG_HAS_BEEN_REMOVED);
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void QuestionView::print_questions_vector(vector<Question *> vector){
	int i {0};
	printf("%s:\n", LIST_OF_QUESTIONS);
	if(vector.size() > 0){
		for(Question *q : vector){
			printf("%d. %s, ", i, q->to_string().c_str());
			this->print_tags_vector(q->get_tags());
			printf("\n");
			i++;
		}
	} else {
		printf("%s.", NO_QUESTIONS);
	}
}

void QuestionView::print_tags_vector(vector<Tag *> vector){
	if(vector.size() > 0){
		printf("%s:", LIST_OF_TAGS);
		for(Tag *t: vector){
			printf("%s, ", t->get_tag().c_str());
		}
	} else {
		printf("%s.\n", NO_TAGS);
	}
}
