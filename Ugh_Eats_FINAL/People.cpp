#include "People.h"
#include "Base.h"
#include "Restaurant.h"
#include "utils.h"
#include "Exceptions.h"
#include <list>
#include <thread>
#include <chrono>
#include <iomanip>



string MAIN_SEPARATOR = ";;;";
string SEC_SEPARATOR = ";";


Vehicle::Vehicle()
{

}

Vehicle::~Vehicle()
{

}

void Vehicle::print()
{
	cout << "Brand: " << this->brand << endl;
	cout << "Type: " << this->type << endl;
	cout << "Registration date: " << this->registration_date << endl;
	cout << "License plate: " << this->license << endl;
	cout << "Completed trips: " << this->trips << endl;
	cout << "Mileage: " << this->mileage << " Km" << endl;
}

void Vehicle::parse(string str){
	vector<string> parts = utils::split(str, ';');
	brand = parts.at(0);
	type = parts.at(1);
	registration_date.parse(parts.at(2));

	license = parts.at(3);
	trips = stoi(parts.at(4));
	mileage = stoi(parts.at(5));
}

void Vehicle::set_registrationDate(Date_time data)
{
	registration_date = data;

}

void Vehicle::set_type(string tipo)
{
	type = tipo;
}

void Vehicle::set_brand(string marca)
{
	brand = marca;
}

void Vehicle::set_license(string l)
{
	license = l;
}

void Vehicle::set_trips(unsigned t)
{
	trips = t;
}

void Vehicle::set_mileage(double m)
{
	mileage = m;
}

Date_time Vehicle::get_registration_date() const
{
	return registration_date;
}

string Vehicle::get_type() const
{
	return type;
}

string Vehicle::get_brand() const
{
	return brand;
}

string Vehicle::get_license() const
{
	return license;
}

unsigned Vehicle::get_trips() const
{
	return trips;
}

double Vehicle::get_mileage() const
{
	return mileage;
}

void Vehicle::readVehicles(Base * base) {
	
	BST<Vehicle> result;
	auto delivery_men = base->getDeliveryPeople();
	for (auto it = delivery_men.begin(); it != delivery_men.end(); it++) {
		result.insert((*it)->get_vehicle());
	}
	base->setVehicles(result);
}

// Person Class Functions
// ------------------------------------------------

Person::Person()
{

}

Person::~Person()
{

}

void Person::set_name(string nome)
{
	name = nome;
}

void Person::set_NIF(int NIF)
{
	this->NIF = NIF;
}

string Person::get_name() const
{
	return name;
}

int Person::get_NIF() const
{
	return NIF;
}

void Person::print() 
{
	cout << "Name: " << name << endl;
	cout << "NIF: " << NIF << endl;
}

// Worker Class Functions
// ------------------------------------------------

Worker::Worker() {
}

Worker::~Worker() {

}

void Worker::load(string path, Base * base) {
	ifstream workers_text(path);
	try {
		if (!workers_text.is_open()) throw FileOpenErrorException(path);
	}
	catch (FileOpenErrorException & f) {
		cout << f;
		exit(0);
	}

	unordered_set<Admin*, hashAdmin, eqAdmin> admins = Admin::readAdmins(workers_text);

	unordered_set<Delivery*, hashDeliv, eqDeliv> deliverers = Delivery::readDeliverers(workers_text, base);

	base->setAdmins(admins);

	base->setDeliveryPeople(deliverers);

	Vehicle::readVehicles(base);
}


void Worker::set_birthday(Date_time birthday) {
	this->birthday = birthday;
}

void Worker::set_wage(double wage) {
	this->wage = wage;
}

void Worker::set_state(bool isActive) {
	this->isActive = isActive;
}

Date_time Worker::get_birthday() const {
	return birthday;
}

double Worker::get_wage() const {
	return wage;
}

bool Worker::get_state() const {
	return isActive;
}

void Worker::print(){

	Person::print();
	cout << "Birthday: " << birthday << endl;
	cout << "Wage: " << wage << endl;


}

// Admin Class Functions
// ------------------------------------------------

Admin::Admin() {

}

Admin::~Admin() {

}

void Admin::set_role(string role) {
	this->role = role;
}

string Admin::get_role() const {
	return role;
}

