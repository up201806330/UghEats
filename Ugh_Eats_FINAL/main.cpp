#include <iostream>
#include "Address.h"
#include "People.h"
#include "Base.h"
#include "Date_time.h"
#include "utils.h"
#include "Restaurant.h"

int main(){
	//string path; cout << "Please input the file path (with .txt): "; cin >> path;
	string path = "bases.txt";
	vector<Base*> bases = Base::load(path);

	// bases.at(0)->seeOneRestaurant();

	/*
	cout << "PREVIOUS: " << bases.at(0)->getClients().at(0)->get_name() << endl;
	bases.at(0)->changeClient();
	cout << "UPDATED: " << bases.at(0)->getClients().at(0)->get_name() << endl;
	*/

	// bases.at(0)->seeOneOrder();

	/*
	for (auto & c : bases.at(0)->getClients()) {
		cout << c->get_name() << endl;
	}
	cout << endl;
	bases.at(0)->removeClient();
	cout << endl;
	for (auto & c : bases.at(0)->getClients()) {
		cout << c->get_name() << endl;
	}
	*/

	/*
	cout << bases.at(0)->getAddress();
	cout << endl << endl;
	cout << "Clients number: " << bases.at(0)->getClients().size() << endl;
	bases.at(0)->addClient();
	cout << endl;
	cout << "Clients number: " << bases.at(0)->getClients().size() << endl;
	cout << "Nome: " << bases.at(0)->getClients().at(4)->get_name() << endl;
	*/
	
	return 0;
}


// preciso testar os prints todos para ver se estao formatados
// preciso arranjar hora atual
// testar o uso de sets