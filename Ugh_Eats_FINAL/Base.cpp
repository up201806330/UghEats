#include "Base.h"
#include "utils.h"

#include <set>

Base::Base()
{

}

Base::~Base()
{

}

vector<Base*> Base::load(string path){

	Base::load_blacklist();

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
	base_text.close();

	return bases;
}

vector<string> Base::blacklist = {};

void Base::load_blacklist()
{
	ifstream stream("blacklisted.txt"); 

	if (!stream.is_open()) cout << "Error reading";

	string input;

	while (!stream.eof()) {
		getline(stream, input);
		blacklist.push_back(input);
	}

	stream.close();
}

Restaurant * Base::findRestaurant(string str){
	for (auto & restaurant : restaurants)
		if (restaurant->get_name() == str)
			return restaurant;
	return nullptr;
}

map<int, Order*> Base::findOrders(string str) {
	map<int, Order*> result;
	vector<string> ids = utils::split(str, ':');
	for (auto i = 0 ; i < ids.size() ; i++) {
		int x = stoi(ids.at(i));
		
		map<int, Order*>::iterator it = orders.find(x);
		if (it != orders.end()) {
			result.insert(pair<int, Order*>(x, (*it).second));
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

void Base::setOrders(map<int, Order*> orders)
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

const map<int, Order*> & Base::getOrders() const{
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
	string answer;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cout << ">> ";
	getline(cin, answer);
	int input = stoi(answer);
	if (cin.fail() || input > clients.size() || cin.eof()) {
		cin.clear();
		return;
	}

	else {
		cout << endl << "INFO" << endl;
		clients.at(input - 1)->print();
		
		cout << "\n>> ";
		cin.ignore();
	}
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
	int id = 1;
	string answer;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cout << ">> ";

	getline(cin, answer);
	int input = stoi(answer);
	if (cin.fail() || input > restaurants.size() || cin.eof()) {
		cin.clear();
		return;
	}

	else {
		cout << endl << "INFO" << endl;
		cout << (*restaurants.at(input - 1));
		if ((*restaurants.at(input - 1)).get_products().size() == 0)
			cout << endl;
		else
		{
			cout << "Products:" << endl;
			vector<Product*>::iterator ite;

			// REVERTED CHANGES HERE
			vector<Product*> vec = restaurants.at(input - 1)->get_products();
			for (ite = vec.begin(); ite != vec.end(); ite++)
				// for (ite = (*restaurants.at(answer - 1)).get_products().begin(); ite != (*restaurants.at(answer - 1)).get_products().end(); ite++)
			{
				cout << *(*ite) << endl;
			}

		}

		cout << "\n>> ";
		cin.ignore();
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
	string input;
	for (it = workers.begin(); it != workers.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	
	cout << ">> ";
	getline(cin, input);
	answer = stoi(input);
	if (cin.fail() || answer > clients.size() || cin.eof()) {
		cin.clear();
		return;
	}
	else {
		cout << "\nINFO" << endl;
		Admin *a = dynamic_cast<Admin *> (workers.at(answer - 1));
		if (a != NULL) //good practice ?
		{
			cout << "Administrator" << endl;
		}
		else
			cout << "Deliverer" << endl;
		workers.at(answer - 1)->print();
		
		cout << "\n>> ";
		cin.ignore();
	}

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
	map<int, Order*>::iterator it;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		cout << *((*it).second);
		cout << endl;
	}

	cout << "\n>> ";
	cin.ignore();
}

void Base::seeOneOrder()
{
	cout << "Pick the Order you want to see" << endl;
	int op = 1, answer;
	string input;
	map<int, Order*>::iterator it;
	vector<int> temporary_ids;

	for (it = orders.begin(); it != orders.end(); it++)
	{
		cout << op << "- ID: " << (*it).second->getID();
		cout << endl;
		temporary_ids.push_back((*it).second->getID());
	}
	cout << ">> ";
	getline(cin, input);
	answer = stoi(input);
	if (cin.fail() || answer > orders.size() || cin.eof()) {
		cin.clear();
		return;
	}
	else {
		cout << "INFO" << endl;
		cout << *(orders.at(temporary_ids.at(answer - 1)));

		cout << "\n>> ";
		cin.ignore();
	}
}


void Base::seeProfits()
{
	cout << "Profit for this Base: ";
	map<int, Order*>::iterator it;
	double total = 0;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		total += (*it).second->getDeliveryFee();
	}
	cout << total << endl;

	cout << "\n>> ";
	cin.ignore();
}

void Base::seeProfitsPerRestaurant()
{
	cout << "Profits per Restaurant" << endl << endl;
	vector< Restaurant *>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		double total = 0;
		map<int, Order*>::iterator ite;
		for (ite = orders.begin(); ite != orders.end(); ite++)
		{
			if ((*it)->get_name() == (*ite).second->getRestaurant()->get_name())
			{
				total += (*ite).second->getDeliveryFee();
			}
		}
		cout << (*it)->get_name() << ": " << total << endl;
	}

	cout << "\n>> ";
	cin.ignore();

}

void Base::seeProfitsPerClient()
{
	cout << "Profits per Client" << endl << endl;
	vector<Client*>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		double total = 0;
		map<int, Order*> vec = (*it)->get_orders();
		map<int, Order*>::iterator ite;
		for (ite = vec.begin(); ite != vec.end(); ite++)
		{
			total += (*ite).second->getDeliveryFee();
		}
		cout << (*it)->get_name() << ": " << total << endl;
	}

	cout << "\n>> ";
	cin.ignore();
}

void Base::seeProfitsPerTime()
{
	string datei, datef, houri, hourf;
	cout << "Type in the initial date (dd/mm/yyyy)" << endl;
	getline(cin, datei);
	Date date1;
	date1.parse(datei);
	cout << "Type in the initial hours (hh:mm:ss)" << endl;
	getline(cin, houri);
	Time hour1;
	hour1.parse(houri);
	cout << "Type in the final date (dd/mm/yyyy)" << endl;
	getline(cin, datef);
	Date date2;
	date2.parse(datef);
	cout << "Type in the final hours (hh:mm:ss)" << endl;
	getline(cin, hourf);
	Time hour2;
	hour2.parse(hourf);
	double total = 0;
	map<int, Order*>::iterator it;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		if (date1 < (*it).second->getDate()) // se a data for depois da data do início
		{
			if ((*it).second->getDate() < date2) // a data for antes da data do fim
				total += (*it).second->getDeliveryFee();
			else if (date2 < (*it).second->getDate())  // a data for depois da data do fim
				continue;
			else // a data for igual à data do fim -> testar horas
			{
				if (hour2 < (*it).second->getTime())
					continue;
				else
					total += (*it).second->getDeliveryFee();
			}
		}
		else if ((*it).second->getDate() < date1) // se a data for antes da data de início
			continue;
		else // se a data e a data de início forem iguais->testar horas
		{
			if (date2 < (*it).second->getDate()) // se a data do fim for antes da data
				continue;
			else
			{
				if ((*it).second->getTime() < hour1) // se a hora da data for antes da hora da data de inicio
					continue;
				else
					total += (*it).second->getDeliveryFee();
			}
		}
	}
	cout << "Profit made in the defined period: " << total;

	cout << "\n>> ";
	cin.ignore();
}




