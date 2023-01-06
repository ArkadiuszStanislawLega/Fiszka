#include "question.h"

Question::Question(std::string value, std::string answer){
	this->_value = value;
	this->_answer = answer;
}

std::string Question::getValue(){
	return this->_value;
}

std::string Question::getAnswer(){
	return this->_answer;
}
