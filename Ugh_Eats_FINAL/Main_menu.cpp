#include "Main_menu.h"
#include "Base.h"
#include "utils.h"
#include "Exceptions.h"

void main_menu_client(Client* client, Base * base) { //j� volta atr�s e j� fecha
	while (true) {
		string input;

		bool retry = true;
		do {
			try
			{
				utils::clear_screen();
				cout << "Welcome to Ugh Eats, " << client->get_name() << endl;
				cout << "1. Make order" << endl;
				cout << "2. Previous orders" << endl;
				cout << "3. My info" << endl;
				cout << "4. Edit Info" << endl;
				cout << "0. Go Back" << endl;
				cout << "5. Close Program" << endl;
				cout << ">> ";

				getline(cin, input);
				retry = false;

				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(5, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}
			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o << endl;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s << endl;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
		} while (retry);


		if (input == "1") { 
			utils::clear_screen();
			client->make_order(base); 
		}

		if (input == "2") {
			utils::clear_screen();

			if (client->get_orders().size() == 0) cout << "None" << endl;
			else {
				for (auto order : client->get_orders()) {
					cout << *order.second << endl << "-------------------------------" << endl;
				}
			}
			cout << ">>";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "3") { 
			utils::clear_screen(); 
			client->print(); 
			
			cout << "\n>>"; 
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}
		if (input == "4")
		{
			client->edit(base);
			continue;
		} //J� volta atr�s
		if (input == "0") {
			break; 
		}
		if (input == "5")
		{
			cin.clear();
			base->writeAll();
		}

		else continue;
	}
}

void main_menu_admin_base(Base * base)
{
	while (true) {
		string input;
		bool retry = true;
		do {
			try {
				utils::clear_screen();
				cout << "1. Show base info" << endl;
				cout << "2. Edit a base" << endl;
				cout << "0. Go Back" << endl;
				cout << ">> ";

				getline(cin, input);
				retry = false;
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(6, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o << endl;
				cout << "Try Again! " << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s << endl;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}

		} while (retry);
	
		if (input == "1") {
			utils::clear_screen();
			base->seeBase();

			cout << "\n>> ";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "2") {
			utils::clear_screen();
			base->changeBase();
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "0") {
			break;
		}
	}
}

void main_menu_admin_clients(Base * base) { 
	while (true) {
		string input;
		bool retry = true;
		do {
			try {
				utils::clear_screen();
				cout << "1. Show all clients" << endl;
				cout << "2. Search a client" << endl;
				cout << "3. Add a client" << endl;
				cout << "4. Edit a client" << endl;
				cout << "5. Remove a client" << endl;
				cout << "0. Go Back" << endl;
				cout << "6. Close Program" << endl;
				cout << ">> ";

				getline(cin, input);
				retry = false;
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(6, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o << endl;
				cout << "Try Again! " << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s << endl;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}

		} while (retry);
		

		if (input == "1") {
			utils::clear_screen();
			if(!base->orderClients()) continue;
			utils::clear_screen();
			base->seeAllClients(); //J� volta atr�s

			cout << "\n>> ";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "2") {
			base->seeOneClient(); //J� volta atr�s
		}

		if (input == "3") {
			utils::clear_screen();
			base->addClient(); //J� volta atr�s

		}

		if (input == "4") {
			utils::clear_screen();
			base->changeClient(); //J� volta atr�s

		}

		if (input == "5") {
			utils::clear_screen();
			base->removeClient(); //J� volta atr�s
		}

		if (input == "0") {
			break;
		}
		if (input == "6")
		{
			cin.clear();
			base->writeAll();
		}
	}
}

void main_menu_admin_workers(Base * base) { // j� volta atr�s e j� fecha
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try {
				utils::clear_screen();
				cout << "1. Show all workers" << endl;
				cout << "2. Search a worker" << endl;
				cout << "3. Add a worker" << endl;
				cout << "4. Edit a worker" << endl;
				cout << "5. Remove a worker" << endl;
				cout << "0. Go Back" << endl;
				cout << "6. Close Program" << endl;
				cout << ">> ";

				getline(cin, input);
				retry = false;
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(6, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}
			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
		} while (retry);
		

		if (input == "1") {
			utils::clear_screen();
			if (!base->orderWorkers()) continue; //N faco ideia como mas funciona lmao
			utils::clear_screen();
			base->seeAllWorkers(); //J� volta para tr�s
			
			cout << "\n>> ";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "2") {
			base->seeOneWorker(); //J� volta para tr�s
		}

		if (input == "3") {
			utils::clear_screen();
			base->addWorker(); //J� volta para tr�s
		}

		if (input == "4") {
			utils::clear_screen();
			base->changeWorker(); //J� volta para tr�s
		}

		if (input == "5") {
			base->removeWorker(); //J� volta para tr�s
			utils::clear_screen();
		}

		if (input == "0") {
			break;
		}
		if (input == "6")
		{
			cin.clear();
			base->writeAll();
		}

		else continue;
	}
}

void main_menu_admin_restaurant(Base * base) { // J� volta atr�s e j� fecha
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "1. Show all restaurant" << endl;
				cout << "2. Search a restaurant" << endl;
				cout << "3. Add a restaurant" << endl;
				cout << "4. Edit a restaurant" << endl;
				cout << "5. Remove a restaurant" << endl;
				cout << "0. Go Back" << endl;
				cout << "6. Close Program" << endl;
				cout << ">> ";

				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(6, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
					utils::clear_screen();
				}
			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}

		} while (retry);
		

		if (input == "1") {
			utils::clear_screen();
			if(!base->orderRestaurants()) continue;
			utils::clear_screen();
			base->seeAllRestaurants(); //J� volta para tr�s

			cout << "\n>> ";
			cin.clear();
			cin.ignore(INT_MAX,'\n');
		}

		if (input == "2") {
			base->seeOneRestaurant(); 
		}

		if (input == "3") {
			utils::clear_screen();
			base->addRestaurant(); //J� volta para tr�s
		}

		if (input == "4") {
			utils::clear_screen();
			base->changeRestaurant(); //J� volta para tr�s
		}

		if (input == "5") {
			utils::clear_screen();
			base->removeRestaurant(); //J� volta para tr�s
		}

		if (input == "0") {
			break;
		}
		if (input == "6")
		{
			cin.clear();
			base->writeAll();
		}
		else continue;
	}
}

