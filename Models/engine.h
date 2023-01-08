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

class Engine{
	private:
		Database * _db;
		std::vector<Question *> _randomised_questions;

	public:
		Engine();
		void test();
		Database * get_database();
		Question * get_random_question();
		void randomise_questions(); 

		template <typename T>
		void quick_remove_at(std::vector<T> &v, std::size_t index);
};
#endif
