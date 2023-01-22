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
		static int create(sqlite3 *, Question *);
		static Question *read(sqlite3 *, long);
		static int update(sqlite3 *, Question *);
		static int del(sqlite3 *, long);
		vector<Tag> read_tags();

		Question();
		
		Question(long, string, string, vector<Tag>);
		Question(sqlite3 *, long);
		long get_id();
		string get_value();
		string get_answer();
		vector<Tag> get_tags();

		void set_id(long);	
		void set_value(string);
		void set_answer(string);
		void set_tags(vector<Tag>);
			
		void add_tag();
		void remove_tag(Tag*);
		bool is_have_tag(Tag *);

		string to_string();
};
#endif
