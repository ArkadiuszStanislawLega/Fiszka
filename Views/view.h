#ifndef VIEW
#define VIEW

#include "../Models/model.h"
#include "../Enums/views.h"
#include "../Enums/crud.h"
#include "question_view.h"

class View{
	private:
		Model * _model;
		QuestionView _question_view;

	public:
		View(Model *);
		QuestionView get_question_view();

		void print_menu();
		void print_wrong_value();
		void print_wrong_value_try_again();
		void print_line();
		void print_first_select_tag();

		void print_tags_list(vector<Tag *>);
		void print_tags_vector(vector<Tag *>);
		
		void print_create_tag();
		void print_created_tag(Tag *, int);

		void print_select_tag();
		
		void print_selected_question(Question *);
		void print_add_tag_to_question(vector<Question *>);
		void print_add_tag_to_question(); 
		void print_added_tag_to_question(int);

		void print_delete_tag();
		void print_deleted_tag(int);

		void print_delete_tag_from_question();
		
		void print_make_series();
		
		void print_tags();
		void print_all_randomised_questions();
		void print_how_many_number_in_series(long);
		void print_questions_number_in_series(long, int);

		void print_set_new_tag();
		void print_tag_updated(int);
		void print_remove_question_from_tag();
		void print_removed_question_from_tag(int);
		void print_main_menu_tag();
		void print_selected_tag(Tag *);
};

#endif
