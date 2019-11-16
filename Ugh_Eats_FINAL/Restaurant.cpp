#include "Restaurant.h"
#include "Base.h"
#include "utils.h"
#include <iomanip>
#include <list>

using namespace std;

string SEPARATOR = ";;;";

Product::Product() {

}

Product::~Product() {

}

bool Product::parse(string str) {
	vector<string> parts = utils::split(str, ':');
	if (parts.size() != 3)
		return false;
	name = parts.at(0);
	cuisine_type = parts.at(1);
	if (!isString(name) || !isString(cuisine_type))
		return false;
	if (!isNumber(parts.at(2)))
		return false;
	price = stoi(parts.at(2));
	return true;

}

void Product::setName(string n) {
	name = n;
}

void Product::setCuisineType(string ct) {
	cuisine_type = ct;
}

void Product::setPrice(size_t p) {
	price = p;
}


string Product::get_name() const {
	return name;
}

string Product::get_cuisine_type() const {
	return cuisine_type;
}

size_t Product::get_price() const {
	return price;
}


ostream & operator<<(ostream & out, const Product & p) {
	out << "   Name: " << p.name << endl;
	out << "   Cuisine Type: " << p.cuisine_type << endl;
	out << "   Price: " << p.price << endl;
	return out;
}



Restaurant::Restaurant() {

}

Restaurant::~Restaurant() {

}

void Restaurant::load(string path, Base * base){
	ifstream restaurants_text(path);
	try {
		if (!restaurants_text.is_open())
			throw FileOpenErrorException(path);
	}
	catch (FileOpenErrorException & f) {
		cout << f;
		exit(0);
	}

	string textline = "";
	vector<Restaurant*> restaurants_vec;
	while (getline(restaurants_text, textline)) {

		if (textline == SEPARATOR) getline(restaurants_text, textline);
		Restaurant restaurant;
		restaurant.setName(textline);

		getline(restaurants_text, textline);
		Address addr;
		addr.parse(textline);
		restaurant.setAddress(addr);

		vector<Product*> prods;

		while (getline(restaurants_text, textline)) {
			if (textline == ";;;") break;
			Product d;

			d.parse(textline);

			Product * ptr2 = new Product;
			*ptr2 = d;
			prods.push_back(ptr2);
		}
		restaurant.setProducts(prods);
		
		// cuisine types
		set<string> cuisineTypes;
		for (auto & prod : restaurant.get_products()) {
			cuisineTypes.insert(prod->get_cuisine_type());
		}
		restaurant.setCuisineTypes(cuisineTypes);

		restaurant.setPriceAverage();

		Restaurant * ptr = new Restaurant;
		*ptr = restaurant;
		restaurants_vec.push_back(ptr);
	}
	
	base->setRestaurants(restaurants_vec);
}

void Restaurant::setName(string n) {
	name = n;
}

void Restaurant::setAddress(Address a) {
	address = a;
}

void Restaurant::setCuisineTypes(set <string> ct) {
	cuisine_types = ct;
}

void Restaurant::setProducts(vector <Product*> p) {
	products = p;
}

void Restaurant::setPriceAverage(double pa) {
	price_average = pa;
}


void Restaurant::setPriceAverage() {
	double total = 0;
	vector<Product*>::iterator it;
	for (it = products.begin(); it != products.end(); it++)
	{
		total += (*it)->get_price();
	}
	price_average = total / products.size();
}

void Restaurant::setBase(Base * b) {
	base = b;
}

string Restaurant::get_name() const {
	return name;
}

Address Restaurant::get_address() const {
	return address;
}

set <string> & Restaurant::get_cuisine_types() {
	return cuisine_types;

}

vector <Product*> Restaurant::get_products() const {
	return products;
}

double Restaurant::get_price_average() const {
	return price_average;
}

Base * Restaurant::get_base() const {
	return base;
}



