#pragma once
#include <string>
#include <iostream>
#include <ctime>

using namespace std;



class Game {



	int indeksi[39] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	int tabela[13][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	int kockice[5] = { 0,0,0,0,0 };
	int brojac_polja = 0;
	int broj_bacanja = 0;
	int broj_bacanja1 = 0;
	int trenutne_kockice[5];
	int zadrzane_kockice[5] = { -1,-1,-1,-1,-1 };




public:


	bool Ful(int niz[]) {
		int brojac[5] = { 0 };

		for (int i = 0; i < 5; ++i) {
			brojac[niz[i]]++;
		}

		bool imaDvaIsta = false;
		bool imaTriIsta = false;

		for (int i = 0; i < 5; ++i) {
			if (brojac[i] == 2) {
				imaDvaIsta = true;
			}
			else if (brojac[i] == 3) {
				imaTriIsta = true;
			}
		}

		return imaDvaIsta && imaTriIsta;
	}




	bool sadrziClanove(int niz[], int velicina, int clanovi[], int velicinaClanova) {
		for (int i = 0; i < velicina; ++i) {
			bool found = false;
			for (int j = 0; j < velicinaClanova; ++j) {
				if (niz[i] == clanovi[j]) {
					found = true;
					break;
				}
			}
			if (!found) {
				return false;
			}
		}
		return true;
	}

	int vrednost_kockica(int index) {
		for (int i = 0; i < 5; i++) {
			kockice[i] = trenutne_kockice[i];

		}
		int vrednost = 0;
		bool nula = false;
		if (index == 0 or index == 13 or index == 26) {

			for (int i = 0; i < 5; i++) {
				if (kockice[i] == 1) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}if (nula == false) {
				return 0;
			}


		}//1
		if (index == 1 or index == 14 or index == 27) {
			for (int i = 0; i < 5; i++) {
				if (kockice[i] == 2) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}
			if (nula == false) {
				vrednost = 0;
			}
			return vrednost;

		}//2
		if (index == 2 or index == 15 or index == 28) {
			for (int i = 0; i < 5; i++) {
				if (kockice[i] == 3) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}
			if (nula == false) {
				vrednost = 0;
			}

			return vrednost;

		}//3
		if (index == 3 or index == 16 or index == 29) {
			for (int i = 0; i < 5; i++) {
				if (kockice[i] == 4) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}
			if (nula == false) {
				vrednost = 0;
			}
			return vrednost;


		}//4
		if (index == 4 or index == 17 or index == 30) {
			for (int i = 0; i < 5; i++) {
				if (kockice[i] == 5) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}
			if (nula == false) {
				vrednost = 0;
			}

			return vrednost;

		}//5
		if (index == 5 or index == 18 or index == 31) {

			nula = false;
			for (int i = 0; i < 5; i++) {

				if (kockice[i] == 6) {
					nula = true;
					vrednost = vrednost + kockice[i];
				}
			}
			if (nula == false) {
				vrednost = 0;
			}			return vrednost;

		}//6
		if (index == 6 or index == 19 or index == 32) {
			for (int i = 0; i < 5; i++) {

				vrednost = vrednost + kockice[i];

			}			return vrednost;

		}//max
		if (index == 7 or index == 20 or index == 33) {
			for (int i = 0; i < 5; i++) {

				vrednost = vrednost + kockice[i];

			}			return vrednost;

		}//min
		if (index == 8 or index == 21 or index == 34) {

			int clanovi_1_2_3_4_5[] = { 1, 2, 3, 4, 5 };
			int clanovi_2_3_4_5_6[] = { 2, 3, 4, 5, 6 };
			bool ima_clanove_1_2_3_4_5 = sadrziClanove(kockice, 5, clanovi_1_2_3_4_5, 5);
			bool ima_clanove_2_3_4_5_6 = sadrziClanove(kockice, 5, clanovi_2_3_4_5_6, 5);
			if ((ima_clanove_1_2_3_4_5 or ima_clanove_2_3_4_5_6) and (broj_bacanja = 1)) {
				vrednost = 65;
			}
			if ((ima_clanove_1_2_3_4_5 or ima_clanove_2_3_4_5_6) and (broj_bacanja = 2)) {
				vrednost = 55;
			}
			if ((ima_clanove_1_2_3_4_5 or ima_clanove_2_3_4_5_6) and (broj_bacanja = 3)) {
				vrednost = 45;
			}
			else { vrednost = 0; }
			return vrednost;


		}//kenta
		if (index == 9 or index == 22 or index == 35) {
			for (int i = 0; i < 5; ++i) {
				int brojac3 = 1;
				for (int j = i + 1; j < 5; ++j) {
					if (kockice[i] == kockice[j]) {
						++brojac3;
						if (brojac3 == 3) {
							vrednost = 20 + 3 * kockice[i];
							return vrednost;
						}

					}
				}break;
			}			return 0;

		}//triling
		if (index == 10 or index == 23 or index == 36) {
			vrednost = 30;
			if (Ful(kockice)) {
				for (int i = 0; i < 5; ++i) {
					vrednost += kockice[i];
				}
			}
			else {
				vrednost = 0;
			}
			return vrednost;


		}//ful
		if (index == 11 or index == 24 or index == 37) {

			for (int i = 0; i < 5; ++i) {
				int brojac2 = 1;
				for (int j = i + 1; j < 5; ++j) {
					if (kockice[i] == kockice[j]) {
						++brojac2;
						if (brojac2 == 4) {
							vrednost = 40 + 4 * kockice[i];
							return vrednost;
						}

					}
				}break;
			}			return 0;

		}//poker
		if (index == 12 or index == 25 or index == 38) {

			for (int i = 0; i < 5; ++i) {
				int brojac1 = 1;
				for (int j = i + 1; j < 5; ++j) {
					if (trenutne_kockice[i] == trenutne_kockice[j]) {
						brojac1++;
						if (brojac1 == 5) {

							vrednost = 50 + 5 * trenutne_kockice[0];
							return vrednost;

						}
					}
				}break;

			}return 0;

		}//jamb


		return vrednost;


	}



	void inicijalizuj_1() {

		for (int i = 0; i < 13; ++i) {
			for (int j = 0; j < 3; ++j) {
				tabela[i][j] = NULL;
			}
		}

	}
	bool daLiSeElementNalazi(int element, const int niz[]) {
		for (int i = 0; i < 39; ++i) {
			if (niz[i] == element) {
				return false;
			}
		}
		return true;
	}
	bool proveriPopunjenaPolja(int tabela[13][3], int red, int kolona) {
		if (kolona == 0) {
			for (int i = 0; i < red; ++i) {
				if (tabela[i][kolona] == NULL and daLiSeElementNalazi(kolona * 13 + i, indeksi)) {
					return false;
				}
			}
		}
		else if (kolona == 2) {
			for (int i = red + 1; i < 13; ++i) {
				if (tabela[i][kolona] == NULL and daLiSeElementNalazi(kolona * 13 + i, indeksi)) {
					return false;
				}
			}
		}

		return true;
	}

	bool popunjenaPolja[13][3] = { false };

	bool proveriPopunjenaIstaPolja(int red, int kolona) {
		return popunjenaPolja[red][kolona];
	}

	int* generisiNiz() {
		srand(static_cast<unsigned int>(std::time(nullptr)));

		int* niz = new int[5];

		for (int i = 0; i < 5; ++i) {
			niz[i] = std::rand() % 6 + 1;
		}

		return niz;
	}


	void load(string table);
	string save();
	void restart();
	int getScore();
	void setDice(int dice[]);
	bool writeResult(int choice);
	bool isGameOver();
	void printResults();
	void printChoices();
	void throwDice();
	bool keepDice(bool dice[]);







};