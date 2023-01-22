#ifndef DATABASE
#define DATABASE
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <sqlite3.h>

#include "question.h"
#include "strings.h"

using std::map;
using std::string;

class Database{
	private:
		sqlite3 *_db;
		map<long, Question*> _db_questions;

	public:
		Database();
		~Database();
		void create_table(string, string);
		void create_table_questions();
		void create_table_tags();
		void create_table_questions_tags();

		sqlite3 *get_access();
		void insert_question(Question *);
		void openDb();
		void create_tables();
		static int callback(void *, int, char **, char**);
};

#endif
