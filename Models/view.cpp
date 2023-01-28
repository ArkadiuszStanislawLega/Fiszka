#include "view.h"

View::View(Model * model){
	this->_model = model;
}

void View::start_app(){
	this->print_menu();
}

void View::print_menu(){
	std::set<string> options = {	"Tag list", "Add tag", "Add question", 
					"Add tag to question", "Remove Tag", 
					"Remove question", "Remove tag from question", 
					"Exit"};
	int i = 0;

	printf("MAIN MENU:\n");
	for(string s : options){
		printf("%d. %s.\n", ++i, s.c_str());
	}
	printf("Chose number:");
}


void View::print_tag_list(){
	printf("List tagow\n");
}

void View::print_add_tag(){
	printf("Dodaj tag:\n");
}

void View::print_add_question(){
	printf("Doddaj pytanie\n");
}

void View::print_add_tag_to_question(){
	printf("Dodaj tag to pytania:");
}

void View::print_remove_tag(){
	printf("Usun tag:");
}

void View::print_remove_question(){
	printf("usun pytanie:");
}

void View::print_remove_tag_from_question(){
	printf("Usun tag z pytania:");
}

void View::print_make_series(){
	printf("Robimy serie");
}


void View::print_wrong_tag(){
	printf("Bledny tag, sprobuj jeszcze raz.\n");
}

void View::get_tag(){
	printf("Wybierz zestaw pytan z podanej listy tagow (wpisz wybrany tag):");
}

void View::print_tags(){
	int i = 1;
	vector<Tag> tags = TagDb::read_all_tags();
	printf("Tagi w bazie danych (%lu):\n", tags.size());
	for(Tag tag : tags){
		printf("%d. %s\n", i++, tag.get_tag().c_str());
	}
	printf("--\n");
}

void View::print_all_randomised_questions(){
	printf("Zrandomizowana lista (%lu):\n", this->_model->get_randomised_questions().size());
	for(Question * q : this->_model->get_randomised_questions()){
		printf(" >> %s\n", q->to_string().c_str());
	}
}

void View::print_number_of_questions_with_tag(){
//	printf("Liczba pytan (%lu) w bazie danych o tagu: #%s,", this->_model->get_randomised_questions().size(), this->_model->get_current_tag().c_str());
	
}

void View::print_how_many_number_in_series(){
	printf("Podaj ilosc pytan ktore chcesz przerobic, cyfra musi byc mniejsza lub rowna (%lu):\n", this->_model->get_randomised_questions().size());
}

void View::print_value_is_invalid(){
	printf("Nieprawidlowa wartosc. Sprobuj jeszcze raz.");
}

void View::print_question_value(Question *q){
	printf("%s\n", q->get_value().c_str());
}

void View::print_question_answer(Question *q){
	printf("%s\n", q->get_answer().c_str());
}