void main_menu_admin_orders(Base * base) // J� volta atr�s e j� fecha
{
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "1. Show all orders" << endl;
				cout << "2. Search an order" << endl;
				cout << "0. Go Back" << endl;
				cout << "3. Close Program" << endl;
				cout << ">> ";

				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(3, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}

		} while (retry);
		

		if (input == "1") {
			utils::clear_screen();
			//if(!base->orderOrders()) continue;
			utils::clear_screen();
			base->seeAllOrders(); 
		}

		if (input == "2") {
			base->seeOneOrder(); 
		}
		
		if (input == "0") {
			break;
		}
		if (input == "3")
		{
			cin.clear();
			base->writeAll();
		}

		else continue;
	}
}

void main_menu_admin_profits(Base * base) { // J� volta atr�s e fecha
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "1. From this base" << endl;
				cout << "2. Per restaurant" << endl;
				cout << "3. Per client" << endl;
				cout << "4. Per time period" << endl;
				cout << "0. Go Back" << endl;
				cout << "5. Close Program" << endl;
				cout << ">> ";

				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(5, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch(InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
		} while (retry);


		if (input == "1") {
			utils::clear_screen();
			base->seeProfits(); //J� volta atr�s
		}
		if (input == "2") {
			utils::clear_screen();
			base->seeProfitsPerRestaurant(); //J� volta atr�s
		}
		if (input == "3") {
			utils::clear_screen();
			base->seeProfitsPerClient(); //J� volta atr�s
		}
		if (input == "4") {
			utils::clear_screen();
			base->seeProfitsPerTime(); //-> implementar as cenas qd a fun��o tiver pronta
		}

		if (input == "0") {
			break;
		}
		if (input == "5")
		{
			cin.clear();
			base->writeAll();
		}
		
		else continue;

	}
}

void main_menu_admin(Base * base) { // j� volta atr�s e j� fecha
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "1. Base" << endl;
				cout << "2. Clients" << endl;
				cout << "3. Workers" << endl;
				cout << "4. Restaurants" << endl;
				cout << "5. Orders" << endl;
				cout << "6. Profits" << endl;
				cout << "0. Go Back" << endl;
				cout << "7. Close Program" << endl;
				cout << ">> ";

				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(7, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
		} while (retry);


		if (input == "1") main_menu_admin_base(base);
		if (input == "2") main_menu_admin_clients(base);
		if (input == "3") main_menu_admin_workers(base);
		if (input == "4") main_menu_admin_restaurant(base);
		if (input == "5") main_menu_admin_orders(base);
		if (input == "6") main_menu_admin_profits(base);

		if (input == "0") { // volta atr�s
			break; 
		}
		if (input == "7")
		{
			cin.clear();
			base->writeAll();
		}
		else continue;
	}
}

