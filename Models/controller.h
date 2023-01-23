#ifndef CONTROLLER
#define CONTROLLER
#include <limits>

#include "../Enums/views.h"
#include "model.h"
#include "view.h"
#include "tag.h"

class Controller{
	private:
		Views _current_view;
		Model *_model;
		View *_view;
		void prepare_randomised_questions();
		void get_questions_number_in_series();
		void get_tag();
		void series();
		
	public:
		Controller(Model *, View *);
		void page();
		void start_app();
		void main_menu();
		void add_tag();
};
#endif
