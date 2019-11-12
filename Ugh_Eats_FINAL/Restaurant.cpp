#include "Restaurant.h"
#include "Base.h"
#include "utils.h"
#include <iomanip>

using namespace std;

string SEPARATOR = ";;;";

Product::Product()
{

}

Product::~Product()
{

}

void Product::parse(string str){
	vector<string> parts = utils::split(str, ':');

	name = parts.at(0);
	cuisine_type = parts.at(1);
	price = stoi(parts.at(2));
}

void Product::setName(string nm)
{
	name = nm;
}

void Product::setCuisineType(string ct)
{
	cuisine_type = ct;
}

void Product::setPrice(size_t p)
{
	price = p;
}

string Product::get_name() const
{
	return name;
}

string Product::get_cuisine_type() const
{
	return cuisine_type;
}

size_t Product::get_price() const
{
	return price;
}


ostream & operator<<(ostream & out, const Product & p)
{
	out << "   Name: " << p.name << endl;
	out << "   Cuisine Type: " << p.cuisine_type << endl;
	out << "   Price: " << p.price << endl;
	return out;
}


Restaurant::Restaurant()
{

}

Restaurant::~Restaurant()
{

}

void Restaurant::load(string path, Base * base){
	ifstream restaurants_text(path);

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
			//cout << "Textline: " << textline << endl;
			d.parse(textline);

			Product * ptr2 = new Product;
			*ptr2 = d;
			//prods.push_back(&d);
			prods.push_back(ptr2);
			// cout << prods.at(0)->get_name() << endl;
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
	//cout << "Vector size: " << restaurants_vec.at(0)->get_products().size() << endl;
	base->setRestaurants(restaurants_vec);
}

void Restaurant::setName(string nm){
	name = nm;
}

void Restaurant::setAddress(Address add)
{
	address = add;
}

void Restaurant::setCuisineTypes(set <string> cts)
{
	cuisine_types = cts;
}

void Restaurant::setProducts(vector <Product*> ps)
{
	products = ps;
}

void Restaurant::setPriceAverage(double p)
{
	price_average = p;
}


void Restaurant::setPriceAverage()
{
	double total = 0;
	vector<Product*>::iterator it;
	for (it = products.begin(); it != products.end(); it++)
	{
		total += (*it)->get_price();
	}
	price_average = total / products.size();
}

void Restaurant::setBase(Base * b)
{
	base = b;
}

string Restaurant::get_name() const {
	return name;
}

Address Restaurant::get_address() const
{
	return address;
}

set <string> Restaurant::get_cuisine_types() const
{
	return cuisine_types;

}

vector <Product*> Restaurant::get_products() const
{
	return products;
}

double Restaurant::get_price_average() const
{
	return price_average;
}

Base * Restaurant::get_base() const
{
	return base;
}

void Restaurant::update_price_average() //implementar depois
{

}

//void Restaurant::update_cuisine_types() //implementar depois
//{
//
//}

bool Restaurant::add_product() //implementar depois
{
	return true;
}




ostream & operator<<(ostream & out, const Restaurant & r)
{
	out << "Name: " << r.name << endl;
	out << r.address;
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
	//out << "Number of Products:" << r.products.size() << endl << endl;


	/*
	out << "Products:" << endl;
	for (auto i = 0; i < r.products.size(); i++) {
		out << r.products.at(i) << endl;
	}*/
	out << "Number of Products: " << r.products.size() << endl << endl;


	return out;
}



bool operator<(Restaurant & left, Restaurant & right)
{
	return left.name < right.name;
}



Order::Order()
{

}

Order::~Order()
{

}

