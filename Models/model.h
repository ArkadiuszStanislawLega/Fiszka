#pragma once
#ifndef MODEL
#define MODEL
#include <iostream>
#include <vector>
#include <iostream>

#include "database.h"
#include "question.h"

using std::vector;

class Model{
	private:
		Database * _db; 
		
		vector<Question *> _randomised_questions;
		string _current_tag;
		int _questions_in_series;
		
	public:
		Model();
		int get_questions_in_series();
		string get_current_tag();
		void start_app();
		vector<Question *> get_randomised_questions();
		set<string>get_all_tags();
		void get_tag();
		Database *get_database();
		bool is_tag_correct();
		void get_questions_number_in_series();
		bool is_questions_number_valid();
		void randomise_questions(); 
		vector<long> get_questions_id_with_tag();
		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		Question * get_random_question();
};
#endif
