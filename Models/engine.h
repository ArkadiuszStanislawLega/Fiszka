#ifndef ENGINE
#define ENGINE

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>

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
		int _questions_number_to_print;

		void fill_database();
		void print_tags();
		void get_tag();
		void randomise_questions(vector<long>); 
		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		void print_all_randominsed_questions();

		vector<long> get_questions_id_with_tag();

		void print_questions_series();
		void print_question();
		Question * get_random_question();

		void get_questions_number_in_series();

	public:
		Engine();
};
#endif