void Restaurant::add_product() {
	Product p;

	// name input
	bool invalidName;
	string name;
	do {
		try {
			invalidName = false;
			cout << "Name: ";
			getline(cin, name);
			if (!isString(name))
				throw InvalidStringException(name);
		}
		catch (InvalidStringException & s)
		{
			invalidName = true;
			cout << s;
			cout << "Try Again!" << endl << endl;

		}

	} while (invalidName);

	p.setName(name);

	// cuisine type input
	bool invalidCuisineType;
	string cuisineType;
	do {
		try {
			invalidCuisineType = false;
			cout << "Cuisine Type: ";
			getline(cin, cuisineType);
			if (!isString(cuisineType))
				throw InvalidStringException(cuisineType);
		}
		catch (InvalidStringException & s)
		{
			invalidCuisineType = true;
			cout << s;
			cout << "Try Again!" << endl << endl;

		}
	} while (invalidCuisineType);

	p.setCuisineType(cuisineType);

	// price input
	bool invalidPrice;
	string strPrice;
	int price;
	do {
		cout << "Price: ";
		getline(cin, strPrice);
		try {
			price = stoi(strPrice);
		}
		catch (...) {
			invalidPrice = true;
			cout << "Invalid Price" << endl;
			cout << "Try Again!" << endl << endl;
		}
	} while (invalidPrice);

	p.setPrice(price);

	Product * ptr = new Product;
	*ptr = p;

	products.push_back(ptr);

	// updating cuisine types
	for (auto & prod : products) {
		this->get_cuisine_types().insert(prod->get_cuisine_type());
	}

	// updating price average
	this->setPriceAverage();

	cout << endl;
	cout << "Restaurant successfully added! (Enter to continue)" << endl;
	cout << ">> ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
}

