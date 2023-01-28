#include "controller.h"
#include "tag.h"

Controller::Controller(Model *model, View *view){
	this->_model = model;
	this->_view = view;
}

void Controller::main_menu(){
	int option_selected = 0;
	this->_view->print_menu();

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> option_selected;
	this->select_action((Views)option_selected);
}

void Controller::tags_list(){
	int option_selected;
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
			break;
		}
		case Views::remove_tag:
		{
			break;
		}
		case Views::remove_question:
		{
			break;
		}
		case Views::remove_tag_from_question:
		{
			break;
		}
		case Views::make_series:
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
		main_menu();
	}
}

void Controller::prepare_randomised_questions(){
	this->get_tag();
	this->_model->randomise_questions();
	this->_view->print_all_randomised_questions();
}

void Controller::get_questions_number_in_series(){
	this->_view->print_how_many_number_in_series();
	//this->_model->get_questions_number_in_series();

	if(!this->_model->is_questions_number_valid()){
		this->_view->print_value_is_invalid();
		this->get_questions_number_in_series();
	}
}

void Controller::get_tag(){
	this->_view->get_tag();
	//this->_model->get_tag();
	//if(!this->_model->is_tag_correct()){
		this->_view->print_wrong_tag();
		this->get_tag();
	//}
}

void Controller::series(){
	size_t i = 0;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	for(; i < this->_model->get_questions_in_series(); i++){ 
//		Question *q = this->_model->get_random_question();
//
//		this->_view->print_question_value(q);
//		getchar();
//
//		this->_view->print_question_answer(q);
//		getchar();
//	}
}
