#ifndef QUESTION_CONTROLLER
#define QUESTION_CONTROLLER
#include <stdio.h>
#include <limits>
#include <string>

#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Models/model.h"
#include "../Views/view.h"
#include "../Enums/crud.h"
#include "../Constants/strings.h"
#include "../Database/database.h"
#include "../Database/question_db.h"

using std::cin;
using std::getline;
using std::numeric_limits;
using std::streamsize;
using std::string;

class QuestionController{
	private:
		Model *_model;
		View *_view;
		Question *_selected_question;
		bool _is_working;

		void clean_input_buffer();
		void select_action(int);

		void create();
		Question *get_new_question();
		void select_question();
		void update();
		void remove();
		void add_tag();
		void remove_tag();

	public:
		QuestionController();
		QuestionController(Model *, View *);
		void main_menu();
};
#endif
