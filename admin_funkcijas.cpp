/*
* Autors: Reinis Ziverts
* Grupa: D2-1
*/
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include "admin_funkcijas.h"
#include <algorithm>

using json = nlohmann::json;
json g;




int meklesana(std::string faila_nosaukums, std::string *meklesanasArray, int meklesanas_i) {
	MEK_FUNKC:
	json meklesana_j;
	std::ifstream p(faila_nosaukums);
	if (p.is_open()) {
		p >> meklesana_j;
	}

	std::cout << "Ievadiet ko velaties meklet: ";
	std::string search;
	std::cin >> search;
	std::transform(search.begin(), search.end(), search.begin(), ::tolower);
	if (search.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345678990/: ") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		goto MEK_FUNKC;
	}
	
	for (auto& el : meklesana_j.items()) {
		std::string nosaukums = el.key();
		int results = meklesanas_funkcija(search, nosaukums);
		for (auto& el2 : meklesana_j.at(nosaukums).at("Nosaukums").items()) {
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

int meklesanas_funkcija(std::string Meklejamais, std::string Mekletajs) {
	int M = Meklejamais.length();
	int N = Mekletajs.length();

	for (int i = 0; i <= N - M; i++) {
		int j;

		for (j = 0; j < M; j++)
			if (Mekletajs[i + j] != Meklejamais[j])
				break;

		if (j == M)
			return i;
	}

	return -1;
}

int viss_saraksts(std::string faila_nosaukums, std::string* meklesanasArray, std::string grupas_nosaukums,int saraksta_x) {

	std::ifstream i(faila_nosaukums);
	if (i.is_open()) {
		i >> g;
	}


	std::cout << grupas_nosaukums << " saraksts: " << std::endl;


	for (auto& el : g.items()) {
		std::string grupasnos = el.key();
		for (auto& el2 : g.at(grupasnos).at("Nosaukums").items()) {
			std::string capnosaukums = el2.value();
			std::cout << saraksta_x << ". " << capnosaukums << std::endl;
			meklesanasArray[saraksta_x - 1] = el.key();
			saraksta_x++;
		}
	}

	return saraksta_x;
	
}
void mainit_key(json &j, std::string& labojamais, std::string& labojums)
{
	auto itr = j.find(labojamais);
	std::swap(j[labojums], itr.value());
	g.erase(itr);
}

void labosana(std::string faila_nosaukums, std::string labojamais, std::string labojamais_value)
{
	std::ifstream i(faila_nosaukums);
	if (i.is_open()) {
		i >> g;
	}
	std::string labojums;
	std::cout << "Ievadiet savu labojumu: ";
	std::getline(std::cin >> std::ws, labojums);
	std::string lowernosaukums = g[labojamais][labojamais_value];
	std::transform(lowernosaukums.begin(), lowernosaukums.end(), lowernosaukums.begin(), ::tolower);

	if (labojamais == lowernosaukums) {
		g[labojamais][labojamais_value] = labojums;
		std::transform(labojums.begin(), labojums.end(), labojums.begin(), ::tolower);
		mainit_key(g, labojamais, labojums);
	}
	else g[labojamais][labojamais_value] = labojums;
	

	std::ofstream o(faila_nosaukums);
	o << std::setw(4) << g << '\n';
	

}



void lidostas()
{
	std::string izvele;
	std::string grupas_nosaukums = "Lidostu";
	std::string faila_nosaukums = "lidostas.json";

	std::string* meklesanasArray;
	meklesanasArray = new std::string[256];


	std::cout << "Ko velaties veikt ar Lidostam ?" << std::endl;
	std::cout << "1. Pievienot" << std::endl;
	std::cout << "2. Labot" << std::endl;
	std::cout << "3. Dzest" << std::endl;
	std::cout << "4. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";
	std::getline(std::cin >> std::ws, izvele);

	if (izvele.find_first_not_of("1234") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		return lidostas();
	}
	else if (izvele == "1") {
		system("cls");

		std::ifstream i("lidostas.json");
		if (i.is_open()) {
			i >> g;
		}

		
		std::cout << "Ievadiet nepieciesamos parametrus: " << std::endl;
		std::cout << "Nosaukums: ";
		std::string nosaukums;
		std::getline(std::cin >> std::ws, nosaukums);
		std::cout << "Saisinajums: ";
		std::string saisinajums;
		std::getline(std::cin >> std::ws, saisinajums);
		std::cout << "Adrese: ";
		std::string adrese;
		std::getline(std::cin >> std::ws, adrese);


		std::string keynosaukums = nosaukums;
		std::transform(keynosaukums.begin(), keynosaukums.end(), keynosaukums.begin(), ::tolower);

		g[keynosaukums]["Nosaukums"] = nosaukums;
		g[keynosaukums]["Saisinajums"] = saisinajums;
		g[keynosaukums]["Adrese"] = adrese;

		std::ofstream o("lidostas.json");
		o << std::setw(4) << g << '\n';
		
	}
	else if (izvele == "2") {
		system("cls");

		IZVELEDIVI:
		std::string izvele_meklesana;

		std::cout << "Ko velies darit?" << std::endl;
		std::cout << "1. Meklet" << std::endl;
		std::cout << "2. Paradit sarakstu" << std::endl;
		std::cout << "3. Atpakal" << std::endl << std::endl;
		std::cout << "Jusu izvele: ";

		std::string izvele2;
		std::getline(std::cin >> std::ws, izvele2);
		if (izvele2.find_first_not_of("123") != std::string::npos) {
			system("cls");
			std::cout << "Ievaditais skaitlis ir nepareizs! " << std::endl;
			goto IZVELEDIVI;
		}
		else if (izvele2 == "1") {

			system("cls");
			std::ifstream i("lidostas.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidosta" << std::endl;
				system("pause");
				system("cls");
				return lidostas();
				
			}
			else {
				int meklesanas_i = 1;
				int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, meklesanas_i);
				if (meklesanas_mainigais == 1) {
					system("cls");
					std::cout << "Nekas netika atrasts! " << std::endl;
					return lidostas();
				}

				MEKLESANAS_LIDOSTA:
				std::cout << "Ievadiet ar kuru lidostu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto MEKLESANAS_LIDOSTA;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > meklesanas_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto MEKLESANAS_LIDOSTA;
				}


				system("cls");

			LIDOSTAS_labot:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Nosaukumu" << std::endl;
				std::cout << "2. Saisinajumu" << std::endl;
				std::cout << "3. Adresi" << std::endl;
				std::cout << "Jusu izvele: ";

				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;

				if (labosanas_izvele.find_first_not_of("123") != std::string::npos) {
					system("cls");
					std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
					goto LIDOSTAS_labot;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Nosaukums";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Saisinajums";
				}
				else if (labosanas_izvele == "3") {
					labojamais_value = "Adrese";
				}
				labosana(faila_nosaukums, labojamais, labojamais_value);



				delete[] meklesanasArray;
			}
		}
		else if (izvele2 == "2") {
			system("cls");
			std::ifstream i("lidostas.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidosta" << std::endl;
				system("pause");
				system("cls");
				return lidostas();

			}
			else {

				int saraksta_x = 1;
				int saraksta_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksta_x);


			SARAKSTS_LIDOSTA:
				std::cout << "Ievadiet ar kuru lidostu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto SARAKSTS_LIDOSTA;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > saraksta_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto SARAKSTS_LIDOSTA;
				}

				system("cls");

			LIDOSTAS_LABOT:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Nosaukumu" << std::endl;
				std::cout << "2. Saisinajumu" << std::endl;
				std::cout << "3. Adresi" << std::endl;
				std::cout << "Jusu izvele: ";

				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;

				if (labosanas_izvele.find_first_not_of("123") != std::string::npos) {
					system("cls");
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto LIDOSTAS_LABOT;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Nosaukums";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Saisinajums";
				}
				else if (labosanas_izvele == "3") {
					labojamais_value = "Adrese";
				}
				labosana(faila_nosaukums, labojamais, labojamais_value);



				delete[] meklesanasArray;
			}
		}
		else if (izvele2 == "3") {
			system("cls");
			return lidostas();
		}

	}
	else if (izvele == "3") {

		system("cls");
		std::ifstream i("lidostas.json");
		if (i.is_open()) {
			i >> g;
		}


		if (g.empty())
		{
			std::cout << "Nav pievienota neviena lidosta" << std::endl;
			system("pause");
			system("cls");
			return lidostas();

		}
		else {

			int saraksta_x = 1;
			std::string izvele_meklesana;
			int sarasksta_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksta_x);

		SARAKSTS_LIDOSTA_DZEST:
			std::cout << "Ievadiet kuru lidostu velaties dzest? ";
			std::getline(std::cin >> std::ws, izvele_meklesana);

			if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto SARAKSTS_LIDOSTA_DZEST;

			}

			int izvele_meklesana2 = std::stoi(izvele_meklesana);

			if (izvele_meklesana2 > sarasksta_mainigais - 1) {
				std::cout << "Ievadits nepareizs skaitlis " << std::endl;
				goto SARAKSTS_LIDOSTA_DZEST;
			}


			std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

			g.erase(labojamais);

			std::ofstream o("lidostas.json");
			o << std::setw(4) << g << '\n';

			delete[] meklesanasArray;
		}
	}
	else if (izvele == "4") {
	system("cls");
	return admin_panel();

	}

	system("cls");
	return admin_panel();
}

