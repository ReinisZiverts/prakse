/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/
#include <iostream>
#include "json.hpp"
#include <string>
#include <fstream>
#include <iomanip>
#include "user_funkcijas.h"
#include <ctime>

extern std::string user;

using json = nlohmann::json;
json h;
json gg;



bool checkdate(int m, int d, int y) {
	if (!(1589 <= y))
		return false;
	if (!(1 <= m && m <= 12))
		return false;
	if (!(1 <= d && d <= 31))
		return false;
	if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
		return false;
	if ((d == 30) && (m == 2))
		return false;
	if ((m == 2) && (d == 29) && (y % 4 != 0))
		return false;
	if ((m == 2) && (d == 29) && (y % 400 == 0))
		return true;
	if ((m == 2) && (d == 29) && (y % 100 == 0))
		return false;
	if ((m == 2) && (d == 29) && (y % 4 == 0))
		return true;

	return true;

}

int meklesana(std::string faila_nosaukums, std::string *meklesanasArray, std::string search, int meklesanas_i) {
	std::ifstream p(faila_nosaukums);
	if (p.is_open()) {
		p >> h;
	}

	

	for (auto& el : h.items()) {
		std::string nosaukums = el.key();
		int results = meklesanas_funkcija(search, nosaukums);
		for (auto& el2 : h.at(nosaukums).at("Nosaukums").items()) {
			std::string capnosaukums = el2.value();
			if (results != -1) {
				std::cout << meklesanas_i << "." << capnosaukums << std::endl;
				meklesanasArray[meklesanas_i - 1] = nosaukums;
				meklesanas_i++;
			}
		}
	}

	return meklesanas_i;
}

void json_atversana() {
	std::ifstream dati("dati.json");
	if (dati.is_open()) {
		dati >> gg;
	}

	std::ifstream reisi("reisi.json");
	if (reisi.is_open()) {
		reisi >> h;
	}
}




