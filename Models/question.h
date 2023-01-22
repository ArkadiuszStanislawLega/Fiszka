#pragma once
#ifndef QUESTION 
#define QUESTION
#include <iostream>
#include <vector>
#include <set>
#include <sqlite3.h>
#include <algorithm>

#include "tag.h"
#include "strings.h"

using std::string;
using std::vector;

class Tag;

class Question{
	private:
		static int read_related_tag(void *, int, char **, char **);
		string _value, _answer;
		long _id;
		vector<Tag> _tags;

	public:
		static int create(sqlite3 *, Question *);
		static Question *read(sqlite3 *, long);
		static int update(sqlite3 *, Question *);
		static int del(sqlite3 *, long);
		static vector<Tag> read_tags(sqlite3 *, Question *);

		Question();
		Question(long, string, string, vector<Tag>);

		long get_id();
		string get_value();
		string get_answer();

		void set_id(long);	
		void set_value(string);
		void set_answer(string);
		void set_tags(vector<Tag>);
			
		void add_tag();
		void remove_tag(Tag*);
		bool is_have_tag(Tag *);

		vector<Tag> get_tags_db();
		string to_string();
};
#endif
