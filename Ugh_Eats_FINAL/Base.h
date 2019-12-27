#ifndef BASE_H
#define BASE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <queue>
#include "Address.h"
#include "People.h"
#include "Restaurant.h"
#include "utils.h"
//#include "hash_table.h"

using namespace std;

/*
struct eqAdmin {
	bool operator()(const Admin* a1, const Admin* a2) const {
		return (
			a1->get_name() == a2->get_name() &&
			a1->get_NIF() == a2->get_NIF() &&
			a1->get_role() == a2->get_role() &&
			a1->get_wage() == a2->get_wage()
			);
	}
};

struct hashAdmin {
	int operator()(const Admin* a1) const {
		int v = 0;

		int nif = a1->get_NIF();

		while (nif > 0) {
			v += 51 * v + nif % 10;

			nif /= 10;
		}

		return v;
	}
};


struct eqDeliv {
	bool operator()(const Delivery* d1, const Delivery* d2) const {
		return (
			d1->get_name() == d2->get_name() &&
			d1->get_NIF() == d2->get_NIF() &&
			d1->get_wage() == d2->get_wage()
			);
	}
};

struct hashDeliv {
	int operator()(const Delivery* d1) const {
		int v = 0;

		int nif = d1->get_NIF();

		while (nif > 0) {
			v += 51 * v + nif % 10;

			nif /= 10;
		}

		return v;
	}
};
*/

class Base {
private:
	string restaurantsFileName;
	string deliveriesFileName;
	string workersFileName;
	string clientsFileName;
	string technicianFileName;
	string district;
	vector<string> areaOfInfluence;
	Address address;
	vector<Restaurant*> restaurants;
	map<int, Order*> orders;

	// vector<Worker*> workers;

	unordered_set<Admin*, hashAdmin, eqAdmin> admins;
	unordered_set<Delivery*, hashDeliv, eqDeliv> deliveryPeople;

	Admin * admin; // TODO change to manager
	vector<Client*> clients;
	priority_queue<Technician> technicians;
public:
	Base();

	~Base();

	static tuple<string, vector<string> > parseAreaOfInfluence(string str);

	/**
	 * @brief Opens file with the name path and builds the base objects with the information insie
	 * 
	 * @param path name of the bases' info file
	 * @return vector<Base*> vector with pointers to all base objects kept in the file
	 */
	static vector<Base*> load(string path); 

	/**
	 * @brief loads blacklist file and saves names of blacklisted clients; No parameters because the name of this file is constant.
	 * 
	 */
	static void load_blacklist();
	static vector<string> blacklist;
	
	/**
	 * @brief looks through a bases' vector of restaurants and finds the one with name str
	 * 
	 * @param str name of restaurant to be searched for
	 * @return Restaurant* pointer to restaurant, if found; is nullptr if not found
	 */
	Restaurant * findRestaurant(string str);
	/**
	 * @brief looks through a bases' map of orders and finds the ones with the ids in str
	 * 
	 * @param str string with "id:id:id:..." of the orders to be searched for
	 * @return map<int, Order*> map of found orders; empty if none are found
	 */
	map<int, Order*> findOrders(string str);

	/**
	 * @brief Set the Restaurants File Name object
	 * 
	 * @param str Restaurants file name
	 */
	void setRestaurantsFileName(string str);
	/**
	 * @brief Set the Deliveries File Name object
	 * 
	 * @param str Deliveries file name
	 */
	void setDeliveriesFileName(string str);
	/**
	 * @brief Set the Workers File Name object
	 * 
	 * @param str Workers file name
	 */
	void setWorkersFileName(string str);
	/**
	 * @brief Set the Clients File Name object
	 * 
	 * @param str Clients file name
	 */
	void setClientsFileName(string str);

	void setTechniciansFileName(string str);

	/**
	 * @brief Set the District object
	 * 
	 * @param d District
	 */
	void setDistrict(string d);
	/**
	 * @brief Set the Area Of Influence object
	 * 
	 * @param areaOfInf vector containing names of all towns adjacent to the bases'
	 */
	void setAreaOfInfluence(vector<string> areaOfInf);
	/**
	 * @brief Set the Address object
	 * 
	 * @param add Address
	 */
	void setAddress(Address add);

	/**
	 * @brief Set the Workers object
	 * 
	 * @param workers Workers
	 */
	/*
	void setWorkers(vector<Worker*> workers);
	*/

	/**
	 * @brief Set the Admins object
	 * 
	 * @param admins Administrators
	 */
	void setAdmins(unordered_set<Admin*, hashAdmin, eqAdmin> admins);

