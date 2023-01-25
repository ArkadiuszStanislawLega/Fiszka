#include "question_db.h"

int QuestionDb::create_table(){
	char *error_message;
	int rc = 0;
	sqlite3 *db;
	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_QUESTIONS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " +
			COLUMN_VALUE + " " + TEXT + ", " + 
			COLUMN_ANSWER + " " + TEXT + ");"};

   	sqlite3_open(DATABASE_NAME.c_str(), &db);
	sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
	if(rc != SQLITE_OK){ printf("%s\n", error_message);}
	sqlite3_close(db);
	return rc;
}

int QuestionDb::create(Question *question){
	if(question != NULL){
		char* error_message;
		int rc;
		sqlite3 *db;
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
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		sqlite3_close(db);
		return rc;
	}
	return 0;
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

int QuestionDb::update(Question *question){
	if(question != NULL){
		char *error_message;
		sqlite3 *db;
		int rc;
		string sql = {	UPDATE + TABLE_QUESTIONS + " " + SET + 
				COLUMN_VALUE + "=\"" + question->get_value() + "\", " + 
				COLUMN_ANSWER + "=\"" + question->get_answer() + "\" " + 
				WHERE + COLUMN_ID + "=" + std::to_string(question->get_id()) +";"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		sqlite3_close(db);
		return rc;
	}
	return 0;
}

int QuestionDb::read_all_questions_callback(void *questions, int columns, char **column_values, char **columns_names){
	if(vector<Question> *q = reinterpret_cast<vector<Question>*>(questions)){
		q->push_back(Question(std::stol(column_values[0]), column_values[1], column_values[2], {}));
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
	if(rc != SQLITE_OK){
		printf("%s\n", error_message);
	}
	sqlite3_close(db);

	for(Question *q : questions){
		if(q != NULL){
		printf("%lu. %s %s\n", q->get_id(), q->get_value().c_str(), q->get_answer().c_str());
		read_related_tags(q);
		}
	}
	return questions;
}

int QuestionDb::read_related_tags(Question *question){
	if(question != NULL){
		vector<Tag> tags;
		char *error_message;
		sqlite3 *db;
		int rc;
		// SELECT Tags.Id, Tag FROM Tags
		// INNER JOIN Questions_tags ON Questions_tags.Tag_id=Tags.Id
		// INNER JOIN Questions ON Questions.Id=Questions_tags.Id
		// WHERE Questions_tags.Question_id = q->id;
		string sql = {	SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
				INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " + 
				INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " + 
				WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + std::to_string(question->get_id()) + ";"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		rc = sqlite3_exec(db, sql.c_str(), &read_related_tag_callback, static_cast<void*>(&tags), &error_message);
		if (rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		question->set_tags(tags);
		sqlite3_close(db);
		return rc;
	}
	return 0; 
}

int QuestionDb::read_related_tag_callback(void *tags, int columns, char **column_values, char **columns_names){
	if(vector<Tag> *t = reinterpret_cast<vector<Tag>*>(tags)){
		Tag tag = Tag();
		tag.set_id(std::stol(column_values[0]));
		tag.set_tag(column_values[1]);
		t->push_back(tag);
	}
	return 0;
}

int QuestionDb::remove_tag(Question *q, Tag *t){
	if(q != NULL && t != NULL){
		char *error_message;
		sqlite3 *db;
		int rc;
		//DELETE FROM QUESTIONS_TAGS
		//WHERE Questions_tags.QUESTION_ID = 5 AND QUESTIONS_TAGS.TAG_ID = 2;
		string sql = {	DELETE + FROM + TABLE_QUESTIONS_TAGS + " " + 
				WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + std::to_string(q->get_id()) +
				AND + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + std::to_string(t->get_id()) + ";"
		};

		sqlite3_open(DATABASE_NAME.c_str(), &db);
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);
		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		sqlite3_close(db);
		return rc;
	}
	return 0;
}
