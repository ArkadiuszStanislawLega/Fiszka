#ifndef QUESTION_VIEW
#define QUESTION_VIEW
#include <iostream>

#include "../Constants/strings.h"
#include "../Constants/values.h"
#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Enums/crud.h"

using std::cout;

class QuestionView{
	public:
		QuestionView();

		void print_main_menu();
		void print_selected_question(Question *);

		void print_create_question();
		void print_created_question(int);

		void print_select_question_number();
		void print_select_question();

		void print_delete_question(Question *);
		void print_deleted_question(int);

		void print_question_value(Question *);
		void print_question_answer(Question *);
		void print_value();
		void print_answer();

		void print_question_already_having_tag();
		void print_remove_tag_from_question(Question *);
		void print_no_related_tags();
		void print_removed_tag_from_question(int);

		void print_questions_vector(vector<Question *>);
		void print_tags_vector(vector<Tag *> vector);
};
#endif
