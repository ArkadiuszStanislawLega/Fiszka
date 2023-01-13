#include "engine.h"

Engine::Engine(){ 
	this->_db = new Database();
	this->test();

	vector<long> questions_ids;
	for(auto item : this->_db->get_questions_by_tags(set<string> {"linux"})){
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
			new Question(1, 
				"|", 
				"Potok", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(2, 
				"^+B", 
				"przesuniecie kursora w lew", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(3, 
				"^+F", 
				"przesuniecie kursora w prawo", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(4, 
				"^+A", 
				"przesuniecie kursora na poczatek wiersza", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(5, 
				"^+E", 
				"przesuniecie kursora na koniec wiersza", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(6, 
				"^+K", 
				"^usuniecie tekstu od kursora do konca wiersza", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(7, 
				"kill -STOP pid", 
				"zatrzymanie procesu", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(8, 
				"kill -CONT pid", 
				"wznawia zatrzymany proces", 
				set<string> {"linux"})
			);
	this->_db->insert_question(
			new Question(9, 
				"kill -l", 
				"sprawdzanie numerow sygnalow", 
				set<string> {"linux"})
			);

	this->_db->insert_question(
			new Question(10, 
				"^+Z", 
				"usypianie procesu", 
				set<string> {"linux"})
			);

	this->_db->insert_question(
			new Question(11, 
				"^+C", 
				"zabijanie procesu", 
				set<string> {"linux"})
			);

	this->_db->insert_question(
			new Question(12, 
				"jobs", 
				"wyswietla uspione procesy", 
				set<string> {"linux"})
			);


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
