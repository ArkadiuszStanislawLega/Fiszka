#include "tag.h"

int Tag::create(){
	if (this->_db != NULL ){
		char* error_message;
		int rc;
		string sql = { 	INSERT + TABLE_TAGS + 
				" (" + COLUMN_TAG + ")" + VALUES + 
				"(\"" + this->_tag + "\");"};


		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);

		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		} 
		return rc;
	}
	return 0;
}

int Tag::read(){
	if (this->_db != NULL && this->_id > 0){
		sqlite3_stmt * stmt;
		string sql  = {	SELECT + "* " + FROM + TABLE_TAGS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(this->_id) + ";"};

		sqlite3_prepare(this->_db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		 
		if((long)sqlite3_column_int(stmt, 0) == this->_id){
			this->_tag = (string)((char*)sqlite3_column_text(stmt, 1));
		} else {
			return 1;
		}
	}
	return 0;
}

int Tag::update(){
	if (this->_db != NULL && this->_id > 0){
		char *error_message;
		int rc;
		string sql = {	UPDATE + TABLE_TAGS + " " + SET + 
				COLUMN_TAG + "=\"" + this->_tag + "\" " + 
				WHERE + COLUMN_ID + "=" + std::to_string(this->_id) +";"};

		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0;
}

int Tag::del(){
	if(this->_db != NULL && this->_id > 0){
		char *error_message;
		int rc;
		string sql = { DELETE + TABLE_TAGS + " " + WHERE + COLUMN_ID + "=" + std::to_string(this->_id) + ";"};

		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	} 
	return 0;
}

int Tag::read_tag_callback(void *tags, int columns, char **column_values, char **column_names){
 	if (vector<Tag>* t = reinterpret_cast<vector<Tag>*>(tags)){
		Tag tag = Tag();
		tag.set_id(std::stol(column_values[0]));
		tag.set_tag(column_values[1]);
		t->push_back(tag);
	}
	return 0;
}

vector<Tag> Tag::read_all_tags(sqlite3 *db){
	vector<Tag> tags;
	if(db != NULL){   
		char *error_message;
		int rc;
		string sql = {SELECT + "* " + FROM + TABLE_TAGS + ";"};
		rc = sqlite3_exec(db, sql.c_str(), &read_tag_callback, static_cast<void*>(&tags), &error_message);
	}
	return tags;
}

int Tag::relate_question(sqlite3 *db, Question *q){
	if(db != NULL && q != NULL){
		char *error_message;
		int rc;

		if(!q->is_have_tag(this)){
			string sql = {
				INSERT + TABLE_QUESTIONS_TAGS + 
				"(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID + ")" + VALUES + 
				"(" + std::to_string(q->get_id()) + ", " + std::to_string(this->_id) + ");"
				};
			rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
			if(rc != SQLITE_OK){
				printf("%s\n", error_message);
			}
			return rc;
		}
	}
	return 0;
}

int Tag::read_related_question(void *questions, int columns, char **column_values, char **columns_names){
 	if (vector<Question>* q = reinterpret_cast<vector<Question>*>(questions)){
        	q->push_back(Question(std::stol(column_values[0]), column_values[1], column_values[2], {}));
	}
	return 0;

}

vector<Question> Tag::read_related_questions(sqlite3 *db){
	vector<Question> questions;
	if(db != NULL){
		char *error_message;
		int rc;
		// select Questions.Id, VALUE, ANSWER from QUESTIONS 
		// inner join QUESTIONS_TAGS on QUESTIONS_TAGS.QUESTION_ID = QUESTIONS.ID 
		// inner join TAGS on QUESTIONS_TAGS.TAG_ID = TAGS.ID 
		// where TAGS.Id = this->id;
		string sql = {	SELECT + TABLE_QUESTIONS + "." + COLUMN_ID + ", " + COLUMN_VALUE + ", " + COLUMN_ANSWER + " " + FROM + TABLE_QUESTIONS + " " +
				INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID  + "=" + TABLE_QUESTIONS + "." + COLUMN_ID + " " +
				INNER_JOIN + TABLE_TAGS + " " + ON +  TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " +
				WHERE + " " + TABLE_TAGS + "." + COLUMN_ID + "=" + std::to_string(this->_id) + ";"
		};
		std::cout << sql << "\n";			
		rc = sqlite3_exec(db, sql.c_str(), &read_related_question, static_cast<void*>(&questions), &error_message);
	}
	return questions;
} 

Tag::Tag(){
	this->_db = NULL;
	this->_id = 0;
	this->_tag = "";
}

Tag::Tag(sqlite3* db, long id){
	this->_db = db;
	this->_id = id;
	this->read();
}

Tag::Tag(sqlite3* db, long id, string tag){
	this->_db = db; 
	this->_id = id;
	this->_tag = tag;
}

long Tag::get_id(){
	return this->_id;
}

string Tag::get_tag(){
	this->read();
	return this->_tag;
}

void Tag::set_id(long id){
	this->_id = id;
}

void Tag::set_tag(string tag){
	this->_tag = tag;
	this->update();
}

void Tag::set_db(sqlite3 *db){
	this->_db = db;
}
