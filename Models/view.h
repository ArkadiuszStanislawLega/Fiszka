#ifndef VIEW
#define VIEW

#include "model.h"

class View{
	private:
		Model * _model;

	public:
		View(Model *);
		void start_app();
		void get_tag();
		void print_wrong_tag();
		void print_tags();
		void print_all_randomised_questions();
		void print_number_of_questions_with_tag();
		void print_question();
		void print_how_many_number_in_series();
		void print_value_is_invalid();
		void print_question_value(Question *);
		void print_question_answer(Question *);

};

#endif
