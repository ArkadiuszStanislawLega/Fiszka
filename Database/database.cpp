#include "database.h"

int Database::execute_query(string query){
	char *message_error;
	int rc = 0;
	sqlite3 *db;

	sqlite3_open(DATABASE_NAME.c_str(), &db);
	rc = sqlite3_exec(db, query.c_str(), NULL, 0, &message_error);
	if(rc != SQLITE_OK){
		printf("%s\n", message_error);
	}
	sqlite3_close(db);
	return rc;
}

int Database::create_table_questions_tags(){
	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_QUESTIONS_TAGS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " + 
			COLUMN_QUESTION_ID + " " + INTEGER_NOT_NULL + ", " +
			COLUMN_TAG_ID + " " + INTEGER_NOT_NULL + ", " +
			FOREIGN_KEY + " (" + COLUMN_QUESTION_ID + ") "+ REFERENCES + " " + TABLE_QUESTIONS + "(" + COLUMN_ID + "), " +
			FOREIGN_KEY + " (" + COLUMN_TAG_ID + ") " + REFERENCES + " " + TABLE_TAGS + "(" + COLUMN_ID + ")" +
			");" };
	return execute_query(sql);
}

int Database::create_relation(Tag *t, Question *q){
	string sql = {INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID  + ")" +
		VALUES + "(" + std::to_string(q->get_id()) + ", " + std::to_string(t->get_id()) + ")"};
	return execute_query(sql);
}

int Database::delete_all_relation_with_tag(Tag *t){
	string sql = {DELETE + TABLE_QUESTIONS_TAGS + " " + 
			WHERE + COLUMN_TAG_ID + "=" + std::to_string(t->get_id()) + ";"};
	return execute_query(sql);
}

int Database::delete_all_relation_with_question(Question *q){
	string sql = {DELETE + TABLE_QUESTIONS_TAGS + " " + 
			WHERE + COLUMN_QUESTION_ID + "=" + std::to_string(q->get_id()) + ";"};
	return execute_query(sql);
}

void Database::create_tables(){
	Database::create_table_questions_tags();
	QuestionDb::create_table();
	TagDb::create_table();
}