unordered_set<Admin*, hashAdmin, eqAdmin> Admin::readAdmins(ifstream & workers_stream) {
	unordered_set<Admin*, hashAdmin, eqAdmin> admins;
	admins.reserve(10);

	string textline;

	while (getline(workers_stream, textline) && textline != MAIN_SEPARATOR) {

		Admin a;

		if (textline == SEC_SEPARATOR) getline(workers_stream, textline);

		a.set_name(textline);

		getline(workers_stream, textline);
		a.set_NIF(stoi(textline));

		getline(workers_stream, textline);
		Date_time d; d.parse(textline);
		a.set_birthday(d);

		getline(workers_stream, textline);
		a.set_wage(stod(textline));

		getline(workers_stream, textline);
		a.set_role(textline);

		
		getline(workers_stream, textline);
		if (textline == "1") a.set_state(true);
		else if (textline == "0") a.set_state(false);
		

		Admin * aPtr = new Admin;
		*aPtr = a;
		admins.insert(aPtr);
	}

	return admins;
}

void Admin::print() { 
	Worker::print();
	cout << "Role: " << role << endl;
}

bool Admin::operator==(const Admin & a) {
	return (
		this->name == a.name &&
		this->NIF == a.NIF &&
		this->role == a.role
		);
}


bool eqAdmin::operator()(const Admin* a1, const Admin* a2) const {
	return (
		a1->get_name() == a2->get_name() &&
		a1->get_NIF() == a2->get_NIF() &&
		a1->get_role() == a2->get_role() &&
		a1->get_wage() == a2->get_wage()
		);
}

int hashAdmin::operator()(const Admin* a1) const {
	int v = 0;

	int nif = a1->get_NIF();

	while (nif > 0) {
		v += 51 * v + nif % 10;

		nif /= 10;
	}

	return v;
}




// Delivery Class Functions
// ------------------------------------------------

Delivery::Delivery() {

}

Delivery::~Delivery() {

}

void Delivery::set_vehicle(Vehicle  veiculo) {
	vehicle = veiculo;
}

void Delivery::set_history(map<int, Order*> historial) {
	history = historial;
}

Vehicle Delivery::get_vehicle() const {
	return vehicle;
}

map<int, Order*> Delivery::get_history() const {
	return history;
}

void Delivery::setDeliveryManPointerOnOrders()
{
	map<int, Order*>::iterator it;
	for (it = history.begin(); it != history.end(); it++) {
		(*it).second->getDeliver()->setDeliveryMan(this);
	}
}

unordered_set<Delivery*, hashDeliv, eqDeliv> Delivery::readDeliverers(ifstream & workers_stream, Base * base) {

	unordered_set<Delivery*, hashDeliv, eqDeliv> deliverers;
	deliverers.reserve(20);

	string textline;

	while (getline(workers_stream, textline)) {

		Delivery del;

		if (textline == SEC_SEPARATOR) getline(workers_stream, textline);

		del.set_name(textline);

		getline(workers_stream, textline);
		del.set_NIF(stoi(textline));

		getline(workers_stream, textline);
		Date_time d; d.parse(textline);
		del.set_birthday(d);

		getline(workers_stream, textline);
		Vehicle v; v.parse(textline);
		del.set_vehicle(v);

		getline(workers_stream, textline);
		del.set_history(base->findOrders(textline));

		getline(workers_stream, textline);
		if (textline == "1") del.set_state(true);
		else if (textline == "0") del.set_state(false);

		Delivery * delPtr = new Delivery;
		*delPtr = del;
		deliverers.insert(delPtr);
	}

	return deliverers;
}

void Delivery::print() {
	Worker::print();
	cout << "Vehicle: " << endl;
	cout << "   Brand: " << vehicle.get_brand() << endl;
	cout << "   Type: " << vehicle.get_type() << endl;
	cout << "   Registration Date: " << vehicle.get_registration_date() << endl;
	cout << "	License plate: " << vehicle.get_license() << endl;
	cout << "	Completed trips: " << vehicle.get_trips() << endl;
	cout << "	Mileage: " << vehicle.get_mileage() << " Km" << endl;
	cout << "History: ";
	if (history.size() == 0)
		cout << "none";
	else
	{
		map<int, Order*>::iterator it;
		for (it = history.begin(); it != history.end(); it++)
		{
			cout << (*it).second->getID() << " ";
		}
	}
	
	cout << endl;
}

double Delivery::calculate_wage() {
	double wage = 0;

	if (this->get_history().size() == 0) return wage;

	for (auto & deliv : this->get_history()) {
		wage += (deliv.second->getDeliveryFee());
	}
	return wage;
}