void Base::changeBase() {
	vector<string> options = { "address" };

	bool invalidOption;
	string strChoice;
	unsigned index = 0;

	cout << "Pick the field you want to change information of:" << endl;
	vector<string>::iterator optionsIt;
	int attributeChoice;
	do {
		index = 0;
		invalidOption = false;

		for (optionsIt = options.begin(); optionsIt != options.end(); ++optionsIt, ++index) {
			cout << index + 1 << ". " << (*optionsIt) << endl;
		}

		try {
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return ;
			}

			attributeChoice = stoi(strChoice);

			if (attributeChoice < 1 || attributeChoice > options.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}

		cout << endl;

	} while (invalidOption);

	// HARD CODED FOR BASE PORTO
	vector<string> areaOfInfluence = { "Porto", "Matosinhos", "Vila Nova de Gaia", "Gondomar", "Maia" };

	Address newAddress;
	bool invalidAddress = false;
	string fullAddress;

	switch (attributeChoice) {
		// Address
		case 1:
			do {
				invalidAddress = false;

				cout << "Current Address: " << this->getAddress().str() << endl;
				cout << "Updated Address (Town / District / Street / No / Floor / Latitude / Longitude): " << endl;
				getline(cin, fullAddress);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				try {
					address.parse(fullAddress);

					// if it doesnt belong to the are of influence it is considered invalid
					if (find(areaOfInfluence.begin(), areaOfInfluence.end(), address.get_district()) == areaOfInfluence.end()) {
						invalidAddress = true;
						cout << "Invalid District (must be in area of influence of the base)" << endl;
					}
				}

				catch (...) {
					invalidAddress = true;
				}

				cout << endl;
			} while (invalidAddress);
			this->setAddress(address);
			
			break;

	}

	cout << "Based successfully edited! (Enter to continue)" << endl;
	cout << ">> ";
	cin.ignore();
}




