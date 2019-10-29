#include "Base.h"
#include "utils.h"

Base::Base()
{

}

Base::~Base()
{

}

vector<Base*> Base::load(string path){
	ifstream base_text(path);

	if (!base_text.is_open()) cout << "Error reading";

	vector<Base*> bases;
	string textline;
	while(!base_text.eof()){
		Base base;
		getline(base_text, textline);
		base.setDistrict(textline);

		getline(base_text,textline);
		Address addr;
		addr.parse(textline);
		base.setAddress(addr);

		getline(base_text, textline);
		Restaurant::load(textline, &base);

		getline(base_text, textline);
		Order::load(textline, &base);

		getline(base_text, textline);
		Worker::load(textline, &base);

		base.setAdmin(dynamic_cast<Admin*>(base.getWorkers()[0]));

		getline(base_text, textline);
		Client::load(textline, &base);

		getline(base_text, textline);
		bases.push_back(&base);
	}
	return bases;
}

Restaurant * Base::findRestaurant(string str){
	for (auto & restaurant : restaurants)
		if (restaurant->get_name() == str)
			return restaurant;
	return nullptr;
}

vector<Order*> Base::findOrders(string str) {
	vector<Order*> result;
	vector<string> ids = utils::split(str, ':');
	for (auto i = 0 ; i < ids.size() ; i++) {
		for (auto & order : this->getOrders()){
			if (order->getID() == stoi(ids.at(i)))
				result.push_back(order);
		}
	}
	return result;
}

void Base::setDistrict(string d){
	district = d;
}

void Base::setAddress(Address add){
	address = add;
}

void Base::setWorkers(vector<Worker*> workers){
	this->workers = workers;
}

void Base::setAdmin(Admin * administrador){
	admin = administrador;
}

void Base::setClients(vector<Client*> clients){
	this->clients = clients;
}

void Base::setRestaurants(vector<Restaurant*> restaurants){
	this->restaurants = restaurants;
}

string Base::getDistrict() const{
	return district;
}

Address Base::getAddress() const{
	return address;
}

vector<Worker*> Base::getWorkers() const{
	return workers;
}

Admin * Base::getAdmin() const{
	return admin;
}

vector<Client*> Base::getClients() const{
	return clients;
}

vector<Restaurant*> Base::getRestaurants() const{
	return restaurants;
}

vector<Order*> Base::getOrders() const{
	return deliveries;
}