void Delivery::update_vehicle()
{
	// +1 trip
	// + random mileage

	this->vehicle.set_trips(vehicle.get_trips() + 1);
	double n = 0.5 + (rand() % 100) / (10);
	this->vehicle.set_mileage(vehicle.get_mileage() + n);
}

bool Delivery::operator==(const Delivery & d) {
	return (
		this->name == d.name &&
		this->NIF == d.NIF
		);
}



bool eqDeliv::operator()(const Delivery* d1, const Delivery* d2) const {
	return (
		d1->get_name() == d2->get_name() &&
		d1->get_NIF() == d2->get_NIF() // &&
		// d1->get_wage() == d2->get_wage()
		);
}

int hashDeliv::operator()(const Delivery* d1) const {
	int v = 0;

	int nif = d1->get_NIF();

	while (nif > 0) {
		v += 51 * v + nif % 10;

		nif /= 10;
	}

	return v;
}



// Client Class Functions
// ------------------------------------------------

Client::Client() {

}

Client::~Client() {

}

void Client::load(string path, Base * base) { 
	ifstream clients_text(path);
	try
	{
		if (!clients_text.is_open())
			throw FileOpenErrorException(path);
	}
	catch (FileOpenErrorException & f)
	{
		cout << f;
		exit(0);
	}
	string textline;
	vector <Client*> clients_vec;
	while (getline(clients_text,textline))
	{
		if (textline == SEC_SEPARATOR) getline(clients_text, textline);

		Client cliente;
		cliente.set_name(textline);

		getline(clients_text, textline);
		Address morada;
		morada.parse(textline);
		cliente.set_address(morada);

		cliente.set_base(base);

		getline(clients_text, textline);
		cliente.set_NIF(stoi(textline));

		getline(clients_text, textline);
		cliente.set_orders(base->findOrders(textline));

		Client * ptr = new Client;
		*ptr = cliente;
		clients_vec.push_back(ptr);
	}
	base->setClients(clients_vec);
}

void Client::set_address(Address add) {
	address = add;
}


void Client::set_base(Base * b) {
	base = b;
}

void Client::set_orders(map<int, Order*> orders_vec) {
	orders = orders_vec;
}

Address Client::get_address() const {
	return address;
}

Base * Client::get_base() const {
	return base;
}

map<int, Order*> Client::get_orders() const {
	return orders;
}

void Client::print() { 
	Person::print();
	cout << address << endl;
//	cout << "Base: " << base->getDistrict() << endl;
	cout << "Orders' IDs: ";
	if (orders.size() == 0)
		cout << "none" << endl;
	else {
		map<int, Order*>::iterator it;
		for (it = orders.begin(); it != orders.end(); it++)
		{
			cout << (*it).first << " ";
		}
		cout << endl;
	}
}


