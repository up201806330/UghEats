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

		/*
		for (auto & x : base.getOrders()) {
			cout << "ID: " << x->getID() << endl;
		}
		*/

		getline(base_text, textline);
		Worker::load(textline, &base);

		/*
		for (int i = 0; i < base.getWorkers().size(); i++) {
			cout << "Name: " << base.getWorkers().at(i)->get_name() << endl;
		}
		*/

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

const vector<Worker*> & Base::getWorkers() const{
	return workers;
}

Admin * Base::getAdmin() const{
	return admin;
}

const vector<Client*> & Base::getClients() const{
	return clients;
}

const vector<Restaurant*> & Base::getRestaurants() const{
	return restaurants;
}

const vector<Order*> & Base::getOrders() const{
	return orders;
}

//Visualiza��o de Informa��o
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

void Base::seeOneClient()
{
	cout << "Pick the Client you want to see: " << endl << endl;
	vector<Client*>::iterator it;
	int id = 1;
	int answer;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cout << endl;
	cin >> answer;
	cout << endl << "INFO" << endl;
	clients[answer - 1]->print();

}

void Base::seeAllRestaurants()
{
	cout << "ALL RESTAURANTS" << endl << endl;
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		cout << *(*it);
	}
}

void Base::seeOneRestaurant()
{
	cout << "Pick the Restaurant you want to see" << endl << endl;
	vector<Restaurant*>::iterator it;
	int id = 1, answer;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cout << endl;
	cin >> answer;
	cout << endl << "INFO" << endl;
	cout << (*restaurants[answer - 1]);
	if ((*restaurants[answer - 1]).get_products().size() == 0)
		cout << endl;
	else
	{
		cout << "Products:" << endl;
		vector<Product*>::iterator ite;
		for (ite = (*restaurants[answer - 1]).get_products().begin(); ite != (*restaurants[answer - 1]).get_products().end(); ite++)
		{
			cout << *(*ite) << endl;
		}
	}
}


void Base::seeAllWorkers()
{

	cout << "ALL WORKERS" << endl << endl;
	cout << "Administrators:" << endl << endl;
	for (int i = 0; i < workers.size(); i++)
	{
		Admin *a = dynamic_cast<Admin *> (workers[i]);
		if (a != NULL)
		{
			a->print();
			cout << endl;
		}
			
		else
			continue;
		
	}
	cout << endl << "Deliverers: " << endl << endl;

	for (int j = 0; j < workers.size(); j++)
	{
		Delivery *d = dynamic_cast<Delivery *> (workers[j]);
		if (d != NULL)
		{
			d->print();
			cout << endl;

		}
			
		else
			continue;
	}
	
}

void Base::seeOneWorker()
{
	cout << "Pick the worker you want to see" << endl;
	vector<Worker*>::iterator it;
	int id = 1, answer;
	for (it = workers.begin(); it != workers.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cin >> answer;
	cout << "INFO" << endl;
	Admin *a = dynamic_cast<Admin *> (workers[answer - 1]);
	if (a != NULL)
	{
		cout << "Administrator" << endl;
	}
	else
		cout << "Deliverer" << endl;
	workers[answer - 1]->print();
	cout << endl;

}
void Base::seeAllDeliverers()
{
	cout << "ALL DELIVERERS" << endl << endl;
	for (int i = 0; i < workers.size(); i++)
	{
		Delivery *d = dynamic_cast<Delivery *> (workers[i]);
		if (d != NULL)
		{
			d->print();
			cout << endl;
		}

	}
}

void Base::seeAllAdministrators()
{
	cout << "ALL ADMINISTRATORS" << endl << endl;
	for (int i = 0; i < workers.size(); i++)
	{
		Admin *a = dynamic_cast<Admin*> (workers[i]);
		if (a != NULL)
		{
			a->print();
			cout << endl;
		}
	}
}

void Base::seeAllOrders()
{
	cout << "ALL ORDERS" << endl << endl;
	vector<Order*>::iterator it;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		cout << *(*it);
		cout << endl;
	}
}

