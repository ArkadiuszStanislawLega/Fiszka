#include "engine.h"
#include <cstdlib>

Engine::Engine(){ 
	this->_db = new Database();
}

void Engine::test(){
	this->_db->insert_question(new Question(1, "mleko, karmel, czekolada", "znany tekst"));
	this->_db->insert_question(new Question(2, "cos tam costam", "odpowiedz"));
	this->_db->insert_question(new Question(3, "teraz fajnie bedzie", "dobra odpowiedze"));
	this->_db->insert_question(new Question(4, "co to teraz bedzie", "elo"));

	for(auto item : this->_db->get_questions())
	{
		printf("%lu = %s\n", item.first, item.second->to_string().c_str());
	}

	this->randomise_questions();
}

Database * Engine::get_database(){
	return this->_db;
}

template <typename T>
void Engine::quick_remove_at(std::vector<T> &v, std::size_t index){
	if(index < v.size()){
		v[index] = std::move(v.back());
		v.pop_back();
		v.shrink_to_fit();
	} 
}

void Engine::randomise_questions(){
	std::vector<int> questions_ids;
	int i = 0; 

	for(auto item : this->_db->get_questions()){
		questions_ids.push_back(item.first);
	}

	for(i = questions_ids.size(); i > 0; i--){
		long index = rand() % i;

		Question * q = this->_db->get_question(questions_ids[index]);
		this->_randomised_questions.push_back(q);

		this->quick_remove_at(questions_ids, index);
	}

	printf("Zrandomizowana lista:\n");
	for(Question * q : this->_randomised_questions){
		printf("%s\n", q->to_string().c_str());
	}
 } 

