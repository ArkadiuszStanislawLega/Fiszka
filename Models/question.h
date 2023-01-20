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
		Question();
		static Question *get_from_db(long, sqlite3*);
		static void add_to_db(sqlite3*, Question*);
		Question(long, string, string, set<string>);
		string get_value();
		string get_answer();
			

		void add_tag();
		void remove_tag(string);
		bool is_have_tag(string);
		set<string> get_tags();

		void set_id(long);	
		void set_value(string);
		void set_answer(string);

		long get_id();
		string to_string();
};
#endif
