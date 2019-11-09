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

	//Visualização de Informação <- Leonor
	void seeAllClients();
	void seeOneClient();
	void seeAllRestaurants(); // display all the restaurants that are connected to the base
	// see one
	void seeAllWorkers(); // display all the workers that are connected to the base
	// see one
	// ... de acordo com o doc word
	// void seeAreOfInfluence(); // display the "area of influence" of the base (districts) <- talvez nao
	void seeAllOrders();
	// see one
	void seeProfits(); // display the profits of the base
	// base
	// restaurante
	// cliente
	// periodo de tempo


	
	int changeBase(); // change info about the base. Calls the following functions:
	// changeAddress(); // change the address of the base (must be in the same district?)



	// criar, alterar e apagar coisas dos vetores de cada base <- JA
	void addClient();
	void changeClient();
	void removeClient();

	void addWorker();
	void changeWorker();
	void removeWorker();

	void createRestaurant();
	void changeRestaurant();
	void removeRestaurant();
	// clients -> eliminar também orders
	// workers
	// restaurants


	// LEONOR
	// search options -> usar algoritmos de ordenação (ordem alfabetica), exceto no range de precos
	//				  -> usar algoritmos de procura
	// por restaurante (mostra os produtos)
	// por zona geografica
	// por intervalo de preços (por preço medio)
	// por tipo de culinária

	// camelCase


	
	// guardar informacao
	// fazer só no fim de tudo

	// overload do <<
	// 

	

};




#endif

