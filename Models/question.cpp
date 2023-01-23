#include "question.h"

int Question::create(){
	if(this->_db != NULL){
		char* error_message;
		int rc;
		string sql = { 	INSERT + TABLE_QUESTIONS + 
				" (" + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
				"(\"" + this->_value + "\", \"" + this->_answer + "\");"};
		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);

		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0;
}


int Question::read(){
	if (this->_db != NULL && this->_id > 0){
		sqlite3_stmt * stmt;
		string sql  = {	SELECT + "* " + FROM + TABLE_QUESTIONS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(this->_id) + ";"};

		sqlite3_prepare(this->_db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		
		if((long)sqlite3_column_int(stmt, 0) == this->_id){
			this->_value = (string)((char*)sqlite3_column_text(stmt, 1));
			this->_answer = (string)((char*)sqlite3_column_text(stmt, 2));
			this->read_tags();
		} 
	}
	return 0;
}

int Question::update(){
	if(this->_db != NULL && this->_id > 0){
		char *error_message;
		int rc;
		string sql = {	UPDATE + TABLE_QUESTIONS + " " + SET + 
				COLUMN_VALUE + "=\"" + this->_value + "\", " + 
				COLUMN_ANSWER + "=\"" + this->_answer + "\" " + 
				WHERE + COLUMN_ID + "=" + std::to_string(this->_id) +";"};

		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0;
}

int Question::del(){
	if (this->_db != NULL && this->_id > 0){
		char *error_message;
		int rc;
		string sql = { DELETE + TABLE_QUESTIONS + " " + WHERE + COLUMN_ID + "=" + std::to_string(this->_id) + ";"};
		std::cout << sql << "\n";

		rc = sqlite3_exec(this->_db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0;
}

void Question::set_id(long value){
	this->_id = value;
}

Question::Question(){
	this->_db = NULL;
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

Question::Question(sqlite3 *db, long id){
	this->_db = db;
	this->_id = id;
	this->_value = "";
	this->_answer = "";
	this->read_tags();
}

Question::Question(sqlite3* db, long id, string value, string answer, vector<Tag>tags){
	this->_db = db;
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

vector<Tag> Question::get_tags(){
	return this->_tags;
}

int Question::read_related_tag(void *tags, int columns, char **column_values, char **columns_names){
	if(vector<Tag> *t = reinterpret_cast<vector<Tag>*>(tags)){
		Tag tag = Tag();
		tag.set_id(std::stol(column_values[0]));
		tag.set_tag(column_values[1]);
		t->push_back(tag);
	}
	return 0;
}

int Question::read_tags(){
	if(this->_db != NULL){
		this->_tags.clear();
		char *error_message;
		int rc;
		// SELECT Tags.Id, Tag FROM Tags
		// INNER JOIN Questions_tags ON Questions_tags.Tag_id=Tags.Id
		// INNER JOIN Questions ON Questions.Id=Questions_tags.Id
		// WHERE Questions_tags.Question_id = q->id;
		string sql = {	SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
				INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " + 
				INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " + 
				WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + std::to_string(this->_id) + ";"};
		rc = sqlite3_exec(this->_db, sql.c_str(), &read_related_tag, static_cast<void*>(&this->_tags), &error_message); 
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0; 
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
	this->update();
}

void Question::set_answer(string value){
	this->_answer = value;
	this->update();
}

void Question::set_db(sqlite3 *db){
	this->_db = db;
}


string Question::to_string(){
	return std::to_string(this->_id) + ". " + this->_value + " " + this->_answer; 
}

bool Question::is_have_tag(Tag *tag){
	return	std::find_if(this->_tags.begin(), this->_tags.end(), [&](Tag &current)
			{ return current.get_id() == tag->get_id();}) != this->_tags.end() ? true : false;
}

void Question::set_tags(vector<Tag> t){
	this->_tags = t;
}
