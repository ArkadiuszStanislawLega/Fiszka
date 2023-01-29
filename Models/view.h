#ifndef VIEW
#define VIEW

#include "model.h"
#include "../Enums/views.h"

class View{
	private:
		Model * _model;

	public:
		View(Model *);
		void start_app();
		void select_view(Views);
		void print_menu();
		void print_wrong_value();
		void print_first_select_tag();

		void print_tag_list();
		void print_create_tag();
		void print_created_tag(Tag *, int);
		void print_create_question();
		void print_created_question(Question *, int);
		void print_select_tag();

		void print_add_tag_to_question();
		void print_remove_tag();
		void print_removed_tag();
		void print_remove_question();
		void print_remove_tag_from_question();
		void print_make_series();
		
		void get_tag();
		void print_wrong_tag();
		void print_tags();
		void print_current_view();
		void print_all_randomised_questions();
		void print_number_of_questions_with_tag();
		void print_question();
		void print_how_many_number_in_series();
		void print_value_is_invalid();
		void print_question_value(Question *);
		void print_question_answer(Question *);
};

#endif
