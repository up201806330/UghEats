#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Date_time.h"
#include "Address.h"
#include "People.h"

class Base;

using namespace std;

//opertor overload fica em private ou public ???

class Order;

class Product {
	string name;
	string cuisine_type;
	size_t price;

public:
	Product();
	
	~Product();

	void parse(string str);

	void setName(string nm);
	void setCuisineType(string ct);
	void setPrice(size_t p);
	string get_name() const;
	string get_cuisine_type() const;
	size_t get_price() const;

	friend ostream & operator<<(ostream & out, const Product & p);
};

class Restaurant {
	string name;
	Address address;
	vector<string> cuisine_types;
	vector<Product*> products;
	size_t price_average;
	Base * base;

public:
	Restaurant();
	
	~Restaurant();

	static void load(string path, Base * base);

	void setName(string nm);
	void setAddress(Address add);
	void setCuisineTypes(vector <string> cts);
	void setProducts(vector <Product *> ps);
	void setPriceAverage(size_t p);
	void setBase(Base* b);
	string get_name() const;
	Address get_address() const;
	vector<string> get_cuisine_types() const;
	vector<Product*> get_products() const;
	size_t get_price_average() const;
	Base * get_base() const;

	void update_price_average();
	void print_price_average(); //estrelinhas
	void update_cuisine_types();
	bool add_product();
	
	
	friend ostream & operator<<(ostream & out, const Restaurant & r);

};

class Order {
	size_t id;
	Base * base;
	Restaurant * restaurant;
	vector<Product*> products;
	Time time;
	Date date;
	bool success;
	string insuccess_message;
	size_t delivery_fee;

public:
	Order();

	~Order();

	static void load(string path, Base * base);

	void setID(size_t i);
	void setBase(Base * b);
	void setRestaurant(Restaurant * r);
	void setClient(Client * c);
	void setProducts(vector <Product*> p);
	void setTime(Time t);
	void setDate(Date d);
	void setSuccess(bool s);
	void setInsuccessMessage(string message);
	void setDeliveryFee(size_t fee);
	size_t getID() const;
	Base * getBase() const;
	Restaurant* getRestaurant() const;
	Client * getClient() const;
	vector <Product*> getProducts() const;
	Time getTime() const;
	bool getSuccess() const;
	string getInsuccessMessage() const;
	size_t getDeliveryFee()const;
	
	vector <Order> findOrders(string textile);


	
	
	

	
	
	bool calculate_fee();
	bool calculate_time();
};

#endif