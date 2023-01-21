#ifndef TAG
#define TAG
#include <string>
#include <vector>
#include <sqlite3.h>

#include "question.h"
#include "strings.h"

using std::string;
using std::vector;

class Tag{
	private:
		static int get_all_tags(void*, int, char**, char**);
		long _id;
		string _tag;

	public:
		static int create(sqlite3 *, Tag *);
		static Tag *read(sqlite3*, long);
		static int update(sqlite3*, Tag *);
		static int del(sqlite3*, long);
		static vector<Tag> read_all_tags(sqlite3*);
		static vector<Question> read_all_connected_questions(sqlite3*, Tag);

		Tag();
		Tag(long, string);

		long get_id();
		string get_tag();

		void set_id(long);
		void set_tag(string);
};
#endif
