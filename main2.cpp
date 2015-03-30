#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define K 20    //ilosc pytan w quizie, potrzebny do tablic przechowujacych pytania z pliku
                // i dopuszczalna ilosc bazy slow w klasie dodaj

class Gracz{
    string imie;
    string nazwisko;
    int wiek;
    int pkt;

public:

    Gracz(){    //konstruktor
    imie = "Jan";
    nazwisko = "Kowalski";
    wiek = 1;
    pkt = 0;
    }

friend  ostream & operator<< (ostream &wyjscie, const Gracz &s);    //przeciazenie "cout << nazwaobiektugracz "wypisuje dane gracza
friend Gracz operator+ ( Gracz &g, int k);      //przeciazenie "nazwaobiektugracz + int" dodaje punkty graczowi

    void dodajswoje(){  //wpisanie wlasnych danych gracza z klawiatury
    cout<<"Podaj imie: "<<endl;
    cin>>imie;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>nazwisko;
    cout<<"Podaj wiek: "<<endl;
    cin>>wiek;
    }
};

// definicje funkcji operatorowych dla gracza, jak wstawiam do klasy to
//cos sie jebie wiec zrobilem przez frienda
ostream & operator<< (ostream &wyjscie, const Gracz &s) { //tu przeciazenie <<
   return wyjscie << "Imie: " <<s.imie << endl << "Nazwisko: " <<s.nazwisko<<endl<<"wiek: "<<s.wiek<<endl<<"Punkty: "<<s.pkt<<endl;
 }
Gracz operator+ (Gracz &g, int k){
    g.pkt = g.pkt + k;
    return g;
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

    int wynik(){ //wyswietla liczbe zdobytych punktow
    cout<<"Koniec quizu. Zdobyte punkty: "<<punkty<<endl;
    return punkty;
    }

};

class Dodaj{
    string wyrazenia[K];
    string tlumaczenia[K];
    int poz;

public:

    Dodaj(){    //konstruktor
        poz=0;
        }

void komunikat(){
    cout<<"Witaj w kreatorze dodawania danych. Mozesz dodac wyrazenia oraz ich tlumaczenia z klawiatury"<<endl;
    cout<<"lub zaladowac wyrazenia z pliku. Plik nalezy przygotowac w nastepujacy sposob: "<<endl;
    cout<<"1 linia: wyrazenie po polsku"<<endl<<"2 linia: wyrazenie po angielsku"<<endl<<"3 linia: pusta    itd..."<<endl;
 }

void slowo(void){   //dodanie slowa i znaczenia z klawiatury
    string linia;
    cout<<endl<<"Podaj zwrot w jezyku polskim: ";
    getline(cin, linia);
    wyrazenia[poz] = linia;
                                                            //przeskakuje tutaj Kacper help
    cout<<endl<<"Podaj zwrot w jezyku angielskim: ";
    getline(cin, linia);
    tlumaczenia[poz] = linia;

}

void slowo(string s){    // dodanie slowa i znaczenia z pliku
    int nr_linii =0;
    fstream plik;
    string linia;
    plik.open("pusty.txt", ios::in); //tutaj chcialbym zeby otwieralo plik o nazwie s podany w argumencie

    if (plik.good()==false)
    {
        cout<<"Blad pliku"<<endl;
        exit(0);
    }

    while(getline(plik,linia))
    {
        switch(nr_linii)
        {
            case 1: wyrazenia[poz] = linia;       break;
            case 2: tlumaczenia[poz] = linia;     break;
            case 3:                               break;
        }
        if (nr_linii==3) {nr_linii=0; poz++;}
        nr_linii++;
    }
    plik.close();
    cout<<"udalo sie";
}

};


int main(){ // przyklad dzialania dotychczasowych funkcji
    Quiz q;

    q.zadaj("h");  // mialo byc losowo ale rand losuje zawse to samo a zarodek czasu z komputera wymaga biblioteki ktorej nie znam w c++

    q.zadaj(7);     //zadaje 7 pytanie z quizu


    Gracz g1;
    Gracz g2;
    g2.dodajswoje();
    cout << g1 <<endl;          //g1 na probe
    cout << g2 <<endl<<endl;
    cout <<"hello"<<endl;

    g2 + q.wynik();           //aktualizujemy stan punktow gracza
    cout<<g2<<endl;

    Dodaj d1;
    d1.komunikat();
    d1.slowo();
    d1.slowo("tupowinnabycnazwapliku"); //string w argumenciie narazie byle jaki, fajnie by bylo gdyby
                                        //mozna bylo przeslac  funkcji nazwe pliku ktory ma  poprzez argument
//wysiwetla blad pliku bo plik nie istnieje jeszcze
    return 0;
}
