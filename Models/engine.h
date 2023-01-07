#ifndef ENGINE
#define ENGINE
#include <iostream>
#include <string>
#include <map>

#include "question.h"
#include "database.h"

class Engine{
	private:
		Database * _db;

	public:
		Engine();
		void test();
		Database * get_database(); 
};
#endif
