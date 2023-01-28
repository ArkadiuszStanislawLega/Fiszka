#include "model.h"


Model::Model(){ 
	this->_current_view = Views::main_v;
	this->_is_working = true;
	this->_current_tag = "";
	this->_questions_in_series = 0;
	this->_menu_user_selection = 0;
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

bool Model::is_questions_number_valid(){
	return this->_questions_in_series <= this->_randomised_questions.size();
}

void Model::randomise_questions(){
	int i = 0; 
	vector<long> ids = this->get_questions_id_with_tag();
	for(i = ids.size(); i > 0; i--){
		std::srand(time(NULL));
		long index = std::rand() % i;

		//Question * q = this->_db->get_question(ids[index]);
		//this->_randomised_questions.push_back(q);

		this->quick_remove_at(ids, index);
	}
}

vector<long> Model::get_questions_id_with_tag(){
	vector<long> questions_ids;
//	for(auto item : this->_db->get_questions_by_tags(set<string> {this->_current_tag})){
//		questions_ids.push_back(item.first);
//	}	
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
