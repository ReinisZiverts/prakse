/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/

#include <iostream>
#include "login_reg.h"
#include <string>



int main()
{

	admin_regist();

	std::string izvele;


	std::cout << "Labdien, Ludzu izvelaties ko velaties darit." << std::endl;
	std::cout << "1. Ielogoties" << std::endl;
	std::cout << "2. Registreties" << std::endl;
	std::cout << "3. Iziet" << std::endl;
	std::cout << "Jusu izvele: ";
	std::getline(std::cin >> std::ws, izvele);

	if (izvele.find_first_not_of("123") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis, ludzu atkartot" << std::endl;
		main(); // Jasalabo.
	}
	else if (izvele == "1") {
		system("cls");
		return logins();

	}
	else if (izvele == "2") {
		system("cls");
		std::cout << "Ludzu ievadiet nepieciesamos datus: ";
		return registracija();

	}
	else if (izvele == "3") {
		return 0;
	}
}