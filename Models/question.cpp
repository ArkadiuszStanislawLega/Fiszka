#include "question.h"

Question *Question::get_from_db(long id, sqlite3 *db){
	char *error_message;
	Question *rc;
    	sqlite3_stmt * stmt;
	string sql = "select * from Questions where id=13";

	sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );//preparing the statement
    	sqlite3_step( stmt );//executing the statement
			     //
	long db_id = (long)sqlite3_column_int(stmt, 0);

	string s1, s2;
	char *str1, *str2;

	str1 = (char*)sqlite3_column_text(stmt, 1);
	s1 = (string)str1;

	str2 = (char*)sqlite3_column_text(stmt, 2);
	s2 = (string)str2;

	return new Question(db_id, s1, s2, {});;
}

void Question::set_id(long value){
	this->_id = value;
}

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

void Question::add_to_db(sqlite3 *db, Question *q){
	char* error_message;
	int rc;
	string sql = { "insert into Questions (Value, Answer) values (\"" 
		+ q->_value + "\", \"" + q->_answer + "\");"};
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
