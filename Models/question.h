#ifndef question 
#define question
#include <iostream>

class Question{
	private:
		std::string _value, _answer;
		long _id;

	public:
		Question();
		Question(long, std::string, std::string);
		std::string get_value();
		std::string get_answer();
		void set_answer(std::string);
		long get_id();
		std::string to_string();
};
#endif
