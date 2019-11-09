#include "People.h"
#include "Base.h"
#include "Restaurant.h"
#include "utils.h"

string MAIN_SEPARATOR = ";;;";
string SEC_SEPARATOR = ";";


Vehicle::Vehicle()
{

}

Vehicle::~Vehicle()
{

}

void Vehicle::parse(string str){
	vector<string> parts = utils::split(str, ':');
	brand = parts.at(0);
	type = parts.at(1);
	registration_date.parse(parts.at(2));
}

void Vehicle::set_registrationDate(Date data)
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

Date Vehicle::get_registration_date() const
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

void Person::set_NIF(size_t NIF)
{
	this->NIF = NIF;
}

string Person::get_name() const
{
	return name;
}

size_t Person::get_NIF() const
{
	return NIF;
}

void Person::print() 
{
	cout << "Name: " << name << endl;
	cout << "NIF: " << NIF << endl;
}

Worker::Worker() {
}

Worker::~Worker() {

}

void Worker::load(string path, Base * base){
	ifstream workers_text(path);
	cout << "Workers file: " << path << endl;
	string textline;
	vector <Worker*> workers_vec;
	while (getline(workers_text,textline) && textline != MAIN_SEPARATOR) {
		if (textline == SEC_SEPARATOR) getline(workers_text, textline);
		Admin x;
		x.set_name(textline);

		getline(workers_text, textline);
		x.set_NIF(stoi(textline));

		getline(workers_text, textline);
		Date d; d.parse(textline);
		x.set_birthday(d);
		
		getline(workers_text, textline);
		x.set_wage(stoi(textline));

		getline(workers_text, textline);
		x.set_role(textline);

		Admin * ptr = new Admin;
		*ptr = x;
		workers_vec.push_back(ptr);
	}

	while(getline(workers_text,textline)){
		
		if (textline == SEC_SEPARATOR) getline(workers_text, textline);
		Delivery x;
		x.set_name(textline);

		getline(workers_text, textline);
		x.set_NIF(stoi(textline));

		getline(workers_text, textline);
		Date d; d.parse(textline);
		x.set_birthday(d);

		getline(workers_text, textline);
		Vehicle v; v.parse(textline); x.set_vehicle(v);

		getline(workers_text, textline);
		x.set_history(base->findOrders(textline));

		Delivery * ptr = new Delivery;
		*ptr = x;
		workers_vec.push_back(ptr);
	}

	base->setWorkers(workers_vec);
}

void Worker::set_birthday(Date data) {
	birthday = data;
}

void Worker::set_wage(size_t salario) {
	wage = salario;
}

Worker * Worker::get_reference()
{
	return this;
}

Date Worker::get_birthday() const {
	return birthday;
}

size_t Worker::get_wage() const {
	return wage;
}

void Worker::print(){

	Person::print();
	cout << "Birthday: " << birthday.str() << endl;
	cout << "Wage: " << wage << endl;


}

Admin::Admin() {

}

Admin::~Admin() {

}

void Admin::set_role(string papel) {
	role = papel;
}

Admin * Admin::get_reference()
{
	return this;
}

string Admin::get_role() const {
	return role;
}

void Admin::print() { 
	Worker::print();
	cout << "Role: " << role << endl;
}

Delivery::Delivery() {

}

Delivery::~Delivery() {

}

void Delivery::set_vehicle(Vehicle  veiculo) {
	vehicle = veiculo;
}

void Delivery::set_history(vector<Order*> historial) {
	history = historial;
}

Delivery * Delivery::get_reference()
{
	return this;
}

Vehicle Delivery::get_vehicle() const {
	return vehicle;
}

vector<Order*> Delivery::get_history() const {
	return history;
}

void Delivery::print() {
	Worker::print();
	cout << "Vehicle: " << endl;
	cout << "   Brand: " << vehicle.get_brand() << endl;
	cout << "   Type: " << vehicle.get_type() << endl;
	cout << "   Registration Date: " << vehicle.get_registration_date().str() << endl;
	cout << "History: ";
	if (history.size() == 0)
		cout << "none";
	else
	{
		vector<Order*>::iterator it;
		for (it = history.begin(); it != history.end(); it++)
		{
			cout << (*it)->getID() << " ";
		}
	}
	
	cout << endl;
}

size_t Delivery::calculate_wage() {//implementar dps 
	return 0;
}

Client::Client() {

}

Client::~Client() {

}

void Client::load(string path, Base * base) { 
	ifstream clients_text(path);

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

void Client::set_orders(vector <Order*> orders_vec) {	
	orders = orders_vec;
}

Address Client::get_address() const {
	return address;
}

Base * Client::get_base() const {
	return base;
}

vector <Order*> Client::get_orders() const {
	return orders;
}

void Client::print() { 
	Person::print();
	cout << address;
//	cout << "Base: " << base->getDistrict() << endl;
	cout << "Orders: ";
	if (orders.size() == 0)
		cout << "none"<<endl;
	else {
		vector<Order*>::iterator it;
		for (it = orders.begin(); it != orders.end(); it++)
		{
			cout << (*it)->getID() << " ";
		}
		cout << endl;
	}



}