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

		for (auto & x : base.getOrders()) {
			cout << "ID: " << x->getID() << endl;
		}

		getline(base_text, textline);
		Worker::load(textline, &base);

		for (int i = 0; i < base.getWorkers().size(); i++) {
			cout << "Name: " << base.getWorkers().at(i)->get_name() << endl;
		}

		base.setAdmin(dynamic_cast<Admin*>(base.getWorkers().at(0)));
		 
		getline(base_text, textline);
		Client::load(textline, &base);

		getline(base_text, textline);

		Base * ptr = new Base;
		*ptr = base;
		bases.push_back(ptr);
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

void Base::setOrders(vector<Order*> orders)
{
	this->orders = orders;
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
	return orders;
}

//Visualização de Informação
void Base::seeAllClients()
{
	cout << "ALL CLIENTS" << endl << endl;
	vector<Client*>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		(*it)->print();
		cout << endl << endl;
	}
}






void Base::addClient() {

	Client c;

	// HARD CODED FOR BASE PORTO
	vector<string> areaOfInfluence = { "Porto", "Matosinhos", "Vila Nova de Gaia", "Gondomar", "Maia"};
	string baseName = this->getDistrict();
	c.set_base(this);
	

	// name input
	bool invalidName;
	string name;
	do {
		invalidName = false;
		
		cout << "Name: ";
		getline(cin, name);
		
	} while (invalidName);

	c.set_name(name);

	// nif input
	bool invalidNif;
	string strNif;
	int nif;
	do {
		invalidNif = false;
		
		cout << "NIF: ";
		getline(cin, strNif);

		try {
			nif = stoi(strNif);
		}

		catch (...) {
			invalidNif = true;
		}

	} while (invalidNif);

	c.set_NIF(nif);

	// address input
	bool invalidAddress;
	Address address;
	do {
		invalidAddress = false;

		string fullAddress;
		cout << "Address: ";
		getline(cin, fullAddress);

		try {
			address.parse(fullAddress);

			// if it doesnt belong to the are of influence it is considered invalid
			if (find(areaOfInfluence.begin(), areaOfInfluence.end(), address.get_district()) == areaOfInfluence.end()) {
				invalidAddress = true;
			}
		}

		catch (...) {
			invalidAddress = true;
		}

	} while (invalidAddress);

	c.set_address(address);
	
	// orders vector that starts empty
	vector <Order*> clientOrders = {};

	c.set_orders(clientOrders);


	Client * ptr = new Client;
	*ptr = c;
	
	clients.push_back(ptr);
	
}