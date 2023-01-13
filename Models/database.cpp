#include "database.h"


map<long, Question *> Database::get_questions(){
	return this->_db_questions;
}

map<long, Question*> Database::get_questions_by_tags(set<string> tags){
	map<long, Question*> questions;
	for(string tag: tags){
		for(auto value: this->_db_questions){
			if(value.second->is_have_tag(tag)){
				questions[value.second->get_id()] = value.second;
			}
		}
	}
	return questions;
}

set<string> Database::get_all_tags(){
	for(auto it: _db_questions){
		for(string tag : it.second->get_tags()){
			this->_all_tags.insert(tag);
		}
	}
	return this->_all_tags;
}



void Database::insert_question(Question * q){
	this->_db_questions[q->get_id()] = q;
}

Question * Database::get_question(long id){
	return this->_db_questions[id];
}
