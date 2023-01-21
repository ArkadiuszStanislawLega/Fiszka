#include "tag.h"

int Tag::create(sqlite3 *db, Tag *tag){
	if (db != NULL && tag != NULL){
		char* error_message;
		int rc;
		string sql = { 	INSERT + TABLE_TAGS + 
				" (" + COLUMN_TAG + ")" + VALUES + 
				"(\"" + tag->get_tag() + "\");"};

		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);

		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		} 
		return rc;
	} else {
		printf("Tag::create -> Database Error or Tag is Null.\n");
	}
	return 0;
}

Tag *Tag::read(sqlite3 *db, long id){
	if (db != NULL && id > 0){
		sqlite3_stmt * stmt;
		string sql  = {	SELECT + "* " + FROM + TABLE_TAGS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};

		sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		
		if((long)sqlite3_column_int(stmt, 0)){
			return new Tag((long)sqlite3_column_int(stmt, 0), 
					(string)((char*)sqlite3_column_text(stmt, 1))
					);
		} 

	} else {
		printf("Tag::read -> Database Error or id is lower than 0.\n");
	}
	return 0;
}

int Tag::update(sqlite3 *db, Tag *tag){
	if (db != NULL && tag != NULL){
		char *error_message;
		int rc;
		string sql = {	UPDATE + TABLE_TAGS + " " + SET + 
				COLUMN_TAG + "=\"" + tag->get_tag() + "\" " + 
				WHERE + COLUMN_ID + "=" + std::to_string(tag->get_id()) +";"};

		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	} else {
		printf("Tag::update -> Database Error or tag is Null.\n");
	}
	return 0;
}

int Tag::del(sqlite3 *db, long id){
	if(db != NULL && id > 0){
		char *error_message;
		int rc;
		string sql = { DELETE + TABLE_TAGS + " " + WHERE + COLUMN_ID + "=" + std::to_string(id) + ";"};

		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	} else {
		printf("Tag::del -> Database Error or id is lower than 0.\n");
	}
	return 0;
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
	return this->_tag;
}

void Tag::set_id(long id){
	this->_id = id;
}

void Tag::set_tag(string tag){
	this->_tag = tag;
}
