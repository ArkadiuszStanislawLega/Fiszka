#ifndef VIEW
#define VIEW

#include "../Models/model.h"
#include "../Enums/views.h"
#include "../Enums/crud.h"

class View{
	private:
		Model * _model;

	public:
		View(Model *);
		void print_menu();
		void print_wrong_value();
		void print_wrong_value_try_again();
		void print_line();
		void print_first_select_tag();

		void print_tags_list(vector<Tag *>);
		void print_questions_vector(vector<Question *>);
		void print_tags_vector(vector<Tag *>);
		void print_select_question_number();
		void print_select_question();
		
		void print_create_tag();
		void print_created_tag(Tag *, int);

		void print_create_question();
		void print_created_question(Question *, int);
		
		void print_select_tag();
		
		void print_selected_question(Question *);
		void print_main_menu();
		void print_add_tag_to_question(vector<Question *>);
		void print_add_tag_to_question(); 
		void print_added_tag_to_question(int);
		void print_remove_tag_from_question(Question *);
		void print_removed_tag_from_question(int);

		void print_delete_tag();
		void print_deleted_tag();

		void print_delete_question(Question *);
		void print_deleted_question(int);

		void print_delete_tag_from_question();
		
		void print_make_series();
		
		void print_tags();
		void print_all_randomised_questions();
		void print_how_many_number_in_series(long);
		void print_questions_number_in_series(long, int);
		void print_question_value(Question *);
		void print_question_answer(Question *);

		void print_value();
		void print_answer();
};

#endif
