#include "tag.h"

void Tag::create(sqlite3 *db, Tag *tag){

}

Tag *Tag::read(sqlite3 *db, long id){
	Tag *t = new Tag();


	return t;
}

void Tag::update(sqlite3 *db, Tag *tag){

}

void Tag::del(sqlite3 *db, long id){

}

vector<Tag> Tag::read_all_tags(sqlite3 *db){
	vector<Tag> tags;

	return tags;
}

vector<Question> Tag::read_all_connected_questions(sqlite3 *db, Tag){
	vector<Question> questions;

	return questions;
} 

Tag::Tag(){
	this->_id = 0;
	this->_tag = "";
}

Tag::Tag(long id, string tag){
	this->_id = id;
	this->_tag = tag;
}

long Tag::get_id(){
	return this->_id;
}

string Tag::get_tag(){
	return this->get_tag();
}