	/**
	 * @brief Set the Delivery People object
	 * 
	 * @param deliverers Delivery People
	 */
	void setDeliveryPeople(unordered_set<Delivery*, hashDeliv, eqDeliv> deliverers);

	/**
	 * @brief Set the Admin object
	 * 
	 * @param administrador Admin
	 */
	void setAdmin(Admin * administrador);
	/**
	 * @brief Set the Clients object
	 * 
	 * @param clients Clients
	 */
	void setClients(vector<Client*> clients);
	/**
	 * @brief Set the Orders object
	 * 
	 * @param orders Orders
	 */
	void setOrders(map<int,Order*> orders);
	/**
	 * @brief Set the Restaurants object
	 * 
	 * @param restaurants Restaurants
	 */
	void setRestaurants(vector<Restaurant*> restaurants);

	void setTechnicians(priority_queue<Technician> tec);


	/**
	 * @brief Get the Restaurants File Name object
	 * 
	 * @return string Restaurant file name
	 */
	string getRestaurantsFileName() const;
	/**
	 * @brief Get the Deliveries File Name object
	 * 
	 * @return string Deliveries file name
	 */
	string getDeliveriesFileName() const;
	/**
	 * @brief Get the Workers File Name object
	 * 
	 * @return string Workers file name
	 */
	string getWorkersFileName() const;
	/**
	 * @brief Get the Clients File Name object
	 * 
	 * @return string Clients file name
	 */
	string getClientsFileName() const;

	string getTechnicianFileName() const;

	/**
	 * @brief Get the District object
	 * 
	 * @return string District
	 */
	string getDistrict() const;
	/**
	 * @brief Get the Area Of Influence object
	 * 
	 * @return vector<string> Area of influence
	 */
	vector<string> getAreaOfInfluence() const;
	/**
	 * @brief Get the Address object
	 * 
	 * @return Address Address
	 */
	Address getAddress() const;

	/**
	 * @brief Get the Workers object
	 * 
	 * @return const vector<Worker*>& Workers vector reference
	 */
	/*
	const vector<Worker*> & getWorkers() const;
	*/

	/**
	 * @brief Get the Admins object
	 * 
	 * @return const unordered_set<Admin*, hashAdmin, eqAdmin> Admins' unordered_set
	 */
	const unordered_set<Admin*, hashAdmin, eqAdmin> getAdmins() const;

	/**
	 * @brief Get the Delivery People object
	 * 
	 * @return const unordered_set<Delivery*, hashDeliv, eqDeliv> Delivery People's unordered_set
	 */
	const unordered_set<Delivery*, hashDeliv, eqDeliv> getDeliveryPeople() const;

	/**
	 * @brief Get the Admin object
	 * 
	 * @return Admin* Admin pointer
	 */
	Admin * getAdmin() const;
	/**
	 * @brief Get the Clients object
	 * 
	 * @return const vector<Client*>& Clients vector reference
	 */
	const vector<Client*> & getClients() const;
	/**
	 * @brief Get the Restaurants object
	 * 
	 * @return const vector<Restaurant*>& Restaurants vector reference 
	 */
	const vector<Restaurant*> & getRestaurants() const;
	/**
	 * @brief Get the Orders object
	 * 
	 * @return const map<int, Order*>& Orders map reference
	 */
	const map<int, Order*> & getOrders() const;

	/**
	 * @brief Get the Delivery (Person) Object that has the Least Number of Deliveries
	 * 
	 * @return Delivery* Delivery (Person) Object
	 */
	Delivery* getDeliveryMan();


	priority_queue<Technician> getTechnicians() const;

	/**
	 * @brief prints all clients' info in human friendly fashion
	 * 
	 */
	void seeAllClients();

	/**
	 * @brief prints a clients' info in human friendly fashion
	 * 
	 */
	void seeOneClient();

	/**
	 * @brief prints all restaurants' info in human friendly fashion
	 * 
	 */
	void seeAllRestaurants();

	/**
	 * @brief prints a restaurants' info in human friendly fashion
	 * 
	 */
	void seeOneRestaurant();


	/**
	 * @brief Displays All of the Workers' Info in a Human Friendly Fashion
	 * 
	 * @param vectorData True If the Data To Display Is in the Next Two Parameters
	 * @param adminVector Vector Containing the Admin Objects
	 * @param delivPeopleVector Vector Containing the Delivery (People) Objects
	 */
	void seeAllWorkers(bool vectorData = false, vector<Admin*> adminVector = {}, vector<Delivery*> delivPeopleVector = {});

