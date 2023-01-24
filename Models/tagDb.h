#ifndef TAG_DB
#define TAG_DB
#include <vector>
#include <string>

#include "tag.h"
#include "question.h"
#include "strings.h"

using std::vector;
using std::string;

class TagDb{
	private:
		static int read_related_questions_callback(void *, int , char **, char **);
		static int read_all_tags_callback(void *, int, char **, char **);

	public:
		static int create_table();
		static int create(Tag *);
		static Tag read(long);
		static int update(Tag *);
		static int remove(long);

		static vector<Tag> read_all_tags();
		static int read_related_questions(Tag *);
		static int remove_question(Question *, Tag *);
		static int relate_tag_with_question(Question *, Tag *);
};
#endif
