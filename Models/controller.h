#ifndef CONTROLLER
#define CONTROLLER
#include <limits>

#include "model.h"
#include "view.h"
#include "tag.h"

class Controller{
	private:
		Model *_model;
		View *_view;
		void prepare_randomised_questions();
		void get_questions_number_in_series();
		void get_tag();
		void series();
		
	public:
		Controller(Model *, View *);
		void start_app();
};

#endif
