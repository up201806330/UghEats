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
	string restaurantsFileName;
	string deliveriesFileName;
	string workersFileName;
	string clientsFileName;
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

	void setRestaurantsFileName(string str);
	void setDeliveriesFileName(string str);
	void setWorkersFileName(string str);
	void setClientsFileName(string str);

	void setDistrict(string d);
	void setAreaOfInfluence(vector<string> areaOfInf);
	void setAddress(Address add);
	void setWorkers(vector<Worker*> workers);
	void setAdmin(Admin * administrador);
	void setClients(vector<Client*> clients);
	void setOrders(map<int,Order*> orders);
	void setRestaurants(vector<Restaurant*> restaurants);

	void setDeliveryManPointerOnOrders(Delivery * x);


	string getRestaurantsFileName() const;
	string getDeliveriesFileName() const;
	string getWorkersFileName() const;
	string getClientsFileName() const;

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
	bool addClient(); //alterei o valor de retorno para bater certo c os menus
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

	void orderClients();
	void orderRestaurants();
	void orderWorkers();
	void orderOrders(); //lmao 

	// LEONOR
	// search options -> usar algoritmos de ordenação (ordem alfabetica), exceto no range de precos
	//				  -> usar algoritmos de procura

	void searchForRestaurant();          // por restaurante (mostra os produtos)
	void searchForGeographicArea();  // por zona geografica
	void searchForPriceRange(); // por intervalo de preços (por preço medio)

	void searchForCuisineTypes(); // por tipo de culinária

	Delivery* getDeliveryMan();

	
	void writeRestaurantsFile(string fileName);
	void writeDeliveriesFile(string fileName);
	void writeWorkersFile(string fileName);
	void writeClientsFile(string fileName);
	//void writeAll();


	

};

//comparison operators for sorts
bool clientByName(const Client * left, const Client * right);
bool clientByNIF(const Client * left, const Client * right);
bool restaurantByName(const Restaurant * left, const Restaurant * right);
bool restaurantByPrice(const Restaurant * left, const Restaurant * right);
bool workerByName(const Worker * left, const Worker * right);
bool workerByNIF(const Worker * left, const Worker * right);
/*
bool orderByPrice(const pair<int, Order*> & left, const pair<int, Order*> & right);
bool orderByFee(const pair<int, Order*> & left, const pair<int, Order*> & right);
*/

#endif

