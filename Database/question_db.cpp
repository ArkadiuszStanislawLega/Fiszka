#include "question_db.h"

int QuestionDb::create_table(){
	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_QUESTIONS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " +
			COLUMN_VALUE + " " + TEXT + ", " + 
			COLUMN_ANSWER + " " + TEXT + ");"};
	return Database::execute_query(sql);
}

int QuestionDb::create(Question *question){
	if(question != NULL){
		string sql = "";
		if(question->get_id()){
			sql = {	INSERT + TABLE_QUESTIONS + 
				" (" + COLUMN_ID + ", " + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
				"(1, \"" + question->get_value() + "\", \"" + question->get_answer() + "\");"};

		} else {
			sql = {	INSERT + TABLE_QUESTIONS + 
				" (" + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
				"(\"" + question->get_value() + "\", \"" + question->get_answer() + "\");"};
		}
		return Database::execute_query(sql);
	}
	return -1;
}

Question *QuestionDb::read(long id){
	Question *q;
	if ( id > 0){
		sqlite3_stmt * stmt;
		sqlite3 *db;
		string sql  = {	SELECT + "* " + FROM + TABLE_QUESTIONS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		
		if((long)sqlite3_column_int(stmt, 0) == id){
			q =  new Question(id, (string)((char*)sqlite3_column_text(stmt, 1)),(string)((char*)sqlite3_column_text(stmt, 2)),  {} );
		} 
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		read_related_tags(q);
	}
	return q;
}

long QuestionDb::read_id(string value, string answer){
	//TODO: Zrobic na to testy.
	if ( value != "" && answer != ""){
		long response = 0;
		sqlite3_stmt * stmt;
		sqlite3 *db;
		string sql  = {	SELECT + COLUMN_ID + " " + FROM + TABLE_QUESTIONS + " " + 
				WHERE +  COLUMN_VALUE + "=\"" + value + "\" " + AND + " " +
				COLUMN_ANSWER + "=\"" + answer  + "\"" + LIMIT + "1;"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);

		response = (long)sqlite3_column_int(stmt, 0);

		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return response;
	}
	return 0;
}

int QuestionDb::update(Question *question){
	if(question != NULL){
		string sql = {	UPDATE + TABLE_QUESTIONS + " " + SET + 
				COLUMN_VALUE + "=\"" + question->get_value() + "\", " + 
				COLUMN_ANSWER + "=\"" + question->get_answer() + "\" " + 
				WHERE + COLUMN_ID + "=" + to_string(question->get_id()) +";"};
		return Database::execute_query(sql);
	}
	return -1;
}

int QuestionDb::read_all_questions_callback(void *questions, int columns, char **column_values, char **columns_names){
	if(vector<Question*> *q = reinterpret_cast<vector<Question*>*>(questions)){
		Question *question = new Question(stol(column_values[0]), column_values[1], column_values[2], {});
		q->push_back(question);
	}
	return 0;
}

vector<Question*> QuestionDb::read_all_questions(){
	vector<Question*> questions;
	char *error_message;
	sqlite3 *db;
	int rc;
	string sql = { SELECT + "* " + FROM + TABLE_QUESTIONS + ";"};
	sqlite3_open(DATABASE_NAME.c_str(), &db);
	rc = sqlite3_exec(db, sql.c_str(), &read_all_questions_callback, static_cast<void*>(&questions), &error_message);

	if(rc != SQLITE_OK){ printf("%s\n", error_message); }
	
	sqlite3_close(db);
	for(Question *q : questions){
		if(q != NULL){
			read_related_tags(q);
		}
	}
	return questions;
}

int QuestionDb::read_related_tag_callback(void *tags, int columns, char **column_values, char **columns_names){
	if(vector<Tag*> *t = reinterpret_cast<vector<Tag*>*>(tags)){
		Tag *tag = new Tag();
		tag->set_id(stol(column_values[0]));
		tag->set_tag(column_values[1]);
		t->push_back(tag);
	}
	return 0;
}

int QuestionDb::read_related_tags(Question *question){
	vector<Tag*> tags;
	char *error_message;
	sqlite3 *db;
	int rc;
	string sql = {	SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
			INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " + 
			INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " + 
			WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + to_string(question->get_id()) + ";"};
	sqlite3_open(DATABASE_NAME.c_str(), &db);
	rc = sqlite3_exec(db, sql.c_str(), &read_related_tag_callback, static_cast<void*>(&tags), &error_message);
	
	if (rc != SQLITE_OK){ printf("%s\n", error_message);}
	
	question->set_tags(tags);
	sqlite3_close(db);
	return rc;
}

int QuestionDb::remove_tag(Question *q, Tag *t){
	if(q != NULL && t != NULL){
		string sql = {	DELETE + TABLE_QUESTIONS_TAGS + " " + 
				WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + to_string(q->get_id()) + " " +
				AND + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + to_string(t->get_id()) + ";"
		};
		return Database::execute_query(sql);
	}
	return -1;
}

int QuestionDb::remove(long id){
	if(id > 0){
		string sql = { DELETE + TABLE_QUESTIONS + " " + WHERE + COLUMN_ID + "=" + to_string(id) + ";"};
		return Database::execute_query(sql);
	}
	return -1;
}

int QuestionDb::relate_question_with_tag(Tag *t, Question *q){
	if(t->is_question_already_related(q)){
		return Database::create_relation(t, q);
	}
	return -1;
}
