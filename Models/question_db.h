#ifndef QUESTION_DB
#define QUESTION_DB
#include <sqlite3.h>

#include "strings.h"
#include "question.h"

class QuestionDb{
	private:
		static int callback(void *, int, char **, char **);
		static sqlite3 *dd;

	public:
		static void create_table();
		static int create(Question *);
		static Question read(long);
		static int update(Question *);
		static int remove(long);
		static sqlite3 *db();
};
#endif 
