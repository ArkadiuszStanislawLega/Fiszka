#pragma once
#ifndef MODEL
#define MODEL
#include <iostream>
#include <vector>
#include <iostream>
#include <limits>

#include "../Enums/views.h"
#include "../Database/database.h"
#include "question.h"

using std::vector;

class Model{
	private:
		Views _current_view;
		Tag *_selected_tag;
		bool _is_working;	
		vector<Question *> _randomised_questions;
		string _current_tag;
		int _questions_in_series, _menu_user_selection;
		
	public:
		static const int ACTIONS_NUMBER = 10;

		Model();
		bool is_working();
		void set_is_working(bool);

		Views get_current_view();
		void set_current_view(Views);
	
		Tag *get_selected_tag();
		void set_selected_tag(Tag *);

		int get_questions_in_series();
		void set_questions_in_series(int);

		void start_app();
		vector<Question *> get_randomised_questions();
		bool is_questions_number_valid();
		void randomise_questions(); 
		vector<long> get_questions_id_related_with_tag();
		template <typename T>
		void quick_remove_at(vector<T> &v, size_t index);
		Question * get_random_question();
};
#endif
