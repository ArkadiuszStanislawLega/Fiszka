#include "engine.h"

Engine::Engine(){
	this->_db = new Database();
}

void Engine::test(){
	this->_db->insert_question(new Question(1, "mleko, karmel, czekolada", "znany tekst"));
	this->_db->insert_question(new Question(2, "cos tam costam", "odpowiedz"));
	this->_db->insert_question(new Question(3, "teraz fajnie bedzie", "dobra odpowiedze"));
	this->_db->insert_question(new Question(4, "co to teraz bedzie", "elo"));

	for(auto counter : this->_db->get_questions())
	{
		std::cout << counter.first << " " << counter.second->get_value() << "\n"; 
	}
}

Database * Engine::get_database(){
	return this->_db;
}
