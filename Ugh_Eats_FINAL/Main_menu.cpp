#include "Main_menu.h"
#include "Base.h"
#include "utils.h"


void main_menu_client(Client* client) {
	while (true) {
		string input;
		utils::clear_screen();

		cout << "Welcome to Ugh Eats!" << endl;
		cout << "1. Make order" << endl;
		cout << "2. Edit Info" << endl;
		cout << "CTRL+Z to save and exit" << endl;
		cout << ">> ";

		getline(cin, input);

		if (input == "1") client->make_order();
		if (input == "2") client->edit();
		if (cin.eof()) exit(0); //<------------------------- implement something to save and exit

		else continue;
	}
}

void main_menu_admin() {
	return;
}

void main_menu_client_login(Base * base){
	while (true) {
		string input;
		utils::clear_screen();

		cout << "login: "; cin.ignore(); getline(cin, input);

		vector<Client*>::iterator it;
		vector<Client*> clients = base->getClients();
		for (it = clients.begin(); it != clients.end(); it++) {
			if ((*it)->get_name() == input) main_menu_client(*it);
		}

		cout << "Client not found; Try again (Enter to continue)" << endl;
		cout << ">> ";
		cin.ignore();
	}
}

void main_menu(vector<Base*> bases) {
	while (true) {
		string input;
		size_t temp;
		Base * selected_base;
		utils::clear_screen();

		cout << "Pick a Base:" << endl;

		for (auto n = 0; n < bases.size(); n++) {
			cout << n + 1 << ". " << bases.at(n)->getDistrict() << endl;
		}

		cout << ">> ";
		
		cin >> temp;
		if (cin.fail() || temp > bases.size()) continue;

		else {
			selected_base = bases.at(temp - 1);
		}

		cout << "\n\n";
		cout << "Client or Admin ?" << endl;
		cout << "1. Client" << endl;
		cout << "2. Admin" << endl;
		cout << ">> ";

		cin >> input;

		if (input == "1") main_menu_client_login(selected_base);
		if (input == "2") main_menu_admin();

		else continue;
	}
}