#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Date_time.h"
#include "Address.h"
#include "People.h"
#include <set>

class Base;

using namespace std;

class Order;

class Product {
	string name;
	string cuisine_type;
	size_t price;

public:

	/**
	 * @brief Construct a new Product object
	 * 
	 */
	Product();
	
	/**
	 * @brief Destroy the Product object
	 * 
	 */
	~Product();

	/**
	 * @brief Checks if the str string passed as a parameter can correspond to a valid Product and sets the value of the attributes 
	 * 
	 * @param str String corresponding to the full product description
	 * @return true If the product parsing occured without issues
	 * @return false If the product string had an invalid number of elements or any invalid fields
	 */
	bool parse(string str);

	/**
	 * @brief Set the Name object
	 * 
	 * @param n
	 */
	void setName(string n);

	/**
	 * @brief Set the Cuisine Type object
	 * 
	 * @param ct 
	 */
	void setCuisineType(string ct);

	/**
	 * @brief Set the Price object
	 * 
	 * @param p 
	 */
	void setPrice(size_t p);


	/**
	 * @brief Get the name object
	 * 
	 * @return string 
	 */
	string get_name() const;

	/**
	 * @brief Get the cuisine type object
	 * 
	 * @return string 
	 */
	string get_cuisine_type() const;

	/**
	 * @brief Get the price object
	 * 
	 * @return size_t 
	 */
	size_t get_price() const;

	/**
	 * @brief Displays an address in a formated way
	 * 
	 * @param out 
	 * @param p 
	 * @return ostream& 
	 */
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
	/**
	 * @brief Construct a new Restaurant object
	 * 
	 */
	Restaurant();
	
	/**
	 * @brief Destroy the Restaurant object
	 * 
	 */
	~Restaurant();

	/**
	 * @brief Load the information of the restaurants of a specific base
	 * 
	 * @param path name of the file that contains the restaurants information
	 * @param base pointer to the Base object that the restaurants belong to
	 */
	static void load(string path, Base * base);


	/**
	 * @brief Set the Name object
	 * 
	 * @param n 
	 */
	void setName(string n);

	/**
	 * @brief Set the Address object
	 * 
	 * @param a 
	 */
	void setAddress(Address a);

	/**
	 * @brief Set the Cuisine Types object
	 * 
	 * @param ct 
	 */
	void setCuisineTypes(set <string> ct);

	/**
	 * @brief Set the Products object
	 * 
	 * @param p 
	 */
	void setProducts(vector <Product *> p);

	void setPriceAverage(double pa);

	/**
	 * @brief Set the Price Average object
	 * 
	 */
	void setPriceAverage();

	/**
	 * @brief Set the Base object
	 * 
	 * @param b 
	 */
	void setBase(Base* b);


	/**
	 * @brief Get the name object
	 * 
	 * @return string 
	 */
	string get_name() const;

	/**
	 * @brief Get the address object
	 * 
	 * @return Address 
	 */
	Address get_address() const;

	/**
	 * @brief Get the cuisine types object
	 * 
	 * @return set<string>& 
	 */
	set<string> & get_cuisine_types();

	/**
	 * @brief Get the products object
	 * 
	 * @return vector<Product*> 
	 */
	vector<Product*> get_products() const;

	/**
	 * @brief Get the price average object
	 * 
	 * @return double 
	 */
	double get_price_average() const;

	/**
	 * @brief Get the base object
	 * 
	 * @return Base* 
	 */
	Base * get_base() const;

	void update_price_average(); //quando se adiciona produtos
	//void update_cuisine_types(); //meter esta funcionalidade no add product
	bool add_product();
	
	/**
	 * @brief Displays a restaurant in a formated way
	 * 
	 * @param out 
	 * @param r 
	 * @return ostream& 
	 */
	friend ostream & operator<<(ostream & out, const Restaurant & r);

	/**
	 * @brief Comparison operator for restaurants (based on the name)
	 * 
	 * @param left 
	 * @param right 
	 * @return true If the name of the parameter left apears first than the one of the parameter right, when considering the alphabetic order
	 * @return false If the name of the parameter right apears first than the one of the parameter left, when considering the alphabetic order
	 */
	friend bool operator<(Restaurant & left, Restaurant & right);

};


class Deliver;


