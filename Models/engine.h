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

	public:
		Engine();
		void fill_database();
		void print_tags();
		void print_all_randominsed_questions();
		void get_tag();
		vector<long> get_questions_at_tag(string);
		Database * get_database();
		Question * get_random_question();
		void randomise_questions(vector<long>); 

		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		int get_questions_number();
};
#endif
