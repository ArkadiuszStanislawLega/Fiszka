#ifndef CONTROLLER
#define CONTROLLER
#include <limits>

#include "../Enums/views.h"

#include "../Models/model.h"
#include "../Models/tag.h"
#include "../Models/question.h"

#include "../Views/view.h"
#include "question_controller.h"
#include "tag_controller.h"

using std::cin;
using std::getline;
using std::numeric_limits;
using std::streamsize;

class Controller{
	private:
		Model *_model;
		View *_view;
		QuestionController _question_controller;
		TagController _tag_controller;
		
		void prepare_randomised_questions();
		void select_action(Views);
		
		void tags_list();
		void create_tag();
		void select_tag();
		void delete_tag();

		void get_questions_number_in_series();
		void get_tag();
		void series();
		void clean_input_buffer();
		
	public:
		Controller();
		Controller(Model *, View *);
		void start_app();
		bool is_main_menu_working();
};
#endif
