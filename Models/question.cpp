#include "question.h"
#include "database.h"
#include "strings.h"

int Question::create(sqlite3 *db, Question *q){
	if(db != NULL && q != NULL){
		char* error_message;
		int rc;
		string sql = { 	INSERT + TABLE_QUESTIONS + 
				" (" + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
				"(\"" + q->get_value() + "\", \"" + q->get_answer() + "\");"};
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);

		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		return rc;
	}
	return 0;
}


Question *Question::read(sqlite3 *db, long id){
	if (db != NULL && id > 0){
		sqlite3_stmt * stmt;
		string sql  = {	SELECT + "* " + FROM + TABLE_QUESTIONS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};

		sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		
		if((long)sqlite3_column_int(stmt, 0)){
			return new Question(
				(long)sqlite3_column_int(stmt, 0), 
				(string)((char*)sqlite3_column_text(stmt, 1)), 
				(string)((char*)sqlite3_column_text(stmt, 2)), 
				{});;
		} 
	}
	return 0;
}

int Question::update(sqlite3 *db, Question *updated_q){
	if(db != NULL && updated_q != NULL){
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
		return rc;
	}
	return 0;
}

int Question::del(sqlite3 *db, long id){
	if (db != NULL && id > 0){
		char *error_message;
		int rc;
		string sql = { DELETE + TABLE_QUESTIONS + " " + WHERE + COLUMN_ID + "=" + std::to_string(id) + ";"};
		std::cout << sql << "\n";

		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
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
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}


Question::Question(long id, string value, string answer, vector<Tag>tags){
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

int Question::read_related_tag(void *tags, int columns, char **column_values, char **columns_names){
	if(vector<Tag> *t = reinterpret_cast<vector<Tag>*>(tags)){
		t->push_back(Tag(std::stol(column_values[0]), column_values[1]));
	}
	return 0;
}

vector<Tag> Question::read_tags(sqlite3* db, Question *q){
	vector<Tag> tags;
	if(db != NULL && q != NULL){
		char *error_message;
		int rc;
		// SELECT Tags.Id, Tag FROM Tags
		// INNER JOIN Questions_tags ON Questions_tags.Tag_id=Tags.Id
		// INNER JOIN Questions ON Questions.Id=Questions_tags.Id
		// WHERE Questions_tags.Question_id = q->id;
		string sql = {	SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
				INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " + 
				INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " + 
				WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + std::to_string(q->get_id()) + ";"};
		rc = sqlite3_exec(db, sql.c_str(), &read_related_tag, static_cast<void*>(&tags), &error_message); 
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
	}
	return tags;
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

bool Question::is_have_tag(Tag *tag){
	return	std::find_if(this->_tags.begin(), this->_tags.end(), [&](Tag &current)
			{ return current.get_id() == tag->get_id();}) != this->_tags.end() ? true : false;
}

void Question::set_tags(vector<Tag> t){
	this->_tags = t;
}

void Question::remove_tag(Tag *tag){
	auto inter = std::find_if(this->_tags.begin(), this->_tags.end(), [&](Tag &current)
			{return current.get_id() == tag->get_id();});
	this->_tags.erase(inter);
}