class Order { 
	int id;
	Restaurant * restaurant;
	vector<Product*> products;
	Date_time date_time;
	double delivery_fee;
	Deliver * delivery;

public:
	/**
	 * @brief Construct a new Order object
	 * 
	 */
	Order();

	/**
	 * @brief Destroy the Order object
	 * 
	 */
	~Order();

	/**
	 * @brief Load the information of the orders of a specific base
	 * 
	 * @param path name of the file that contains the orders information
	 * @param base pointer to the Base object that the orders belong to
	 */
	static void load(string path, Base * base);

	/**
	 * @brief Set the ID object
	 * 
	 * @param i 
	 */
	void setID(int i);

	/**
	 * @brief Set the Restaurant object
	 * 
	 * @param r 
	 */
	void setRestaurant(Restaurant * r);

	/**
	 * @brief Set the Products object
	 * 
	 * @param p 
	 */
	void setProducts(vector <Product*> p);

	/**
	 * @brief Set the Date Time object
	 * 
	 * @param t 
	 */
	void setDateTime(Date_time t);

	/**
	 * @brief Set the Delivery Fee object
	 * 
	 * @param f
	 */
	void setDeliveryFee(double f);

	/**
	 * @brief Set the Deliver object
	 * 
	 * @param d 
	 */
	void setDeliver(Deliver *d);


	/**
	 * @brief Get the ID object
	 * 
	 * @return int 
	 */
	int getID() const;

	/**
	 * @brief Get the Restaurant object
	 * 
	 * @return Restaurant* 
	 */
	Restaurant* getRestaurant() const;

	/**
	 * @brief Get the Products object
	 * 
	 * @return vector <Product*> 
	 */
	vector <Product*> getProducts() const;

	/**
	 * @brief Get the Date Time object
	 * 
	 * @return Date_time 
	 */
	Date_time getDateTime() const;
	
	/**
	 * @brief Get the Delivery Fee object
	 * 
	 * @return double 
	 */
	double getDeliveryFee()const;

	/**
	 * @brief Get the Deliver object
	 * 
	 * @return Deliver* 
	 */
	Deliver * getDeliver()const;
	
	/**
	 * @brief Displays an order in a formated way
	 * 
	 * @param out 
	 * @param o 
	 * @return ostream& 
	 */
	friend ostream & operator<<(ostream & out, Order & o);

	bool calculate_fee();
	bool calculate_time();
};



class Deliver {
	int id;
	Date_time date_time;
	bool success;
	string insuccess_message;
	Delivery * delivery_man;

public:

	/**
	 * @brief Construct a new Deliver object
	 * 
	 */
	Deliver();

	/**
	 * @brief Construct a new Deliver object
	 * 
	 * @param i value to be set to the id attribute
	 * @param t value to be set to the date_time attribute
	 * @param s value to be set to the success attribute
	 * @param dm value to be set to the delivery_man attribute
	 */
	Deliver(int i, Date_time t, bool s, Delivery * dm);

	/**
	 * @brief Set the ID object
	 * 
	 * @param i 
	 */
	void setID(int i);

	/**
	 * @brief Set the Date Time object
	 * 
	 * @param t 
	 */
	void setDateTime(Date_time t);

	/**
	 * @brief Set the Insuccess Message object
	 * 
	 * @param s 
	 */
	void setInsuccessMessage(string s);

	/**
	 * @brief Set the Success object
	 * 
	 * @param s 
	 */
	void setSuccess(bool s);

	/**
	 * @brief Set the Delivery Man object
	 * 
	 * @param dm 
	 */
	void setDeliveryMan(Delivery * dm);


	/**
	 * @brief 
	 * 
	 * @return int 
	 */
	int  getID() const;

	/**
	 * @brief Get the Date Time object
	 * 
	 * @return Date_time 
	 */
	Date_time getDateTime();

	/**
	 * @brief Get the Success object
	 * 
	 * @return true 
	 * @return false 
	 */
	bool getSuccess() const;

	/**
	 * @brief Get the Insuccess Message object
	 * 
	 * @return string 
	 */
	string getInsuccessMessage() const;

	/**
	 * @brief Get the Delivery Man object
	 * 
	 * @return Delivery* 
	 */
	Delivery * getDeliveryMan() const;

};

#endif