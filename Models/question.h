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
		sqlite3 *_db;

	public:
		Question();
		Question(sqlite3 *, long);
		Question(sqlite3 *, long, string, string, vector<Tag>);

		int create();
		int read();
		int update();
		int del();
		int read_tags();

		long get_id();
		string get_value();
		string get_answer();
		sqlite3 *get_db();
		vector<Tag> get_tags();

		void set_id(long);	
		void set_value(string);
		void set_answer(string);
		void set_tags(vector<Tag>);
		void set_db(sqlite3 *);
			
		void add_tag();
		void remove_tag(Tag*);
		bool is_have_tag(Tag *);

		string to_string();
};
#endif
