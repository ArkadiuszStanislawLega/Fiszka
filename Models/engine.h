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
using std::cin;

class Engine{
	private:
		Database * _db;
		vector<Question *> _randomised_questions;
		string _current_tag;

		void fill_database();
		Database * get_database();
		vector<long> get_questions_id_with_tag();
		void randomise_questions(vector<long>); 

		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);

	public:
		Engine();
		void print_tags();
		void print_all_randominsed_questions();
		void get_tag();

		Question * get_random_question();

		int get_questions_number();
};
#endif
