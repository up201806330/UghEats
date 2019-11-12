#ifndef BASE_H
#define BASE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>
#include "Address.h"
#include "People.h"
#include "Restaurant.h"
#include "utils.h"


using namespace std;

class Base {
private:
	string district;
	vector<string> areaOfInfluence;
	Address address;
	vector<Restaurant*> restaurants;
	map<int, Order*> orders;
	vector<Worker*> workers;
	Admin * admin;
	vector<Client*> clients;

public:
	Base();

	~Base();

	static tuple<string, vector<string> > parseAreaOfInfluence(string str);

	static vector<Base*> load(string path);
	static void load_blacklist();

	static vector<string> blacklist;
	
	Restaurant * findRestaurant(string str);
	map<int, Order*> findOrders(string str);

	void setDistrict(string d);
	void setAreaOfInfluence(vector<string> areaOfInf);
	void setAddress(Address add);
	void setWorkers(vector<Worker*> workers);
	void setAdmin(Admin * administrador);
	void setClients(vector<Client*> clients);
	void setOrders(map<int,Order*> orders);
	void setRestaurants(vector<Restaurant*> restaurants);

	void setDeliveryManPointerOnOrders(Delivery * x);

	string getDistrict() const;
	vector<string> getAreaOfInfluence() const;
	Address getAddress() const;
	const vector<Worker*> & getWorkers() const;
	Admin * getAdmin() const;
	const vector<Client*> & getClients() const;
	const vector<Restaurant*> & getRestaurants() const;
	const map<int, Order*> & getOrders() const;

	//Visualização de Informação <- Leonor
	void seeAllClients();
	void seeOneClient();
	void seeAllRestaurants(); // display all the restaurants that are connected to the base
	void seeOneRestaurant();
	void seeAllWorkers(); // display all the workers that are connected to the base
	void seeOneWorker();
	void seeAllDeliverers();
	void seeAllAdministrators();
	// void seeAreOfInfluence(); // display the "area of influence" of the base (districts) <- talvez nao
	void seeAllOrders();
	void seeOneOrder();
	void seeProfits(); // display the profits of the base
	void seeProfitsPerRestaurant(); // restaurante
	void seeProfitsPerClient(); // cliente
	void seeProfitsPerTime();  // periodo de tempo

	
	
	void changeBase(); // change address of the base

	// criar, alterar e apagar coisas dos vetores de cada base <- JA
	void addClient();
	void changeClient();
	void removeClient();

	void addWorker();
	void changeWorker();
	void removeWorker();

	void addRestaurant();
	void changeRestaurant();
	void removeRestaurant();
	// clients -> eliminar também orders
	// workers
	// restaurants


	// LEONOR
	// search options -> usar algoritmos de ordenação (ordem alfabetica), exceto no range de precos
	//				  -> usar algoritmos de procura

	void searchForRestaurant();          // por restaurante (mostra os produtos)
	void searchForGeographicArea();  // por zona geografica
	void searchForPriceRange(); // por intervalo de preços (por preço medio)

	void searchForCuisineTypes(); // por tipo de culinária

	Delivery* getDeliveryMan();

	

	


	// camelCase


	
	// guardar informacao
	// fazer só no fim de tudo

	// overload do <<
	// 

	

};




#endif

