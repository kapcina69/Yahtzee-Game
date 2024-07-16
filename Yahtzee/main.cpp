#include "game.h"
#include <iostream>
#include <string>



void Game::load(string tabele) {
    size_t startPos = 0;
    size_t endPos;

    int i = 0;
    while ((endPos = tabele.find('\n', startPos)) != string::npos && i < 13) {
        string red = tabele.substr(startPos, endPos - startPos);
        startPos = endPos + 1;

        size_t startFieldPos = 0;
        size_t endFieldPos;

        int j = 0;
        while ((endFieldPos = red.find(',', startFieldPos)) != string::npos) {
            string polje = red.substr(startFieldPos, endFieldPos - startFieldPos);

            if (!polje.empty()) {
                tabela[i][j] = stoi(polje);
                indeksi[j * 13 + i] = j * 13 + i;
            }

            startFieldPos = endFieldPos + 1;
            ++j;
        }

        // Poslednje polje u redu
        string polje = red.substr(startFieldPos);

        if (!polje.empty()) {
            tabela[i][j] = stoi(polje);
            indeksi[j * 13 + i] = j * 13 + i;
        }

        ++i;
    }
}



string Game::save() {
    string result;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!(daLiSeElementNalazi(j * 13 + i, indeksi))) {
                // Konvertujte broj u string i dodajte ga rezultatu
                result += to_string(tabela[i][j]);
            }
            if (j < 3 - 1) {
                // Dodajte zarez izme�u elemenata
                result += ",";
            }
        }
        // Dodajte novi red nakon svakog reda u tabeli
        result += "\n";
    }
    return result;
}



void Game::restart() {

    inicijalizuj_1();
    brojac_polja = 0;
    broj_bacanja = 0;
    broj_bacanja1 = 0;


    for (int i = 0; i < 5; ++i) {

        kockice[i] = NULL;
        zadrzane_kockice[i] = -1;
    }

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 3; ++j) {
            popunjenaPolja[i][j] = false;

        }
    }
    for (int i = 0; i < 39; ++i) {
        indeksi[i] = -1;

    }
}


int Game::getScore() {

    int suma = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            suma += tabela[i][j];
        }
    }
    for (int i = 8; i < 13; ++i) {
        for (int j = 0; j < 3; ++j) {
            suma += tabela[i][j];
        }
    }
    suma = suma + tabela[0][0] * (tabela[6][0] - tabela[7][0]) + tabela[0][1] * (tabela[6][1] - tabela[7][1]) + tabela[0][2] * (tabela[6][2] - tabela[7][2]);
    return suma;
}



void Game::setDice(int dice[]) {


    for (int i = 0; i < 5; i++) {
        trenutne_kockice[i] = dice[i];
    }
}



bool Game::writeResult(int index) {

    indeksi[index] = index;
    if (index >= 0 && index <= 38) {
        int red = index % 13;
        int kolona = index / 13;

        if (!proveriPopunjenaPolja(tabela, red, kolona)) {
            indeksi[index] = -1;
            return false;
        }
        if (proveriPopunjenaIstaPolja(red, kolona)) {
            return false;
        }


        int vrijednost = vrednost_kockica(index);
        tabela[red][kolona] = vrijednost;
        popunjenaPolja[red][kolona] = true;
        brojac_polja++;
        broj_bacanja = 0;
        broj_bacanja1 = 0;


        for (int i = 0; i < 5; ++i) {

            kockice[i] = NULL;
            zadrzane_kockice[i] = -1;
        }

    }

    else {
        return false;
    }
}

bool Game::isGameOver() {


    if (brojac_polja == 38) {
        return true;
    }
    else { return false; }

}



void Game::printResults() {


    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!(daLiSeElementNalazi(j * 13 + i, indeksi))) {
                cout << tabela[i][j];
            }
            if (j < 3 - 1) {
                cout << ",";
            }
        }
        cout << "\n";
    }

}


void  Game::printChoices() {
    for (int i = 0; i < 39; i++) {
        if (indeksi[i] == -1) {
            cout << " " << i;
        }
    }
}



void Game::throwDice() {

    for (int i = 0; i < 5; i++) {
        if (trenutne_kockice[i] != NULL) {
            trenutne_kockice[i] = generisiNiz()[i];
        }
    }

    if (broj_bacanja1 == 0) {
        for (int i = 0; i < 5; i++) {

            if (zadrzane_kockice[i] != NULL) {
                cout << " " << trenutne_kockice[i];
            }
            else { cout << " 0"; }
        }
    }

    if (broj_bacanja1 == 1) {
        for (int i = 0; i < 5; i++) {

            if (zadrzane_kockice[i] != NULL) {

                cout << " " << trenutne_kockice[i];

            }
            else {
                trenutne_kockice[i] = kockice[i];

                cout << " 0";
            }
        }
    }

    if (broj_bacanja1 == 2) {



        for (int i = 0; i < 5; i++) {
            if (kockice[i] != 0) {
                trenutne_kockice[i] = kockice[i];
            }


        }
        for (int i = 0; i < 5; i++) {

            cout << " " << trenutne_kockice[i];

        }
    }
}


bool Game::keepDice(bool dice[]) {
    bool pomocni_niz[5];

    if (broj_bacanja1 == 0) {
        for (int i = 0; i < 5; i++) {
            if (dice[i] == true) {
                pomocni_niz[i] = true;
                kockice[i] = trenutne_kockice[i];
                zadrzane_kockice[i] = NULL;


            }
        }cout << "\nZadrzane kockice su:";
        for (int i = 0; i < 5; i++) {
            if (kockice[i] != 0) {
                cout << " " << kockice[i];
            }
        }
        cout << endl;

    }
    if (broj_bacanja1 == 1) {
        for (int i = 0; i < 5; i++) {
            if (dice[i] == pomocni_niz[i]) { return false; }
            if (dice[i] == true) {
                pomocni_niz[i] = true;
                kockice[i] = trenutne_kockice[i];
                zadrzane_kockice[i] = NULL;

            }

        }
        cout << "\nZadrzane kockice su:";
        for (int i = 0; i < 5; i++) {
            if (kockice[i] != 0) {

                cout << " " << kockice[i];
            }
        }

        cout << endl;

    }
    broj_bacanja1++;

}

