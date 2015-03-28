#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define K 20    //ilosc pytan w quizie, potrzebny do tablic przechowujacych pytania z pliku i do petli zadajacej pytania

class Gracz{
    public:
    string imie;
    string nazwisko;
    int wiek;
    int punkty;

    Gracz(){    //konstruktor
    imie = "Jan";
    nazwisko = "Kowalski";
    wiek = 1;
    punkty = 0;
    }

friend  ostream & operator<< (ostream &wyjscie, const Gracz &s); //przeciazone  << wypisuje dane gracza

    void dodajswoje(){
    cout<<"Podaj imie: "<<endl;
    cin>>imie;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>nazwisko;
    cout<<"Podaj wiek: "<<endl;
    cin>>wiek;
    }
};

ostream & operator<< (ostream &wyjscie, const Gracz &s) { //tu przeciazenie <<
   return wyjscie << "Imie: " <<s.imie << endl << "Nazwisko: " <<s.nazwisko<<endl<<"wiek: "<<s.wiek<<endl<<"Punkty: "<<s.punkty<<endl;
 }

class Quiz{
string tresc[K];
string odp1[K], odp2[K], odp3[K];
string poprawna[K];
string odpowiedz;
    int punkty;
    int nr_linii;
    int nr_pytania;

    public:

     Quiz(){  //Konstruktor ktory przy zadeklarowaniu obiektu klasy quiz wczytuje dane do tablic ,tresc, odp1,odp2..., jesli nie odnalazl pliku zwraca komunikat o bledzie
        punkty = 0;
        nr_linii = 1;
        nr_pytania = 0;
    fstream plik;
    string linia;
    plik.open("idiomquiz.txt", ios::in);

    if (plik.good()==false)
    {
        cout<<"Blad pliku"<<endl;
        exit(0);
    }

    while(getline(plik,linia))
    {
        switch(nr_linii)
        {
            case 1: tresc[nr_pytania] = linia;       break;
            case 2: odp1[nr_pytania] = linia;        break;
            case 3: odp2[nr_pytania] = linia;        break;
            case 4: odp3[nr_pytania] = linia;        break;
            case 5: poprawna[nr_pytania] = linia;    break;
        }
        if (nr_linii==5) {nr_linii=0; nr_pytania++;}
        nr_linii++;
    }
    plik.close();
    }

    void zadaj(int i){ //zadaje pytanie o indeksie i (od zera)
        cout<<endl<<tresc[i]<<endl;
        cout<<odp1[i]<<endl;
        cout<<odp2[i]<<endl;
        cout<<odp3[i]<<endl;
        cout<<"Twoja odpowiedz: ";
        cin>>odpowiedz;

        if (odpowiedz==poprawna[i])
        {
            cout<<"Dobrze! Zdobywasz punkt!"<<endl;
            punkty++;
        }
        else cout<<"Zle! Brak punktu! Poprawna odpowiedz: "<<poprawna[i]<<endl;
    }

    void zadaj(string s){  //przeciazenie, zadaje losowe pytanie
        int i;
                        //powinno byc srand(time(NULL)); ale jaka biblioteka?
        i = rand()%20;

      cout<<endl<<tresc[i]<<endl;
        cout<<odp1[i]<<endl;
        cout<<odp2[i]<<endl;
        cout<<odp3[i]<<endl;
        cout<<"Twoja odpowiedz: ";
        cin>>odpowiedz;

        if (odpowiedz==poprawna[i])
        {
            cout<<"Dobrze! Zdobywasz punkt!"<<endl;
            punkty++;
        }
        else cout<<"Zle! Brak punktu! Poprawna odpowiedz: "<<poprawna[i]<<endl;
    }

    void wynik(){ //wyswietla liczbe zdobytych punktow
    cout<<"Koniec quizu. Zdobyte punkty: "<<punkty<<endl;
    }
};

int main(){// przyklad dzialania dotychczasowych funkcji
    Quiz q;

    for (int i=0; i< 5; i++)
    {
        q.zadaj(i);
    }

    q.zadaj("h");
    q.zadaj("hhh");
    q.wynik();

    Gracz g1;
    Gracz g2;
    g2.dodajswoje();
    cout << g1 <<endl;
    cout << g2 <<endl;
    return 0;
}
