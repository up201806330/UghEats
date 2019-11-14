#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Date_time.h"
#include "Address.h"
#include "People.h"
#include <set>

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

	bool parse(string str);

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
	set<string> cuisine_types;
	vector<Product*> products;
	double price_average;
	Base * base;

public:
	Restaurant();
	
	~Restaurant();

	static void load(string path, Base * base);

	void setName(string nm);
	void setAddress(Address add);
	void setCuisineTypes(set <string> cts); //USAR SET
	void setProducts(vector <Product *> ps);
	void setPriceAverage(double p);
	void setPriceAverage();
	void setBase(Base* b);
	string get_name() const;
	Address get_address() const;
	set<string> get_cuisine_types() const;
	vector<Product*> get_products() const;
	double get_price_average() const;
	Base * get_base() const;

	void update_price_average(); //quando se adiciona produtos
	//void update_cuisine_types(); //meter esta funcionalidade no add product
	bool add_product();
	
	
	friend ostream & operator<<(ostream & out, const Restaurant & r);
	friend bool operator<(Restaurant & left, Restaurant & right);

};


class Deliver;

class Order { 
	size_t id;
	Restaurant * restaurant;
	vector<Product*> products;
	Date_time date_time;
	//bool success;
	//string insuccess_message;
	double delivery_fee;
	Deliver * delivery;

public:
	Order();

	~Order();

	static void load(string path, Base * base);
	void setID(size_t i);
	void setRestaurant(Restaurant * r);
	void setClient(Client * c);
	void setProducts(vector <Product*> p);
	void setDateTime(Date_time t);
	void setDeliveryFee(double fee);
	void setDeliver(Deliver *d);
	size_t getID() const;
	Restaurant* getRestaurant() const;
	vector <Product*> getProducts() const;
	Date_time getDateTime() const;
	double getDeliveryFee()const;
	Deliver * getDeliver()const;
	
	vector <Order> findOrders(string textile);
	friend ostream & operator<<(ostream & out, Order & o);

	
	
	

	
	
	bool calculate_fee();
	bool calculate_time();
};



class Deliver
{
private:
	int id; // a partir daqui vai buscar a informa��o necess�ria ao vetor das orders
	Date_time date_time;
	bool success;
	string insuccess_message;
	Delivery * delivery_man;
public:
	Deliver();
	Deliver(int i, Date_time t, bool s, Delivery * dm);
	void setID(int i);
	void setDateTime(Date_time t);
	void setInsuccessMessage(string s);
	void setSuccess(bool s);
	void setDeliveryMan(Delivery * dm);
	int  getID() const;
	Date_time getDateTime(); //cant be const cuz must return reference
	bool getSuccess() const;
	string getInsuccessMessage() const;
	Delivery * getDeliveryMan() const;

};

#endif