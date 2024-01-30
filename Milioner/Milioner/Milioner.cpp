#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <random>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;

//Struktura za unos podataka o korisniku
struct Milioner {
    char ime_igraca[50 + 1];
    char godine[50 + 1];
    char grad[50 + 1];
}; 
int broj_pitanja = 1; //Pocetno pitanje
int broj_tacnih_odgovora = 0; //Broj trenutno tacnih odgovora
int svota_novca = 0; //Zaradjen novac
int broj = 0; //Broj iskoriscene pomoci pola - pola
int broj123 = 0; //Broj iskoriscene pomoci zamene pitanja
bool Pitanje[26] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
fstream fajl; //kreiranje ulazno/izlaznog toka

void pocetni_ekran(); //Prikaz sa svim ponudjenim opcijama
void prikaz_pitanja(); //Prikazuje nasumicno izabrano pitanje
void prikaz();  //Prikaz trenutnog ekrana
void odgovori(string pitanje, string a, string b, string c, string d, char konacan_odgovor); //Izbor odgovora za svako pitanje
void rezultati(); //Konacni rezultati
void pravila(); //Pravila igre
void ZamenaPitanja(); //Pomoc zamena pitanja
int main()
{   
    int izbor, izbor2;
    char izbor_odgovora, ime_datoteke[50 + 1];
    Milioner *igrac;
     //Dinamicka dodela memorije
    igrac = new Milioner;
    if (igrac == NULL) {
        cerr << "Nije uspela dodela memorije!" << endl;
        exit(1);
    }
    //Rad sa datotekom koja mora biti kreirana pod imenom igrac.txt
    fajl.open("igrac.txt", ios::out | ios::in | ios::_Nocreate);
    if (!fajl) {
        cerr << "Greska pri otvaranju datoteke!" << endl;
        exit(1);
    }
    //Pocetni ekran tokom pokretanja
    do
    {
        pocetni_ekran();
        cout << endl << endl;
        cout << "Vasa opcija: ";
        cin >> izbor;
        cout << endl << endl;
        if (izbor != 1 && izbor != 2) {
            cout << "Niste uneli odgovarajucu opciju, pokusajte ponovo:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while ((izbor != 1) && (izbor != 2));
    if (izbor == 1) {
        do {
            system("cls");
            pravila();
            cout << "Za nastavak uneti broj (3): ";
            cin >> izbor2;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (izbor2 == 3) {               
                system("cls");
                cout << "Pre nego sto nastavimo uneti podatke o vama: "<< endl << endl;
                cout << "Podaci (ime, godine, grad):" << endl << endl;
                bool ispravnoIme;
                bool ispravneGodine;
                bool ispravanGrad;
                do {
                    ispravnoIme = true;
                    cout << "Ime: ";
                    cin.getline(igrac->ime_igraca, sizeof(igrac->ime_igraca));
                    for (size_t i = 0; i < strlen(igrac->ime_igraca); ++i) {
                        if (!isalpha(igrac->ime_igraca[i])){
                            ispravnoIme = false;
                            break;
                        }
                    }
                    if (!ispravnoIme || strlen(igrac->ime_igraca) == 0) {
                        cout << "Molimo unesite ispravno ime (samo slova).\n ";
                        cin.clear();
                        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        ispravnoIme = false;
                    }
                } while (!ispravnoIme);
                do {
                    ispravneGodine = true;
                    cout << "Godine starosti: ";
                    cin >> igrac->godine;
                    for (size_t i = 0; i < strlen(igrac->godine); ++i) {
                        if (!isdigit(igrac->godine[i])) {
                            ispravneGodine = false;
                            break;
                        }
                    }
                    if (!ispravneGodine) {
                        cout << "Molimo unesite ispravan format godina (samo brojevi).\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    
                } while (!ispravneGodine);
                do {
                    ispravanGrad = true;
                    cout << "Grad: ";
                    cin >> igrac->grad;
                    for (size_t i = 0; i < strlen(igrac->grad); ++i) {
                        if (!isalpha(igrac->grad[i])) {
                            ispravanGrad = false;
                            break;
                        }
                    }
                    if (!ispravanGrad) {
                        cout << "Grad treba da ima makar neko ime\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (!ispravanGrad);
                cin.ignore();
                cout << "Ime: " << igrac->ime_igraca << endl;
                cout << "Godine: " << igrac->godine << endl;
                cout << "Grad: " << igrac->grad << endl;
                prikaz();

                delete igrac;
            }
        } while (izbor2 != 3);
    }
    //Opcija za napustanje programa
    if (izbor == 2) {
        system("cls");
        cout << "Hvala na poseti!" << endl;
    }
    
    fajl.close();
    return 0;
}
//Pocetni ekran kada se pokrene program
void pocetni_ekran() {
    cout << "Dobro dosli u igru \"Milioner\"! " << endl << endl;
    cout << "*********************************" << endl << endl;
    cout << "1.Zapocni kviz" << endl << endl;
    cout << "2.Izlaz iz kviza" << endl << endl << endl;
    cout << "*********************************" << endl << endl;
    cout << "Izaberite jednu od ponudjenih opcija (1 ili 2): ";
}
//Funkcija sa ponudjenim odgovorima i naredbama za unos
void odgovori(string pitanje, string a, string b, string c, string d, char tacan_odgovor) {
    cout << pitanje << endl << endl;
//Svi ponudjeni odgovori
    cout << "A: " << a << "\t\tB: " << b << endl << endl;
    cout << "C: " << c << "\t\tD: " << d << endl << endl;
    cout << "\t\t\t\t\tZa pomoc pola - pola uneti slovo P." << endl;
    cout << "\t\t\t\t\tZa zamenu pitanja uneti slovo Z." << endl;
    cout << "Ako se dvaput iskoristi ista pomoc zaustavlja se kviz i izbacuje konacan rezultat!" << endl << endl;
    cout << "Vas odgovor je (unositi malim slovima): ";
    char odgovor;
    cin >> odgovor;
    odgovor = tolower(odgovor);
    if (odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' && odgovor != 'z' && odgovor != 'p') {
        cout << "Niste uneli odgovarajuci odgovor, molimo pokusajte ponovo." << endl;
        odgovori(pitanje, a, b, c, d, tacan_odgovor); //rekurzivni poziv funkcije
        return;
    }
    //uslov za pomoc pola - pola kao i njegova funkcija za izvrsenje
    if ((odgovor == 'p') && broj < 1) {
        broj++;
        srand(time(0));
        char odgovor123;
        char drugi_odgovor;
        odgovor123 = tacan_odgovor;
        cout << "Ostali ponudjeni odgovori su :" << endl;
        cout << "**********************************" << endl;
        cout << (char)toupper(odgovor123) << ": ";
        drugi_odgovor = 97 + rand() % 4;
        if (drugi_odgovor != odgovor123) {
            cout << (char)toupper(drugi_odgovor) << ": ";
        }
        else {
            drugi_odgovor = 97 + rand() % 3;
            cout << (char)toupper(drugi_odgovor) << ": ";
        }
        cout << endl << endl << endl;
        cout << "Vas odgovor je: ";
        cin >> odgovor;
        odgovor = tolower(odgovor);
        if (odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' && odgovor != 'z' && odgovor != 'p') {
            cout << "Niste uneli odgovarajuci odgovor, molimo pokusajte ponovo." << endl;
            odgovori(pitanje, a, b, c, d, tacan_odgovor); //rekurzivni poziv funkcije
            return;
        }
    }
    else if ((odgovor == 'z') && broj123 < 1) {
        broj123++;
        ZamenaPitanja();
        cout << endl << endl << endl;
        cout << "Vas odgovor je: ";
        cin >> odgovor;
        odgovor = tolower(odgovor);
        if (odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' && odgovor != 'z' && odgovor != 'p') {
            cout << "Niste uneli odgovarajuci odgovor, molimo pokusajte ponovo." << endl;
            odgovori(pitanje, a, b, c, d, tacan_odgovor); //rekurzivni poziv funkcije
            return;
        }
    }

    //Provera da li je odgovor koji je unet tacan
    if (odgovor == tacan_odgovor || toupper(odgovor) == tacan_odgovor) {
        broj_tacnih_odgovora++;
        svota_novca += 50000;
        fajl << broj_pitanja << ". " << pitanje << " " << odgovor << ")" << endl;
    }
    else {
        cout << "Nazalost Vas odgovor na pitanje je netacan!" << endl;
        rezultati();
        exit(1);
    }
    broj_pitanja++;
    prikaz();
}
//Prikaz tekuceg pitanja
void prikaz() {
        system("cls");
        cout << "Pitanje broj: " << broj_pitanja << endl << endl << endl;
        prikaz_pitanja();
}
//Generisanje nasumicnih pitanja
void prikaz_pitanja() {
    int i;
    srand(time(0));
    bool tekuce_pitanje = false;
    for (i = 0; i < 20; i++){
        if (Pitanje[i]) {
            tekuce_pitanje = true;
            break;
        }
    }
    //Nasumicno izvlacenje pitanja
    while (tekuce_pitanje) {
        int no = rand() % 20;
        if (Pitanje[no]) {
            Pitanje[no] = false;
            switch (no) {
            case 0:
                odgovori("Koji od srpskih gradova je u proslosti nazivan srpskom Atinom ? ", "Beograd", "Novi Sad", "Subotica", "Nis", 'b');
                break;
            case 1:
                odgovori("Sta je C++? ", "Objektno orijentisani programski jezik", "Proceduralni jezik", "Objektno orijentisani i proceduralni jezik", "Funkcionalni programski jezik", 'c');
                break;
            case 2:
                odgovori("Koja je najmnogoljudnija zemlja posle Kine ?", "Italija", "Indonezija", "Iran", "Indija", 'd');
                break;
            case 3:
                odgovori("Koji simbol se koristi za deklarisanje pretprocesorske direktive? ", "$", "#", "%", "*", 'b');
                break;
            case 4:
                odgovori("Koga smatraju osnivacem teorije o revoluciji ?", "Darvina", "Laplasa", "Njutna", "Frojda", 'a');
                break;
            case 5:
                odgovori("Demokratija je: ", "vladavina grupe", "vladavina pojedinca", "vladavina naroda", "niko ne vlada", 'c');
                break;
            case 6:
                odgovori("Sta od sledeceg nije tip konstruktora u C++? ", "default konstruktor", "konstruktor sa parametrima", "konstruktor kopiranja", "prijatelj konstruktor", 'd');
                break;
            case 7:
                odgovori("Ko je otkrio parnu masinu ?", "Dzejms Vat", "Robert Fulton", "Abraham Darbi", "Dzordz Stivenson", 'a');
                break;
            case 8:
                odgovori("\"Ilijadu i Odiseju \" je napisao: ", "Homer", "Ezop", "Herodot", "Euripid", 'a');
                break;
            case 9:
                odgovori("Grcka boginja ljubavi zove se: ", "Hera", "Venera", "Afrodita", "Atina", 'c');
                break;
            case 10:
                odgovori("Sta je Faraon ?", "Gradjanin u Atini", "Vladar u Egiptu", "Rob u Rimu", "Seljak u Mesopotamiji", 'b');
                break;
            case 11:
                odgovori("Koja je najduza evropska reka ?", "Rajna", "Sena", "Dunav", "Volga", 'd');
                break;
            case 12:
                odgovori("Osnivac loze Nemanjica je: ", "Lazar", "Rastko", "Milutin", "Stefan Nemanja", 'd');
                break;
            case 13:
                odgovori("Sta se koristi za komentarisanje u C++? ", "/* komentar */", "// komentar */", "// komentar", "//komentar ili /* komentar */", 'd');
                break;
            case 14:
                odgovori("Novcana jedinica u Japanu je: ", "Lej", "Lev", "Real", "Jen", 'd');
                break;
            case 15:
                odgovori("Simbol kiseonika je: ", "C", "H", "O", "N", 'c');
                break;
            case 16:
                odgovori("Koji od sledecih tipova ima u C++ a ne u C? ", "double", "float", "int", "bool", 'd');
                break;
            case 17:
                odgovori("Kada je poceo Prvi svetski rat ?", "1915.", "1918.", "1914.", "1920.", 'c');
                break;
            case 18:
                odgovori("Simbol azota je: ", "Na", "S", "Mg", "N", 'd');
                break;
            case 19:
                odgovori("Kako se zvao vodja Huna ?", "Atila", "Arpad", "Janos", "Istvan", 'a');
                break;
            }
        }
    }
    rezultati();
    exit(1);
}
//Funkcija za krajnji rezultat
void rezultati() {
    system("cls");
    cout << "Konacni rezultati:" << endl;
    cout << "**************************" << endl;
    cout << "Ukupan broj pitanja: " << broj_pitanja - 1 << endl;
    cout << "Broj tacnih odgovora: " << broj_tacnih_odgovora << endl;
    cout << "Ukupna svota novca: " << svota_novca << "$" << endl;
    cout << "**************************" << endl << endl;
}
//Funkcija za pravila igre
void pravila() {
    cout << "\t\t\t\t\tPravila igre \"Milioner\"" << endl << endl;
    cout << "\t\t\t====================================================" << endl << endl;
    cout << "Na pitanja odgovarate sa cetiri ponudjena odgovora, od toga birate samo jedan odgovor." << endl;
    cout << "Svaki tacan odgovor donosi 50.000 dinara." << endl;
    cout << "Svaki odgovor na pitanje kao i samo pitanje ce biti sacuvani u fajlu po imenu igrac.txt!" << endl;
    cout << "*********************************************************************************************************" << endl;
    cout << "Takodje na raspolaganju imate dve vrste pomoci, a to su: pomoc pola - pola i zamena pitanja." << endl;
    cout << "Pomoc pola - pola radi tako sto se odstrane dva odgovora koja su netacna i ostaju jedan odgovor koji je tacan i jedan nasumicno izabran odgovor." << endl;
    cout << "Zamena pitanja je kada zelite da zamenite pitanje na koje niste sigurni i ne zelite da odgovorite na njega." << endl;
    cout << "*********************************************************************************************************" << endl;
    cout << "\t\t\t\t\t\tVazna napomena!" << endl;
    cout << "\t\t\t==========================================================" << endl;
    cout << "Ako se dvaput unese ista pomoc kao odgovor program ne dozvoljava dalje odgovaranje na pitanja" << endl;
    cout << "i izbacuje konacan rezultat!" << endl << endl;
}
//Funkcija za zamenu pitanja
void ZamenaPitanja() {
    cout << "*******************************************************************" << endl << endl;
    cout << "Vrsi se zamena pitanja sa nekim drugim nasumicno izabranim pitanjem" << endl << endl;
    bool tekuce_pitanje = true;
    srand(time(0));
    while (tekuce_pitanje) {
        int zamena = rand() % (26 - 20) + 20;
        if (Pitanje[zamena]) {
            Pitanje[zamena] = false;
            switch (zamena) {
            case 20:
                odgovori("Vrhovni bog u grckoj mitoligiji je: ", "Zevs", "Posejdon", "Had", "Ares", 'a');
                break;
            case 21:
                odgovori("Inke su iz ?", "Brazila", "Perua", "Argentine", "Meksika", 'b');
                break;
            case 22:
                odgovori("Koji od ponudjenih odgovora je pravilno deklarisan niz? ", "niz{10}", "niz niz[10]", "int niz", "int niz[10]", 'd');
                break;
            case 23:
                odgovori("Ko je izmislio telefon ?", "Edison", "Bel", "Tesla", "Vat", 'b');
                break;
            case 24:
                odgovori("Ko je otkrio Ameriku ?", "Vasko de Gama", "Pedro Kabral", "Kristofer Kolumbo", "Fernando Magelan", 'c');
                break;
            case 25:
                odgovori("Koji kompozitor je pred kraj zivota postao gluv ?", "Betoven", "Hajdn", "Mocart", "Bah", 'a');
                break;
            }
        }
    }
}