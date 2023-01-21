#include "tests.h"

int main(){
	Tag *tag = new Tag();
	assert(Tag::create(NULL, tag));
	assert(Tag::update(NULL, tag));
	return 0;
}
