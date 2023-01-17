#ifndef DATABASE
#define DATABASE
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <sqlite3.h>

#include "question.h"

using std::map;
using std::string;

class Database{
	private:
		sqlite3 *_db;
		map<long, Question*> _db_questions;
		set<string> _all_tags;

	public:
		Database();
		~Database();
		map<long, Question*> get_questions();
		map<long, Question*> get_questions_by_tags(set<string>);
		void insert_question(Question *);
		Question * get_question(long);
		set<string> get_all_tags();
		void fill_database();  
		void openDb();
		void create_tables();
		static int callback(void *, int, char **, char**);
};

#endif