void Base::seeOneOrder()
{
	cout << "Pick the Order you want to see" << endl;
	int op = 1, answer;
	vector<Order*>::iterator it; 
	for (it = orders.begin(); it != orders.end(); it++)
	{
		cout << op << "- ID: " << (*it)->getID();
		cout << endl;
	}
	cin >> answer;
	cout << "INFO" << endl;
	cout << *(orders[answer - 1]);

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

void Base::changeClient() {

	cout << "Pick the client you want to change information about:" << endl;

	vector<Client*>::iterator it;
	bool invalidOption;
	string strChoice;
	int clientChoice;
	unsigned index = 0;
	
	
	do {
		index = 0;
		invalidOption = false;

		for (it = clients.begin(); it != clients.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			getline(cin, strChoice);
			clientChoice = stoi(strChoice);

			if (clientChoice < 1 || clientChoice > clients.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}
		
		cout << endl;

	} while (invalidOption);
	
	clientChoice--; // not to excede the max index available

	clients.at(clientChoice)->edit();
}

void Base::removeClient() {

	cout << "Pick the client you want to change information about:" << endl;

	vector<Client*>::iterator it;
	bool invalidOption;
	string strChoice;
	int clientChoice;
	unsigned index = 0;


	do {
		index = 0;
		invalidOption = false;

		for (it = clients.begin(); it != clients.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			getline(cin, strChoice);
			clientChoice = stoi(strChoice);

			if (clientChoice < 1 || clientChoice > clients.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}

		cout << endl;

	} while (invalidOption);

	clientChoice--; // not to excede the max index available
	
	clients.erase(clients.begin() + clientChoice);

}


// TESTING NEEDED -> need to check if I missed cases dinamically allocated memory vanishing after function ending
void Base::addWorker() {
	
	
	// checks if there is a manager (if it exists, it is the first element of the vector workers
	bool managerExists = (dynamic_cast<Admin*>(workers.at(0))->get_role() == "manager") ? true : false;
	

	// type of worker input
	bool invalidWorkerType;
	string strWorkerType;
	int workerType;
	do {
		invalidWorkerType = false;
		cout << "Adding an Administrator or a Delivery person?" << endl;
		cout << "1. Administrator" << endl;
		cout << "2. Delivery" << endl;
		getline(cin, strWorkerType);

		try {
			workerType = stoi(strWorkerType);
		}
		catch (...) {
			invalidWorkerType = true;
		}
		cout << endl;

	} while (invalidWorkerType);
	

	// name input
	bool invalidName;
	string name;
	do {
		invalidName = false;

		cout << "Name: ";
		getline(cin, name);

		cout << endl;
	} while (invalidName);

	
	
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

		cout << endl;
	} while (invalidNif);

	

	// birthday input
	bool invalidBirthday;
	Date birthday;
	do {
		invalidBirthday = false;

		string fullBirthday;
		cout << "Birthday: ";
		getline(cin, fullBirthday);

		try {
			birthday.parse(fullBirthday);
		}
		catch (...) {
			invalidBirthday = true;
		}

		cout << endl;
	} while (invalidBirthday);

	
	Admin admin;
	Delivery delivery;
	Vehicle vehicle;

	// up until this point, all workers are the same. from now on, they'll follow different "paths"
	bool invalidManagerInput = false;
	string strManagerInput;
	int managerInput;

	bool invalidRoleInput = false;
	string roleInput;
	
	string vehicleBrand;
	string vehicleType;

	bool invalidRegistrationDate = false;
	string strRegistrationDate;
	Date registrationDate; 


		// chose Admin
	if (workerType == 1) {
		// if there isn't a manager yet gives the option that the admin to be the manager
		if (!managerExists) {

			do {
				invalidManagerInput = false;

				cout << "Is this Administrator the Manager? " << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;
				getline(cin, strManagerInput);

				try {
					managerInput = stoi(strManagerInput);
				}
				catch (...) {
					invalidManagerInput = true;
				}

				cout << endl;
			} while (invalidManagerInput);

			// if it chooses to be manager
			if (managerInput == 1) {
				admin.set_role("manager");
			}

			// if it chooses not to be manager
			else {
				do {
					invalidRoleInput = false;

					cout << "Role: ";
					getline(cin, roleInput);

					// if it chose not to be manager it can't then be manager
					if (roleInput == "manager") {
						invalidRoleInput = true;
					}

					cout << endl;
				} while (invalidRoleInput);

				admin.set_role(roleInput);
			}

		}

		// if there is already a manager
		else {

			do {
				invalidRoleInput = false;

				cout << "Role: ";
				getline(cin, roleInput);

				// can't be manager
				if (roleInput == "manager") {
					invalidRoleInput = true;
				}

				cout << endl;
			} while (invalidRoleInput);

			admin.set_role(roleInput);
		}

		admin.set_name(name);
		admin.set_NIF(nif);
		admin.set_birthday(birthday);

		Admin * ptr3 = new Admin;
		*ptr3 = admin;

		if (ptr3->get_role() == "manager") {
			workers.insert(workers.begin(), ptr3);
		}
		else {
			workers.insert(workers.begin() + 1, ptr3);
		}
	}

	// chose Delivery
	else if (workerType == 2) {
		cout << "Vehicle Brand: ";
		getline(cin, vehicleBrand);
		cout << endl;
		cout << "Vehicle Type: ";
		getline(cin, vehicleType);
		cout << endl;
		do {
			invalidRegistrationDate = false;
			cout << "Registration Date: ";
			getline(cin, strRegistrationDate);

			try {
				registrationDate.parse(strRegistrationDate);
			}

			catch (...) {
				invalidRegistrationDate = true;
			}

			cout << endl;
		} while (invalidRegistrationDate);

		vehicle.set_brand(vehicleBrand);
		vehicle.set_type(vehicleType);
		vehicle.set_registrationDate(registrationDate);

		// Vehicle * ptr2 = new Vehicle;
		// *ptr2 = vehicle;
		delivery.set_vehicle(vehicle);

		delivery.set_name(name);
		delivery.set_NIF(nif);
		delivery.set_birthday(birthday);

		Delivery * ptr4 = new Delivery;
		*ptr4 = delivery;
		workers.push_back(ptr4);


	}
	
	
}



// TO DO
void Base::changeWorker() {
	
}



void Base::createRestaurant() {
	
	Restaurant r;

	// HARD CODED FOR BASE PORTO
	vector<string> areaOfInfluence = { "Porto", "Matosinhos", "Vila Nova de Gaia", "Gondomar", "Maia" };
	string baseName = this->getDistrict();
	r.setBase(this);

	// name input
	bool invalidName = false;
	string name;
	do {
		invalidName = false;

		cout << "Name: ";
		getline(cin, name);
	} while (invalidName);

	r.setName(name);

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

	r.setAddress(address);

	// products input
	/**/

	// cuisine types calculated from the vector of products
	/**/

	// price average calculated form the vector of products
	/**/

	Restaurant * ptr6 = new Restaurant;
	*ptr6 = r;

	restaurants.push_back(ptr6);
}