void lidmasinas()
{
	std::string izvele;
	std::string grupas_nosaukums = "Lidmasinu";
	std::string faila_nosaukums;
	faila_nosaukums = "lidmasinas.json";

	std::string* meklesanasArray;
	meklesanasArray = new std::string[256];

	std::cout << "Ko velaties veikt ar Lidmasinam ?" << std::endl;
	std::cout << "1. Pievienot" << std::endl;
	std::cout << "2. Labot" << std::endl;
	std::cout << "3. Dzest" << std::endl;
	std::cout << "4. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";

	std::getline(std::cin >> std::ws, izvele);

	if (izvele.find_first_not_of("1234") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		return lidmasinas();
	}
	else if (izvele == "1") {
		system("cls");

		std::ifstream i("lidmasinas.json");
		if (i.is_open()) {
			i >> g;
		}


		json gg;
		std::ifstream ii("lidostas.json");
		if (ii.is_open()) {
			ii >> gg;
		}

		if (gg.empty())
		{
			std::cout << "Nav pievienota neviena lidosta!" << std::endl;
			system("pause");
			system("cls");
			return lidostas();

		}

		std::cout << "Meklejiet kurai lidostai velaties pievienot lidmasinu." << std::endl;
		int meklesanas_i = 1;
		int meklesanas_mainigais = meklesana("lidostas.json", meklesanasArray, meklesanas_i);

		if (meklesanas_mainigais == 1) {
			system("cls");
			std::cout << "Nekas netika atrasts! " << std::endl;
			return lidmasinas();
		}

		std::string izvele_meklesana;
		std::cout << "Ievadiet Kurai lidostai velaties pievienot lidmasinu : ";
		std::getline(std::cin >> std::ws, izvele_meklesana);

		if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			return lidmasinas();

		}

		int izvele_meklesana2 = std::stoi(izvele_meklesana);

		if (izvele_meklesana2 > meklesanas_mainigais - 1) {
			std::cout << "Ievadits nepareizs skaitlis " << std::endl;
			return lidmasinas();
		}


		system("cls");

	
		std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
		std::string izveletais = meklesanasArray[izvele_meklesana2 - 1];


		

		std::cout << "Ievadiet nepieciesamos parametrus: " << std::endl;
		std::cout << "Modelis: ";
		std::string modelis;
		std::getline(std::cin >> std::ws, modelis);
		std::cout << "Razosanas gads: ";
		std::string razosanas_gads;
		std::getline(std::cin >> std::ws, razosanas_gads);
		std::cout << "Vietu skaits: ";
		std::string vietu_skaits;
		std::getline(std::cin >> std::ws, vietu_skaits);
		
		std::string keymodelis = modelis;
		std::transform(keymodelis.begin(), keymodelis.end(), keymodelis.begin(), ::tolower);

		g[keymodelis]["Nosaukums"] = modelis;
		g[keymodelis]["Razosanas gads"] = razosanas_gads;
		g[keymodelis]["Vietu skaits"] = vietu_skaits;
		gg[izveletais]["Lidmasinas" + keymodelis] = g[keymodelis]["Vietu skaits"];

		std::ofstream oo("lidostas.json");
		oo << std::setw(4) << gg << '\n';

		std::ofstream o("lidmasinas.json");
		o << std::setw(4) << g << '\n';
	}
	else if (izvele == "2") {
		system("cls");

		Lidmasinas_LABOT:

		std::string izvele_meklesana;

		std::cout << "Ko velies darit?" << std::endl;
		std::cout << "1. Meklet" << std::endl;
		std::cout << "2. Paradit sarakstu" << std::endl;
		std::cout << "3. Atpakal" << std::endl << std::endl;
		std::cout << "Jusu izvele: ";
		std::string izvele2;
		std::getline(std::cin >> std::ws, izvele2);

		if (izvele2.find_first_not_of("123") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
			goto Lidmasinas_LABOT;
		}
		else if (izvele2 == "1") {

			system("cls");
			std::ifstream i("lidmasinas.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidmasina" << std::endl;
				system("pause");
				system("cls");
				return lidmasinas();

			}
			else {


				int meklesana_i = 1;
				int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, meklesana_i);
				if (meklesanas_mainigais == 1) {
					system("cls");
					std::cout << "Nekas netika atrasts! " << std::endl;
					return lidmasinas();
				}

			MEKLESANA_LIDMASINA:
				std::cout << "Ievadiet ar kuru lidmasinu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto MEKLESANA_LIDMASINA;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > meklesanas_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto MEKLESANA_LIDMASINA;
				}

				system("cls");
			Labosana_lidm:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Modeli" << std::endl;
				std::cout << "2. Razosanas gadu" << std::endl;
				std::cout << "3. Vietu skaitu" << std::endl;
				std::cout << "Jusu izvele: ";

				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;

				if (labosanas_izvele.find_first_not_of("123") != std::string::npos) {
					system("cls");
					std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
					goto Labosana_lidm;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Modelis";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Razosanas gads";
				}
				else if (labosanas_izvele == "3") {
					std::ifstream i("lidmasinas.json");
					if (i.is_open()) {
						i >> g;
					}
					json gg;
					std::ifstream ii("lidostas.json");
					if (ii.is_open()) {
						ii >> gg;
					}

					std::string labojums;
					std::cout << "Ievadiet savu labojumu: ";
					std::getline(std::cin >> std::ws, labojums);
					
					g[labojamais][labojamais_value] = labojums;
					for (auto lid : gg.items()) {
						std::string lid_nos = lid.key();
						if (gg["Lidmasinas" + labojamais] == "Lidmasinas" + labojamais) {
							gg["Lidmasinas" + labojamais]["Vietu skaits"] = labojums;
						}
					}
					

					std::ofstream o(faila_nosaukums);
					o << std::setw(4) << g << '\n';

				}

				labosana(faila_nosaukums, labojamais, labojamais_value);


				delete[] meklesanasArray;
			}
		}
		else if (izvele2 == "2") {

			system("cls");
			std::ifstream i("lidmasinas.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidmasina" << std::endl;
				system("pause");
				system("cls");
				return lidmasinas();

			}
			else {

				int saraksts_x = 1;
				int saraksts_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksts_x);


			SARAKSTS_LIDMASINA:
				std::cout << "Ievadiet ar kuru lidmasinu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto SARAKSTS_LIDMASINA;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > saraksts_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto SARAKSTS_LIDMASINA;
				}


				system("cls");
			LABOSANA_lidmasinas:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Modeli" << std::endl;
				std::cout << "2. Razosanas gadu" << std::endl;
				std::cout << "3. Vietu skaitu" << std::endl;
				std::cout << "Jusu izvele: ";

				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;

				if (labosanas_izvele.find_first_not_of("123") != std::string::npos) {
					system("cls");
					std::cout << "Ievaditais skaitlis nav pareizs!" << std::endl;
					goto LABOSANA_lidmasinas;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Modelis";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Razosanas gads";
				}
				else if (labosanas_izvele == "3") {
					labojamais_value = "Adrese";
				}

				labosana(faila_nosaukums, labojamais, labojamais_value);



				delete[] meklesanasArray;
			}
		}
	}
	else if (izvele == "3") {

		system("cls");
		std::ifstream i("lidmasinas.json");
		if (i.is_open()) {
			i >> g;
		}


		if (g.empty())
		{
			std::cout << "Nav pievienota neviena lidmasina!" << std::endl;
			system("pause");
			system("cls");
			return lidmasinas();

		}
		else {

			int saraksts_x = 1;
			std::string izvele_meklesana;
			int saraksts_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksts_x);

		SARAKSTS_LIDMASINA_DZEST:
			std::cout << "Ievadiet kuru lidostu velaties dzest: ";
			std::getline(std::cin >> std::ws, izvele_meklesana);

			if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
				std::cout << "Ievadits nepareizs skaitlis" << std::endl;
				goto SARAKSTS_LIDMASINA_DZEST;

			}

			int izvele_meklesana2 = std::stoi(izvele_meklesana);

			if (izvele_meklesana2 > saraksts_mainigais - 1) {
				std::cout << "Ievadits nepareizs skaitlis " << std::endl;
				goto SARAKSTS_LIDMASINA_DZEST;
			}

			std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

			g.erase(labojamais);

			std::ofstream o("lidmasinas.json");
			o << std::setw(4) << g << '\n';

			delete[] meklesanasArray;
		}
	}
	else if (izvele == "4") {
	system("cls");
	return admin_panel();
	}
	system("cls");
	return admin_panel();
}