void Client::edit(Base * base) {

	utils::clear_screen();

	vector<Client*>::iterator it; // <-- not needed here ?
	bool invalidOption;
	string strChoice;
	unsigned index = 0;

	// Changing the (past) orders or the "value" isn't realistic, right?
	list<string> options = { "Name", "Nif","Address" };


	list<string>::iterator it2;
	int attributeChoice;
	do {
		index = 0;
		invalidOption = false;
		cout << "Pick the field you want to change information of:" << endl;
		for (it2 = options.begin(); it2 != options.end(); ++it2, ++index) {
			cout << index + 1 << ". " << (*it2) << endl;
		}

		try {
			cout << ">> ";
			getline(cin, strChoice);
			//if (cin.eof())
			//{
			//	cin.clear();
			//	return;
			//}
			
			if (!isNumber(strChoice))
				throw InvalidNumberException(strChoice);
			
			if (strChoice != "")
			{
				attributeChoice = stoi(strChoice);
				if (InvalidOptions(options.size(), attributeChoice)) {
					throw InvalidOptionException(attributeChoice);
				}
			}
			else
			{
				invalidOption = true;
				utils::clear_screen();
			}
		}
		catch (InvalidOptionException & o) {
			invalidOption = true;
			cout << o;
			cout << "Try Again!" << endl << endl;
		}
		catch (InvalidNumberException & s)
		{
			invalidOption = true;
			cout << s;
			cout << "Try Again!" << endl << endl;
		}

		

	} while (invalidOption);


	// HARD CODED FOR BASE PORTO
	// vector<string> areaOfInfluence = { "Porto", "Matosinhos", "Vila Nova de Gaia", "Gondomar", "Maia" };
	vector<string> areaOfInf = base->getAreaOfInfluence();
	
	string newName;

	string strNewNif;
	bool invalidNif = false;

	Address newAddress;
	bool invalidAddress = false;
	string fullAddress;
	bool retry = true;

	switch (attributeChoice) {
		// Name
	case 1:
		do
		{
			try
			{
				retry = false;
				cout << "Current Name: " << this->get_name() << endl;
				cout << "Updated Name: ";
				getline(cin, newName);
				if (!isString(newName))
					throw InvalidStringException(newName);
			}
			catch (InvalidStringException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
			}
			
		} while (retry);

		this->set_name(newName);

		break;

		// Nif
	case 2:
		do {
			invalidNif = false;

			cout << "Current Nif: " << this->get_NIF() << endl;
			cout << "Updated Nif: ";
			getline(cin, strNewNif);
			try {
				if (!isNumber(strNewNif) || strNewNif.size() != 9)
					throw InvalidNIFException(strNewNif);
			}

			catch (InvalidNIFException & n) {
				invalidNif = true;
				cout << n;
				cout <<"Try Again!" << endl << endl;
			}
			

			cout << endl;

		} while (invalidNif);
		this->set_NIF(stoi(strNewNif));
		break;

		// Address
	case 3:
		do {
			invalidAddress = false;

			cout << "Current Address: " << this->get_address().str() << endl;
			cout << "Updated Address (District / Town / Street / No / Floor / Latitude / Longitude): " << endl;
			getline(cin, fullAddress);

			try {
				bool teste = address.parse(fullAddress);
				if (!teste)
					throw InvalidAddressException(fullAddress);

				// if it doesnt belong to the are of influence it is considered invalid
				if (find(areaOfInf.begin(), areaOfInf.end(), address.get_town()) == areaOfInf.end()) { // area of influence is empty
					throw InvalidCityException(address.get_town());
				}
			}

			catch (InvalidAddressException & a) {
				invalidAddress = true;
				cout << a;
				cout << "Try Again!" << endl << endl;
			}
			catch (InvalidCityException & c)
			{
				invalidAddress = true;
				cout << c;
				cout << "Try Again!" << endl << endl;
			}

			cout << endl;
		} while (invalidAddress);
		this->set_address(address);
		break;
	}

	cout << endl;
	cout << "Client successfully edited! (Enter to continue)" << endl;
	cout << ">> ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
}

