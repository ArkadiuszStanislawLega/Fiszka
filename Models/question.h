#ifndef question 
#define question
#include <iostream>
#include <vector>
#include <set>
#include <sqlite3.h>

#include "strings.h"

using std::string;
using std::set;

class Question{
	private:
		string _value, _answer;
		long _id;
		set<string> _tags;

	public:
		static int create(sqlite3*, Question*);
		static Question *read(sqlite3*, long);
		static int update(sqlite3*, Question*);
		static int del(sqlite3*, long);

		Question();
		Question(long, string, string, set<string>);

		long get_id();
		string get_value();
		string get_answer();

		void set_id(long);	
		void set_value(string);
		void set_answer(string);
			
		void add_tag();
		void remove_tag(string);
		bool is_have_tag(string);

		set<string> get_tags();
		string to_string();
};
#endif