void Restaurant::change_product() {

	vector<Product*>::iterator it;
	bool invalidOption;
	string strChoice;
	int productChoice;
	unsigned index = 0;

	do {
		index = 0;
		invalidOption = false;
		cout << "Pick the product you want to change information about:" << endl;
		for (it = products.begin(); it != products.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			cout << "0. Go Back" << endl;
			cout << ">> ";
			getline(cin, strChoice);
			if (strChoice == "0")
			{
				cin.clear();
				utils::clear_screen();
				return;
			}

			if (!isNumber(strChoice))
				throw InvalidNumberException(strChoice);
			if (strChoice != "") {
				productChoice = stoi(strChoice);

				if (InvalidOptions(products.size(), productChoice)) {
					throw InvalidOptionException(productChoice);
				}
			}
			else {
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

	productChoice--; // not to excede the max index available

	list<string> options = { "name", "cuisine type", "price"};

	list<string>::iterator optionsIt;
	int attributeChoice;
	do {
		index = 0;
		invalidOption = false;
		cout << "Pick the field you want to change information of:" << endl;
		for (optionsIt = options.begin(); optionsIt != options.end(); ++optionsIt, ++index) {
			cout << index + 1 << ". " << (*optionsIt) << endl;
		}

		try {
			cout << ">> ";
			getline(cin, strChoice);
			
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

		cout << endl;

	} while (invalidOption);
	
	string newName;
	bool invalidName;

	string newCuisineType;
	bool invalidCuisineType;

	string strNewPrice;
	int newPrice;
	bool invalidPrice;

	switch (attributeChoice) {
		// Name
		case 1:
			do {
				try {
					invalidName = false;
					cout << "Current Name: " << products.at(productChoice)->get_name() << endl;
					cout << "Updated Name: ";
					getline(cin, newName);
					if (!isString(newName))
						throw InvalidStringException(newName);
					
					cout << endl;
					products.at(productChoice)->setName(newName);
				}
				catch (InvalidStringException & s)
				{
					invalidName = true;
					cout << s;
					cout << "Try Again!" << endl << endl;
				}
			} while (invalidOption);
			break;

		// Cuisine Type
		case 2:
			do {
				try {
					invalidCuisineType = false;
					cout << "Current Cuisine Type: " << products.at(productChoice)->get_cuisine_type() << endl;
					cout << "Updated Cuisine Type: ";
					getline(cin, newCuisineType);
					if (!isString(newCuisineType))
						throw InvalidStringException(newCuisineType);

					cout << endl;
					products.at(productChoice)->setCuisineType(newCuisineType);
				}
				catch (InvalidStringException & s)
				{
					invalidCuisineType = true;
					cout << s;
					cout << "Try Again!" << endl << endl;
				}
			} while (invalidCuisineType);
			break;

		// Price
		case 3:
			do {
				try {
					cout << "Current Price: " << products.at(productChoice)->get_price() << endl;
					cout << "Updated Price: ";
					getline(cin, strNewPrice);
					newPrice = stoi(strNewPrice);
					products.at(productChoice)->setPrice(newPrice);
				}
				catch (...) {
					invalidPrice = true;
					cout << "Invalid Price" << endl;
					cout << "Try Again!" << endl << endl;
				}
			} while (invalidPrice);
			break;
	}

	// updating cuisine types
	for (auto & prod : products) {
		this->get_cuisine_types().insert(prod->get_cuisine_type());
	}

	// updating price average
	this->setPriceAverage();
}

void Restaurant::removeProduct() {

	vector<Product*>::iterator it;
	bool invalidOption;
	string strChoice;
	int productChoice;
	unsigned index = 0;

	do {
		index = 0;
		invalidOption = false;
		cout << "Pick the restaurant you want to change information about:" << endl;
		for (it = products.begin(); it != products.end(); ++it, ++index) {
			cout << index + 1 << ". " << (*it)->get_name() << endl;
		}
		try {
			cout << "0. Go Back" << endl;
			cout << ">> ";
			getline(cin, strChoice);

			if (strChoice == "0") {
				cin.clear();
				utils::clear_screen();
				return;
			}

			if (!isNumber(strChoice))
				throw InvalidNumberException(strChoice);
			if (strChoice != "")
			{
				productChoice = stoi(strChoice);

				if (InvalidOptions(products.size(), productChoice)) {
					throw InvalidOptionException(productChoice);
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
			cout << "Try Again!" << endl;
		}
		catch (InvalidNumberException & s)
		{
			invalidOption = true;
			cout << s;
			cout << "Try Again!" << endl << endl;
		}
	} while (invalidOption);

	productChoice--;	// not to excede the max index available

	// To free the memory
	vector<Product*>::iterator eraseIt = products.begin() + productChoice;
	delete * eraseIt;

	// To erase from the vector
	products.erase(products.begin() + productChoice);


	// updating cuisine types
	for (auto & prod : products) {
		this->get_cuisine_types().insert(prod->get_cuisine_type());
	}

	// updating price average
	this->setPriceAverage();

	cout << "Product removed successfully" << endl;
	cout << ">> ";
	cin.clear();
	cin.ignore(INT_MAX,'\n');
}


ostream & operator<<(ostream & out, const Restaurant & r) {
	out << "Name: " << r.name << endl;
	out << r.address << endl;
	out << "Cuisine Types: ";
	if (r.cuisine_types.size() == 0)
		out << "none" << endl;
	else
	{
		set<string>::iterator it;
		size_t index;
		for (index = 0, it = r.cuisine_types.begin(); index < r.cuisine_types.size() - 1; index++, it++)
		{
			out << (*it) << " ; ";
		}
		out << (*it) << endl;
	}
	out << "Price Average: " << fixed << setprecision(2) << r.price_average << endl;
	
	out << "Number of Products: " << r.products.size() << endl << endl;

	return out;
}

bool operator<(Restaurant & left, Restaurant & right) {
	return left.name < right.name;
}



Order::Order() {

}

Order::~Order() {

}


void Order::load(string path, Base * base) {
	ifstream orders_text(path);
	try
	{
		if (!orders_text.is_open())
			throw FileOpenErrorException(path);
	}
	catch (FileOpenErrorException & f)
	{
		cout << f;
		exit(0);
	}

	string textline;
	int temp; 
	map<int, Order*> orders_map = {};
	while(!orders_text.eof()){
		
		if (textline == "") break;
		if (textline == SEPARATOR) {
			getline(orders_text, textline);
		}
		Order order;
		Deliver deliver;

	
		getline(orders_text, textline);
		temp = stoi(textline);		

		order.setID(temp);
		deliver.setID(temp);

		getline(orders_text, textline);

		order.setRestaurant(base->findRestaurant(textline));
		
		getline(orders_text, textline);

		temp = stoi(textline);
		order.setDeliveryFee(temp);

		getline(orders_text, textline);
		deliver.setInsuccessMessage(textline);
		if (textline == "-") {
			deliver.setSuccess(true);
		}
		else {
			deliver.setSuccess(false);
		}

		getline(orders_text, textline);

		Date_time x; x.parse(textline);
		order.setDateTime(x);
		
		getline(orders_text, textline);

		Date_time y; y.parse(textline);

		Deliver * bleh = new Deliver;
		*bleh = deliver;
		order.setDeliver(bleh);

		order.getDeliver()->setDateTime(y);


		vector<Product*> prods;
		while(getline(orders_text, textline)){
			if (textline == ";;;") break;
			vector <string> parts = utils::split(textline, ':');

			Product p;
			p.setName(parts.at(0));
			p.setCuisineType(parts.at(1));
			p.setPrice(stoi(parts.at(2)));

			Product* ptr = new Product;
			*ptr = p;
			prods.push_back(ptr);
		}
		order.setProducts(prods);

		Order * ptr = new Order;
		*ptr = order;
		pair<int, Order*> pair; pair.first = order.id; pair.second =  ptr;
		orders_map.insert(pair);

	}	
	base->setOrders(orders_map);
}


void Order::setID(int i) {
	id = i;
}

void Order::setRestaurant(Restaurant* r) {
	restaurant = r;
}

void Order::setProducts(vector <Product*> p) {
	products = p;
}

void Order::setDateTime(Date_time t) {
	date_time = t;
}

void Order::setDeliveryFee(double f) {
	delivery_fee = f;
}

void Order::setDeliver(Deliver *d) {
	delivery = d;
}


int Order::getID() const {
	return id;
}

Restaurant* Order::getRestaurant() const {
	return restaurant;
}

vector <Product*> Order::getProducts()  const {
	return products;
}

Date_time Order::getDateTime() const {
	return date_time;
}

double Order::getDeliveryFee() const {
	return delivery_fee;
}

Deliver * Order::getDeliver() const {
	return delivery;
}


ostream & operator<<(ostream & out, Order & o) {
	out << "ID: " << o.id << endl;
	out << "Restaurant: " << o.restaurant->get_name() << endl;
	out << "Products: " << endl;
	vector<Product*>::iterator it;
	int c = 0;
	for (it = o.products.begin(); it != o.products.end(); it++)
	{
		out << *(*it);
		if (c != o.products.size() - 1)
			cout << endl;
		c++;
		
	}
	out << "Order Date: " << o.date_time << endl;
	
	if (o.getDeliver()->getSuccess())
		out << "SUCCESSFUL" << endl;
	else
		out << o.getDeliver()->getInsuccessMessage()<< endl;

	out << "Arrival Date: " << o.getDeliver()->getDateTime() << endl;

	out << "Delivery worker: " << o.getDeliver()->getDeliveryMan()->get_name() << endl;

	out << "Delivery Fee: " << o.delivery_fee;
	
	return out;
}



Deliver::Deliver() {

}

Deliver::Deliver(int i, Date_time t, bool s, Delivery * dm) {
	id = i;
	date_time = t;
	success = s;
	delivery_man = dm;
}


void Deliver::setID(int i) {
	id = i;
}

void Deliver::setDateTime(Date_time t) {
	date_time = t;
}

void Deliver::setInsuccessMessage(string s) {
	insuccess_message = s;
}


void Deliver::setSuccess(bool s) {
	success = s;
}

void Deliver::setDeliveryMan(Delivery * dm) {
	delivery_man = dm;
}


int Deliver::getID() const {
	return id;
}

Date_time Deliver::getDateTime() {
	return date_time;
}

bool Deliver::getSuccess() const {
	return success;
}

string Deliver::getInsuccessMessage() const {
	return insuccess_message;
}

Delivery* Deliver::getDeliveryMan() const {
	return delivery_man;
}