void Client::make_order(Base * b) { 

	// Tasks:
	// - Select Restaurant
	// - Select Products
	// - Create Order / Deliver
	// - Assign delivery guy
	// - Determining if it was successfull
	
	
	/*
	bool invalidSearchOption;
	
	// TO DO -> options for choosing search criteria
	list<string> searchOptions = { "" };
	cout << "Search Options:" << endl;

	do {
		invalidSearchOption = false;




	} while (invalidSearchOption);
	*/



	bool invalidRestaurant;
	string strRestaurant, temp;
	int restaurantChoice;
	double starting, ending;

	vector<Restaurant*> selectedRestaurants = b->getRestaurants();
	bool retry = true;
	do {
		try {
			retry = false;
			cout << "Search Restaurant:" << endl;
			cout << "1. Show all" << endl;
			cout << "2. By town" << endl;
			cout << "3. By price average" << endl;
			cout << "4. By cuisine type" << endl;
			cout << "0. Go Back" << endl;
			cout << ">> ";

			getline(cin, temp);
			if (!isNumber(temp))
				throw InvalidNumberException(temp);
			if (temp != "")
			{
				if (InvalidOptions(4, stoi(temp)))
					throw InvalidOptionException(stoi(temp));
			}
			else
			{
				retry = true;
				utils::clear_screen();

			}
		}
		catch (InvalidNumberException & n)
		{
			retry = true;
			cout << n;
			cout << "Try Again!" << endl << endl;
		}
		catch (InvalidOptionException & o)
		{
			retry = true;
			cout << o;
			cout << "Try Again!" << endl << endl;
		}

	} while (retry);

	utils::clear_screen();

	if (temp == "0") {
		return;
	}

	if (temp == "1") {}

	if (temp == "2") {
		cout << "Type the town you want to search in: "; getline(cin, temp); utils::trim(temp);

		vector<Restaurant*>::iterator it;
		for (it = selectedRestaurants.begin(); it != selectedRestaurants.end();) {
			if ((*it)->get_address().get_town() != temp) it = selectedRestaurants.erase(it);
			else it++;
		}
	}

	if (temp == "3") {
		try {
			cout << "Type start of interval: "; getline(cin, temp);
			if (temp == "") temp = "0";
			starting = stod(temp);
			cout << "\nType end of interval: "; getline(cin, temp);
			if (temp == "") temp = "9999";
			ending = stod(temp);
		}
		catch (...) {
			cout << "\nInvalid price" << endl << ">>";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			return;
		}

		vector<Restaurant*>::iterator it;
		for (it = selectedRestaurants.begin(); it != selectedRestaurants.end();) {
			if ((*it)->get_price_average() < starting || (*it)->get_price_average() > ending) it = selectedRestaurants.erase(it);
			else it++;
		}
	}

	if (temp == "4") {
		cout << "Type desired cuisine types (separated by ':'): "; getline(cin, temp);
		vector<string> selectedTypes = utils::split(temp, ':');
		for (auto & x : selectedTypes) {
			x = utils::defaultcase(x); //set all to default case, which is assured to be the format of the types in the set
			utils::trim(x);	//trim whitespaces
		}
		
		vector<Restaurant*>::iterator it;
		vector<string>::iterator jt;
		for (it = selectedRestaurants.begin(); it != selectedRestaurants.end();) {
			bool typeFound = false;

			for (jt = selectedTypes.begin(); jt != selectedTypes.end(); jt++) {
				if (((*it)->get_cuisine_types().find((*jt))!=(*it)->get_cuisine_types().end())) {
					typeFound = true;
					break;
				}
			}
			if (!typeFound) it = selectedRestaurants.erase(it);
			else it++;
		}
	}

	if (selectedRestaurants.size() == 0) {
		cout << endl << "No restaurants found" << endl;
		cout << ">>";
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		return;
	}


	// choosing restaurant
	utils::clear_screen();
	cout << "Available Restaurants: " << endl;
	do {
		invalidRestaurant = false;

		for (size_t i = 0; i < selectedRestaurants.size(); ++i) {
			cout << i + 1 << ". " << selectedRestaurants.at(i)->get_name() << endl;
		}

		try {
			cout << "0. Go Back" << endl;
			cout << ">> ";
			getline(cin, strRestaurant);

			//if (cin.eof()) {
			//	cin.clear();
			//	return;
			//}
			if (strRestaurant == "0")
			{
				return;
			}
			
			if (!isNumber(strRestaurant))
				throw InvalidNumberException(strRestaurant);

			restaurantChoice = stoi(strRestaurant);

			if (InvalidOptions(b->getRestaurants().size(), restaurantChoice)) {
				throw InvalidOptionException(restaurantChoice);
			}
		}
		catch (InvalidNumberException & n) {
			invalidRestaurant = true;
			cout << n;
			cout << "Try Again!" << endl;
		}
		catch (InvalidOptionException & o)
		{
			invalidRestaurant = true;
			cout << o;
			cout << "Try Again!" << endl;
		}
		cout << endl;
	} while (invalidRestaurant);

	restaurantChoice--; // not to excede the max index available
	
	Restaurant * restPtr = new Restaurant;
	restPtr = selectedRestaurants.at(restaurantChoice);

	cout << endl;

	double fee = (this->get_address().get_town() != b->getAreaOfInfluence().at(0)) ? 5.0 : 3.0;
	cout << "Delivery fee: " << (int)fee << " euros" << endl;

	vector<Product*> pickedProducts;
	bool invalidProduct;
	string strProducts;	

	// choosing product(s)
	
	for (size_t i = 0; i < restPtr->get_products().size(); ++i) {
		cout << i + 1 << ". " << restPtr->get_products().at(i)->get_name();
		cout << " (" << restPtr->get_products().at(i)->get_cuisine_type();
		cout << "), " << restPtr->get_products().at(i)->get_price() << " euros" << endl;
	}
	cout << "Insert the id of the products you wish to order, separating them from each other with ':'" << endl;
	do {
		invalidProduct = false;
		
		getline(cin, strProducts);

		try {
			vector<string> splitProducts = utils::split(strProducts, ':'); 
			for (auto & prod : splitProducts) {
				if (!isNumber(prod))
					throw InvalidNumberException(prod);
				if (InvalidOptions(restPtr->get_products().size(), stoi(prod)) || stoi(prod) == 0)
					throw InvalidOptionException(stoi(prod));
				Product * productPtr = new Product;
				productPtr = b->getRestaurants().at(restaurantChoice)->get_products().at(stoi(prod) - 1);
				pickedProducts.push_back(productPtr);
			}
		}
		catch (InvalidNumberException & n) {
			invalidProduct = true;
			cout << n;
			cout << "Try Again!" << endl << endl;
		}
		catch (InvalidOptionException & o)
		{
			invalidProduct = true;
			cout << o;
			cout << "Try Again!" << endl << endl;
		}
	} while (invalidProduct);
	
	
	int lastId = b->getOrders().rbegin()->first;
	Order *orderPtr = new Order;
	orderPtr->setID(lastId + 1);
	orderPtr->setRestaurant(restPtr);
	orderPtr->setProducts(pickedProducts);

	Date_time dateTimeOrder; dateTimeOrder.setCurrentTime();
	orderPtr->setDateTime(dateTimeOrder); // <-------- adicionar data e hora de entrega

	orderPtr->setDeliveryFee(fee);
	
	Deliver deliver;

	Date_time deliverTime; 
	deliverTime = dateTimeOrder; 
	deliverTime.addRandomTimeInterval();
	deliver.setDateTime(deliverTime);

	deliver.setID(orderPtr->getID()); 
	// deliver.setDateTime() <-------- adicionar data e hora de entrega
	deliver.setDeliveryMan(b->getDeliveryMan()); 
	

	// Success/Insuccess and message
	vector<string> errorReasons = { "traffic", "unknown", "restaurant cancelled the order", "driver couldn't meet client" };
	srand((unsigned int)time(NULL));
	int randomSuccess = rand() % 8; //test different values
	bool delivSuccess = (randomSuccess) ? true : false;
	int randomMessage = rand() % errorReasons.size();
	string insuccessMessage = (delivSuccess) ? "-" : errorReasons.at(randomMessage);
	
	deliver.setSuccess(delivSuccess);
	deliver.setInsuccessMessage(insuccessMessage);

	Deliver * deliverPtr = new Deliver;
	*deliverPtr = deliver;

	orderPtr->setDeliver(deliverPtr);

	// Loading effect
	cout << "\nLoading";
	string loadingDelivery = "...";
	
	for (char c : loadingDelivery) {
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << c << std::flush;
	}

	cout << endl;


	// Updating Client orders
	map<int, Order*> updatedClients = this->get_orders();
	updatedClients.insert(pair<int, Order*>(orderPtr->getID(), orderPtr));
	this->set_orders(updatedClients);

	// Updating Delivery man history
	map<int, Order*> updatedHistory = b->getDeliveryMan()->get_history();
	updatedHistory.insert(pair<int, Order*>(orderPtr->getID(), orderPtr));
	b->getDeliveryMan()->set_history(updatedHistory);

	// Updating Delivery man wage
	double newWage = deliver.getDeliveryMan()->calculate_wage();
	deliver.getDeliveryMan()->set_wage(newWage);

	// Updating Vehicles' stats
	deliver.getDeliveryMan()->update_vehicle();
	
	if (delivSuccess) deliver.getDeliveryMan()->update_vehicle();

	// Updating Base Orders
	map<int, Order*> updatedOrders = b->getOrders();
	updatedOrders.insert(pair<int, Order*>(orderPtr->getID(), orderPtr));
	b->setOrders(updatedOrders);


	if (delivSuccess) {
		string deliv; stringstream d; 
		d << "Successful Delivery! Your order will arrive at " << setw(2) << setfill('0') << deliver.getDateTime().getHours() << ":" << setw(2) << setfill('0') << deliver.getDateTime().getMinutes();
		deliv = d.str();
		for (char c : deliv) {
			this_thread::sleep_for(std::chrono::milliseconds(50));
			cout << c << std::flush;
		}

	}
	else {
		for (char c : "Unsuccessful Delivery (reason: " + insuccessMessage + ")") {
			this_thread::sleep_for(std::chrono::milliseconds(50));
			cout << c << std::flush;
		}
	}

	cout << "\n>> ";
	// cout << "Here: " << updatedOrders.at(updatedOrders.size() - 1)->getProducts().at(0)->get_price();
	cin.clear();
	cin.ignore(INT_MAX,'\n');

	// if (delivSuccess) cout << "Successful Delivery!" << endl;
	// else cout << "Unsuccessful Delivery (" << insuccessMessage << ")" << endl;


	// ---------------------------------------------------------------------------

	//srand(time(NULL));
	//cout << "Pick the Restaurant you want" << endl;
	//int c = 1, answer1;
	//vector<Restaurant*> restaurants = b->getRestaurants();
	//vector<Restaurant*>::iterator it;
	//for (it = restaurants.begin(); it != restaurants.end(); it++)
	//{
	//	cout << c << "- " << (*it)->get_name() << endl;
	//	c++;
	//}
	//cin >> answer1;
	//cout << endl << "Pick the Products you want (Ex: 1 3 ...)" << endl;
	//c = 1;
	//string answer2;
	//vector<Product*> products = restaurants[answer1 - 1]->get_products();
	//vector<Product*>::iterator ite;
	//for (ite = products.begin(); ite != products.end(); ite++)
	//{
	//	cout << c << ": " << endl;
	//	cout << *(*ite);
	//	cout << endl;
	//}
	//getline(cin, answer2);
	//vector<int> answers; // produtos que o cliente quer
	//int a;
	//istringstream ss(answer2);
	//while (ss >> a)
	//	answers.push_back(a);
	//vector<Product*> p;
	//for (int i = 0; i < answers.size(); i++)
	//{
	//	p.push_back(products[answers[i]]);
	//}
	//Order o;
	//int last_id = b->getOrders()[b->getOrders().size() - 1]->getID();
	//o.setID(last_id + 1);
	//o.setBase(b);
	//o.setRestaurant(restaurants[answer1 - 1]);
	//o.setProducts(p);
	//tm * time;
	//o.setDate(Date::getCurrentDate(time));
	//Time t(*time);
	//o.setTime(t);
	////preciso de ver onde checkar os concelhos que fazem parte do distrito ou que s�o adjacentes para a delivery fee
	//Deliver d;
	//d.setID(last_id + 1);
	//int delivery_minutes = (rand() % 60) + 11;
	//tm * dt;
	//if (addTimeAndMinutes(*time, delivery_minutes, dt))
	//{
	//	Date dd;
	//	dd = addOneDay(o.getDate());
	//	d.setDate(dd);
	//	Time time_d(*dt);
	//	d.setTime(time_d);
	//}
	////como testo se foi successful ou n�o?
	//d.setDeliveryMan(b->getDeliveryMan());
	//orders.push_back(&o);
	//d.getDeliveryMan()->get_history().push_back(&o);







}

