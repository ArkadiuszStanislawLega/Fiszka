#ifndef DATABASE
#define DATABASE
#include <iostream>
#include <map>
#include <string>

#include "question.h"

using std::map;
using std::string;

class Database{
	private:
		map<long, Question*> _db_questions;

	public:
		map<long, Question*> get_questions();
		map<long, Question*> get_questions_by_tags(set<string>);
		void insert_question(Question *);
		Question * get_question(long);
};

#endif
