#ifndef CONTROLLER
#define CONTROLLER
#include <limits>

#include "../Enums/views.h"
#include "model.h"
#include "view.h"
#include "tag.h"

class Controller{
	private:
		Model *_model;
		View *_view;
		void prepare_randomised_questions();
		void select_action(Views);
		
		void tags_list();
		void create_tag();
		void add_question();
		void add_tag_to_question();
		void remove_tag();
		void remove_question();
		void remove_tag_from_question();

		void get_questions_number_in_series();
		void get_tag();
		void series();
		
	public:
		Controller(Model *, View *);
		void start_app();
		void main_menu();
};
#endif
