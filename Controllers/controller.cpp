#include "controller.h"

Controller::Controller(){
	this->_model = NULL;
	this->_view = NULL;
	this->_question_controller = QuestionController(this->_model, this->_view);
	this->_tag_controller = TagController(this->_model, this->_view);
}

Controller::Controller(Model *model, View *view){
	this->_model = model;
	this->_view = view;
	this->_question_controller = QuestionController(this->_model, this->_view);
	this->_tag_controller = TagController(this->_model, this->_view);
}

void Controller::start_app(){
	this->_model->start_app();

	while(this->is_main_menu_working());
}

bool Controller::is_main_menu_working(){
	int option_selected;
	this->_view->print_menu();
	
	scanf("%d", &option_selected);

	if(option_selected == MENU_EXIT_VALUE){
		return false;
	}

	if(option_selected <= 0 || option_selected > Model::ACTIONS_NUMBER && option_selected != MENU_EXIT_VALUE){
		this->_view->print_wrong_value();
		this->clean_input_buffer();
		return true;
	}

	this->select_action((Views)option_selected);
	return true;
}


void Controller::select_tag(){
	int option_selected;
	vector<Tag*> tags;

	tags = TagDb::read_all_tags();

	this->_view->print_select_tag();
	this->_view->get_tag_view()->print_tags_vector(tags);

	scanf("%d", &option_selected);

	tags = TagDb::read_all_tags();

	if(option_selected < tags.size()){
		this->_model->set_selected_tag(tags.at(option_selected));
	} else {
		this->_view->print_wrong_value();
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

			this->_view->get_question_view()->print_question_value(q);
			getchar();

			this->_view->get_question_view()->print_question_answer(q);
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
		case Views::tag_menu:
		{
			this->_tag_controller.main_menu();
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

