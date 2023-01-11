#include "engine.h"
#include <cstdlib>
#include <ctime>

Engine::Engine(){ 
	this->_db = new Database();
	this->test();

	vector<long> questions_ids;
	for(auto item : this->_db->get_questions_by_tags(set<string> {"wiedza"})){
		questions_ids.push_back(item.first);
	}	
	this->randomise_questions(questions_ids);

	printf("Zrandomizowana lista (%lu):\n", this->_randomised_questions.size());
	for(Question * q : this->_randomised_questions){
		printf(" >> %s\n", q->to_string().c_str());
	}
}

int Engine::get_questions_number(){
	return this->_randomised_questions.size();
}

void Engine::test(){
	this->_db->insert_question(
			new Question(1, "mleko, karmel, czekolada", "znany tekst", set<string> {"jedzenie"}));
	this->_db->insert_question(
			new Question(2, "cos tam costam", "odpowiedz", set<string> {"wiedza"}));
	this->_db->insert_question(
			new Question(3, "teraz fajnie bedzie", "dobra odpowiedze", set<string> {"uczucia"}));
	this->_db->insert_question(
			new Question(4, "co to teraz bedzie", "elo", set<string> {"oczekiwania"}));
	this->_db->insert_question(
			new Question(5, "mleko, karmel, czekolada", "znany tekst", set<string> {"jedzenie"}));
	this->_db->insert_question(
			new Question(6, "cos tam costam", "odpowiedz", set<string> {"wiedza", "uczucia"}));
	this->_db->insert_question(
			new Question(7, "teraz fajnie bedzie", "dobra odpowiedze", set<string> {"uczucia, emocje"}));
	this->_db->insert_question(
			new Question(8, "co to teraz bedzie", "elo", set<string> {"uczucia"}));

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

void Engine::randomise_questions(vector<long> ids){
	int i = 0; 
	for(i = ids.size(); i > 0; i--){
		std::srand(time(NULL));
		long index = std::rand() % i;

		Question * q = this->_db->get_question(ids[index]);
		this->_randomised_questions.push_back(q);

		this->quick_remove_at(ids, index);
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
