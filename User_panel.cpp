/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/
#include <iostream>
#include <string>
#include "user_funkcijas.h"


extern std::string user;

void user_panel()
{
	system("cls");
	std::string izvele;

	std::cout << "Profils: " << user << std::endl;
	std::cout << "Ko Jus velaties darit? " << std::endl;
	std::cout << "1. Meklet reisu" << std::endl;
	std::cout << "2. Paradit rezervaciju" << std::endl;
	std::cout << "3. Izlogoties" << std::endl;
	std::cout << "Jusu izvele: ";
	std::getline(std::cin >> std::ws, izvele);

	if (izvele.find_first_not_of("123") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		return user_panel();
	}
	else if (izvele == "1") { 
		system("cls");
		rezervesana();

	}
	else if (izvele == "2") {
		system("cls");
		return rezervacijas();

	}
	else if (izvele == "3") {
		system("cls");
		main();
	} 





}