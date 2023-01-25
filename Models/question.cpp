#include "question.h"

void Question::set_id(long value){
	this->_id = value;
}

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

Question::Question(long id, string value, string answer, vector<Tag> tags){
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

vector<Tag> Question::get_tags(){
	return this->_tags;
}

string Question::get_value(){
	return this->_value;
}

string Question::get_answer(){
	return this->_answer;
}

long Question::get_id(){
	return this->_id;
}

void Question::set_answer(string value){
	this->_answer = value;
}

void Question::set_value(string value){
	this->_value = value;
}


string Question::to_string(){
	return std::to_string(this->_id) + ". " + this->_value + " " + this->_answer; 
}

bool Question::is_have_tag(Tag *tag){
	return	std::find_if(this->_tags.begin(), this->_tags.end(), [&](Tag &current)
			{ return current.get_id() == tag->get_id();}) != this->_tags.end() ? true : false;
}

void Question::set_tags(vector<Tag> t){
	this->_tags = t;
}