	/**
	 * @brief Displays a Specific Workers' Info in a Human Friendly Fashion
	 * 
	 */
	void seeOneWorker();

	/**
	 * @brief prints all delivery mens' info in human friendly fashion
	 * 
	 */
	/*
	void seeAllDeliverers();
	*/
	

	/**
	 * @brief Displays All of the Deliveries' People's Info in a Human Friendly Fashion
	 * 
	 * @param i Start Index For The Listing
	 * @param vectorData True If the Data To Display Is in the Next Parameter
	 * @param delivPeopleVector Vector Containing the Delivery (People) Objects
	 */
	void seeAllDeliveryPeople(int i = 1, bool vectorData = false, vector<Delivery*> delivPeopleVector = {});

	/**
	 * @brief prints all administrators' info in human friendly fashion
	 * 
	 */
	// void seeAllAdministrators();


	/**
	 * @brief Displays All of the Administrators' Info in a Human Friendly Fashion
	 * 
	 * @param i Start Index For The Listing
	 * @param vectorData True If the Data To Display Is in the Next Parameter
	 * @param adminVector Vector Containing the Admin Objects
	 */
	void seeAllAdmins(int i = 1, bool vectorData = false, vector<Admin*> adminVector = {});

	/**
	 * @brief prints all orders' info in human friendly fashion
	 * 
	 */
	void seeAllOrders();

	/**
	 * @brief prints an orders' info in human friendly fashion
	 * 
	 */
	void seeOneOrder();

	/**
	 * @brief prints profits generated by the base
	 * 
	 */
	void seeProfits(); 

	/**
	 * @brief prints profits generated by each restaurant
	 * 
	 */
	void seeProfitsPerRestaurant(); 

	/**
	 * @brief prints profits generated by each client
	 * 
	 */
	void seeProfitsPerClient(); 

	/**
	 * @brief prints profits generated during a time period
	 * 
	 */
	void seeProfitsPerTime();  // periodo de tempo
	
	void seeBase();

	/**
	 * @brief edits info of the base 
	 * 
	 */
	void changeBase(); 

	/**
	 * @brief add client to bases' vector of clients
	 * 
	 * @return true if successful (client not blacklisted)
	 * @return false otherwise
	 */
	bool addClient(); 
	/**
	 * @brief edits select client
	 * 
	 */
	void changeClient();
	/**
	 * @brief removes select client
	 * 
	 */
	void removeClient();

	/**
	 * @brief Add a Worker to the Base
	 * 
	 */
	void addWorker();

	/**
	 * @brief Add an Administrator to the Base
	 * 
	 */
	void addAdmin();

	/**
	 * @brief Checks if the Base has Already a Manager
	 * 
	 * @return true if it does
	 * @return false if it does not
	 */
	bool checkForManager();

	/**
	 * @brief Checks If the Admin Passed As a Parameter Is Already In The Database
	 * 
	 * @param a 
	 * @return true If Admin (Inactive) Was Found In Database (and Changed to Active)
	 * @return false If Admin Was Not Found In Database
	 */
	bool checkInactiveAdminInDatabase(Admin a);

	/**
	 * @brief Add a Delivery Person to the Base
	 * 
	 */
	void addDeliverer();

	/**
	 * @brief Checks If the Delivery (Person) Passed As a Parameter Is Already In The Database
	 * 
	 * @param d 
	 * @return true If Delivery (Person) (Inactive) Was Found In Database (and Changed to Active)
	 * @return false If Delivery (Person) Was Not Found In Database
	 */
	bool checkInactiveDelivPersonInDatabase(Delivery d);

	/**
	 * @brief Creates a Vehicle Object (and returns it)
	 * 
	 * @return Vehicle 
	 */
	Vehicle newVehicle();

	/**
	 * @brief Changes some Information about a Specific Worker
	 * 
	 */
	void changeWorker();

	// ------------------------------------------
	// Attributes to change

	/**
	 * @brief Receives the Current Name and Returns the Updated Name
	 * 
	 * @param currentName 
	 * @return string 
	 */
	string changeName(string currentName);

	/**
	 * @brief Receives the Current Nif and Returns the Updated Nif
	 * 
	 * @param currentNif 
	 * @return int 
	 */
	int changeNif(int currentNif);

	/**
	 * @brief Receives the Current Birthday and Returns the Updated Birthday
	 * 
	 * @param currentBday 
	 * @return Date_time 
	 */
	Date_time changeBirthday(Date_time currentBday);