void main_menu_client_login(Base * base){ // j� volta atr�s e j� fecha
	while (true) {
		string input;
		bool retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "1. Login" << endl;
				cout << "2. Sign up" << endl;
				cout << "0. Go Back" << endl;
				cout << "3. Close Program" << endl;
				cout << ">> ";
				
				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(3, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
		} while (retry);


		if (input == "1") {
			
			bool retry = true;
			do
			{
				try
				{
					retry = false;
					vector<Client*>::iterator it;
					vector<Client*> clients = base->getClients();

					cout << "\n\nClient name: ";
					getline(cin, input);

					if (!isString(input))
						throw InvalidStringException(input);



					bool notFound = true;
					for (it = clients.begin(); it != clients.end(); it++) {
						if ((*it)->get_name() == input)
						{
							main_menu_client(*it, base);
							notFound = false;
						}

						if ((*it)->get_name() == input) {
							main_menu_client(*it, base);
							notFound = false;
						}
					}


					if (notFound) {
						throw ClientNotFoundException(input);
					}
				}
				catch (ClientNotFoundException & c)
				{
					cout << c;
					cout << ">> ";
					cin.clear();
					cin.ignore(INT_MAX,'\n');
				}
				catch (InvalidStringException & s)
				{
					retry = true;
					cout << s;
					cout << "Try Again!" << endl << endl;				
					cin.clear();
					cin.ignore(INT_MAX,'\n');
				}
			} while (retry);
			


		}

		if (input == "2") {
			utils::clear_screen();
			bool teste = base->addClient();
			if (teste)
				main_menu_client(base->getClients().at(base->getClients().size() - 1), base);
			else
			{
				continue;
			}
		}

		if (input == "0") {
			break;
		}
		if (input == "3")
		{
			cin.clear();
			base->writeAll();
		}
		
		else continue;
	}
}

void main_menu(vector<Base*> bases) { 
	while (true) {
		string input;
		string temp;
		Base * selected_base;

		bool retry = true;
		do
		{
			try {
				utils::clear_screen();
				cout << "Pick a Base:" << endl;

				for (auto n = 0; n < bases.size(); n++) {
					cout << n + 1 << ". " << bases.at(n)->getDistrict() << endl;
				}

				cout << "0. Close" << endl;

				cout << ">> ";

				getline(cin, temp);

				retry = false;
				if (!isNumber(temp))
					throw InvalidNumberException(temp);
				if (temp != "")
				{
					if (InvalidOptions(bases.size(), stoi(temp)))
						throw InvalidOptionException(stoi(temp));
					else if (stoi(temp) == 0)
						throw InvalidOptionException(stoi(temp));
				}
				else
				{
					retry = true;
				}
			
			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}

		} while (retry);

		if (stoi(temp) == 0) exit(0);

		selected_base = bases.at(stoi(temp) - 1);

		retry = true;
		do
		{
			try
			{
				utils::clear_screen();
				cout << "Client or Admin ?" << endl; // j� volta atr�s e j� fecha
				cout << "1. Client" << endl;
				cout << "2. Admin" << endl;
				cout << "0. Go Back" << endl;
				cout << "3. Close Program" << endl;
				cout << ">> ";

				retry = false;
				getline(cin, input);
				if (!isNumber(input))
					throw InvalidNumberException(input);
				if (input != "")
				{
					if (InvalidOptions(3, stoi(input)))
						throw InvalidOptionException(stoi(input));
				}
				else
				{
					retry = true;
				}

			}
			catch (InvalidOptionException & o)
			{
				retry = true;
				cout << o;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			catch (InvalidNumberException & s)
			{
				retry = true;
				cout << s;
				cout << "Try Again!" << endl << endl;
				cin.clear();
				cin.ignore(INT_MAX,'\n');
			}
			if (input == "1")
			{
				main_menu_client_login(selected_base);
				retry = true;
				cout << endl;
			}
			if (input == "2")
			{
				main_menu_admin(selected_base);
				retry = true;
				cout << endl;
			}
			if (input == "0") {
				break; 
			}
			if (input == "3")
			{
				cin.clear();
				vector<Base*>::iterator it;
				//for (it = bases.begin(); it != bases.end(); it++)
				//{
				//	(*it)->writeAll();
				//}
				for (it = bases.begin(); it != bases.end(); it++)
				{
					//(*it)->writeAll();
				}

				exit(0);
				// return;  // <--- needs to return so that it plays the music.
				// Alternative is to get the 2 lines of the music part and put them before the exit(0)
			}
		} while (retry);
	}
}