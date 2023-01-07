#include "database.h"


std::map<long, Question *> Database::get_questions(){
	return this->_db_questions;
}

void Database::insert_question(Question * q){
	this->_db_questions[q->get_id()] = q;
}

Question * Database::get_question(long id){
	return this->_db_questions[id];
}