void Base::addClient() { //usar em try para apanhar execao blacklisted

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

		if (cin.eof()) {
			cin.clear();
			return;
		}
		
	} while (invalidName);

	c.set_name(name);
	if (find(Base::blacklist.begin(), Base::blacklist.end(), c.get_name()) != Base::blacklist.end()) {
		cout << "Client is blacklisted and cannot register" << endl;
		cout << ">> ";
		cin.ignore();
		return;
		//excecao aqui
	}


	// nif input
	bool invalidNif;
	string strNif;
	int nif;
	do {
		invalidNif = false;
		
		cout << "NIF: ";
		getline(cin, strNif);

		if (cin.eof()) {
			cin.clear();
			return;
		}

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
		cout << "Address (Town / District / Street / No / Floor / Latitude / Longitude):" << endl;
		getline(cin, fullAddress);

		if (cin.eof()) {
			cin.clear();
			return;
		}

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
	map<int, Order*> clientOrders = {};

	c.set_orders(clientOrders);


	Client * ptr = new Client;
	*ptr = c;
	
	clients.push_back(ptr);

	cout << endl;
	cout << "Client added successfully" << endl;
	cout << ">> ";
	cin.ignore();
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
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

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

	cout << "Pick the client you want to remove:" << endl;

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
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

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
	
	//loop a apagar todas as orders dele !!

	clients.erase(clients.begin() + clientChoice);

	cout << "Client removed successfully" << endl;
	cout << ">> ";
	cin.ignore();

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
		cout << ">> ";
		getline(cin, strWorkerType);

		if (cin.eof()) {
			cin.clear();
			return;
		}

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

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
				cout << ">> ";
				getline(cin, strManagerInput);

				if (cin.eof()) {
					cin.clear();
					return;
				}

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

					if (cin.eof()) {
						cin.clear();
						return;
					}

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

				if (cin.eof()) {
					cin.clear();
					return;
				}

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

		cout << endl;
		cout << "Vehicle Type: ";
		getline(cin, vehicleType);

		if (cin.eof()) {
			cin.clear();
			return;
		}

		cout << endl;
		do {
			invalidRegistrationDate = false;
			cout << "Registration Date: ";
			getline(cin, strRegistrationDate);

			if (cin.eof()) {
				cin.clear();
				return;
			}

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
	
	cout << endl;
	cout << "Worker successfully added! (Enter to continue)" << endl;
	cout << ">> ";
	cin.ignore();
}



void Base::changeWorker() {

	Admin *adminCheck;
	Delivery *deliveryCheck;
	int firstDeliveryIndex = 0;
	bool foundFirstDelivery = false;
	bool invalidOption = false;
	string strWorkerChoice;
	int workerChoice;


	cout << "Pick the worker you want to change information about:" << endl;

	do {
		invalidOption = false;
		foundFirstDelivery = false;

		for (size_t i = 0; i < workers.size(); i++) {
			adminCheck = dynamic_cast<Admin*> (workers.at(i));
			if (adminCheck != NULL) {
				firstDeliveryIndex++;
				// if i == 0, then i converts to false, so !i == true
				// 0 converts to false, any other convertable to bool convert to true
				if (!i) {
					cout << "Administrators" << endl;
					cout << i + 1 << ". " << adminCheck->get_name() << " (" << adminCheck->get_role() << ")" << endl;
				}
				else {
					cout << i + 1 << ". " << adminCheck->get_name() << endl;
				}

			}
			else {
				deliveryCheck = dynamic_cast<Delivery*> (workers.at(i));
				if (!foundFirstDelivery) {
					foundFirstDelivery = true;
					cout << "\nDeliverers" << endl;
				}
				cout << i + 1 << ". " << deliveryCheck->get_name() << endl;
			}
		}

		// cout << "\nFirst Index Delivery: " << firstDeliveryIndex << endl;

		try {
			cout << ">> ";
			getline(cin, strWorkerChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			workerChoice = stoi(strWorkerChoice);

			if (workerChoice < 1 || workerChoice > workers.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}
		cout << endl;

		// cout << dynamic_cast<Delivery*>(workers.at(3))->get_vehicle().get_brand() << endl;

	} while (invalidOption);

	workerChoice--; // not to excede the max index available



	utils::clear_screen();



	// cout << workers.at(workerChoice)->get_name() << endl;
	unsigned index = 0;
	string strAdminAttributeChoice;
	int adminAttributeChoice;

	string strDelivAttributeChoice;
	int delivAttributeChoice;

	vector<string>::iterator it1;
	vector<string> adminOptions = { "Name", "Nif", "Birthday", "Wage", "Role" };
	vector<string> deliveryOptions = { "Name", "Nif", "Birthday", "Wage", "Vehicle" };
	cout << "Pick the field you want to change information of:" << endl;
	// cout << dynamic_cast<Delivery*>(workers.at(workerChoice))->get_vehicle().get_brand() << endl;
	// auto x = dynamic_cast<Delivery*>(workers.at(workerChoice));
	// Admin newAdmin;
	// Delivery newDelivery;

	auto adminObject = dynamic_cast<Admin*>(workers.at(workerChoice));
	auto delivObject = dynamic_cast<Delivery*>(workers.at(workerChoice));

	string newName;

	string strNewNif;
	int newNif = 0;
	bool invalidNif = false;

	bool invalidBirthday = false;
	Date newBirthday;
	string fullBirthday;

	bool invalidWage = false;
	string strNewWage;
	int newWage;

	bool adminExists = false;
	bool invalidRole = false;
	string newRole;

	bool invalidRegistrationDate = false;
	string newVehicleBrand;
	string newVehicleType;
	string strNewRegistDate;
	Date newRegistDate;
	Vehicle newVehicle;

	// worker chosen is an Admin
	if (workerChoice < firstDeliveryIndex) {
		do {
			index = 0;
			invalidOption = false;

			for (it1 = adminOptions.begin(); it1 != adminOptions.end(); ++it1, ++index) {
				cout << index + 1 << ". " << (*it1) << endl;
			}

			try {
				cout << ">> ";
				getline(cin, strAdminAttributeChoice);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				adminAttributeChoice = stoi(strAdminAttributeChoice);

				if (adminAttributeChoice < 1 || adminAttributeChoice > adminOptions.size()) {
					invalidOption = true;
				}
			}

			catch (...) {
				invalidOption = true;
			}

			cout << endl;
		} while (invalidOption);


		switch (adminAttributeChoice) {

			// Name
			case 1:
				cout << "Current Name: " << adminObject->get_name() << endl;
				cout << "Updated Name: ";
				getline(cin, newName);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				cout << endl;
				adminObject->set_name(newName);
				break;

			// Nif
			case 2:
				do {
					invalidNif = false;

					cout << "Current Nif: " << adminObject->get_NIF() << endl;
					cout << "Updated Nif: ";
					getline(cin, strNewNif);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newNif = stoi(strNewNif);
					}

					catch (...) {
						invalidNif = true;
					}
					break;

					cout << endl;
				} while (invalidNif);
				adminObject->set_NIF(newNif);
				break;

			// Birthday
			case 3:
				do {
					invalidBirthday = false;

					cout << "Current Birthday: " << adminObject->get_birthday().get_day() << " / "
						<< adminObject->get_birthday().get_month() << " / " << adminObject->get_birthday().get_year() << endl;
					cout << "Updated Birthday: ";
					getline(cin, fullBirthday);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newBirthday.parse(fullBirthday);
					}
					catch (...) {
						invalidBirthday = true;
					}

					cout << endl;

					cout << endl;
				} while (invalidBirthday);
				adminObject->set_birthday(newBirthday);
				break;

			// Wage
			case 4:
				do {
					invalidWage = false;

					cout << "Current Wage: " << adminObject->get_wage() << endl;
					cout << "Updated Wage: ";
					getline(cin, strNewWage);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newWage = stoi(strNewWage);
					}
					catch (...) {
						invalidWage = true;
					}

					cout << endl;
				} while (invalidWage);
				adminObject->set_wage(newWage);
				break;

			// Role
			case 5:
				adminExists = ((dynamic_cast<Admin*>(workers.at(0))->get_role() == "manager") && (workerChoice != 0)) ? true : false;
				do {
					cout << "Current role: " << adminObject->get_role() << endl;
					cout << "Updated role: ";
					getline(cin, newRole);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					if (newRole == "manager" && adminExists) {
						invalidRole = true;
					}

					cout << endl;
				} while (invalidRole);
				adminObject->set_role(newRole);
				break;
		}
	}

	// worker chosen is an Delivery
	else if (workerChoice >= firstDeliveryIndex) {

		do {
			index = 0;
			invalidOption = false;

			for (it1 = deliveryOptions.begin(); it1 != deliveryOptions.end(); ++it1, ++index) {
				cout << index + 1 << ". " << (*it1) << endl;
			}

			try {
				cout << ">> ";
				getline(cin, strDelivAttributeChoice);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				delivAttributeChoice = stoi(strDelivAttributeChoice);

				if (delivAttributeChoice < 1 || delivAttributeChoice > deliveryOptions.size()) {
					invalidOption = true;
				}
			}

			catch (...) {
				invalidOption = true;
			}

			cout << endl;
		} while (invalidOption);



		switch (delivAttributeChoice) {

			// Name
			case 1:
				cout << "Current Name: " << delivObject->get_name() << endl;
				cout << "Updated Name: ";
				getline(cin, newName);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				cout << endl;
				delivObject->set_name(newName);
				break;

			// Nif
			case 2:
				do {
					invalidNif = false;

					cout << "Current Nif: " << delivObject->get_NIF() << endl;
					cout << "Updated Nif: ";
					getline(cin, strNewNif);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newNif = stoi(strNewNif);
					}

					catch (...) {
						invalidNif = true;
					}
					break;

					cout << endl;
				} while (invalidNif);
				delivObject->set_NIF(newNif);
				break;

			// Birthday
			case 3:
				do {
					invalidBirthday = false;

					cout << "Current Birthday: " << delivObject->get_birthday().get_day() << " / "
						<< delivObject->get_birthday().get_month() << " / " << delivObject->get_birthday().get_year() << endl;
					cout << "Updated Birthday: ";
					getline(cin, fullBirthday);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newBirthday.parse(fullBirthday);
					}
					catch (...) {
						invalidBirthday = true;
					}

					cout << endl;

					cout << endl;
				} while (invalidBirthday);
				delivObject->set_birthday(newBirthday);
				break;

			// Wage
			case 4:
				do {
					invalidWage = false;

					cout << "Current Wage: " << delivObject->get_wage() << endl;
					cout << "Updated Wage: ";
					getline(cin, strNewWage);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newWage = stoi(strNewWage);
					}
					catch (...) {
						invalidWage = true;
					}

					cout << endl;
				} while (invalidWage);
				delivObject->set_wage(newWage);
				break;

			// Vehicle
			case 5:
				cout << "Current Brand: " << delivObject->get_vehicle().get_brand() << endl;
				cout << "Updated Brand: ";
				getline(cin, newVehicleBrand);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				newVehicle.set_brand(newVehicleBrand);
				cout << endl;

				
				cout << "Current Type: " << delivObject->get_vehicle().get_type() << endl;
				cout << "Updated Type: ";
				getline(cin, newVehicleType);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				newVehicle.set_type(newVehicleType);
				cout << endl;

				do {
					invalidRegistrationDate = false;

					cout << "Current Registration Date: " << delivObject->get_vehicle().get_registration_date().get_day()
						<< " / " << delivObject->get_vehicle().get_registration_date().get_month() << " / "
						<< delivObject->get_vehicle().get_registration_date().get_year() << endl;
					cout << "Updated Registration Date: ";
					getline(cin, strNewRegistDate);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					try {
						newRegistDate.parse(strNewRegistDate);
					}

					catch (...) {
						invalidRegistrationDate = true;
					}
					cout << endl;
				} while (invalidRegistrationDate);
				newVehicle.set_registrationDate(newRegistDate);

				// Vehicle * ptrNewVehicle = new Vehicle;
				// *ptrNewVehicle = newVehicle;
				delivObject->set_vehicle(newVehicle);
				break;
		
		}
	}

	cout << endl;
	cout << "Worker successfully edited! (Enter to continue)" << endl;
	cout << ">> ";
	cin.ignore();
}


