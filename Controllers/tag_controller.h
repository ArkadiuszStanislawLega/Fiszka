#ifndef TAG_CONTROLLER
#define TAG_CONTROLLER
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


class TagController{
	private:
		Model *_model;
		View *_view;
		Tag *_selected_tag;
		bool _is_working;

		void clean_input_buffer();
		void select_action(int);

		void create();
		Tag *get_new_tag();
		void select_tag();
		void update();
		void remove();
		void add_question();
		void remove_question();

	public:
		TagController();
		TagController(Model *, View *);
		void main_menu();

};
#endif