void reisi()
{
	std::string izvele;
	std::string grupas_nosaukums = "Reisu";
	std::string faila_nosaukums;
	faila_nosaukums = "reisi.json";
	std::string* meklesanasArray;
	meklesanasArray = new std::string[256];

	std::cout << "Ko velaties veikt ar Reisiem ?" << std::endl;
	std::cout << "1. Pievienot" << std::endl;
	std::cout << "2. Labot" << std::endl;
	std::cout << "3. Dzest" << std::endl;
	std::cout << "4. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";

	std::getline(std::cin >> std::ws, izvele);
	if (izvele.find_first_not_of("1234") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
		return reisi();
	}
	else if (izvele == "1") {
		system("cls");

		std::ifstream i("reisi.json");
		if (i.is_open()) {
			i >> g;
		}

		json gg;
		std::ifstream lidm("lidmasinas.json");
		if (lidm.is_open()) {
			lidm >> gg;
		}

		std::cout << "Ievadiet nepieciesamos parametrus: " << std::endl;
		Datums:
		std::cout << "Izlidosanas datums(D/M/YYYY): ";
		int dd, mm, yy;
		scanf_s("%d/%d/%d", &dd, &mm, &yy);

		if (!(checkdate(mm, dd, yy))) {
			system("cls");
			std::cout << "Ievaditais datums nav pareiza formata vai nav derigs" << std::endl;
			goto Datums;
		}

		std::string datums = std::to_string(dd) + "/" + std::to_string(mm) + "/" + std::to_string(yy);

		Laiks:
		std::cout << "Izlidosanas laiks (HH:MM): ";
		int HH, MM;
		scanf_s("%d:%d", &HH, &MM);

		if (HH > 24 || MM > 60 || HH < 0 || MM < 0) {
			system("cls");
			std::cout << "Nepareizs formats" << std::endl;
			goto Laiks;
		}
		
		std::string laiks = std::to_string(HH) + ":" + std::to_string(MM);

		std::cout << "Virziens (no - uz): ";
		std::string virziens_no_uz;
		std::getline(std::cin >> std::ws, virziens_no_uz);

		Datums_Ielidosana:
		std::cout << "Ielidosanas datums(D/M/YYYY): ";
		int d_ie, m_ie, y_ie;
		scanf_s("%d/%d/%d", &d_ie, &m_ie, &y_ie);

		if (!(checkdate(m_ie, d_ie, y_ie))) {
			system("cls");
			std::cout << "Ievaditais datums nav pareiza formata vai nav derigs" << std::endl;
			goto Datums_Ielidosana;
		}

		std::string datums_ielidosana = std::to_string(d_ie) + "/" + std::to_string(m_ie) + "/" + std::to_string(y_ie);

	Laiks_ielidosana:
		std::cout << "Ielidosanas laiks (HH:MM): ";
		int H_ie, M_ie;
		scanf_s("%d:%d", &H_ie, &M_ie);

		if (H_ie > 24 || M_ie > 60 || H_ie < 0 || M_ie < 0) {
			system("cls");
			std::cout << "Nepareizs formats" << std::endl;
			goto Laiks_ielidosana;
		}

		std::string laiks_ielidosana = std::to_string(H_ie) + ":" + std::to_string(M_ie);
		REISI_MEKL_LIDM:
		std::cout << "Meklejiet lidmasinas modelis sajam reisam: ";
		int meklesana_i = 1;
		int meklesanas_mainigais = meklesana("lidmasinas.json", meklesanasArray, meklesana_i);
		if (meklesanas_mainigais == 1) {
			system("cls");
			std::cout << "Nekas netika atrasts! " << std::endl;
			goto REISI_MEKL_LIDM;
		}
	
		MEKLESANA_LIDMASINA_REISI:
		std::cout << "Ievadiet kuru lidmasinu velaties pievienot sim reisam! " << std::endl;
		std::string izvele_meklesana;
		std::getline(std::cin >> std::ws, izvele_meklesana);

		if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto MEKLESANA_LIDMASINA_REISI;

		}

		int izvele_meklesana2 = std::stoi(izvele_meklesana);

		if (izvele_meklesana2 > meklesanas_mainigais - 1) {
			std::cout << "Ievadits nepareizs skaitlis " << std::endl;
			goto MEKLESANA_LIDMASINA_REISI;
		}
		
		system("cls");
		std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
		std::string lidmasina = meklesanasArray[izvele_meklesana2 - 1];

		



		std::string keyvirziens = virziens_no_uz;
		std::transform(keyvirziens.begin(), keyvirziens.end(), keyvirziens.begin(), ::tolower);
		std::string keydatums = datums;
		std::transform(keydatums.begin(), keydatums.end(), keydatums.begin(), ::tolower);
		std::string keylaiks = laiks;
		std::transform(keylaiks.begin(), keylaiks.end(), keylaiks.begin(), ::tolower);

			g[keyvirziens + " " + keydatums + " " + keylaiks]["Izlidosanas datums"] = datums;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Izlidosanas laiks"] = laiks;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Virziens no-uz"] = virziens_no_uz;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Nosaukums"] = virziens_no_uz + " " + datums + " " + laiks;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Ielidosanas datums"] = datums_ielidosana;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Ielidosanas laiks"] = laiks_ielidosana;
			g[keyvirziens + " " + keydatums + " " + keylaiks]["Lidmasina"] = gg[lidmasina];



		std::ofstream o("reisi.json");
		o << std::setw(4) << g << '\n';
	}
	else if (izvele == "2") {
		system("cls");

		Lid_Labot:
		std::string izvele_meklesana;
		std::string izvele2;

		std::cout << "Ko velies darit?" << std::endl;
		std::cout << "1. Meklet" << std::endl;
		std::cout << "2. Paradit sarakstu" << std::endl;
		std::cout << "3. Atpakal" << std::endl << std::endl;
		std::cout << "Jusu izvele: ";

		std::getline(std::cin >> std::ws, izvele2);
		if (izvele2.find_first_not_of("123") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis!" << std::endl;
			goto Lid_Labot;
		}
		else if (izvele2 == "1") {

			system("cls");
			std::ifstream i("reisi.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidosta" << std::endl;
				system("pause");
				system("cls");
				return reisi();

			}
			else {
				int meklesana_i = 1;
				int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, meklesana_i);
				if (meklesanas_mainigais == 1) {
					system("cls");
					std::cout << "Nekas netika atrasts! " << std::endl;
					return reisi();
				}
			MEKLESANA_REISI:
				std::cout << "Ievadiet ar kuru reisu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto MEKLESANA_REISI;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > meklesanas_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto MEKLESANA_REISI;
				}


				system("cls");
			Labot_REISI:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Izlidosanas datums" << std::endl;
				std::cout << "2. Ielidosanas datums" << std::endl;
				std::cout << "3. Izlidosanas laiks" << std::endl;
				std::cout << "4. Ielidosanas laiks" << std::endl;
				std::cout << "5. Virziens (no - uz)" << std::endl;
				std::cout << "Jusu izvele: ";


				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;
				if (labosanas_izvele.find_first_not_of("12345") != std::string::npos) {
					system("cls");
					std::cout << "Ievadits nepareizs skaitlis !" << std::endl;
					goto Labot_REISI;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Izlidosanas datums";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Ielidosanas datums";
				}
				else if (labosanas_izvele == "3") {
					labojamais_value = "Izlidosanas laiks";
				}
				else if (labosanas_izvele == "4") {
					labojamais_value = "Ielidosanas laiks";
				}
				else if (labosanas_izvele == "5") {
					labojamais_value = "Virziens no-uz";
				}




				std::string labojums;
				std::cout << "Ievadiet savu labojumu: ";
				std::getline(std::cin >> std::ws, labojums);
				if (labosanas_izvele == "2" || labosanas_izvele == "4") {
					g[labojamais][labojamais_value] = labojums;
				}
				else {
					g[labojamais][labojamais_value] = labojums;
					std::string labojums3 = g[labojamais]["Izlidosanas datums"];
					std::string labojums4 = g[labojamais]["Izlidosanas laiks"];
					std::string labojums2 = g[labojamais]["Virziens no-uz"];
					std::transform(labojums.begin(), labojums.end(), labojums.begin(), ::tolower);
					std::string labojums1 = labojums2 + " " + labojums3 + " " + labojums4;
					g[labojamais]["Nosaukums"] = labojums1;
					std::transform(labojums1.begin(), labojums1.end(), labojums1.begin(), ::tolower);


					mainit_key(g, labojamais, labojums1);
				}

				std::ofstream o(faila_nosaukums);
				o << std::setw(4) << g << '\n';


				delete[] meklesanasArray;
			}
		} 
		else if (izvele2 == "2") {

			system("cls");
			std::ifstream i("reisi.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidosta" << std::endl;
				system("pause");
				system("cls");
				return reisi();

			}
			else {


				int saraksts_x = 1;
				int saraksts_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksts_x);


			SARAKSTS_REISI:
				std::cout << "Ievadiet ar kuru reisu velaties veikt labojumus: ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto SARAKSTS_REISI;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > saraksts_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto SARAKSTS_REISI;
				}


				system("cls");
			Labot_REISS:
				std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];


				std::cout << "Ko velaties labot ?" << std::endl;
				std::cout << "1. Izlidosanas datums" << std::endl;
				std::cout << "2. Ielidosanas datums" << std::endl;
				std::cout << "3. Izlidosanas laiks" << std::endl;
				std::cout << "4. Ielidosanas laiks" << std::endl;
				std::cout << "5. Virziens (no - uz)" << std::endl;
				std::cout << "Jusu izvele: ";


				std::string labosanas_izvele;
				std::getline(std::cin >> std::ws, labosanas_izvele);
				std::string labojamais_value;
				if (labosanas_izvele.find_first_not_of("12345") != std::string::npos) {
					system("cls");
					std::cout << "Ievadits nepareizs skaitlis !" << std::endl;
					goto Labot_REISS;
				}
				else if (labosanas_izvele == "1") {
					labojamais_value = "Izlidosanas datums";
				}
				else if (labosanas_izvele == "2") {
					labojamais_value = "Ielidosanas datums";
				}
				else if (labosanas_izvele == "3") {
					labojamais_value = "Izlidosanas laiks";
				}
				else if (labosanas_izvele == "4") {
					labojamais_value = "Ielidosanas laiks";
				}
				else if (labosanas_izvele == "5") {
					labojamais_value = "Virziens no-uz";
				}




				std::string labojums;
				std::cout << "Ievadiet savu labojumu: ";
				std::getline(std::cin >> std::ws, labojums);
				if (labosanas_izvele == "2" || labosanas_izvele == "4") {
					g[labojamais][labojamais_value] = labojums;
				}
				else {
					g[labojamais][labojamais_value] = labojums;
					std::string labojums3 = g[labojamais]["Izlidosanas datums"];
					std::string labojums4 = g[labojamais]["Izlidosanas laiks"];
					std::string labojums2 = g[labojamais]["Virziens no-uz"];
					std::transform(labojums.begin(), labojums.end(), labojums.begin(), ::tolower);
					std::string labojums1 = labojums2 + " " + labojums3 + " " + labojums4;
					g[labojamais]["Nosaukums"] = labojums1;
					std::transform(labojums1.begin(), labojums1.end(), labojums1.begin(), ::tolower);


					mainit_key(g, labojamais, labojums1);
				}

				std::ofstream o(faila_nosaukums);
				o << std::setw(4) << g << '\n';


				delete[] meklesanasArray;
			}
		}
		else if (izvele2 == "3") {
			system("cls");
			return reisi();
		}
	}
	else if (izvele == "3") {

		Meklesanas_izvele:
		std::string izvele2;
		std::cout << "Ievadiet savu izveli" << std::endl;
		std::cout << "1. Meklet" << std::endl;
		std::cout << "2. Paradit sarakstu" << std::endl;
		std::cout << "3. Atpakal" << std::endl << std::endl;
		std::cout << "Jusu izvele: ";

		std::getline(std::cin >> std::ws, izvele2);
		if (izvele2.find_first_not_of("123") != std::string::npos) {
			system("cls");
			std::cout << "Ievadits nepareizs skaitlis !" << std::endl;
			goto Meklesanas_izvele;
		}
		else if (izvele2 == "1") {

			system("cls");
			std::ifstream i("reisi.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienots neviens reiss" << std::endl;
				system("pause");
				system("cls");
				return reisi();

			}
			else {

				int meklesana_i = 1;
				int meklesanas_mainigais = meklesana(faila_nosaukums, meklesanasArray, meklesana_i);
				if (meklesanas_mainigais == 1) {
					system("cls");
					std::cout << "Nekas netika atrasts! " << std::endl;
					return reisi();
				}

			MEKLESANA_REISI_DZEST:
				std::string izvele_meklesana;
				std::cout << "Ievadiet kuru reisu velaties dzest? ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto MEKLESANA_REISI_DZEST;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > meklesanas_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto MEKLESANA_REISI_DZEST;
				}

				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				g.erase(labojamais);

				std::ofstream o("reisi.json");
				o << std::setw(4) << g << '\n';

				delete[] meklesanasArray;
			}

		}
		else if (izvele2 == "2") {

			system("cls");
			std::ifstream i("reisi.json");
			if (i.is_open()) {
				i >> g;
			}


			if (g.empty())
			{
				std::cout << "Nav pievienota neviena lidosta" << std::endl;
				system("pause");
				system("cls");
				return reisi();

			}
			else {




				int saraksts_x = 1;
				std::string izvele_meklesana;
				int saraksts_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksts_x);

			SARAKSTS_REISI_DZEST:
				std::cout << "Ievadiet kuru lidostu velaties dzest? ";
				std::getline(std::cin >> std::ws, izvele_meklesana);

				if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
					std::cout << "Ievadits nepareizs skaitlis" << std::endl;
					goto SARAKSTS_REISI_DZEST;

				}

				int izvele_meklesana2 = std::stoi(izvele_meklesana);

				if (izvele_meklesana2 > saraksts_mainigais - 1) {
					std::cout << "Ievadits nepareizs skaitlis " << std::endl;
					goto SARAKSTS_REISI_DZEST;
				}


				std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

				g.erase(labojamais);

				std::ofstream o("reisi.json");
				o << std::setw(4) << g << '\n';

				delete[] meklesanasArray;
			}
		}
		else if (izvele2 == "3") {
			system("cls");
			return reisi();
		}
	}
	else if (izvele == "4") {
		system("cls");
		return admin_panel();
	}

	system("cls");
	return admin_panel();
}

