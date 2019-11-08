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
	vector<Order*> orders;
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
	void setOrders(vector<Order*> orders);
	void setRestaurants(vector<Restaurant*> restaurants);
	string getDistrict() const;
	Address getAddress() const;
	vector<Worker*> getWorkers() const;
	Admin * getAdmin() const;
	vector<Client*> getClients() const;
	vector<Restaurant*> getRestaurants() const;
	vector <Order*> getOrders() const;

	//Visualização de Informação
	void seeAllClients();

	// PROPOSTAS de funções para implementar; posso ser eu a implementar as funções da classe Base if u peeps want ( - Já )
	void seeAllRestaurants(); // display all the restaurants that are connected to the base
	void seeAllWorkers(); // display all the workers that are connected to the base
	void seeAreOfInfluence(); // display the "area of influence" of the base (districts)
	void seeProfits(); // display the profits of the base

	int changeBase(); // change info about the base. Calls the following functions:
	int changeAddress(); // change the address of thee base (must be in the same district?)
	// IN PROGRESS

};




#endif

