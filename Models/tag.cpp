#include "tag.h"

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
	return this->_tag;
}

void Tag::set_id(long id){
	this->_id = id;
}

void Tag::set_tag(string tag){
	this->_tag = tag;
}
