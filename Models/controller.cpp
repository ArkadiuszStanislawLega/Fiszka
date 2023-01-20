#include "controller.h"
#include "question.h"
#include <limits>

Controller::Controller(Model *model, View *view){
	this->_model = model;
	this->_view = view;
}

void Controller::start_app(){
	this->_model->start_app();
	this->_view->start_app();

	Question * q = new Question();
	q->set_value("Kolejne pytanie");
	q->set_answer("Kolejna odpowiedz.");

	Question::add_to_db(this->_model->get_database()->get_access(), q);

	q = q->get_from_db(1, this->_model->get_database()->get_access());

	std::cout << "TEST\n"; 
	std::cout << q->to_string();

	this->prepare_randomised_questions();
	this->get_questions_number_in_series();
	this->series();
}

void Controller::prepare_randomised_questions(){
	this->get_tag();
	this->_model->randomise_questions();
	this->_view->print_all_randomised_questions();
}

void Controller::get_questions_number_in_series(){
	this->_view->print_how_many_number_in_series();
	this->_model->get_questions_number_in_series();

	if(!this->_model->is_questions_number_valid()){
		this->_view->print_value_is_invalid();
		this->get_questions_number_in_series();
	}
}

void Controller::get_tag(){
	this->_view->get_tag();
	this->_model->get_tag();
	if(!this->_model->is_tag_correct()){
		this->_view->print_wrong_tag();
		this->get_tag();
	}
}

void Controller::series(){
	size_t i = 0;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for(; i < this->_model->get_questions_in_series(); i++){ 
		Question *q = this->_model->get_random_question();

		this->_view->print_question_value(q);
		getchar();

		this->_view->print_question_answer(q);
		getchar();
	}
}
