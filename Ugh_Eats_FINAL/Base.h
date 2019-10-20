#ifndef BASE_H
#define BASE_H

#include <vector>
#include <fstream>
#include <sstream>
#include "Address.h"
#include "People.h"
#include "Restaurant.h"
#include "utils.h"


using namespace std;

class Base {
private:
	string district;
	Address address;
	vector<Restaurant*> restaurants;
	vector<Order*> deliveries;
	vector<Worker*> workers;
	Admin * admin;
	vector<Client*> clients;

public:
	Base();

	~Base();

	static vector<Base*> load(string path);
	
	Restaurant * findRestaurant(string str);
	vector<Order*> findOrders(string str);

	void setDistrict(string d);
	void setAddress(Address add);
	void setWorkers(vector<Worker*> workers);
	void setAdmin(Admin * administrador);
	void setClients(vector<Client*> clients);
	void setRestaurants(vector<Restaurant*> restaurants);
	string getDistrict() const;
	Address getAddress() const;
	vector<Worker*> getWorkers() const;
	Admin * getAdmin() const;
	vector<Client*> getClients() const;
	vector<Restaurant*> getRestaurants() const;
	vector <Order*> getOrders() const;

};




#endif

