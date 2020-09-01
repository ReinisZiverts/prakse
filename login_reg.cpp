/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "UserAdmin.h"
#include <string>



using json = nlohmann::json;

json j;
std::string pass;
std::string user;
std::string vards;
std::string uzvards;
std::string pass2;

void admin_regist() {

	std::ifstream i("dati.json");
	if (i.is_open()) {
		i >> j;
	}

	if (j["admin"]["Username"] == "admin") {

	}
	else {
		j["admin"]["Username"] = "admin";
		j["admin"]["Password"] = "admin";
		j["admin"]["Vards"] = "admin";
		j["admin"]["Uzvards"] = "admin";
		j["admin"]["Admin"] = 1;


		std::ofstream o("dati.json");
		o << std::setw(4) << j << '\n';
	}
}


void registracija()
{

	std::cout << std::endl << "Username: ";
	std::getline(std::cin >> std::ws, user);
	if (user.find_first_of(32) != std::string::npos) {
		system("cls");
		std::cout << "Lietotajvards Nevar saturet atstarpes!" << std::endl;
		return registracija();
	}

	std::string keyuser = user;
	std::transform(keyuser.begin(), keyuser.end(), keyuser.begin(), ::tolower);

	if (user == j[keyuser]["Username"]) {
		std::cout << "Lietotajvards aiznemts!" << std::endl;
		return registracija();
	}
	else {

		Vards:
		std::cout << "Vards: ";
		std::getline(std::cin >> std::ws, vards);
		if (vards.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
		{
			std::cout << "Vards nevar saturet specialos simbolus un ciparus" << std::endl;
			goto Vards;
		}
		vards[0] = toupper(vards[0]);
		for (unsigned int sk = 1; sk < vards.length(); sk++) {
			vards[sk] = tolower(vards[sk]);
		}

	
		Uzvards:
		std::cout << "Uzvards: ";
		std::getline(std::cin >> std::ws, uzvards);
		if (uzvards.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
		{
			std::cout << "Uzvards nevar saturet specialos simbolus un ciparus" << std::endl;
			goto Uzvards;
		}

		uzvards[0] = toupper(uzvards[0]);
		for (unsigned int sk = 1; sk < uzvards.length(); sk++) {
			uzvards[sk] = tolower(uzvards[sk]);
		}

		Paroles:

		std::cout << "Password: ";
		std::getline(std::cin >> std::ws, pass);
		if (pass.find_first_of(32) != std::string::npos) {
			std::cout << "Paroles nevar saturet atstarpes" << std::endl;
			goto Paroles;
		}
		std::cout << "Atkartoti paroli: ";
		std::getline(std::cin >> std::ws, pass2);
		if (pass != pass2) {
			std::cout << "Ievaditas paroles nesakrit, ludzu ievadiet atkartoti " << std::endl;
			goto Paroles;
		}
		std::ifstream i("dati.json");
		if (i.is_open()) {
			i >> j;
		}


		j[keyuser]["Username"] = user;
		j[keyuser]["Password"] = pass;
		j[keyuser]["Vards"] = vards;
		j[keyuser]["Uzvards"] = uzvards;
		j[keyuser]["Admin"] = 0;

		std::ofstream o("dati.json");
		o << std::setw(4) << j << '\n';

	}

	main();
}

void logins()
{
	
	std::ifstream i("dati.json");
	if (i.is_open()) {
		i >> j;
	}
	std::string izvele;
	std::cout << "1. Turpinat" <<std::endl;
	std::cout << "2. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";
	std::getline(std::cin >> std::ws, izvele);
	if (izvele.find_first_not_of("12") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis" << std::endl;
		return logins();
	}
	else if (izvele == "1") {
		system("cls");
		std::cout << "Ievadiet savu lietotajvardu: ";
		std::getline(std::cin >> std::ws, user);
		std::cout << "Ievadiet savu paroli: ";
		std::getline(std::cin >> std::ws, pass2);

		if (pass2 == j[user]["Password"]) {
			std::cout << "Jus esat veiksmigi ielogojies sistema.";
			if (j[user]["Admin"] == 1) {
				system("cls");
				return admin_panel();
			}
			else {
				system("cls");
				return user_panel();
			}

		}
		else {
			system("cls");
			std::cout << "Parole/lietotajvards  nav pareiza" << std::endl;
			logins();
			
		}
	}
	else if (izvele == "2") {
		system("pause");
		main();
	}

	

	 

}