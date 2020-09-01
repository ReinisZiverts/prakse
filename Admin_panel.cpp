/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/
#include <iostream>
#include <string>
#include "admin_funkcijas.h"
#include "login_reg.h"

extern std::string user;

void admin_panel()
{
	
	std::string izvele;

	std::cout << "Profils: " << user << std::endl;

	std::cout << "Ar ko velaties veikt darbibas?" << std::endl;
	std::cout << "1. Lidostas" << std::endl;
	std::cout << "2. Lidmasinas" << std::endl;
	std::cout << "3. Reisi" << std::endl;
	std::cout << "4. Statistika" << std::endl;
	std::cout << "5. Pievienot/ Nonemt admin" << std::endl;
	std::cout << "6. Izlogoties" << std::endl;
	std::cout << "Jusu izvele: ";
	std::getline(std::cin >> std::ws, izvele);
	if (izvele.find_first_not_of("123456") != std::string::npos)
	{
		std::cout << "Ievaditais skaitlis neieklaujas 1 - 6 robezas" << std::endl;
		return admin_panel();
	}
	else if (izvele == "1") {
		system("cls");
		return lidostas();
	}
	else if (izvele == "2") {
		system("cls");
		return lidmasinas();
	}

	else if (izvele == "3") {
		system("cls");
		return reisi();
	}
	else if (izvele == "4") {
		system("cls");
		return statistika();
	}
	else if (izvele == "5") {
		system("cls");
		return pievienot_admin();

	}
	else if (izvele == "6") {
		int izvele_admin_log;
		std::cout << "Vai tiesam velaties izogoties? " << std::endl;
		std::cout << "1. Ja" << std::endl;
		std::cout << "2. Ne" << std::endl;
		std::cin >> izvele_admin_log;
		if (izvele_admin_log == 1) {
			system("cls");
			main();
	
		}
	}

}
