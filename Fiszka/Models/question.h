#ifndef question 
#define question
#include <iostream>

class Question{
	private:
		std::string _value, _answer;

	public:
		Question(std::string, std::string);
		std::string getValue();
		std::string getAnswer();
};
#endif
