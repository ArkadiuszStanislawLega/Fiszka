#ifndef ENGINE
#define ENGINE

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "question.h"
#include "database.h"

using std::vector;
using std::string;
using std::size_t;

class Engine{
	private:
		Database * _db;
		vector<Question *> _randomised_questions;

	public:
		Engine();
		void test();
		Database * get_database();
		Question * get_random_question();
		void randomise_questions(vector<long>); 

		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		int get_questions_number();
};
#endif
