#pragma once
#ifndef TAG
#define TAG
#include <string>
#include <vector>
#include <sqlite3.h>

#include "question.h"
#include "strings.h"

using std::string;
using std::vector;

class Question;

class Tag{
	private:
		static int read_tag_callback(void*, int, char**, char**);
		static int read_related_question(void *, int, char**, char**);

		long _id;
		string _tag;

	public:
		static int create(sqlite3 *, Tag *);
		static Tag *read(sqlite3*, long);
		static int update(sqlite3*, Tag *);
		static int del(sqlite3*, long);
		static vector<Tag> read_all_tags(sqlite3*);

		Tag();
		Tag(long, string);

		long get_id();
		string get_tag();

		void set_id(long);
		void set_tag(string);
		
		int relate_question(sqlite3 *, Question *);
		vector<Question> read_related_questions(sqlite3*);
};
#endif
