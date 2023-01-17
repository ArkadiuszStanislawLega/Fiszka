#include "database.h"

Database::Database(){
	this->fill_database();
	this->openDb();
}

void Database::openDb(){
	sqlite3 *db;
  	char *zErrMsg = 0;
   	int rc;
	
   	rc = sqlite3_open("test.db", &db);
   	if( rc ) {
      		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   	} else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   	sqlite3_close(db);
}

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

void Database::fill_database(){
	this->insert_question(
			new Question(1, 
				"|", 
				"Potok", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(2, 
				"^+B", 
				"przesuniecie kursora w lew", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(3, 
				"^+F", 
				"przesuniecie kursora w prawo", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(4, 
				"^+A", 
				"przesuniecie kursora na poczatek wiersza", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(5, 
				"^+E", 
				"przesuniecie kursora na koniec wiersza", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(6, 
				"^+K", 
				"^usuniecie tekstu od kursora do konca wiersza", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(7, 
				"kill -STOP pid", 
				"zatrzymanie procesu", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(8, 
				"kill -CONT pid", 
				"wznawia zatrzymany proces", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(9, 
				"kill -l", 
				"sprawdzanie numerow sygnalow", 
				set<string> {"linux"})
			);

	this->insert_question(
			new Question(10, 
				"^+Z", 
				"usypianie procesu", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(11, 
				"^+C", 
				"zabijanie procesu", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(12, 
				"jobs", 
				"wyswietla uspione procesy", 
				set<string> {"linux"})
			);
	this->insert_question(
			new Question(13, 
				"void insert_sorted()",
				"sortowanie listy/vectora", 
				set<string> {"C++"})
			);
}
