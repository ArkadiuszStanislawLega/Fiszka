#include "engine.h" 

Engine::Engine(){ 
	this->_db = new Database();
	this->fill_database();
	this->print_tags();

	printf("Wybierz zestaw pytan z podanej listy tagow (wpisz wybrany tag):");
	this->get_tag();
	printf("\n");

	this->randomise_questions(this->get_questions_id_with_tag());
	this->print_all_randominsed_questions();

	this->get_questions_number_in_series();
	this->print_questions_series();
}

void Engine::print_tags(){
	int i = 1;
	printf("Tagi w bazie danych (%lu):\n", this->_db->get_all_tags().size());
	for(string tag : this->_db->get_all_tags()){
		printf("%d. %s\n", i++, tag.c_str());
	}
	printf("--\n");
}

void Engine::get_tag(){
	cin >> this->_current_tag;	
	const set<string> tags  = this->_db->get_all_tags();
	if(tags.find(this->_current_tag) == tags.end()){
		printf("Bledny tag, sprobuj jeszcze raz.\n");
		this->get_tag();
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

template <typename T>
void Engine::quick_remove_at(std::vector<T> &v, std::size_t index){
	if(index < v.size()){
		v.at(index) = std::move(v.back());
		v.pop_back();
	} 
}

void Engine::print_all_randominsed_questions(){
	printf("Zrandomizowana lista (%lu):\n", this->_randomised_questions.size());
	for(Question * q : this->_randomised_questions){
		printf(" >> %s\n", q->to_string().c_str());
	}
}

vector<long> Engine::get_questions_id_with_tag(){
	vector<long> questions_ids;
	for(auto item : this->_db->get_questions_by_tags(set<string> {this->_current_tag})){
		questions_ids.push_back(item.first);
	}	
	printf("Liczba pytan (%lu) w bazie danych o tagu: #%s,", questions_ids.size(), this->_current_tag.c_str());
 	return questions_ids;
}

void Engine::get_questions_number_in_series(){
	printf("Podaj ilosc pytan ktore chcesz przerobic, cyfra musi byc mniejsza od %lu:\n", this->_randomised_questions.size());
	cin >> this->_questions_number_to_print;
	if(this->_questions_number_to_print > this->_randomised_questions.size()){
		printf("Nieprawidlowa wartosc. Sprobuj jeszcze raz.");
		this->get_questions_number_in_series();
	}
}

void Engine::print_questions_series(){
	size_t i = 0;
	for(; i < this->_questions_number_to_print; i++){
		this->print_question();
	}
}

void Engine::print_question(){
	Question *q = get_random_question();
	int space = 0;

	printf("%s\n", q->get_value().c_str());
	getchar();
	printf("%s\n", q->get_answer().c_str());
	getchar();
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

void Engine::fill_database(){
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
}
