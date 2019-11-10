#include "Base.h"
#include "utils.h"


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
	cout << ">> ";
	cin >> answer;
	if (cin.fail() || answer > clients.size() || cin.eof()) {
		cin.clear();
		return;
	}

	else {
		cout << endl << "INFO" << endl;
		clients.at(answer - 1)->print();
		
		cout << "\n>> ";
		cin.ignore(); //WHY ????
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
	int id = 1, answer;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		cout << id << "- " << (*it)->get_name() << endl;
		id++;
	}
	cout << endl;
	cin >> answer;
	cout << endl << "INFO" << endl;
	cout << (*restaurants.at(answer-1));
	if ((*restaurants.at(answer - 1)).get_products().size() == 0)
		cout << endl;
	else
	{
		cout << "Products:" << endl;
		vector<Product*>::iterator ite;

		// REVERTED CHANGES HERE
		vector<Product*> vec = restaurants[answer - 1]->get_products();
		for (ite = vec.begin(); ite != vec.end(); ite++)
		// for (ite = (*restaurants.at(answer - 1)).get_products().begin(); ite != (*restaurants.at(answer - 1)).get_products().end(); ite++)
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
	Admin *a = dynamic_cast<Admin *> (workers.at(answer - 1));
	if (a != NULL)
	{
		cout << "Administrator" << endl;
	}
	else
		cout << "Deliverer" << endl;
	workers.at(answer - 1)->print();
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
	cout << *(orders.at(answer - 1));

}


void Base::seeProfits()
{
	cout << "Profit for this Base: ";
	vector<Order*>::iterator it;
	float total = 0;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		total += (*it)->getDeliveryFee();
	}
	cout << total << endl;


}

void Base::seeProfitsPerRestaurant()
{
	cout << "Profits per Restaurant" << endl << endl;
	vector< Restaurant *>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		int total = 0;
		vector<Order*>::iterator ite;
		for (ite = orders.begin(); ite != orders.end(); ite++)
		{
			if ((*it)->get_name() == (*ite)->getRestaurant()->get_name())
			{
				total += (*ite)->getDeliveryFee();
			}
		}
		cout << (*it)->get_name() << ": " << total << endl;
	}



}

void Base::seeProfitsPerClient()
{
	cout << "Profits per Client" << endl << endl;
	vector<Client*>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		int total = 0;
		vector<Order*> vec = (*it)->get_orders();
		vector<Order*>::iterator ite;
		for (ite = vec.begin(); ite != vec.end(); ite++)
		{
			total += (*ite)->getDeliveryFee();
		}
		cout << (*it)->get_name() << ": " << total << endl;
	}


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
	int total = 0;
	vector<Order*>::iterator it;
	for (it = orders.begin(); it != orders.end(); it++)
	{
		if (date1 < (*it)->getDate()) // se a data for depois da data do início
		{
			if ((*it)->getDate() < date2) // a data for antes da data do fim
				total += (*it)->getDeliveryFee();
			else if (date2 < (*it)->getDate())  // a data for depois da data do fim
				continue;
			else // a data for igual à data do fim -> testar horas
			{
				if (hour2 < (*it)->getTime())
					continue;
				else
					total += (*it)->getDeliveryFee();
			}
		}
		else if ((*it)->getDate() < date1) // se a data for antes da data de início
			continue;
		else // se a data e a data de início forem iguais->testar horas
		{
			if (date2 < (*it)->getDate()) // se a data do fim for antes da data
				continue;
			else
			{
				if ((*it)->getTime() < hour1) // se a hora da data for antes da hora da data de inicio
					continue;
				else
					total += (*it)->getDeliveryFee();
			}
		}
	}
	cout << "Profit made between the time defined: " << total;
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
			getline(cin, strWorkerChoice);
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
				getline(cin, strAdminAttributeChoice);
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
				getline(cin, strDelivAttributeChoice);
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
				newVehicle.set_brand(newVehicleBrand);
				cout << endl;

				
				cout << "Current Type: " << delivObject->get_vehicle().get_type() << endl;
				cout << "Updated Type: ";
				getline(cin, newVehicleType);
				newVehicle.set_type(newVehicleType);
				cout << endl;

				do {
					invalidRegistrationDate = false;

					cout << "Current Registration Date: " << delivObject->get_vehicle().get_registration_date().get_day()
						<< " / " << delivObject->get_vehicle().get_registration_date().get_month() << " / "
						<< delivObject->get_vehicle().get_registration_date().get_year() << endl;
					cout << "Updated Registration Date: ";
					getline(cin, strNewRegistDate);

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
			getline(cin, strWorkerChoice);
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
	float min, max;
	cout << "Which Price Range do you want?" << endl;
	cout << "Min: ";
	cin >> min;
	cout << "Max: ";
	cin >> max;
	cout << endl << "Products" << endl;
	vector<Restaurant*>::iterator it;
	for (it = restaurants.begin(); it != restaurants.end(); it++)
	{
		float price = (*it)->get_price_average();
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