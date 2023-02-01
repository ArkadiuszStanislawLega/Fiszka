#include "view.h"

View::View(Model * model){
	this->_model = model;
}

void View::print_menu(){
	std::vector<string> options = {	"Tag list", "Add tag", "Add question", 
					"Add tag to question", "Remove Tag", 
					"Remove question", "Remove tag from question", 
					"Select Tag", "Make series" ,"Exit"};
	int i = 1;

	printf("MAIN MENU:\n");
	if(this->_model->get_selected_tag() != NULL){
		printf("Selected tag: %s\n", this->_model->get_selected_tag()->get_tag().c_str());
	}

	for(string s : options){
		printf("%d. %s.\n", i, s.c_str());
		i++;
	}
	printf("Chose number:");
}

void View::print_wrong_value(){
	printf("Wrong value.\n");
}

void View::print_wrong_value_try_again(){
	printf("Wrong value. Try again.");
}

void View::print_line(){
	printf("%s\n", string(40, '=').c_str());
}

void View::print_first_select_tag(){
	printf("Select Tag first.\n");
}

void View::print_tag_list(){
	int i = 0;
	printf("Tags list:\n");
	for(Tag *t : TagDb::read_all_tags()){
		printf("%d. %s\n", i, t->get_tag().c_str());
		i++;
	}
}

void View::print_create_tag(){
	printf("Add tag:\n");
}

void View::print_created_tag(Tag *t, int sql_answer){
	if(sql_answer == 0){
		printf("Tag created correctly: %s\n", t->get_tag().c_str());
	} else {
		printf("Database error.");
	}
}

void View::print_create_question(){
	printf("Add a question. First, the query, and then after pressing the ENTER key, the answer. Then confirm by pressing the ENTER key.\n");
}

void View::print_created_question(Question *q, int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("Question created correctly: %lu\n", q->get_id());
	} else {
		printf("Database error.\n");
	}
}

void View::print_select_tag(){
	printf("Choose tag from list:\n");
	this->print_tag_list();
}

void View::print_add_tag_to_question(vector<Question *> questions){
	int i = 0;
	printf("Add the tag (%s) to the question:\n", this->_model->get_selected_tag()->get_tag().c_str());
	for(Question *q: questions){ 
		printf("%d. Value: %s, Answer: %s\n", i, q->get_value().c_str(), q->get_answer().c_str());
		i++;
	}
}

void View::print_added_tag_to_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("Tag added succesfully.\n");
	} else {
		printf("Database error.\n");
	}
}

void View::print_delete_tag(){
	printf("Remove tag: %s\n", this->_model->get_selected_tag()->get_tag().c_str());
	printf("Confirm deletion by typing(Y).");
}

void View::print_deleted_tag(){
	printf("The tag: %s - has been succesfully removed from database.\n", this->_model->get_selected_tag()->get_tag().c_str());
}

void View::print_delete_question(vector<Question *> questions){
	int i = 0;
	if(questions.size() > 0){
		printf("Question removed (%lu):\n", questions.size());
		for(Question *q: questions){
			printf("%d. Value: %s, Answer: %s", i, q->get_value().c_str(), q->get_answer().c_str());
			if(q->get_tags().size() > 0){
				printf(", Tag: %s", q->get_tags().at(0)->get_tag().c_str());

			}
			printf("\n");
		
			i++;
		}
	} else {
		printf("There are no questions to remove.\n");
	}
}

void View::print_deleted_question(int sql_answer){
	if(sql_answer == SQLITE_OK){
		printf("Question successfully deleted.\n");
	} else {
		printf("Database error while deleting the question.\n");
	}
}

void View::print_delete_tag_from_question(){
	printf("Remove the tag from the question:");
}

void View::print_make_series(){
	printf("Make series:");
}

void View::print_questions_number_in_series(long current_number, int max_number){
	printf("(%lu/%d) ", current_number, max_number);
}


void View::print_tags(){
	int i = 1;
	vector<Tag*> tags = TagDb::read_all_tags();
	printf("Tags in database (%lu):\n", tags.size());
	for(Tag *tag : tags){
		printf("%d. %s\n", i++, tag->get_tag().c_str());
	}
	printf("--\n");
}

void View::print_how_many_number_in_series(long size){
	printf("Enter the number of questions you want to do, the number must  be less than %lu:", size);
}

void View::print_all_randomised_questions(){
	printf("List with random questions (%lu):\n", this->_model->get_randomised_questions().size());
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
