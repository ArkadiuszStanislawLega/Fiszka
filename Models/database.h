#pragma once
#ifndef DATABASE
#define DATABASE
#include <string>
#include <sqlite3.h>

#include "question_db.h"
#include "tag_db.h"


using std::string;

class Database{
	public:
		static int create_table_questions_tags();
		static int create_relation(Tag *, Question *);
		static int delete_all_relation_with_tag(Tag *);
		static int delete_all_relation_with_question(Question *);
		static void create_tables();
		static int execute_query(string sql);
};
#endif
