#include "model.h"


Model::Model(){ 
	this->_current_view = Views::main_v;
	this->_is_working = true;
	this->_current_tag = "";
	this->_questions_in_series = 0;
	this->_menu_user_selection = 0;
}

int Model::get_questions_in_series(){
	return this->_questions_in_series;
}

void Model::set_questions_in_series(int value){
	this->_questions_in_series = value;
}

Views Model::get_current_view(){
	return this->_current_view;
}

void Model::set_current_view(Views value){
	this->_current_view = value;
}


void Model::start_app(){
	this->randomise_questions();
}

vector<Question *> Model::get_randomised_questions(){
	return this->_randomised_questions;
} 

bool Model::is_working(){
	return this->_is_working;
}

void Model::set_is_working(bool value){
	this->_is_working = value;
}

Tag *Model::get_selected_tag(){
	return this->_selected_tag;
}

void Model::set_selected_tag(Tag *value){
	this->_selected_tag = value;
}

bool Model::is_questions_number_valid(){
	return this->_questions_in_series <= TagDb::read_related_questions(this->_selected_tag).size() && this->_questions_in_series > 0;
}

void Model::randomise_questions(){
	int i; 
	vector<long> ids;
	this->_randomised_questions.clear();

	ids = this->get_questions_id_related_with_tag();

	if(this->_questions_in_series == 0){
		this->_questions_in_series = ids.size();
	}

	for(i = this->_questions_in_series; i > 0; i--){
		std::srand(time(NULL));
		long index = std::rand() % ids.size();

		Question * q = QuestionDb::read(ids.at(index)); 
		this->_randomised_questions.push_back(q);

		this->quick_remove_at(ids, index);
	}

}

vector<long> Model::get_questions_id_related_with_tag(){
	vector<long> questions_ids;
	for(Question *q : TagDb::read_related_questions(this->_selected_tag)){ 
		questions_ids.push_back(q->get_id());
	}	
 	return questions_ids;
}

template <typename T>
void Model::quick_remove_at(std::vector<T> &v, std::size_t index){
	if(index < v.size()){
		v.at(index) = std::move(v.back());
		v.pop_back();
	} 
}

Question * Model::get_random_question(){
	if(this->_randomised_questions.size()){
		Question * value = this->_randomised_questions.at(0);
		this->_randomised_questions.at(0) = std::move(this->_randomised_questions.back());
		this->_randomised_questions.pop_back();
		return value;
	}
	return NULL;
}
