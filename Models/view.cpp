#include "view.h"

View::View(Model * model){
	this->_model = model;
}

void View::start_app(){
	this->print_menu();
}

void View::select_view(Views view){
	switch(view){
		case Views::main_v:
		{	
			this->print_menu();
			break;
		}
		case Views::add_tag:
		{
			this->print_add_tag();
			break;
		}
		case Views::tag_list:
		{
			this->print_tag_list();
			break;
		}
		case Views::add_question:
		{
			this->print_add_question();
			break;
		}
	}
}

void View::print_add_tag(){
	printf("Dodaj tag:\n");
}

void View::print_tag_list(){
	printf("List tagow\n");
}

void View::print_add_question(){
	printf("Doddaj pytranie\n");
}

void View::print_menu(){
	printf("1. Create tag.\n2. List tags.\n0. Exit.\nChose number:");
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
	printf("Liczba pytan (%lu) w bazie danych o tagu: #%s,", this->_model->get_randomised_questions().size(), this->_model->get_current_tag().c_str());
	
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
