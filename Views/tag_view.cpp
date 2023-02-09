#include "tag_view.h"

TagView::TagView(){

}

void TagView::print_main_menu_tag(){
	printf("%s\n", TAG_MENU);
	printf("%d. %s.\n", (int)Crud::create, CREATE);
	printf("%d. %s.\n", (int)Crud::read, SELECT_TAG);
	printf("%d. %s.\n", (int)Crud::update, UPDATE_TAG);
	printf("%d. %s.\n", (int)Crud::del, REMOVE_SELECTED_TAG);
	printf("%d. %s.\n", (int)Crud::tag_add, ADD_QUESTION_TO_TAG);
	printf("%d. %s.\n", (int)Crud::tag_remove, REMOVE_QUESTION_FROM_TAG);
	printf("%d. %s.\n", MENU_EXIT_VALUE, EXIT);
	printf("%s:", PLEASE_SELECT_OPTION);
}

void TagView::print_tags_vector(vector<Tag *> tags){
	int i {0};
	printf("%s:\n", TAGS_LIST.c_str());
	for(Tag *t : tags){
		printf("%d. %s\n", i, t->get_tag().c_str());
		i++;
	}
}

void TagView::print_create_tag(){
	printf("%s:\n", ADD_TAG);
}

void TagView::print_created_tag(Tag *t, int sql_answer){
	if(sql_answer == 0){
		printf("%s: %s\n", TAG_CREATED_CORRECTLY.c_str(),t->get_tag().c_str());
	} else {
		printf("%s.", DATABASE_ERROR.c_str());
	}
}

void TagView::print_tag_already_having_tag(){
	printf("%s.\n", TAG_ALREADY_CONNECTED_WITH_QUESTION);
}

void TagView::print_add_tag_to_question(vector<Question *> questions, Tag *tag){
	int i {0};
	printf("%s (%s) %s:\n", ADD_THE_TAG.c_str(), tag->get_tag().c_str(), TO_THE_QUESTION.c_str());
	for(Question *q: questions){ 
		printf("%d. %s: %s, %s: %s\n", i, VALUE,q->get_value().c_str(), ANSWER, q->get_answer().c_str());
		i++;
	}
}

void TagView::print_selected_tag(Tag *t){
	printf("%s: %s\n", CURRENTLY_SELECTED_TAG, t->get_tag().c_str());
}

void TagView::print_add_tag_to_question(){
	printf("%s\n", INFO_SELECT_TAG_TO_ADD_QUESTION);
}

void TagView::print_added_tag_to_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", TAG_ADDED_SUCCESFULLY.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void TagView::print_delete_tag(Tag *t){
	printf("%s: %s\n%s", REMOVE_TAG, t->get_tag().c_str(), INFO_CONFIRM_REMOVE);
}

void TagView::print_deleted_tag(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s %s.\n", THE_TAG.c_str(), SUCCESFULLY_REMOVED.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void TagView::print_set_new_tag(){
	printf("%s:", SET_NEW_TAG);
}

void TagView::print_tag_updated(int sql_anwer){
	if(sql_anwer == SQLITE_OK){
		printf("%s.\n", TAG_UPDATE_SUCCESFULLY);
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void TagView::print_remove_question_from_tag(){
	printf("%s.\n", SELECT_QUESTION_TO_REMOVE_FROM_TAG);
}

void TagView::print_no_related_questions(){
	printf("%s\n", EMPTY_LIST_RELATED_QUESTIONS_WITH_TAG);
}

void TagView::print_removed_question_from_tag(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", REMOVED_RELATION_QUESTION_AND_TAG_SUCCESFULLY);
		
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void TagView::print_tags_in_row(vector<Tag *> tags){
	for(Tag *t : tags){
		printf("%s,", t->get_tag().c_str());
	}
	printf("\b.");
} 

void TagView::print_questions_vector(vector<Question *> vector){
	int i {0};
	printf("%s:\n", LIST_OF_QUESTIONS);
	if(vector.size() > 0){
		for(Question *q : vector){
			printf("%d. %s, ", i, q->to_string().c_str());
			this->print_tags_in_row(q->get_tags());
			printf("\n");
			i++;
		}
	} else {
		printf("%s\n", NO_QUESTIONS);
	}
}
