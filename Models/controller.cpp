#include "controller.h"
#include "question.h"
#include "tag.h"

Controller::Controller(Model *model, View *view){
	this->_model = model;
	this->_view = view;
}

bool Controller::main_menu(){
	int option_selected;
	this->_view->print_menu();
	
	scanf("%d", &option_selected);

	if(option_selected <= 0 || option_selected > Model::ACTIONS_NUMBER){
		return false;
	}

	if(option_selected < Model::ACTIONS_NUMBER && option_selected > 0){
		this->select_action((Views)option_selected);
	} 

	if(option_selected == Model::ACTIONS_NUMBER){
		this->_model->set_is_working(false);
	}

	if(option_selected > Model::ACTIONS_NUMBER && option_selected < 0){
		this->_view->print_wrong_value();
	}
	return true;
}

void Controller::tags_list(){
	this->_view->print_tag_list();
}

void Controller::create_tag(){
	this->_view->print_create_tag();
	string tag;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> tag;

	Tag *t = new Tag();
	t->set_tag(tag);
	this->_view->print_created_tag(t, TagDb::create(t));
}

void Controller::create_question(){
	if(this->_model->get_selected_tag() == NULL){
		this->_view->print_first_select_tag();
	} else {
		string value, answer;
		int sql_answer = -1;
		Question *q = new Question();

		this->_view->print_create_question();
		
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, value);	
		std::getline(std::cin, answer);

		q->set_value(value);
		q->set_answer(answer);

		sql_answer = QuestionDb::create(q);
		this->_view->print_created_question(q, sql_answer); 

		if(sql_answer == SQLITE_OK){
			q->set_id(QuestionDb::read_id(value, answer));
			Database::create_relation(this->_model->get_selected_tag(), q);
		}
	}
}

void Controller::select_tag(){
	int option_selected = 0;
	vector<Tag*> tags;

	this->_view->print_select_tag();

	std::cin >> option_selected;
	tags = TagDb::read_all_tags();
	if(option_selected < tags.size()){
		this->_model->set_selected_tag(tags.at(option_selected));
	} else {
		this->_view->print_wrong_value();
	}
}

void Controller::delete_tag(){
	if(this->_model->get_selected_tag()!=NULL){
		string input = "";
		this->_view->print_delete_tag();
		std::cin >> input;
		if(input == "T"){
			int del1, del2;
			del1 = Database::delete_all_relation_with_tag(this->_model->get_selected_tag());
			del2 = TagDb::remove(this->_model->get_selected_tag()->get_id());
			if(del1 ==SQLITE_OK && del2== SQLITE_OK){
				this->_view->print_deleted_tag();
				this->_model->set_selected_tag(NULL);
			}
		}
	} else {
		this->_view->print_first_select_tag();
	}
}

void Controller::add_tag_to_question(){
	int input = 0;
	vector<Question *> questions = QuestionDb::read_all_questions();
	if(this->_model->get_selected_tag() != NULL){
		this->_view->print_add_tag_to_question(questions);
		std::cin >> input;

		if(input < questions.size() && input >= 0){
			int sql_answer = Database::create_relation(this->_model->get_selected_tag(), questions.at(input));
			this->_view->print_added_tag_to_question(sql_answer);
		}
	} else {
		this->_view->print_first_select_tag();
	}
}

void Controller::delete_question(){
	int input = 0;
	vector<Question *> questions = this->get_questions_list_depends_on_tag();

	this->_view->print_delete_question(questions);

	std::cin >> input;

	if(this->is_input_in_vector_size(questions.size(), input)){
		this->_view->print_deleted_question(get_delete_question_response(questions.at(input)));
	} else {
		this->_view->print_wrong_value();
	}
}

vector<Question *> Controller::get_questions_list_depends_on_tag(){
	vector<Question *> questions;

	if(this->_model->get_selected_tag() == NULL){
		questions = QuestionDb::read_all_questions();
	} else {
		questions = TagDb::read_related_questions(this->_model->get_selected_tag());
	}
	return questions;
}

bool Controller::is_input_in_vector_size(long size, int input){
	return size > 0 && input < size && input >= 0;
}

int Controller::get_delete_question_response(Question *q){
	return Database::delete_all_relation_with_question(q) + QuestionDb::remove(q->get_id()) == SQLITE_OK ? 0 : 1;
	
}

void Controller::series(){
	printf("series TESTS");
	if(this->_model->get_selected_tag() != NULL){
		size_t i = 0;
		printf("TEST 0");
		this->prepare_randomised_questions();
		printf("TEST 1");
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		long size = TagDb::read_related_questions(this->_model->get_selected_tag()).size();
		printf("%lu\n", size);
		for(; i < size; i++){ 
			Question *q = this->_model->get_random_question();

			this->_view->print_question_value(q);
			getchar();

			this->_view->print_question_answer(q);
			getchar();
		}
	} else {
		this->_view->print_first_select_tag();
	}
}

void Controller::prepare_randomised_questions(){
	this->_model->randomise_questions();
	printf("TEST 4");
	this->_view->print_all_randomised_questions();
}

void Controller::select_action(Views view){
	switch(view){
		case Views::main_v:
		{	
			this->main_menu();
			break;
		}
		case Views::tag_list:
		{
			this->tags_list();
			break;
		}
		case Views::add_tag:
		{
			this->create_tag();
			break;
		}
		case Views::add_question:
		{
			this->create_question();
			break;
		}
		case Views::add_tag_to_question:
		{
			add_tag_to_question();
			break;
		}
		case Views::remove_tag:
		{
			this->delete_tag();
			break;
		}
		case Views::remove_question:
		{
			this->delete_question();
			break;
		}
		case Views::remove_tag_from_question:
		{
			break;
		}
		case Views::select_tag:
		{
			this->select_tag();
			break;
		}
		case Views::make_series:
		{
			this->series();
			break;
		}
		default:
		{
			break;
		}
	}
}

void Controller::start_app(){
	this->_model->start_app();
	this->_view->start_app();

	while(this->_model->is_working())
	{
		if(!main_menu()){
			this->_view->print_wrong_value();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}


void Controller::get_questions_number_in_series(){
	this->_view->print_how_many_number_in_series();
	//this->_model->get_questions_number_in_series();

	if(!this->_model->is_questions_number_valid()){
		this->_view->print_value_is_invalid();
		this->get_questions_number_in_series();
	}
}
