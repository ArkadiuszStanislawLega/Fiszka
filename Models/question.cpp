#include "question.h"

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

Question::Question(long id, std::string value, std::string answer){
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
}

std::string Question::get_value(){
	return this->_value;
}

std::string Question::get_answer(){
	return this->_answer;
}

long Question::get_id(){
	return this->_id;
}

void Question::set_answer(std::string value){
	this->_answer = value;
}

std::string Question::to_string(){
	return std::to_string(this->_id) + ". " + this->_value + " " + this->_answer; 
}
