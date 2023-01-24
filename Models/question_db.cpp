#include "question_db.h"


int QuestionDb::callback(void *NotUsed, int argc, char **argv, char **colName){
	int i;
	for(i = 0; i<argc; i++) {
	      printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void QuestionDb::create_table(){
	char *message_error;
	sqlite3 *db;
   	sqlite3_open(DATABASE_NAME.c_str(), &db);

	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_QUESTIONS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " +
			COLUMN_VALUE + " " + TEXT + ", " + 
			COLUMN_ANSWER + " " + TEXT + ");"};

	sqlite3_exec(db, sql.c_str(), callback, 0, &message_error);
	sqlite3_close(db);
}

int QuestionDb::create(Question *question){
	if(question != NULL){
		char* error_message;
		int rc;
		sqlite3 *db;
		string sql = { 	INSERT + TABLE_QUESTIONS + 
				" (" + COLUMN_VALUE + ", " + COLUMN_ANSWER + ")" + VALUES + 
				"(\"" + question->get_value() + "\", \"" + question->get_answer() + "\");"};
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error_message);

		if(rc != SQLITE_OK){
			printf("%s\n", error_message);
		}
		sqlite3_close(db);
		return rc;
	}
	return 0;
}


Question QuestionDb::read(long id){
	Question q;
	if ( id > 0){
		sqlite3_stmt * stmt;
		sqlite3 *db;
		string sql  = {	SELECT + "* " + FROM + TABLE_QUESTIONS + " " + 
				WHERE +  COLUMN_ID + "=" + std::to_string(id) + ";"};
		sqlite3_open(DATABASE_NAME.c_str(), &db);
		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL );
		sqlite3_step(stmt);
		
		if((long)sqlite3_column_int(stmt, 0) == id){
			//TODO: Zrobic tutaj uzupelnienie w liste tagow.!!!!!!!!!!!
			q = Question(id, (string)((char*)sqlite3_column_text(stmt, 1)),(string)((char*)sqlite3_column_text(stmt, 2)),  {} );
		} 
	}
	return q;
}

int QuestionDb::update(Question question){
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