bool operator<(const Vehicle & l, const Vehicle & r)
{
	if (l.get_trips() == r.get_trips()) return l.get_mileage() < r.get_mileage();
	else return l.get_trips() < r.get_trips();
}

// Technician Class Functions
// ------------------------------------------------

Technician::Technician()
{

}

Technician::~Technician()
{

}

void Technician::set_availability(int a)
{
	availability = a;

}

void Technician::set_maintenance(int m)
{
	maintenance = m;
}

int Technician::get_availability() const
{
	return availability;
}

int Technician::get_maintenance() const
{
	return maintenance;
}

void Technician::print()
{
	Person::print();
	cout << "Availability: " << availability << endl;
	cout << "Maintenance: " << maintenance << endl;
}

 void Technician::load(string path, Base * base)
{
	 ifstream technicians_text(path);
	 try
	 {
		 if (!technicians_text.is_open())
			 throw FileOpenErrorException(path);
	 }
	 catch (FileOpenErrorException & f)
	 {
		 cout << f;
		 exit(0);
	 }
	 string textline;
	 priority_queue<Technician> tec;
	 while (getline(technicians_text, textline))
	 {
		 if (textline == ";")
			 getline(technicians_text, textline);
		 Technician tecnico;
		 tecnico.set_name(textline);
		 getline(technicians_text, textline);
		 tecnico.set_NIF(stoi(textline));
		 getline(technicians_text, textline);
		 tecnico.set_availability(stoi(textline));
		 getline(technicians_text, textline);
		 tecnico.set_maintenance(stoi(textline));
		 tec.push(tecnico);
	 }
	 base->setTechnicians(tec);
}

bool Technician::operator<(const Technician& tec) const
{
	if (availability == tec.availability)
		return maintenance < tec.maintenance;
	else
		return availability > tec.availability;
}