	/**
	 * @brief Receives the Current Wage and Returns the Updated Wage
	 * 
	 * @param currentWage 
	 * @return double 
	 */
	double changeWage(double currentWage);

	/**
	 * @brief Receives the Current Role and Returns the Updated Role
	 * 
	 * @param currentRole 
	 * @param managerExists Prevents an Administrator from Changing his Role to Manager if a Manager Already Exists on the Base 
	 * @return string 
	 */
	string changeRole(string currentRole, bool managerExists);

	/**
	 * @brief Receives the Current Vehicle and Returns the Updated Vehicle
	 * 
	 * @param currentVehicle 
	 * @return Vehicle 
	 */
	Vehicle changeVehicle(Vehicle currentVehicle);

	map<int, Order*> changeHistory(map<int, Order*> currentHistory);

	// ------------------------------------------

	/**
	 * @brief Receives a Delivery (Person) Object, Updates it and Returns it 
	 * 
	 * @param d Delivery (Person) Object
	 * @return Delivery 
	 */
	Delivery changeDeliveryPerson(Delivery d);

	/**
	 * @brief Receives an Administrator Object, Updates it and Returns it 
	 * 
	 * @param a Administrator Object
	 * @return Admin 
	 */
	Admin changeAdmin(Admin a);

	/**
	 * @brief "Removes" a Specific worker (Changes the Respective Object to "Inactive")
	 * 
	 */
	void removeWorker();

	/**
	 * @brief add restaurant to bases' vector of restaurants
	 * 
	 */
	void addRestaurant();
	/**
	 * @brief edits select restaurant
	 * 
	 */
	void changeRestaurant();
	/**
	 * @brief removes select restaurant
	 * 
	 */
	void removeRestaurant();

	/**
	 * @brief orders vector of clients with select parameter
	 * 
	 * @return true if successful
	 * @return false otherwise
	 */
	bool orderClients();
	/**
	 * @brief orders vector of restaurants with select parameter
	 * 
	 * @return true if successful
	 * @return false otherwise
	 */
	bool orderRestaurants();

	/**
	 * @brief orders vector of workers with select parameter
	 * 
	 * @return true if successful
	 * @return false otherwise
	 */
	// bool orderWorkers();

	/**
	 * @brief Sorts All Workers Based on a Specific Parameter and Displays Their Information (seeAllWorkers Call)
	 * 
	 */
	void sortDisplayWorkers();

	bool orderOrders(); //lmao dont delete this may be useful


	void searchForRestaurant();          // por restaurante (mostra os produtos)
	void searchForGeographicArea();  // por zona geografica
	void searchForPriceRange(); // por intervalo de pre�os (por pre�o medio)
	void searchForCuisineTypes(); // por tipo de culin�ria

	/**
	 * @brief Write current restaurants objects to the file
	 * 
	 * @param fileName Restaurants file name
	 */
	void writeRestaurantsFile(string fileName);

	/**
	 * @brief Write current deliveries objects to the file
	 * 
	 * @param fileName Deliveries file name
	 */
	void writeDeliveriesFile(string fileName);

	/**
	 * @brief Write the Current Workers' Information to the Respective File
	 * 
	 * @param fileName Workers File Name to Write
	 */
	void writeWorkersFile(string fileName);

	/**
	 * @brief Write current clients objects to the file
	 * 
	 * @param fileName Clients file name
	 */
	void writeClientsFile(string fileName);

	/**
	 * @brief Call all write to file functions
	 * 
	 */
	void writeAll();

};

//comparison operators for sorts

/**
 * @brief compares clients by name
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool clientByName(const Client * left, const Client * right);
/**
 * @brief compares clients by NIF
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool clientByNIF(const Client * left, const Client * right);
/**
 * @brief compares restaurants by name
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool restaurantByName(const Restaurant * left, const Restaurant * right);
/**
 * @brief compares restaurants by price average
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool restaurantByPrice(const Restaurant * left, const Restaurant * right);
/**
 * @brief compares workers by name
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool workerByName(const Worker * left, const Worker * right);
/**
 * @brief compares workers by NIF
 * 
 * @param left 
 * @param right 
 * @return true 
 * @return false 
 */
bool workerByNIF(const Worker * left, const Worker * right);
/*
bool orderByPrice(const pair<int, Order*> & left, const pair<int, Order*> & right);
bool orderByFee(const pair<int, Order*> & left, const pair<int, Order*> & right);
*/

#endif