void Order::load(string path, Base * base){
	// cout << "Path: " << path << endl;
	ifstream orders_text(path);

	string textline;
	int temp; 
	map<int, Order*> orders_map;
	while(!orders_text.eof()){
		

		if (textline == SEPARATOR) {
			getline(orders_text, textline);
		}
		Order order;
		Deliver deliver;

	
		getline(orders_text, textline);
		temp = stoi(textline);		

		order.setID(temp);
		deliver.setID(temp);

		// orders_text >> textline;  //tem que detetar se e nullptr
		getline(orders_text, textline);
		//

		order.setRestaurant(base->findRestaurant(textline));
		
		// orders_text >> temp;
		getline(orders_text, textline);

		temp = stoi(textline);
		order.setDeliveryFee(temp);

		// orders_text >> textline;
		getline(orders_text, textline);

		deliver.setInsuccessMessage(textline);
		if (textline == "-") {
			deliver.setSuccess(true);
		}
		else {
			deliver.setSuccess(false);
		}

		getline(orders_text, textline);
		// orders_text >> textline;

		Time t; t.parse(textline);  
		order.setTime(t);

		getline(orders_text, textline);
		// orders_text >> textline;

		Date d; d.parse(textline);
		order.setDate(d);
		
		getline(orders_text, textline);
		// orders_text >> textline;

		Time x; x.parse(textline);  
		deliver.setTime(x);

		getline(orders_text, textline);
		// orders_text >> textline;

		Date y; y.parse(textline);
		deliver.setDate(y);

		//Delivery guy seria aqui

		Deliver * bleh = new Deliver;
		*bleh = deliver;
		order.setDeliver(bleh);

		vector<Product*> prods;
		while(getline(orders_text, textline)){
		// while(orders_text >> textline) {
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

void Order::setID(size_t i)
{
	id = i;
}

void Order::setRestaurant(Restaurant* r)
{
	restaurant = r;
}

void Order::setClient(Client * c)
{
}

void Order::setProducts(vector <Product*> p)
{
	products = p;
}


void Order::setTime(Time t)
{
	time = t;
}

void Order::setDate(Date d){
	date = d;
}

void Order::setDeliveryFee(double fee)
{
	delivery_fee = fee;
}

void Order::setDeliver(Deliver *d)
{
	delivery = d;
}

size_t Order::getID() const
{
	return id;
}

Restaurant* Order::getRestaurant() const
{
	return restaurant;
}

vector <Product*> Order::getProducts()  const
{
	return products;
}

Time Order::getTime() const
{
	return time;
}

Date Order::getDate() const
{
	return date;
}

double Order::getDeliveryFee() const
{
	return delivery_fee;
}
 

Deliver * Order::getDeliver() const
{
	return delivery;
}

bool Order::calculate_fee() //implementar depois
{
	return true;
}

bool Order::calculate_time() //implementar depois
{
	return true;
}

ostream & operator<<(ostream & out, Order & o)
{
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
	out << "Order Time: " << o.time << endl;
	out << "Date: " << o.date << endl;
	
	if (o.getDeliver()->getSuccess())
		out << "SUCCESSFUL" << endl;
	else
		out << o.getDeliver()->getInsuccessMessage()<< endl;

	out << "Arrival time: " << o.getDeliver()->getTime() << endl;
	out << "Date: " << o.getDeliver()->getDate() << endl;

	out << "Delivery worker: " << o.getDeliver()->getDeliveryMan()->get_name() << endl;

	out << "Delivery Fee: " << o.delivery_fee;
	
	return out;
}


Deliver::Deliver()
{

}

Deliver::Deliver(int i, Time t, Date d, bool s, Delivery * dm)
{
	id = i;
	time = t;
	date = d;
	success = s;
	delivery_man = dm;
}


void Deliver::setID(int i)
{
	id = i;
}

void Deliver::setTime(Time t)
{
	time = t;
}


void Deliver::setDate(Date d)
{
	date = d;
}

void Deliver::setInsuccessMessage(string s)
{
	insuccess_message == s;
}


void Deliver::setSuccess(bool s)
{
	success = s;
}

void Deliver::setDeliveryMan(Delivery * dm)
{
	delivery_man = dm;
}

int Deliver::getID() const
{
	return id;
}

Time & Deliver::getTime()
{
	return time;
}

Date & Deliver::getDate()
{
	return date;
}

bool Deliver::getSuccess() const
{
	return success;
}

string Deliver::getInsuccessMessage() const
{
	return insuccess_message;
}

Delivery* Deliver::getDeliveryMan() const
{
	return delivery_man;
}

