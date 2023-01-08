#include "engine.h"
#include <cstdlib>
#include <ctime>

Engine::Engine(){ 
	this->_db = new Database();
	this->test();
	this->randomise_questions();

	printf("Zrandomizowana lista (%lu):\n", this->_randomised_questions.size());
	for(Question * q : this->_randomised_questions){
		printf(" >> %s\n", q->to_string().c_str());
	}
}

void Engine::test(){
	this->_db->insert_question(new Question(1, "mleko, karmel, czekolada", "znany tekst"));
	this->_db->insert_question(new Question(2, "cos tam costam", "odpowiedz"));
	this->_db->insert_question(new Question(3, "teraz fajnie bedzie", "dobra odpowiedze"));
	this->_db->insert_question(new Question(4, "co to teraz bedzie", "elo"));
	this->_db->insert_question(new Question(5, "mleko, karmel, czekolada", "znany tekst"));
	this->_db->insert_question(new Question(6, "cos tam costam", "odpowiedz"));
	this->_db->insert_question(new Question(7, "teraz fajnie bedzie", "dobra odpowiedze"));
	this->_db->insert_question(new Question(8, "co to teraz bedzie", "elo"));

	for(auto item : this->_db->get_questions())
	{
		printf("%lu = %s\n", item.first, item.second->to_string().c_str());
	}
}

Database * Engine::get_database(){
	return this->_db;
}

template <typename T>
void Engine::quick_remove_at(std::vector<T> &v, std::size_t index){
	if(index < v.size()){
		v.at(index) = std::move(v.back());
		v.pop_back();
	} 
}

void Engine::randomise_questions(){
	std::vector<int> questions_ids;
	int i = 0; 

	for(auto item : this->_db->get_questions()){
		questions_ids.push_back(item.first);
	}	
	printf("Wielkosc przed randomizacja: %lu\n", this->_randomised_questions.size());
	for(i = questions_ids.size(); i > 0; i--){
		std::srand(time(NULL));
		long index = std::rand() % i;

		Question * q = this->_db->get_question(questions_ids[index]);
		this->_randomised_questions.push_back(q);

		this->quick_remove_at(questions_ids, index);
	}
 } 

Question * Engine::get_random_question(){
	if(this->_randomised_questions.size()){
		Question * value = this->_randomised_questions.at(0);
		this->_randomised_questions.at(0) = std::move(this->_randomised_questions.back());
		this->_randomised_questions.pop_back();
		return value;
	}
	return NULL;
}
