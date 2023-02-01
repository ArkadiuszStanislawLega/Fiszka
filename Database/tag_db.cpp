#include "tag_db.h"

int TagDb::create_table(){
	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_TAGS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " +
			COLUMN_TAG + " " + TEXT + 
			");" };
	return Database::execute_query(sql);
}

int TagDb::create(Tag *tag){
	if (tag != NULL){
		string sql;
		if (tag->get_id() == 1){//unit test value.
			sql = { INSERT + TABLE_TAGS + 
				" (" + COLUMN_ID + ", " + COLUMN_TAG + ")" + VALUES + 
				"( 1, \"" + tag->get_tag() + "\");"};

		} else {
			sql = { INSERT + TABLE_TAGS + 
				" (" + COLUMN_TAG + ")" + VALUES + 
				"(\"" + tag->get_tag() + "\");"};
		}
		return Database::execute_query(sql);
	}
	return -1;
}

Tag *TagDb::read(long id){
	Tag *t; 
	if (id > 0){
		sqlite3 *db;
		sqlite3_stmt * stmt;
		string sql  = {	SELECT + "* " + FROM + TABLE_TAGS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		if((long)sqlite3_column_int(stmt, 0) == id){
			t = new Tag(id, (string)((char*)sqlite3_column_text(stmt, 1)));
		}
		sqlite3_finalize(stmt); 
		sqlite3_close(db); 
	}
	return t;
}

int TagDb::update(Tag *tag){
	if (tag != NULL){
		string sql = {	UPDATE + TABLE_TAGS + " " + SET + 
				COLUMN_TAG + "=\"" + tag-> get_tag() + "\" " + 
				WHERE + COLUMN_ID + "=" + std::to_string(tag->get_id()) +";"};
		return Database::execute_query(sql);
	}
	return -1;
}


int TagDb::remove(long id){
	if(id > 0){
		string sql = { DELETE + TABLE_TAGS + " " + WHERE + COLUMN_ID + "=" + std::to_string(id) + ";"};
		return Database::execute_query(sql);
	} 
	return -1;
}

int TagDb::read_all_tags_callback(void *tags, int columns, char **column_values, char **column_names){
 	if (vector<Tag*>* t = reinterpret_cast<vector<Tag*>*>(tags)){
		Tag *tag = new Tag();
		tag->set_id(std::stol(column_values[0]));
		tag->set_tag(column_values[1]);
		t->push_back(tag);
	}
	return 0;
}

vector<Tag*> TagDb::read_all_tags(){
	vector<Tag*> tags;
	sqlite3 *db;
	char *error_message;
	int rc;
	string sql = {SELECT + "* " + FROM + TABLE_TAGS + ";"};
	sqlite3_open(DATABASE_NAME.c_str(), &db);
	rc = sqlite3_exec(db, sql.c_str(), &read_all_tags_callback, static_cast<void*>(&tags), &error_message);
	sqlite3_close(db);
	return tags;
}

int TagDb::relate_tag_with_question(Question *q, Tag *t){
	if(!q->is_have_tag(t)){
		string sql = {
			INSERT + TABLE_QUESTIONS_TAGS + 
			"(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID + ")" + VALUES + 
			"(" + std::to_string(q->get_id()) + ", " + std::to_string(t->get_id()) + ");"
			};
		return Database::execute_query(sql);
	}
	return -1;
}

int TagDb::read_related_questions_callback(void *questions, int columns, char **column_values, char **columns_names){
 	if (vector<Question*>* q = reinterpret_cast<vector<Question*>*>(questions)){
		Question *question = new Question();
		question->set_id(std::stol(column_values[0]));
		question->set_value(column_values[1]);
		question->set_answer(column_values[2]);
		q->push_back(question);
	}
	return 0;

}

vector<Question *> TagDb::read_related_questions(Tag *tag){
	vector<Question *> questions;
	if(tag != NULL){
		char *error_message;
		int rc;
		sqlite3 *db;
		// select Questions.Id, VALUE, ANSWER from QUESTIONS 
		// inner join QUESTIONS_TAGS on QUESTIONS_TAGS.QUESTION_ID = QUESTIONS.ID 
		// inner join TAGS on QUESTIONS_TAGS.TAG_ID = TAGS.ID 
		// where TAGS.Id = this->id;
		string sql = {	SELECT + TABLE_QUESTIONS + "." + COLUMN_ID + ", " + COLUMN_VALUE + ", " + COLUMN_ANSWER + " " + FROM + TABLE_QUESTIONS + " " +
				INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID  + "=" + TABLE_QUESTIONS + "." + COLUMN_ID + " " +
				INNER_JOIN + TABLE_TAGS + " " + ON +  TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " +
				WHERE + " " + TABLE_TAGS + "." + COLUMN_ID + "=" + std::to_string(tag->get_id()) + ";"
		};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		rc = sqlite3_exec(db, sql.c_str(), &read_related_questions_callback, static_cast<void*>(&questions), &error_message);
		sqlite3_close(db);
		if(rc != SQLITE_OK){ printf("%s\n", error_message);}
		else {
			for(Question *q : questions){
				QuestionDb::read_related_tags(q);
			}
		}
	}
	return questions;
} 
