#include "Restaurant.h"
#include "Base.h"
#include "utils.h"

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

Restaurant::Restaurant()
{

}

Restaurant::~Restaurant()
{

}

void Restaurant::load(string path, Base * base){
	ifstream restaurants_text;

	string textline;
	vector<Restaurant*> restaurants_vec;
	while(!restaurants_text.eof()){
		Restaurant restaurant;
		restaurants_text >> textline;
		restaurant.setName(textline);

		restaurants_text >> textline;
		Address addr;
		addr.parse(textline);
		restaurant.setAddress(addr);

		vector<Product*> prods;
		while(textline != ";"){
			restaurants_text >> textline;
			Product d;
			d.parse(textline);
			prods.push_back(&d);
		}

		restaurants_vec.push_back(&restaurant);
	}
	base->setRestaurants(restaurants_vec);
}

void Restaurant::setName(string nm){
	name = nm;
}

void Restaurant::setAddress(Address add)
{
	address = add;
}

void Restaurant::setCuisineTypes(vector <string> cts)
{
	cuisine_types = cts;
}

void Restaurant::setProducts(vector <Product*> ps)
{
	products = ps;
}

void Restaurant::setPriceAverage(size_t p)
{
	price_average = p;
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

vector <string> Restaurant::get_cuisine_types() const
{
	return cuisine_types;

}

vector <Product*> Restaurant::get_products() const
{
	return products;
}

size_t Restaurant::get_price_average() const
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

void Restaurant::print_price_average() //implementar depois - n�o seria necess�rio aqui um ostream ???
{

}

void Restaurant::update_cuisine_types() //implementar depois
{

}

bool Restaurant::add_product() //implementar depois
{
	return true;
}

Order::Order()
{

}

Order::~Order()
{

}

void Order::load(string path, Base * base){
	ifstream orders_text(path);

	string textline;
	size_t temp; 
	vector<Order*> orders_vec;
	while(!orders_text.eof()){
		Order order;

		orders_text >> temp; 
		order.setID(temp);
		
		order.setBase(base);

		orders_text >> textline; 
		order.setRestaurant(base->findRestaurant(textline));
		
		orders_text >> temp;
		order.setDeliveryFee(temp);

		orders_text >> textline;
		order.setInsuccessMessage(textline);
		if (textline == "-") {
			order.setSuccess(true);
		}
		else {
			order.setSuccess(false);
		}

		orders_text >> textline;
		Time t; t.parse(textline); order.setTime(t);

		orders_text >> textline;
		Date d; d.parse(textline);
		order.setDate(d);

		vector<Product*> prods;
		while(textline != ";"){
			orders_text >> textline;
			vector <string> parts = utils::split(textline, ':');

			Product p;
			p.setName(parts.at(0));
			p.setCuisineType(parts.at(1));
			p.setPrice(stoi(parts.at(2)));
			prods.push_back(&p);
		}
		order.setProducts(prods);
	}	
}

void Order::setID(size_t i)
{
	id = i;
}

void Order::setBase(Base * b)
{
	base = b;
}

void Order::setRestaurant(Restaurant* r)
{
	restaurant = r;
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

void Order::setSuccess(bool s)
{
	success = s;
}

void Order::setInsuccessMessage(string message)
{
	insuccess_message = message;
}

void Order::setDeliveryFee(size_t fee)
{
	delivery_fee = fee;
}

size_t Order::getID() const
{
	return id;
}

Base * Order::getBase() const
{
	return base;
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

bool Order::getSuccess() const
{
	return success;
}

string Order::getInsuccessMessage() const
{
	return insuccess_message;
}

size_t Order::getDeliveryFee() const
{
	return delivery_fee;
}
 
bool Order::calculate_fee() //implementar depois
{
	return true;
}

bool Order::calculate_time() //implementar depois
{
	return true;
}