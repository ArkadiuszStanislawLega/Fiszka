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
		Views _current_view;
		bool _is_working;	
		vector<Question *> _randomised_questions;
		string _current_tag;
		int _questions_in_series, _menu_user_selection;
		
	public:
		Model();
		bool is_working();

		Views get_current_view();
		void set_current_view(Views);

		void start_app();
		vector<Question *> get_randomised_questions();
		bool is_questions_number_valid();
		void randomise_questions(); 
		vector<long> get_questions_id_with_tag();
		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		Question * get_random_question();
};
#endif