void Base::removeWorker() {

	Admin *adminCheck;
	Delivery *deliveryCheck;
	int firstDeliveryIndex = 0;
	bool foundFirstDelivery = false;
	bool invalidOption = false;
	string strWorkerChoice;
	int workerChoice;


	cout << "Pick the worker you want to remove:" << endl;

	do {
		invalidOption = false;
		foundFirstDelivery = false;

		for (size_t i = 0; i < workers.size(); i++) {
			adminCheck = dynamic_cast<Admin*> (workers.at(i));
			if (adminCheck != NULL) {
				firstDeliveryIndex++;
				// if i == 0, then i converts to false, so !i == true
				// 0 converts to false, any other convertable to bool convert to true
				if (!i) {
					cout << "Administrators" << endl;
					cout << i + 1 << ". " << adminCheck->get_name() << " (" << adminCheck->get_role() << ")" << endl;
				}
				else {
					cout << i + 1 << ". " << adminCheck->get_name() << endl;
				}

			}
			else {
				deliveryCheck = dynamic_cast<Delivery*> (workers.at(i));
				if (!foundFirstDelivery) {
					foundFirstDelivery = true;
					cout << "\nDeliverers" << endl;
				}
				cout << i + 1 << ". " << deliveryCheck->get_name() << endl;
			}
		}

		// cout << "\nFirst Index Delivery: " << firstDeliveryIndex << endl;

		try {
			cout << ">> ";
			getline(cin, strWorkerChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			workerChoice = stoi(strWorkerChoice);

			if (workerChoice < 1 || workerChoice > workers.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}
		cout << endl;

		// cout << dynamic_cast<Delivery*>(workers.at(3))->get_vehicle().get_brand() << endl;

	} while (invalidOption);

	workerChoice--; // not to excede the max index available

	workers.erase(workers.begin() + workerChoice);

	cout << "Worker removed successfully" << endl;
	cout << ">> ";
	cin.ignore();

}


void Base::addRestaurant() {

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

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

		if (cin.eof()) {
			cin.clear();
			return;
		}

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
	bool invalidProduct;
	string strProduct;
	Product product;
	vector<Product*> productsVec;

	bool notEnded = true;

	cout << "List of Products (Name : Type : Price), type 'done' to stop input" << endl;

	do {
		
		do {
			invalidProduct = false;

			getline(cin, strProduct);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			if (strProduct == "done") {
				notEnded = false;
				break;
			}

			try {
				product.parse(strProduct);
				Product * productPtr = new Product;
				*productPtr = product;
				productsVec.push_back(productPtr);
			}
			catch (...) {
				invalidProduct = true;
				cout << "Invalid entry" << endl;
			}
		} while (invalidProduct);

	} while (notEnded);

	r.setProducts(productsVec);


	// cuisine types
	set<string> cuisineTypes;
	for (auto & prod : r.get_products()) {
		cuisineTypes.insert(prod->get_cuisine_type());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// r.setCuisineTypes(cuisineTypes);  <-- make Cuisine types a set ?
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	// price average calculated form the vector of products
	r.setPriceAverage();

	Restaurant * restaurantPtr = new Restaurant;
	*restaurantPtr = r;
	restaurants.push_back(restaurantPtr);

	cout << endl;
	cout << "Restaurant successfully added! (Enter to continue)" << endl;
	cout << ">> ";
	cin.ignore();
}

void Base::changeRestaurant() {

	vector<Restaurant*>::iterator it;
	bool invalidOption;
	string strChoice;
	int restaurantChoice;
	unsigned index = 0;

	cout << "Pick the restaurant you want to change information about:" << endl;

	do {
		index = 0;
		invalidOption = false;

		for (it = restaurants.begin(); it != restaurants.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			restaurantChoice = stoi(strChoice);

			if (restaurantChoice < 1 || restaurantChoice > restaurants.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}

		cout << endl;

	} while (invalidOption);

	restaurantChoice--;	// not to excede the max index available

	vector<string> options = { "name", "address", "products" };
	cout << "Pick the field you want to change information of:" << endl;

	vector<string>::iterator it2;
	int attributeChoice;
	do {
		index = 0;
		invalidOption = false;

		for (it2 = options.begin(); it2 != options.end(); ++it2, ++index) {
			cout << index + 1 << ". " << (*it2) << endl;
		}

		try {
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			attributeChoice = stoi(strChoice);

			if (attributeChoice < 1 || attributeChoice > options.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}

		cout << endl;

	} while (invalidOption);



	// HARD CODED FOR BASE PORTO
	vector<string> areaOfInfluence = { "Porto", "Matosinhos", "Vila Nova de Gaia", "Gondomar", "Maia" };

	string newName;
	bool invalidName;

	Address newAddress;
	bool invalidAddress = false;
	string fullAddress;

	bool invalidProduct;
	string strProduct;
	Product product;
	vector<Product*> productsVec;
	bool notEnded = true;

	set<string> cuisineTypes;

	switch (attributeChoice) {
		// Name
		case 1:
			do {
				invalidName = false;
				cout << "Current Name: " << restaurants.at(restaurantChoice)->get_name() << endl;
				cout << "Updated Name: ";
				getline(cin, newName);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				cout << endl;
				restaurants.at(restaurantChoice)->setName(newName);
			} while (invalidName);
			break;

		// Address
		case 2:
			do {
				invalidAddress = false;

				cout << "Current Address:\n" << restaurants.at(restaurantChoice)->get_address() << endl;
				cout << "Updated Address (Town / District / Street / No / Floor / Latitude / Longitude): " << endl;
				getline(cin, fullAddress);

				if (cin.eof()) {
					cin.clear();
					return;
				}

				try {
					newAddress.parse(fullAddress);

					// if it doesnt belong to the are of influence it is considered invalid
					if (find(areaOfInfluence.begin(), areaOfInfluence.end(), address.get_district()) == areaOfInfluence.end()) {
						invalidAddress = true;
						cout << "Invalid District (must be in area of influence of the base)" << endl;
					}
				}

				catch (...) {
					invalidAddress = true;
				}

				cout << endl;
			} while (invalidAddress);

			cout << endl;
			restaurants.at(restaurantChoice)->setAddress(newAddress);
			break;

		// Products
		case 3:
			cout << "Current List of Products:" << endl;

			for (auto & prod : restaurants.at(restaurantChoice)->get_products()) {
				cout << prod->get_name() << " : " << prod->get_cuisine_type() << " : " << prod->get_price() << endl;
			}

			cout << endl;
			cout << "Updated List of Products (Name : Type : Price), type 'done' to stop input" << endl;

			do {
				do {
					invalidProduct = false;

					getline(cin, strProduct);

					if (cin.eof()) {
						cin.clear();
						return;
					}

					if (strProduct == "done") {
						notEnded = false;
						break;
					}

					try {
						product.parse(strProduct);
						Product * productPtr = new Product;
						*productPtr = product;
						productsVec.push_back(productPtr);
					}
					catch (...) {
						invalidProduct = true;
						cout << "Invalid entry" << endl;
					}
				} while (invalidProduct);
				
			} while (notEnded);
			restaurants.at(restaurantChoice)->setProducts(productsVec);

			// updating cuisine types
			
			for (auto & prod : restaurants.at(restaurantChoice)->get_products()) {
				cuisineTypes.insert(prod->get_cuisine_type());
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// restaurants.at(restaurantChoice)->setCuisineTypes(cuisineTypes);  <-- make Cuisine types a set ?
			// 
			// implement setCuisineTypes like the setPriceAverage ?
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// updating price average
			restaurants.at(restaurantChoice)->setPriceAverage();

			break;
	}

	cout << endl;
	cout << "Restaurant successfully edited! (Enter to continue)" << endl;
	cout << ">> ";
	cin.ignore();
}


void Base::removeRestaurant() {

	vector<Restaurant*>::iterator it;
	bool invalidOption;
	string strChoice;
	int restaurantChoice;
	unsigned index = 0;

	cout << "Pick the restaurant you want to change information about:" << endl;

	do {
		index = 0;
		invalidOption = false;

		for (it = restaurants.begin(); it != restaurants.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			cout << ">> ";
			getline(cin, strChoice);

			if (cin.eof()) {
				cin.clear();
				return;
			}

			restaurantChoice = stoi(strChoice);

			if (restaurantChoice < 1 || restaurantChoice > restaurants.size()) {
				invalidOption = true;
			}
		}
		catch (...) {
			invalidOption = true;
		}

		cout << endl;

	} while (invalidOption);

	restaurantChoice--;	// not to excede the max index available

	restaurants.erase(restaurants.begin() + restaurantChoice);

	cout << "Restaurant removed successfully" << endl;
	cout << ">> ";
	cin.ignore();
}


void Base::searchForRestaurant() 
{
	string name;
	cout << "Which Restaurant do you want?" << endl;
	getline(cin, name);
	//sort(restaurants.begin(), restaurants.end(), sortRule<Restaurant *>);
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++) // Sequencial Search
	{
	    if ((*it)->get_name() == name)
		{
			cout << "Products Available" << endl;
			vector<Product*> vec = (*it)->get_products();
			vector<Product*>::iterator ite;
			for (ite = vec.begin(); ite != vec.end(); ite++)
			{
				cout << *(*ite);
				cout << endl;
			}
			cout << endl;
		}
	}
}



void Base::searchForGeographicArea()
{
	string city;
	cout << "Which City do you want?" << endl;
	getline(cin, city);
	cout << "Products Available" << endl << endl;
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++) // Sequencial Search
	{
		if ((*it)->get_address().get_town() == city)
		{
			cout << (*it)->get_name() << ": " << endl;
			vector<Product*> vec = (*it)->get_products();
			vector<Product*>::iterator ite;
			for (ite = vec.begin(); ite != vec.end(); ite++)
			{
				cout << *(*ite);
				cout << endl;
			}
			cout << endl;
		}
	}
}



void Base::searchForPriceRange() // o price range não tá a ter casas decimais
{
	double min, max;
	cout << "Which Price Range do you want?" << endl;
	cout << "Min: ";
	cin >> min;
	cout << "Max: ";
	cin >> max;
	cout << endl << "Products" << endl;
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		double price = (*it)->get_price_average();
		if (price >= min && price <= max)
		{
			cout << (*it)->get_name() << endl;
			vector<Product*> vec = (*it)->get_products();
			vector<Product*>::iterator ite;
			for (ite = vec.begin(); ite != vec.end(); ite++)
			{
				cout << *(*ite);
				cout << endl;
			}
		}
	}
}


void Base::searchForCuisineTypes()
{
	string type;
	cout << "Which Cuisine Type do you want?" << endl;
	getline(cin, type);
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		vector<Product*> vec = (*it)->get_products();
		vector<Product*>::iterator ite;
		int count = 0;
		for (ite = vec.begin(); ite != vec.end(); ite++)
		{
			if ((*ite)->get_cuisine_type() == type)
			{
				if (!count)
				{
					cout << (*it)->get_name() << ": " << endl;
					count++;
				}
				cout << *(*ite);
				cout << endl;
			}
				
		}

	}
}

Delivery* Base::getDeliveryMan()
{
	//buscar o delivery man c menos historial feito
	vector<Delivery*> delivery_men;
	for (int i = 0; i < workers.size(); i++)
	{
		Delivery *d = dynamic_cast<Delivery *> (workers[i]);
		if (d != NULL)
		{
			delivery_men.push_back(d);
		}
	}
	int comp = delivery_men[0]->get_history().size();
	Delivery * result = delivery_men[0];
	vector<Delivery*>::iterator it;
	for (it = delivery_men.begin(); it != delivery_men.end(); it++)
	{
		if ((*it)->get_history().size() < comp)
		{
			comp = (*it)->get_history().size();
			result = (*it);
		}
	}
	return result;
}
