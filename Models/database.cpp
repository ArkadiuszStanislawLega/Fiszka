#include "database.h"
#include <string>

int Database::execute_query(string query){
	char *message_error;
	int rc = 0;
	sqlite3 *db;

	sqlite3_open(DATABASE_NAME.c_str(), &db);
	sqlite3_exec(db, query.c_str(), NULL, 0, &message_error);
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

int Database::remove_all_relation_with_tag(Tag *t){
	string sql = {DELETE + FROM + TABLE_QUESTIONS_TAGS + " " + 
			WHERE + COLUMN_TAG_ID + "=" + std::to_string(t->get_id()) + ";"};
	return execute_query(sql);
}

int Database::remove_all_relation_with_question(Question *q){
	string sql = {DELETE + FROM + TABLE_QUESTIONS_TAGS + " " + 
			WHERE + COLUMN_QUESTION_ID + "=" + std::to_string(q->get_id()) + ";"};
	return execute_query(sql);
}

void Database::create_tables(){
	Database::create_table_questions_tags();
	QuestionDb::create_table();
	TagDb::create_table();
}

//void Database::fill_database(){
	//this->insert_question(
			//new Question(1, 
				//"|", 
				//"Potok", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(2, 
				//"^+B", 
				//"przesuniecie kursora w lew", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(3, 
				//"^+F", 
				//"przesuniecie kursora w prawo", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(4, 
				//"^+A", 
				//"przesuniecie kursora na poczatek wiersza", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(5, 
				//"^+E", 
				//"przesuniecie kursora na koniec wiersza", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(6, 
				//"^+K", 
				//"^usuniecie tekstu od kursora do konca wiersza", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(7, 
				//"kill -STOP pid", 
				//"zatrzymanie procesu", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(8, 
				//"kill -CONT pid", 
				//"wznawia zatrzymany proces", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(9, 
				//"kill -l", 
				//"sprawdzanie numerow sygnalow", 
				//set<string> {"linux"})
			//);
//
	//this->insert_question(
			//new Question(10, 
				//"^+Z", 
				//"usypianie procesu", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(11, 
				//"^+C", 
				//"zabijanie procesu", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(12, 
				//"jobs", 
				//"wyswietla uspione procesy", 
				//set<string> {"linux"})
			//);
	//this->insert_question(
			//new Question(13, 
				//"void insert_sorted()",
				//"sortowanie listy/vectora", 
				//set<string> {"C++"})
			//);
//}
