#include "question.h"
#include "strings.h"

void Question::add_to_db(sqlite3 *db, Question *q){
	char* error_message;
	int rc;
	string sql = { 	INSERT + TABLE_QUESTIONS + 
			" (" + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
			"(\"" + q->get_value() + "\", \"" + q->get_answer() + "\");"};
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);

	if(rc != SQLITE_OK){
		printf("%s\n", error_message);
	}
}


Question *Question::get_from_db(sqlite3 *db, long id){
    	sqlite3_stmt * stmt;
	string sql  = {	SELECT + "* " + FROM + TABLE_QUESTIONS + " " + 
			WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};

	sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
    	sqlite3_step(stmt);

	return new Question(
			(long)sqlite3_column_int(stmt, 0), 
			(string)((char*)sqlite3_column_text(stmt, 1)), 
			(string)((char*)sqlite3_column_text(stmt, 2)), 
			{});;
}

void Question::update_in_db(sqlite3 *db, Question *updated_q){
	char *error_message;
	int rc;
	string sql = {	UPDATE + TABLE_QUESTIONS + " " + SET + 
			COLUMN_VALUE + "=\"" + updated_q->get_value() + "\", " + 
			COLUMN_ANSWER + "=\"" + updated_q->get_answer() + "\" " + 
			WHERE + COLUMN_ID + "=" + std::to_string(updated_q->get_id()) +";"};

	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
	if(rc != SQLITE_OK){
		printf("%s\n", error_message);
	}
}

void Question::set_id(long value){
	this->_id = value;
}

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
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
