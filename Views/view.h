#ifndef VIEW
#define VIEW

#include "../Models/model.h"
#include "../Enums/views.h"
#include "../Enums/crud.h"
#include "question_view.h"
#include "tag_view.h"

class View{
	private:
		Model * _model;
		QuestionView _question_view;
		TagView _tag_view;

	public:
		View(Model *);
		QuestionView get_question_view();
		TagView get_tag_view();

		void print_menu();
		void print_wrong_value();
		void print_wrong_value_try_again();
		void print_line();

		void print_tags();
		void print_first_select_tag();
		void print_select_tag();
		
		void print_selected_question(Question *);
		void print_delete_tag_from_question();
		
		void print_make_series();
		
		void print_all_randomised_questions();
		void print_how_many_number_in_series(long);
		void print_questions_number_in_series(long, int);
};

#endif
