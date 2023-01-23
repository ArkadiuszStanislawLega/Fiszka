#pragma once
#ifndef MODEL
#define MODEL
#include <iostream>
#include <vector>
#include <iostream>
#include <limits>

#include "../Enums/views.h"
#include "database.h"
#include "question.h"

using std::vector;

class Model{
	private:
		Database * _db; 
		Views _current_view;

		bool _is_working;	
		vector<Question *> _randomised_questions;
		string _current_tag;
		int _questions_in_series, _menu_user_selection;
		
	public:
		Model();
		void select_model(Views);
		void get_main_menu_option();
		void get_add_tag();
		void get_tag_list();
		void get_add_question();
		void get_user_selection();
		Views get_current_view();
		int get_questions_in_series();
		bool is_working();
		string get_current_tag();
		void start_app();
		vector<Question *> get_randomised_questions();
		void get_tag();
		Database *get_database();
		void get_questions_number_in_series();
		bool is_questions_number_valid();
		void randomise_questions(); 
		vector<long> get_questions_id_with_tag();
		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		Question * get_random_question();
};
#endif
