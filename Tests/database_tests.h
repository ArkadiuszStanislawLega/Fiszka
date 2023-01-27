#ifndef DATABASE_TESTS
#define DATABASE_TESTS
#include <assert.h>

#include "../Models/tag.h"
#include "../Models/question.h"

#include "../Models/database.h"
#include "../Models/question_db.h"
#include "../Models/tag_db.h"

class DatabaseTests{
	private:
		static void create_tag_table();
		static void create_tag();
		static void read_tag();
		static void set_tag();
		static void read_all_tags();
		static void create_table_questions();
		static void create_question();
		static void read_question();
		static void update_question();
		static void create_table_questions_tags();
		static void add_realation_question_and_tags();
		static void read_related_tags();
		static void read_all_questions();
		static void remove_tag_from_question();
		static void remove_tag();
		static void remove_question();
	public:
		static void database_tests();
};
#endif
