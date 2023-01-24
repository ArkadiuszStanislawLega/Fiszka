#ifndef TAG
#define TAG
#include <string>

#include "strings.h"

using std::string;

class Question;

class Tag{
	private:
		long _id;
		string _tag;
	public:
		Tag();
		Tag(long, string);

		long get_id();
		string get_tag();

		void set_id(long);
		void set_tag(string);
};
#endif
