#ifndef PEOPLE_H
#define PEOPLE_H

#include <vector>
#include <unordered_set>

#include "utils.h"
#include "Date_time.h"
#include "Address.h"
#include "Exceptions.h"
// #include "hash_table.h"

class Base;
class Order;

using namespace std;

class Vehicle { 
	string brand;
	string type;
	Date_time registration_date;

	string license;
	unsigned trips;
	double mileage;

public:
	/**
	 * @brief Construct a new Vehicle object
	 * 
	 */
	Vehicle();

	/**
	 * @brief Destroy the Vehicle object
	 * 
	 */
	~Vehicle();

	/**
	 * @brief Operator< overload
	 * 
	 * @param l 
	 * @param r 
	 * @return true 
	 * @return false 
	 */
	friend bool operator<(const Vehicle & l, const Vehicle & r);

	/**
	 * @brief checks if the string passed as parameter can correspond to a valid vehicle and sets the value of the attributes
	 * 
	 * @param str String corresponding to all the vehicle info
	 */
	void parse(string str);

	/**
	 * @brief Set the registrationDate object
	 * 
	 * @param data 
	 */
	void set_registrationDate(Date_time data);
	/**
	 * @brief Set the type object
	 * 
	 * @param tipo 
	 */
	void set_type(string tipo);
	/**
	 * @brief Set the brand object
	 * 
	 * @param marca 
	 */
	void set_brand(string marca);
	/**
	 * @brief Set the license object
	 * 
	 * @param l 
	 */
	void set_license(string l);
	/**
	 * @brief Set the trips object
	 * 
	 * @param t 
	 */
	void set_trips(unsigned t);
	/**
	 * @brief Set the mileage object
	 * 
	 * @param m 
	 */
	void set_mileage(double m);
	/**
	 * @brief Get the registration date object
	 *
	 * @return Date_time
	 */
	Date_time get_registration_date() const;
	/**
	 * @brief Get the type object
	 * 
	 * @return string 
	 */
	string get_type() const;
	/**
	 * @brief Get the brand object
	 * 
	 * @return string 
	 */
	string get_brand() const;
	/**
	 * @brief Get the license object
	 * 
	 * @return string 
	 */
	string get_license() const;
	/**
	 * @brief Get the trips object
	 * 
	 * @return unsigned 
	 */
	unsigned get_trips() const;
	/**
	 * @brief Get the mileage object
	 * 
	 * @return double 
	 */
	double get_mileage() const;
};


class Person {
protected:
	string name;
	int NIF;

public:
	/**
	 * @brief Construct a new Person object
	 * 
	 */
	Person();

	/**
	 * @brief Destroy the Person object
	 * 
	 */
	~Person();

	/**
	 * @brief Set the name object
	 * 
	 * @param nome 
	 */
	virtual void set_name(string nome);
	/**
	 * @brief 
	 * 
	 * @param NIF 
	 */
	virtual void set_NIF(int NIF);
	/**
	 * @brief Get the name object
	 * 
	 * @return string 
	 */
	string get_name() const;
	/**
	 * @brief Get the NIF object
	 * 
	 * @return int
	 */
	int get_NIF() const;
	/**
	 * @brief Shows on screen the persons attributes
	 * 
	 */
	virtual void print();

};


class Worker : public Person {
protected:
	Date_time birthday;
	double wage;
	bool isActive;

public:
	/**
	 * @brief Construct a new Worker object
	 * 
	 */
	Worker();

	/**
	 * @brief Destroy the Worker object
	 * 
	 */
	~Worker();

	/**
	 * @brief Opens the file with the name path and builds the worker objects with the information inside, saving them in the bases worker vector
	 * 
	 * @param path name of the workers' info file
	 * @param base base that will store the workers
	 */
	static void load(string path, Base * base);
	
	/**
	 * @brief Set the birthday object
	 * 
	 * @param data 
	 */
	virtual void set_birthday(Date_time birthday);
	/**
	 * @brief Set the wage object
	 * 
	 * @param salario 
	 */
	virtual void set_wage(double wage);

	/**
	 * @brief Set the state object
	 * 
	 * @param isActive If True, The Worker Is Currently Employee Of The Base; If False, It Is A Former Employee.
	 */
	virtual void set_state(bool isActive);

	/**
	 * @brief Get the birthday object
	 * 
	 * @return Date_time 
	 */
	Date_time get_birthday() const;
	/**
	 * @brief Get the wage object
	 * 
	 * @return double 
	 */
	double get_wage() const;

	/**
	 * @brief Get the state object
	 * 
	 * @return true If The Worker Is Currently Employee Of The Base
	 * @return false If The Worker Is A Former Employee
	 */
	bool get_state() const;


	/**
	 * @brief Shows on screen the workers attributes
	 * 
	 */
	virtual void print();
};



class Admin;

struct eqAdmin {
	bool operator()(const Admin* a1, const Admin* a2) const;
};

struct hashAdmin {
	int operator()(const Admin* a1) const;
};




class Admin : public Worker {
	string role;

public:

