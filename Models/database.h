#ifndef DATABASE
#define DATABASE
#include <iostream>
#include <map>
#include <string>

#include "question.h"

class Database{
	private:
		std::map<long, Question*> _db_questions;

	public:
		std::map<long, Question*> get_questions();
		void insert_question(Question *);
		Question * get_question(long);
};

#endif
