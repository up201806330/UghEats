#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <vector>
class Base;
class Client;

/**
 * @brief opens main menu, to select base and then client / admin mode
 * 
 * @param bases 
 */
void main_menu(std::vector<Base*> bases);
/**
 * @brief opens menu of selected client, to make order, see and edit info;
 * 
 * @param client 
 * @param base 
 */
void main_menu_client(Client* client, Base * base);
/**
 * @brief opens menu of selected base, to edit info
 * 
 * @param base 
 */
void main_menu_admin_base(Base * base);
/**
 * @brief opens menu of clients, to add, remove, edit and see info
 * 
 * @param base 
 */
void main_menu_admin_clients(Base * base);
/**
 * @brief opens menu of workers, to add, remove, edit and see info
 * 
 * @param base 
 */
void main_menu_admin_workers(Base * base);
/**
 * @brief opens menu of restaurants, to add, remove, edit and see info
 * 
 * @param base 
 */
void main_menu_admin_restaurant(Base * base);
/**
 * @brief opens menu of orders, see info
 * 
 * @param base 
 */
void main_menu_admin_orders(Base * base);
/**
 * @brief opens menu of profits
 * 
 * @param base 
 */
void main_menu_admin_profits(Base * base);

/**
 * @brief opens menu of vehicle info
 *
 * @param base
 */
void main_menu_admin_vehicles(Base * base);

/**
 * @brief opens menu of technicias info 
 *
 * @param base
 */
void main_menu_admin_technicians(Base * b);

/**
 * @brief opens menu of admin, to select other admin menus
 * 
 * @param base 
 */
void main_menu_admin(Base * base);
/**
 * @brief opens menu of client login / signup
 * 
 * @param base 
 */
void main_menu_client_login(Base * base);


#endif 