	/**
	 * @brief Construct a new Admin object
	 * 
	 */
	Admin();

	/**
	 * @brief Destroy the Admin object
	 * 
	 */
	~Admin();

	/**
	 * @brief Set the role object
	 * 
	 * @param papel 
	 */
	void set_role(string role);
	/**
	 * @brief Get the role object
	 * 
	 * @return string 
	 */
	string get_role() const;

	/**
	 * @brief Read Admins from stream (which contains the information from the text file) to unordered_set
	 * 
	 * @param workers_stream ifstream of the .txt file's info
	 * @return unordered_set<Admin*, hashAdmin, eqAdmin> 
	 */
	static unordered_set<Admin*, hashAdmin, eqAdmin> readAdmins(ifstream & workers_stream);

	/**
	 * @brief Shows on screen the admins attributes
	 * 
	 */
	void print();

	/**
	 * @brief Checks Equality of Admin Objects Based on Name, Nif and Role
	 * 
	 * @param a 
	 * @return true 
	 * @return false 
	 */
	bool operator==(const Admin &a);
};




class Delivery;

struct eqDeliv {
	bool operator()(const Delivery* d1, const Delivery* d2) const;
};

struct hashDeliv {
	int operator()(const Delivery* d1) const;
};


class Delivery : public Worker {
	Vehicle  vehicle;
	map<int, Order*> history;

public:
	/**
	 * @brief Construct a new Delivery object
	 * 
	 */
	Delivery();

	/**
	 * @brief Destroy the Delivery object
	 * 
	 */
	~Delivery();

	/**
	 * @brief Set the vehicle object
	 * 
	 * @param veiculo 
	 */
	void set_vehicle(Vehicle veiculo);
	/**
	 * @brief Set the history object
	 * 
	 * @param historial 
	 */
	void set_history(map<int, Order*> historial);
	/**
	 * @brief Set the Delivery Man Pointer on all of his order objects
	 * 
	 */
	void setDeliveryManPointerOnOrders();
	/**
	 * @brief Get the vehicle object
	 * 
	 * @return Vehicle 
	 */
	Vehicle  get_vehicle() const;
	/**
	 * @brief Get the history object
	 * 
	 * @return map<int, Order*> 
	 */
	map<int, Order*> get_history() const;

	/**
	 * @brief Read Deliverers from stream (which contains the information from the text file) to unordered_set
	 * 
	 * @param workers_stream ifstream of the .txt file's info
	 * @param base 
	 * @return unordered_set<Delivery*, hashDeliv, eqDeliv> 
	 */
	static unordered_set<Delivery*, hashDeliv, eqDeliv> readDeliverers(ifstream & workers_stream, Base * base);

	/**
	 * @brief Shows on screen the delivery mans attributes
	 * 
	 */
	void print();

	/**
	 * @brief Calculates the delivery mans' wage from his deliveries
	 * 
	 * @return double calculated value
	 */
	double calculate_wage();

	void update_vehicle();

	/**
	 * @brief Checks Equality of Delivery (People) Objects Based on Name and Nif
	 * 
	 * @param d 
	 * @return true 
	 * @return false 
	 */
	bool operator==(const Delivery &d);

};






class Client : public Person {
	Address address;
	Base * base;
	map<int, Order*> orders;

public:
	/**
	 * @brief Construct a new Client object
	 * 
	 */
	Client();

	/**
	 * @brief Destroy the Client object
	 * 
	 */
	~Client();
	
	/**
	 * @brief Opens the file with the name path and builds the client objects with the information inside, saving them in the bases worker vector

	 * 
	 * @param path name of the clients' info file
	 * @param base base that will store the clients
	 */
	static void load(string path, Base * base);

	/**
	 * @brief Set the address object
	 * 
	 * @param add 
	 */
	void set_address(Address add);
	/**
	 * @brief Set the base object
	 * 
	 * @param b 
	 */
	void set_base(Base * b);
	/**
	 * @brief Set the orders object
	 * 
	 * @param orders_vec 
	 */
	void set_orders(map<int, Order*> orders_vec);
	/**
	 * @brief Get the address object
	 * 
	 * @return Address 
	 */
	Address get_address() const;
	/**
	 * @brief Get the base object
	 * 
	 * @return Base* 
	 */
	Base * get_base() const;
	/**
	 * @brief Get the orders object
	 * 
	 * @return map<int, Order*> 
	 */
	map<int, Order*> get_orders() const;

	/**
	 * @brief Shows on screen the clients attributes
	 * 
	 */
	void print();

	/**
	 * @brief Creates a new order 
	 * 
	 * @param base base where the order will be saved
	 */
	void make_order(Base * base);
	/**
	 * @brief Edits a clients info
	 * 
	 * @param base base where the client belongs
	 */
	void edit(Base * base);
};


class Technician : public Person
{
private:	
	int availability;
	int maintenance;
public:
	Technician();
	~Technician();
	void set_availability(int a);
	void set_maintenance(int m);
	int get_availability() const;
	int get_maintenance() const;
	static void load(string path, Base * base);
	bool operator<(const Technician & tec) const;


};


#endif
