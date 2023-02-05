#include "question_view.h"

void QuestionView::print_main_menu(){
	printf("%d. %s.\n", (int)Crud::create, "Create");
	printf("%d. %s.\n", (int)Crud::read, "Select question");
	printf("%d. %s.\n", (int)Crud::update, "Update selected question");
	printf("%d. %s.\n", (int)Crud::del, "Remove selected question");
	printf("%d. %s.\n", (int)Crud::tag_add, "Add tag to selected question");
	printf("%d. %s.\n", (int)Crud::tag_remove, "Remove tag from selected question");
	printf("10. Exit.\n");
	printf("Please select option:");
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
	printf("Please select question, choose number:");
}

void QuestionView::print_select_question(){
	printf("Select question first.\n");
}







void QuestionView::print_delete_question(Question *question){
	printf("Are you sure do you want to remove %s? If yes push (Y).", question->to_string().c_str());
}

void QuestionView::print_deleted_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("%s.\n", QUESTIONS_SUCCESFULLY_REMOVED.c_str());
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void QuestionView::print_question_value(Question *q){
	printf("Value: %s", q->get_value().c_str());
}

void QuestionView::print_question_answer(Question *q){
	printf("Answer: %s\n", q->get_answer().c_str());
}

void QuestionView::print_value(){
	printf("Value:");
}

void QuestionView::print_answer(){
	printf("Answer:");
}


void QuestionView::print_remove_tag_from_question(Question *q){
	printf("Select tag from the list below to remove it from the question (%s).\n", q->to_string().c_str());
}

void QuestionView::print_removed_tag_from_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("Tag has been removed.\n");
	} else {
		printf("%s.\n", DATABASE_ERROR.c_str());
	}
}

void QuestionView::print_questions_vector(vector<Question *> vector){
	int i {0};
	printf("List of questions:\n");
	if(vector.size() > 0){
		for(Question *q : vector){
			printf("%d. %s, ", i, q->to_string().c_str());
			this->print_tags_vector(q->get_tags());
			printf("\n");
			i++;
		}
	} else {
		printf("No questions.\n");
	}
}

void QuestionView::print_tags_vector(vector<Tag *> vector){
	if(vector.size() > 0){
		printf("List of tags: ");
		for(Tag *t: vector){
			printf("%s, ", t->get_tag().c_str());
		}
	} else {
		printf("No tags.\n");
	}
}
