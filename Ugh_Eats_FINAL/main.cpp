#pragma comment(lib, "winmm.lib")

#include <iostream>
#include "Address.h"
#include "People.h"
#include "Base.h"
#include "Date_time.h"
#include "utils.h"
#include "Restaurant.h"
#include "Main_menu.h"

#include <Windows.h>
#include <mmsystem.h>

int main() {
	PlaySound(TEXT("MicrosoftWindowsXPStartupSoundEffect.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//string path; cout << "Please input the file path (with .txt): "; cin >> path;
	string path = "bases.txt";
	vector<Base*> bases = Base::load(path);


	
	// bases.at(0)->getClients().at(1)->make_order(bases.at(0));
	// cout << bases.at(0)->getClients().at(1)->get_orders().size() << endl;

	/*
	cout << bases.at(0)->getWorkers().at(3)->get_name() << endl;
	bases.at(0)->removeWorker();
	cout << bases.at(0)->getWorkers().at(3)->get_name() << endl;
	*/

	/*
	cout << bases.at(0)->getClients().at(2)->get_name() << endl;
	bases.at(0)->removeClient();
	cout << bases.at(0)->getClients().at(2)->get_name() << endl;
	*/
	
	/*
	cout << bases.at(0)->getRestaurants().at(0)->get_name() << endl;
	bases.at(0)->removeRestaurant();
	cout << bases.at(0)->getRestaurants().at(0)->get_name() << endl;
	*/

	//bases.at(0)->getClients().at(1)->make_order(bases.at(0));
	//cout << bases.at(0)->getClients().at(1)->get_orders().size() << endl;

	//bases.at(0)->getClients().at(0)->make_order(bases.at(0));

	// bases.at(0)->getClients().at(0)->make_order(bases.at(0));


	// bases.at(0)->changeClient();
	// cout << bases.at(0)->getAreaOfInfluence().size() << endl;
	// cout << bases.at(0)->getClients().at(0)->get_name() << endl;
	// cout << bases.at(0)->getClients().at(0)->get_NIF() << endl;

	// cout << bases.at(0)->getClients().at(0)->get_address() << endl;
	// cout << bases.at(0)->getClients().at(0)->get_base()->getAreaOfInfluence().size() << endl;

	// bases.at(0)->writeRestaurantsFile("idk.txt");

	//bases.at(0)->writeDeliveriesFile("idk.txt");

	 //bases.at(0)->writeDeliveriesFile("idk.txt");
	//bases.at(0)->writeWorkersFile("idk.txt");
	// bases.at(0)->writeClientsFile("idk.txt");

	/*
	cout << bases.at(0)->getAddress() << endl;
	bases.at(0)->changeBase();
	cout << bases.at(0)->getAddress() << endl;
	*/

	/*for (auto & t : bases.at(0)->getAreaOfInfluence()) {
		cout << t << endl;
	}*/
	
	//bases.at(0)->changeBase();
	
	//bases[0]->searchForCuisineTypes();
	/*
	cout << bases.at(0)->getRestaurants().at(0)->get_name() << endl;
	cout << bases.at(0)->getRestaurants().size() << endl;
	bases.at(0)->removeRestaurant();
	cout << bases.at(0)->getRestaurants().at(0)->get_name() << endl;
	cout << bases.at(0)->getRestaurants().size() << endl;
	*/

	// bases.at(0)->changeRestaurant();

	/*
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_name() << endl;
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_products().size() << endl;
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_products().at(0)->get_name() << endl;
	cout << endl;
	bases.at(0)->createRestaurant();
	cout << endl;
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_name() << endl;
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_products().size() << endl;
	cout << bases.at(0)->getRestaurants().at(bases.at(0)->getRestaurants().size() - 1)->get_products().at(0)->get_name() << endl;
	*/

	/*
	cout << bases.at(0)->getWorkers().at(2)->get_name() << endl;
	bases.at(0)->removeWorker();
	cout << bases.at(0)->getWorkers().at(2)->get_name() << endl;
	*/

	// bases[0]->seeProfitsPerTime();

	// bases.at(0)->createRestaurant();


	// cout << "Brand: " << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(3))->get_vehicle().get_brand() << endl;
	// cout << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(3))->get_birthday().get_day() << endl;
	//bases.at(0)->changeWorker();
	// cout << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(3))->get_birthday().get_day() << endl;
	// cout << "Brand: " << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(3))->get_vehicle().get_brand() << endl;
	// cout << "I DID IT: " << bases.at(0)->getWorkers().at(1)->get_name() << endl;
	
	// bases[0]->searchForPriceRange();


	/*
	cout << bases.at(0)->getWorkers().at(1)->get_birthday().get_day() << endl;
	bases.at(0)->addWorker();
	cout << bases.at(0)->getWorkers().at(1)->get_birthday().get_day() << endl;
	*/

	/*
	cout << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(bases.at(0)->getWorkers().size() - 1))->get_vehicle().get_brand() << endl;
	bases.at(0)->addWorker();
	cout << dynamic_cast<Delivery*>(bases.at(0)->getWorkers().at(bases.at(0)->getWorkers().size() -1))->get_vehicle().get_brand() << endl;
	*/
	
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
	

	main_menu(bases);
	

	// Sleep(5000);
	PlaySound(TEXT("MicrosoftWindowsXPShutdownSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(3000);
	return 0;

}