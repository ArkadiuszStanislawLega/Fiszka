#ifndef CONTROLLER
#define CONTROLLER
#include <limits>

#include "../Enums/views.h"
#include "model.h"
#include "../Views/view.h"
#include "tag.h"

class Controller{
	private:
		Model *_model;
		View *_view;
		void prepare_randomised_questions();
		void select_action(Views);
		
		void tags_list();
		void create_tag();
		void create_question();
		Question *get_new_question();

		void select_tag();
		void add_tag_to_question();
		void delete_tag();

		void delete_question();
		vector<Question *> get_questions_list_depends_on_tag();
		bool is_input_in_vector_size(long, int);	
		int get_delete_question_response(Question *);

		void remove_tag_from_question();
		void get_questions_number_in_series();
		void get_tag();
		void series();
		
	public:
		Controller(Model *, View *);
		void start_app();
		bool main_menu();
};
#endif