void pievienot_admin()
{
	std::string izvele_meklesana;
	std::string grupas_nosaukums = "Lietotaju";
	std::string faila_nosaukums;
	faila_nosaukums = "dati.json";
	std::string* meklesanasArray;
	meklesanasArray = new std::string[256];

	std::cout << "Ko velaties darit?" << std::endl;
	std::cout << "1. Pievienot" << std::endl;
	std::cout << "2. Nonemt" << std::endl;
	std::cout << "3. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";

	std::string izvele;
	std::getline(std::cin >> std::ws, izvele);
	if (izvele.find_first_not_of("123") != std::string::npos) {
		system("cls");
		std::cout << "Ievadits nepareizs skaitlis" << std::endl;
		return pievienot_admin();
	}	
	else if (izvele == "1") {
		system("cls");

		std::ifstream i("dati.json");
		if (i.is_open()) {
			i >> g;
		}

		std::string search;
		std::cin >> search;
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);
		int ii = 1;

		for (auto& el : g.items()) {
			std::string nosaukums = el.key();
			int results = meklesanas_funkcija(search, nosaukums);
			for (auto& el2 : g.at(nosaukums).at("Username").items()) {
				std::string capnosaukums = el2.value();
				if (results != -1) {
					std::cout << ii << "." << capnosaukums << std::endl;
					meklesanasArray[ii - 1] = nosaukums;
					ii++;
				}
			}
		}


		IZVELE_MEKLESANA_ADMIN:
		std::cout << "Ievadiet kuru lietotaju velaties pievienot admin: ";
		std::getline(std::cin >> std::ws, izvele_meklesana);

		if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto IZVELE_MEKLESANA_ADMIN;

		}

		int izvele_meklesana2 = std::stoi(izvele_meklesana);

		if (izvele_meklesana2 > ii - 1) {
			std::cout << "Ievadits nepareizs skaitlis " << std::endl;
			goto IZVELE_MEKLESANA_ADMIN;
		}
		if (ii == 1) {
			system("cls");
			std::cout << "Nekas netika atrasts! " << std::endl;
			return pievienot_admin();
		}

		system("cls");
		std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
		std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];

		g[labojamais]["Admin"] = 1;

		std::ofstream o("dati.json");
		o << std::setw(4) << g << '\n';
	}
	else if (izvele == "2") {
		std::ifstream i("dati.json");
		if (i.is_open()) {
			i >> g;
		}

		int saraksts_x = 1;
		int saraksts_mainigais = viss_saraksts(faila_nosaukums, meklesanasArray, grupas_nosaukums, saraksts_x);


		SARAKSTS_ADMIN:
		std::cout << "Ievadiet kuram lietotajam velaties nonemt admin: ";
		std::getline(std::cin >> std::ws, izvele_meklesana);

		if (izvele_meklesana.find_first_not_of("123456789") != std::string::npos) {
			std::cout << "Ievadits nepareizs skaitlis" << std::endl;
			goto SARAKSTS_ADMIN;

		}

		int izvele_meklesana2 = std::stoi(izvele_meklesana);

		if (izvele_meklesana2 > saraksts_mainigais - 1) {
			std::cout << "Ievadits nepareizs skaitlis " << std::endl;
			goto SARAKSTS_ADMIN;
		}
		

		system("cls");
		std::cout << "Jus izvelejaties: " << meklesanasArray[izvele_meklesana2 - 1] << std::endl;
		std::string labojamais = meklesanasArray[izvele_meklesana2 - 1];
		
		g[labojamais]["Admin"] = 0;

		std::ofstream o("dati.json");
		o << std::setw(4) << g << '\n';
	}
	else if (izvele == "3") {
		system("cls");
		return admin_panel();
	}
	system("cls");
	return admin_panel();
}

