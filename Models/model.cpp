#include "model.h"


Model::Model(){ 
	this->_db = new Database();
	this->_current_tag = "";
	this->_questions_in_series = 0;
}

int Model::get_questions_in_series(){
	return this->_questions_in_series;
}

string Model::get_current_tag(){
	return this->_current_tag;
}

void Model::start_app(){
	this->randomise_questions();
}

vector<Question *> Model::get_randomised_questions(){
	return this->_randomised_questions;
} 

set<string> Model::get_all_tags(){
	return this->_db->get_all_tags();
}

void Model::get_tag(){
	std::cin >> this->_current_tag;	
}

bool Model::is_tag_correct(){
	const set<string> tags = this->_db->get_all_tags();
	return tags.find(this->_current_tag) != tags.end();
}

void Model::get_questions_number_in_series(){
	std::cin >> this->_questions_in_series;
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

		Question * q = this->_db->get_question(ids[index]);
		this->_randomised_questions.push_back(q);

		this->quick_remove_at(ids, index);
	}
}

vector<long> Model::get_questions_id_with_tag(){
	vector<long> questions_ids;
	for(auto item : this->_db->get_questions_by_tags(set<string> {this->_current_tag})){
		questions_ids.push_back(item.first);
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