void rezervesana() {

	std::string izvele;
	std::string faila_nosaukums = "reisi.json";
	std::string *meklesanasArray = new std::string[1000];
	int izvele_meklesana;

	std::cout << "Pec kadiem parametriem velaties meklet?" << std::endl;
	std::cout << "1. Pec datuma" << std::endl;
	std::cout << "2. Pec (izlidosanas vietas, Galamerka, izlidosanas vietas - galamerka" << std::endl;
	std::cout << "3. Atpakal" << std::endl;
	std::cout << "Jusu izvele: " << std::endl;

	std::getline(std::cin >> std::ws, izvele);

	if (izvele.find_first_not_of("123") != std::string::npos)
	{
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		return rezervesana();
	}
	else if (izvele == "1") {
		system("cls");
	datums:
		int dd, mm, yy;

		std::cout << "Ievdiet datumu pec kura meklesiet (D/M/YYYY)" << std::endl;
		scanf_s("%d/%d/%d", &dd, &mm, &yy);

		std::string datums = std::to_string(dd) + "/" + std::to_string(mm) + "/" + std::to_string(yy);

		if (checkdate(mm, dd, yy)) {
			json_atversana();
			int meklesana_x = 1;
			int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, datums,meklesana_x);
			if (meklesanas_mainigais == 1) {
				system("cls");
				std::cout << "Nekas netika atrasts! " << std::endl;
				return rezervesana();
			}


			MEKLESANA_USER_REISU_ADR:
			std::cout << "Izvelaties reisu: ";
			std::cin >> izvele_meklesana;
			if (izvele_meklesana > meklesanas_mainigais - 1 || izvele_meklesana < 1) {
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto MEKLESANA_USER_REISU_ADR;

			} 

			system("cls");

			std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana - 1] << std::endl;
			std::string izveletais = meklesanasArray[izvele_meklesana - 1];

			Izvele_rezervacija:

			std::cout << "Ko velaties darit: " << std::endl;
			std::cout << "1. Rezervet" << std::endl;
			std::cout << "2. Meklet jaunu" << std::endl;
			std::cout << "Jusu izvele: ";
			std::string izvele_rezerv;
			std::getline(std::cin >> std::ws, izvele_rezerv);
			if (izvele_rezerv.find_first_not_of("123") != std::string::npos) {
				system("cls");
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto Izvele_rezervacija;
			}
			else if (izvele_rezerv == "1") {

				int value = rand() % 999999999 + 000000001;
				
					for (auto&el : gg.items()) {
						std::string username = el.key();
						if (gg[username].find("Rezervacijas") != gg[username].end()) {

							for (auto& el2 : gg.at(username).at("Rezervacijas").items()) {
								std::string rezervnos = el2.key();
								for (auto& el3 : gg.at(username).at("Rezervacijas").at(rezervnos).at("Rezervacijas Nr").items()) {
									int value2 = el3.value();
									if (value2 == value) {
										value = rand() % 999999999 + 000000001;
									}
								}
							}
						}
					}
				
				

				
				gg[user]["Rezervacijas"][izveletais] = h[izveletais];
				gg[user]["Rezervacijas"][izveletais]["Rezervacijas Nr"] = value;

				std::ofstream o("dati.json");
				o << std::setw(4) << gg << '\n';

			}
			else if (izvele_rezerv == "2") {
				return rezervesana();
			}


		}
		else {
			system("cls");
			std::cout << "Ievadits nepareizs formats vai nederigs datums" << std::endl;
			goto datums;
		}

	}
	else if (izvele == "2") {
		system("cls");
		json_atversana();

	Izvele2:
		std::cout << "Izvelaties ko darit !" << std::endl;
		std::cout << "1. Meklet" << std::endl;
		std::cout << "2. Atpakal " << std::endl;
		std::cout << "Jusu izvele: ";

		std::string izvele2;
		std::getline(std::cin >> std::ws, izvele2);
		if (izvele2.find_first_not_of("12") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto Izvele2;
		}
		else if (izvele2 == "2") {
			system("cls");
			return user_panel();
		}
		else if (izvele2 == "1") {
			Izlidosanas_vieta:
			std::string izlidosanas_vieta;
			std::cout << "Ievadiet meklejamo parametru: ";
			std::getline(std::cin >> std::ws, izlidosanas_vieta);

			if (izlidosanas_vieta.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ") != std::string::npos) {
				system("cls");
				std::cout << "Ievaditais satur neatlautus simbolus" << std::endl;
				goto Izlidosanas_vieta;
			}

			std::transform(izlidosanas_vieta.begin(), izlidosanas_vieta.end(), izlidosanas_vieta.begin(), ::tolower);

			int meklesana_x = 1;
			int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, izlidosanas_vieta, meklesana_x);
			if (meklesanas_mainigais == 1) {
				system("cls");
				std::cout << "Nekas netika atrasts! " << std::endl;
				return rezervesana();
			}


			MEKLESANA_USER_REISU:
			std::cout << "Izvelaties reisu: ";
			std::cin >> izvele_meklesana;
			if (izvele_meklesana > meklesanas_mainigais - 1 || izvele_meklesana < 1) {
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto MEKLESANA_USER_REISU;

			}

			system("cls");

			std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana - 1] << std::endl;
			std::string izveletais = meklesanasArray[izvele_meklesana - 1];

			Izvele_rezervacija2:

			std::cout << "Ko velaties darit: " << std::endl;
			std::cout << "1. Rezervet" << std::endl;
			std::cout << "2. Meklet jaunu" << std::endl;
			std::cout << "3. Uz Profilu" << std::endl;
			std::cout << "Jusu izvele: ";

			std::string izvele_rezerv;
			std::getline(std::cin >> std::ws, izvele_rezerv);
			if (izvele_rezerv.find_first_not_of("123") != std::string::npos) {
				system("cls");
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto Izvele_rezervacija2;
			}
			else if (izvele_rezerv == "1") {

				if (h[izveletais]["Lidmasina"]["Vietu skaits"] <= "0") {
					std::cout << "Saja reisa vietu vairak nav!" << std::endl;
					return rezervesana();
				}
				else {
					int value = rand() % 999999999 + 000000001;

					for (auto&el : gg.items()) {
						std::string username = el.key();
						if (gg[username].find("Rezervacijas") != gg[username].end()) {

							for (auto& el2 : gg.at(username).at("Rezervacijas").items()) {
								std::string rezervnos = el2.key();
								for (auto& el3 : gg.at(username).at("Rezervacijas").at(rezervnos).at("Rezervacijas Nr").items()) {
									int value2 = el3.value();
									if (value2 == value) {
										value = rand() % 999999999 + 000000001;
									}
								}
							}
						}
					}


					gg[user]["Rezervacijas"][izveletais] = h[izveletais];
					gg[user]["Rezervacijas"][izveletais]["Rezervacijas Nr"] = value;

					std::string ss = h[izveletais]["Lidmasina"]["Vietu skaits"];
					int d = std::stoi(ss);
					int c = d - 1;
					std::string b = std::to_string(c);

					h[izveletais]["Lidmasina"]["Vietu skaits"] = b;


					std::ofstream lid("reisi.json");
					lid << std::setw(4) << h << '\n';

					std::ofstream o("dati.json");
					o << std::setw(4) << gg << '\n';
				}
			}
			else if (izvele_rezerv == "2") {
				return rezervesana();
			}
		}
	


		
	}
	else if (izvele == "3") {
	return user_panel();
		}
		
		return user_panel();
}
void rezervacijas() {


	json rezerv;
	std::ifstream rez("dati.json");
	if (rez.is_open()) {
		rez >> rezerv;
	}

	

	if (rezerv[user].find("Rezervacijas") == rezerv[user].end())
	{
		std::cout << "Jums nav rezervaciju!" << std::endl;
		system("pause");
		system("cls");
		return user_panel();
	}
	else {
		std::cout << "Jusu rezervacijas: " << std::endl;

		std::string *meklesanasArray = new std::string[1000];

		std::cout << "Rezervaciju saraksts: " << std::endl;

		int x = 1;


		for (auto& el : rezerv.at(user).at("Rezervacijas").items()) {
			std::string rez_nosaukums = el.key();
			for (auto& el2 : rezerv.at(user).at("Rezervacijas").at(rez_nosaukums).at("Nosaukums").items()) {
				std::string rez_caps = el2.value();

				std::cout << x << ". " << rez_caps << std::endl;
				meklesanasArray[x - 1] = rez_nosaukums;
				x++;
			}
		}


		IZVELE_ATCELT_REZERVACIJU:
		int izvele_meklesana;
		std::cout << "Ievadiet ar kuru rezervaciju velaties veikt labojumus: ";
		std::cin >> izvele_meklesana;
		if (izvele_meklesana > x - 1 || izvele_meklesana < 1) {
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto IZVELE_ATCELT_REZERVACIJU;

		}

		system("cls");

		std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana - 1] << std::endl;
		std::string izveletais = meklesanasArray[izvele_meklesana - 1];

		Rezerv_Izvele:
		std::cout << "Ko velaties darit ?" << std::endl;
		std::cout << "1. Atcelt" << std::endl;
		std::cout << "2. Drukat bileti" << std::endl;
		std::cout << "3. Atpakal" << std::endl;
		std::cout << "Jusu izvele: ";

		std::string izveletais_skaitlis;
		std::getline(std::cin >> std::ws, izveletais_skaitlis);
		if (izveletais_skaitlis.find_first_not_of("12") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto Rezerv_Izvele;
		} 
		else if (izveletais_skaitlis == "1") {

			if (x == 2) {
				json_atversana();

				std::string vietas = h[izveletais]["Lidmasina"]["Vietu skaits"];
				int cipar_vietas = std::stoi(vietas);
				int c_vietas = cipar_vietas + 1;
				std::string b_vietas_str = std::to_string(c_vietas);

				h[izveletais]["Lidmasina"]["Vietu skaits"] = b_vietas_str;
				std::ofstream lid("reisi.json");
				lid << std::setw(4) << h << '\n';

				rezerv.at(user).erase("Rezervacijas");
			}
			else {
				rezerv.at(user).at("Rezervacijas").erase(izveletais);
				json_atversana();

				std::string vietas = h[izveletais]["Lidmasina"]["Vietu skaits"];
				int cipar_vietas = std::stoi(vietas);
				int c_vietas = cipar_vietas + 1;
				std::string b_vietas_str = std::to_string(c_vietas);

				h[izveletais]["Lidmasina"]["Vietu skaits"] = b_vietas_str;
				std::ofstream lid("reisi.json");
				lid << std::setw(4) << h << '\n';

				rezerv.at(user).erase("Rezervacijas");
			}

			std::ofstream o("dati.json");
			o << std::setw(4) << rezerv << '\n';

			std::cout << "Rezervacija izdzesta!" << std::endl;
			system("pause");

		}
		else if (izveletais_skaitlis == "2") {
			json_atversana();
			std::string vards = gg.at(user).at("Vards");
			std::string uzvards = gg.at(user).at("Uzvards");
			int rezervacijas_nr = gg.at(user).at("Rezervacijas").at(izveletais).at("Rezervacijas Nr");
			std::string virziens_no_uz = gg.at(user).at("Rezervacijas").at(izveletais).at("Virziens no-uz");
			std::string izlid_datums = gg.at(user).at("Rezervacijas").at(izveletais).at("Izlidosanas datums");
			std::string izlid_laiks = gg.at(user).at("Rezervacijas").at(izveletais).at("Izlidosanas laiks");
			std::string ielid_datums = gg.at(user).at("Rezervacijas").at(izveletais).at("Ielidosanas datums");
			std::string ielid_laiks = gg.at(user).at("Rezervacijas").at(izveletais).at("Ielidosanas laiks");
			std::string lidm = gg.at(user).at("Rezervacijas").at(izveletais).at("Lidmasina").at("Nosaukums");
			std::ofstream e;
			std::string faila_nosaukums = user + "_Rezervacija.html";
			e.open(faila_nosaukums);

			e << "<!DOCTYPE HTML>";
			e << "<html>";
			e << "<body>";
			e << "<style>";
			e << "table,td {border:1px solid black; border-collapse:collapse;}";
			e << "</style>";
			e << "<table>";
			e << "<tr>";
			e << "<td>" << vards << " " << uzvards << "</td>";
			e << "<td>" << "Rez. Nr " << rezervacijas_nr << "</td>";
			e << "</tr>";
			e << "<tr>";
			e << "<td>Lidojums</td>";
			e << "<td>" << virziens_no_uz << "</td>";
			e << "</tr>";
			e << "<tr>";
			e << "<td>Izlidosana</td>";
			e << "<td>" << izlid_datums <<" "<< izlid_laiks << "</td>";
			e << "</tr>";
			e << "<tr>";
			e << "<td>Ielidosana</td>";
			e << "<td>" << ielid_datums << " " << ielid_laiks << "</td>";
			e << "</tr>";
			e << "<tr>";
			e << "<td>Lidmasina</td>";
			e << "<td>" << lidm << "</td>";
			e << "</tr>";
			e << "</table>";
			e << "</body>";
			e << "</html>";


			e.close();

		}
		else return user_panel();


	}

	return user_panel();
}