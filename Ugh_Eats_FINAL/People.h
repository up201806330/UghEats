#ifndef PEOPLE_H
#define PEOPLE_H

#include <vector>
#include "utils.h"
#include "Date_time.h"
#include "Address.h"


class Base;
class Order;

using namespace std;

class Vehicle {  //ideias para funcoes para aqui??
	string brand;
	string type;
	Date registration_date;

public:
	Vehicle();

	~Vehicle();

	void parse(string str);

	void set_registrationDate(Date data);
	void set_type(string tipo);
	void set_brand(string marca);
	Date get_registration_date() const;
	string get_type() const;
	string get_brand() const;
};

class Person {
protected:
	string name;
	size_t NIF;

public:
	Person();

	~Person();

 // tratar da entrada ; excepcoes aqui ??
	virtual void set_name(string nome);
	virtual void set_NIF(size_t NIF);
	string get_name() const;
	size_t get_NIF() const;
	virtual void print();

};

class Worker : public Person {
protected:
	Date birthday;
	size_t wage;

public:
	Worker();

	~Worker();

	static void load(string path, Base * base);
	
	virtual void set_birthday(Date data);
	virtual void set_wage(size_t salario);
	virtual Worker * get_reference();
	Date get_birthday() const;
	size_t get_wage() const;

	virtual void print();
};

class Admin : public Worker {
	string role;

public:
	Admin();

	~Admin();

	void set_role(string papel);
	Admin * get_reference();
	string get_role() const;

	void print();
};

class Delivery : public Worker {
	Vehicle  vehicle;
	map<int, Order*> history;

public:
	Delivery();

	~Delivery();

	void set_vehicle(Vehicle veiculo);
	void set_history(map<int, Order*> historial);
	Delivery * get_reference();
	Vehicle  get_vehicle() const;
	map<int, Order*> get_history() const;
	void setDeliveryManPointerOnOrders();
	size_t calculate_wage();
	void print();
};

class Client : public Person {
	Address address;
	Base * base;
	map<int, Order*> orders;

public:
	Client();

	~Client();
	
	static void load(string path, Base * base);

	void set_address(Address add);
	void set_base(Base * b);
	void set_orders(map<int, Order*> orders_vec);
	Address get_address() const;
	Base * get_base() const;
	map<int, Order*> get_orders() const;

	void print();

	void make_order(Base * base);
	void edit();
};



#endif
