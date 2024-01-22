#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<string> wczytajHaslaZPliku(const string& nazwaPliku) {
    vector<string> hasla;
    ifstream plik("hasla.txt");
    if (plik.is_open()) {
        string haslo;
        while (getline(plik, haslo)) {
            hasla.push_back(haslo);
        }
        plik.close();
    } else {
        cout << "Blad wczytywania hasel z pliku." << endl;
    }
    return hasla;
}

int liczbaHaselNumerycznych(const vector<string>& hasla) {
    int licznik = 0;
    for (const string& haslo : hasla) {
        if (all_of(haslo.begin(), haslo.end(), ::isdigit)) { //sprawdza by zobaczyc czy wszystkie znaki to cyfry
            licznik++;
    }
    }   
    return licznik;
}

vector<string> haslaWielokrotnegoUzytku(const vector<string>& hasla) {
    unordered_map<string, vector<int>> mapaHaselUzytkownikow;

    for (int i = 0; i < hasla.size(); i++) {
        const string& haslo = hasla[i];
        mapaHaselUzytkownikow[haslo].push_back(i);
    }

    vector<string> wynik;
    for (const auto& entry : mapaHaselUzytkownikow) {
        if (entry.second.size() > 1) {
          wynik.push_back(entry.first);
     }
    }

    sort(wynik.begin(), wynik.end());
    return wynik;
}

int liczbaUzytkownikowZFragmentem(const vector<string>& hasla, const string& fragment) {
    unordered_set<int> uzytkownicy;

    for (int i = 0; i < hasla.size(); i++) {
        const string& haslo = hasla[i];

        
        for (int j = 0; j <= haslo.size() - 4; j++) {
            if (j + 3 < haslo.size()) {  
                string czteroznakowyFragment = haslo.substr(j, 4);
                sort(czteroznakowyFragment.begin(), czteroznakowyFragment.end());

                if (czteroznakowyFragment == fragment) {
                    uzytkownicy.insert(i);
                    break;  
           }
       }
       }
    }

    return uzytkownicy.size();
}

int liczbaHaselWarunki(const vector<string>& hasla) {
    int licznik = 0;
    for (const string& haslo : hasla) {
        if (any_of(haslo.begin(), haslo.end(), ::isdigit) &&
            any_of(haslo.begin(), haslo.end(), ::islower) &&
            any_of(haslo.begin(), haslo.end(), ::isupper)) {
            licznik++;
        }
    }
    return licznik;
}

int main() {
    vector<string> hasla = wczytajHaslaZPliku("hasla.txt");

    ofstream wyniki("wyniki_hasla.txt");
    if (wyniki.is_open()) {
        //Zadanie 74.1
        wyniki << "74.1. Liczba haseł złożonych jedynie ze znaków numerycznych: " << liczbaHaselNumerycznych(hasla) << endl;

        //Zadanie 74.2
        wyniki << "74.2. Hasła używane przez co najmniej dwóch różnych użytkowników:" << endl;
        vector<string> wielokrotniUzytkownicyHasla = haslaWielokrotnegoUzytku(hasla);
        for (const string& haslo : wielokrotniUzytkownicyHasla) {
            wyniki << haslo << endl;
        }

        //Zadanie 74.3
        string fragment = "abcd";  // Dokończyć
        wyniki << "74.3. Liczba użytkowników posiadających hasła z fragmentem '" << fragment << "': "
               << liczbaUzytkownikowZFragmentem(hasla, fragment) << endl;

        //Zadanie 74.4
        wyniki << "74.4. Liczba haseł spełniających warunki: " << liczbaHaselWarunki(hasla) << endl;

        wyniki.close();
    } else {
        cout << "Błąd podczas otwierania pliku wynikowego." << endl; 
    }

    return 0;
}
