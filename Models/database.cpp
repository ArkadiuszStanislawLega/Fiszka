#include "database.h"

Database::Database(){
	this->openDb();	
	this->create_tables();
}

Database::~Database(){
	sqlite3_close(this->_db);
}

sqlite3 *Database::get_access(){
	return this->_db;
}

int Database::callback(void *NotUsed, int argc, char **argv, char **colName){
	int i;
	for(i = 0; i<argc; i++) {
	      printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void Database::openDb(){
	sqlite3 *db;
  	char *zErrMsg = 0;
   	int rc;
	
   	rc = sqlite3_open(DATABASE_NAME.c_str(), &db);
   	if( rc ) {
      		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->_db));
   	}
}


}

void Database::create_table_questions_tags(){
	string sql = {CREATE_TABLE_IF_NOT_EXISTS + " " + TABLE_QUESTIONS_TAGS + "(" +
			COLUMN_ID + " " + PRIMARY_KEY + ", " + 
			COLUMN_QUESTION_ID + " " + INTEGER_NOT_NULL + ", " +
			COLUMN_TAG_ID + " " + INTEGER_NOT_NULL + ", " +
			FOREIGN_KEY + " (" + COLUMN_QUESTION_ID + ") "+ REFERENCES + " " + TABLE_QUESTIONS + "(" + COLUMN_ID + "), " +
			FOREIGN_KEY + " (" + COLUMN_TAG_ID + ") " + REFERENCES + " " + TABLE_TAGS + "(" + COLUMN_ID + ")" +
			");" };
	this->create_table(sql, TABLE_QUESTIONS_TAGS);
}

void Database::create_tables(){
	this->create_table_questions();
	this->create_table_tags();
	this->create_table_questions_tags();
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
