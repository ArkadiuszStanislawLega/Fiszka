#ifndef QUESTION_DB
#define QUESTION_DB
#include <sqlite3.h>

#include "strings.h"
#include "question.h"

class QuestionDb{
	private:
		static int read_related_tag_callback(void *, int, char **, char **);
		static int read_all_questions_callback(void *, int, char **, char **);

	public:
		static int create_table();
		static int create(Question *);
		static Question read(long);
		static int update(Question *);
		static int remove(long);


		static vector<Question> read_all_questions();
		static int read_related_tags(Question *);
		static int remove_tag(Question *, Tag *);
};
#endif 
