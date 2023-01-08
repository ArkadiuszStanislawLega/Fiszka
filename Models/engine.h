#ifndef ENGINE
#define ENGINE
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <algorithm>

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
		int get_random_question();
		void randomise_questions();

		template <typename T>
		void quick_remove_at(std::vector<T> &v, std::size_t index);
};
#endif