void statistika()
{

	std::cout << "Ko velaties darit? " << std::endl;
	std::cout << "1. Izveidot statistiku" << std::endl;
	std::cout << "2. Atpakal" << std::endl;
	std::cout << "Jusu izvele: ";

	std::string izvele;
	std::getline(std::cin >> std::ws, izvele);
	if (izvele.find_first_not_of("12") != std::string::npos) {
		system("cls");
		std::cout << "Ievaditais skaitlis ir nepareizs!" << std::endl;
		return statistika();
	}
	else if (izvele == "1") {

		std::string *meklesanasArray = new std::string[256];
		int meklesanas_i = 0;
		std::ofstream e;
		e.open("statistika.csv");

		std::string menesis;
		std::cout << "Ievadiet kuru menesi velaties atspogulot statistika" << std::endl;
		std::getline(std::cin >> std::ws, menesis);
		if (menesis.find_first_not_of("123456789") != std::string::npos) {
			system("cls");
			std::cout << "Ievaditais neatbilst nevienam menesim" << std::endl;
			return statistika();
		}


		json meklesana_j;
		std::ifstream p("reisi.json");
		if (p.is_open()) {
			p >> meklesana_j;
		}


		for (auto& el : meklesana_j.items()) {
			std::string nosaukums = el.key();
			std::string meklejamais_stat = meklesana_j[nosaukums]["Izlidosanas datums"];
			int results = meklesanas_funkcija(menesis,meklejamais_stat) ;
			for (auto& el2 : meklesana_j.at(nosaukums).at("Nosaukums").items()) {
				std::string capnosaukums = el2.value();
				if (results != -1) {
					std::cout << meklesanas_i << "." << capnosaukums << std::endl;
					meklesanasArray[meklesanas_i] = nosaukums;
					meklesanas_i++;
					system("pause");
				}
			}
		}

		
		

		e << "Menesa parskats par reisiem: " << '\n' << '\n';
		for (int j = 0; j < meklesanas_i; j++) {
			
			e << meklesanasArray[j] << '\n';
			e << meklesana_j[meklesanasArray[j]] << '\n';
		}

		e.close();
	}
	else if (izvele == "2") {
		system("cls");
		return admin_panel();
	}

	system("cls");
	return admin_panel();
}