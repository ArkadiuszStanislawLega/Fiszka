#include "controller.h"

Controller::Controller(){
	this->_model = NULL;
	this->_view = NULL;
	this->_question_controller = QuestionController(this->_model, this->_view);
}

Controller::Controller(Model *model, View *view){
	this->_model = model;
	this->_view = view;
	this->_question_controller = QuestionController(this->_model, this->_view);
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
//	this->_view->print_tag_list();
}

void Controller::create_tag(){
	this->_view->print_create_tag();
	string tag;
	
	this->clean_input_buffer();
	cin >> tag;

	Tag *t = new Tag();
	t->set_tag(tag);
	this->_view->print_created_tag(t, TagDb::create(t));
}

void Controller::select_tag(){
	int option_selected;
	vector<Tag*> tags;

	this->_view->print_select_tag();

	scanf("%d", &option_selected);

	tags = TagDb::read_all_tags();

	if(option_selected < tags.size()){
		this->_model->set_selected_tag(tags.at(option_selected));
	} else {
		this->_view->print_wrong_value();
	}
}

void Controller::delete_tag(){
	if(this->_model->get_selected_tag()!=NULL){
		char input;
		this->_view->print_delete_tag();

		scanf("%c", &input);

		if(input == ANSWER_YES_LARGE || input == ANSWER_YES_SMALL){
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

void Controller::get_questions_number_in_series(){
	if(this->_model->get_selected_tag() != NULL){
		int input;
		long max_size = TagDb::read_related_questions(this->_model->get_selected_tag()).size();

		this->_view->print_how_many_number_in_series(max_size);

		cin >> input;

		this->_model->set_questions_in_series(input);

		if(input > max_size || input < 0){
			this->_view->print_wrong_value_try_again();
			this->get_questions_number_in_series();
		}
	} else {
		this->_view->print_first_select_tag();
	}

}

void Controller::series(){
	if(this->_model->get_selected_tag() != NULL){
		size_t i = 0;

		this->prepare_randomised_questions();
		this->_view->print_line();
		this->clean_input_buffer();

		for(; i < this->_model->get_questions_in_series(); i++){ 
			Question *q;
			
			this->_view->print_questions_number_in_series(i+1, this->_model->get_questions_in_series());
			q = this->_model->get_random_question();

			this->_view->print_question_value(q);
			getchar();

			this->_view->print_question_answer(q);
			this->_view->print_line();
		}
	} else {
		this->_view->print_first_select_tag();
	}
}

void Controller::prepare_randomised_questions(){
	this->_model->randomise_questions();
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
		case Views::remove_tag:
		{
			this->delete_tag();
			break;
		}
		case Views::select_tag:
		{
			this->select_tag();
			break;
		}
		case Views::make_series:
		{
			this->get_questions_number_in_series();
			this->series();
			break;
		}
		case Views::question_menu:
		{
			this->_question_controller.main_menu();
			break;
		}
		default:
		{
			break;
		}
	}
}

void Controller::clean_input_buffer(){
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Controller::start_app(){
	this->_model->start_app();

	while(this->_model->is_working())
	{
		if(!main_menu()){
			this->_view->print_wrong_value();
			this->clean_input_buffer();
		}
	}
}
