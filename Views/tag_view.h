#ifndef TAG_VIEW
#define TAG_VIEW
#include <iostream>

#include "../Constants/strings.h"
#include "../Models/tag.h"
#include "../Models/question.h"
#include "../Enums/crud.h"

using std::cout;

class TagView{
	public:
		TagView();
		void print_main_menu_tag();

		void print_tags_list(vector<Tag *>);
		void print_tags_vector(vector<Tag *>);
		
		void print_create_tag();
		void print_created_tag(Tag *, int);

		void print_selected_tag(Tag *);
		void print_set_new_tag();
		void print_tag_updated(int);

		void print_delete_tag(Tag *);
		void print_deleted_tag(int);

		void print_add_tag_to_question(vector<Question *>, Tag *);
		void print_add_tag_to_question(); 
		void print_added_tag_to_question(int);
		void print_remove_question_from_tag();
		void print_removed_question_from_tag(int);
		void print_questions_vector(vector<Question *>);
};
#endif
