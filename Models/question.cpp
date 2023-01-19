#include "question.h"

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

void Question::add_to_db(sqlite3 *db){
	char* error_message;
	int rc;
	string sql = { "insert into Questions (Value, Answer) values (\"" 
		+ this->_value + "\", \"" + this->_answer + "\");"};
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
}

Question::Question(long id, string value, string answer, set<string>tags){
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

set<string> Question::get_tags(){
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

void Question::set_value(string value){
	this->_value = value;
}

void Question::set_answer(string value){
	this->_answer = value;
}


string Question::to_string(){
	return std::to_string(this->_id) + ". " + this->_value + " " + this->_answer; 
}

bool Question::is_have_tag(string tag){
	return this->_tags.find(tag) != this->_tags.end();
}

void Question::remove_tag(string tag){
	this->_tags.erase(tag);
}
