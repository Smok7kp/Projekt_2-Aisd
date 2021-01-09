//Program do analizy dwoch algorytmow sortujacych: Sortowanie Gnoma i Sortowanie przez Zliczanie.

#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std::chrono;
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Wyswietlanie tablicy - funkcja pomocnicza, przydawala sie podaczas testowania manualnego algorytmow
void wyswietl_tablice (int tablica[], int dlugosc){
cout<<"tablica: [ ";
    for (int j=0; j<dlugosc; j++){
      cout<<tablica[j]<<" ";}
    cout<<"]"<<endl;}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Generuje tablice, w ktorej mozna zmieniac zarowno gorna jak i dolna granice
void generuj_tablice(int tablica[], int dlugosc, int dolna_granica, int gorna_granica){
    srand((unsigned) time(0));
    for (int j=0; j<dlugosc; j++){
      tablica[j]=(dolna_granica+rand() % gorna_granica ); if(tablica[j]>gorna_granica){tablica[j]-=dolna_granica;}}
  //cout<<"Stworzona ";
  //wyswietl_tablice(tablica, dlugosc);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Kopiuje tablice, zeby moc dzialac na jednej tablicy pare razy, bedzie urzywana na poczatku algorytmow by oba dzialaly na tej samej tablicy
void kopiowanie_talbicy(int tablica[], int tablica_kopia[], int dlugosc){
 for(int i=0; i<dlugosc; i++){
  tablica_kopia[i]=tablica[i];
 }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Algorytm - sortowanie gnoma
int sortowanie_gnoma (int tablica[], int dlugosc, int h) {

int tablica_kopia[dlugosc];
kopiowanie_talbicy(tablica, tablica_kopia, dlugosc);
int i = 0;
while (i < dlugosc) { //przechodzimy po kolei tablice
    if (i == 0){i++;} //jesli wrocimy sie do 0 przechodzimy znowu tablice
    if (tablica_kopia[i] >= tablica_kopia[i - 1]){
     i++; //jesli elementy sa w odpowiedniej kolejnosci idziemy dalej
    }else{
     swap(tablica_kopia[i], tablica_kopia[i - 1]); //jesli elementy nie sa w odpowiedniej kolejnosci zamieniamy je i wracamy sie do poprzednich elementow by zobaczyc czy nie sa wieksze od zamienionego
    i--;
    }
}

  //cout<<"Posortowana sortowaniem gnoma ";  //odkomentowac jesli chcemy wyswietlac na ekranie
  //wyswietl_tablice(tablica_kopia, dlugosc);

  return tablica_kopia[h]; //zwracamy element tablicy o okreslonym indeksie, by ulatwic wyswietlanie
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Algorytm - sortowanie przez zliczanie
int sortowanie_przez_zliczanie(int tablica[], int dlugosc,  int gorna_granica, int h) {

 int tablica_kopia[dlugosc];
 kopiowanie_talbicy(tablica, tablica_kopia, dlugosc);
  int wyjscie[dlugosc]; //tworzymy pomocnicza tablice, ktora posluzy do wpisania danych do oryginalnej tablicy

  int maks = tablica_kopia[0]; //szukamy maksymalnej wartosci w tablicy
  for (int i = 1; i < dlugosc; i++) {
    if (tablica_kopia[i] > maks)
      maks = tablica_kopia[i];
  }

  int licznik[maks+1]; //tablica ktora bedzie zliczac ile razy wystepuje kazdy element
  for (int i = 0; i <= maks; i++) { //wypelniamy ja zerami
    licznik[i] = 0;
  }

  for (int i = 0; i < dlugosc; i++) { //w tablicy licznik na miejscu o indeksie rownym kazdej wartosci zliczamy ile razy wystepuje ta wartosc
    licznik[tablica_kopia[i]]++;
  }

  for (int i = 1; i <= maks; i++) { //znajdujemy faktyczna pozycje wartosci w tablicy wyjsciowej
    licznik[i] += licznik[i - 1];
  }

  for (int i = dlugosc - 1; i >= 0; i--) {
    wyjscie[licznik[tablica_kopia[i]] - 1] = tablica_kopia[i]; //wpisujemy wartosc w miejsce z indeksem rownym odpowiadajacemu mu numerowi w liczniku minus jeden
    licznik[tablica_kopia[i]]--; //zmniejszamy numer w liczniku, przez co wypiszemy odpowiednia ilosc takich samych wartosci
  }

  for (int i = 0; i < dlugosc; i++) { //zapisujemy wartosci z wyjscia do oryginalnej tablicy, potrzebowalismy jej do tej pory dlatego mielismy talbice pomocnicza wyjscia
    tablica_kopia[i] = wyjscie[i];
  }

  //cout<<"Posortowana sortowaniem przez zliczanie "; //odkomentowac jesli chcemy wyswietlac na ekranie
  //wyswietl_tablice(tablica_kopia, dlugosc);

  return tablica_kopia[h]; //zwracamy element tablicy o okreslonym indeksie, by ulatwic wyswietlanie
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Funkcja do testowania, ma du¿o parametrow by moc dokladnie sprawdzic w jakich warunkach najlepiej i najgorzej dzialaja algorytmy
void testy(int dlugosc_od, int dlugosc_do, int skok_dlugosci, int dolna_granica_od, int dolna_granica_do, int skok_dolnej,  int gorna_granica_od, int gorna_granica_do, int skok_gornej){

fstream output;
output.open("Testy.txt", ios::out); //otwieramy plik do ktorego bedziemy zapisywac dane

output<<"Gnome Zliczanie dlugosc dolna_granica gorna_granica"<<endl; //nazwy kolum do pliku w excelu w ktorym bede generowal wykresy

//ustalamy jak beda wygladac tabele, by moc stworzyc taki zestaw danych, jaki bedzie nam potrzebny
for (int dlugosc=dlugosc_od; dlugosc<=dlugosc_do; dlugosc+=skok_dlugosci){ //wybieramy od jakiej do jakiej dlugosci beda generowane tablice, oraz o ile beda sie te dlugosci zmieniac
       for (int dolna_granica=dolna_granica_od; dolna_granica<=dolna_granica_do; dolna_granica+=skok_dolnej){ //wybieramy jaka wartosc moze miec najmniejszy element, przydaje sie to jesli chcemy miec wieksze wartosci w tablicach
         for (int gorna_granica=gorna_granica_od; gorna_granica<=gorna_granica_do; gorna_granica+=skok_gornej){ //wymieramy jaka moze byc najwieksza wartosc, tego glownie urzywalem by zwiekszyc roznorodnosc wartosci

int tablica[dlugosc];
generuj_tablice (tablica,dlugosc,dolna_granica,gorna_granica); //tworzymy tablice z odpowiednimi parametrami

steady_clock::time_point start ; //inicjujemy rzeczy potrzebne do liczenia czasu
steady_clock::time_point stop ;
std::chrono::duration<double> czas ;

start = steady_clock::now(); //mierzymy ile zajmuje posortowanie Gnomem
sortowanie_gnoma (tablica,dlugosc,0);
stop = steady_clock::now();
czas = stop-start;
output<<setprecision(10)<<(czas.count())*10000000<<" "; //zapisujemy ten czas

start = steady_clock::now(); //mierzymy ile zajmuje posortowanie przez Zliczanie
sortowanie_przez_zliczanie (tablica,dlugosc,gorna_granica,0);
stop = steady_clock::now();
czas = stop-start;
output<<setprecision(10)<<(czas.count())*10000000<<" "<<dlugosc<<" "<<dolna_granica<<" "<<gorna_granica; //zapisujemy czas i parametry tabeli ktora sortowalismy

output<<" tablica: [ "; //zapisujemy jak wygladala tablica przed sortowanie, zeby zobaczy na podstawie grafu ktore tablice byly problemem dla algorytmow
for (int j=0; j<dlugosc; j++){
output<<tablica[j]<<" ";}
output<<"]"<<endl;
}}}
output.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Funkcja, ktora wczytuje tablice i sortuje ja oboma algorytmami
void posortuj_tablice(int dlugosc){

fstream input;
input.open("tablica.txt", ios::in); //otwieramy plik z ktorego wczytujemy tablice
fstream output;
output.open("Posortowana tablica.txt", ios::out); //otwieramy plik do ktorego wpiszemy posortowana tablice

int tablica[dlugosc];
for(int i=0; i<dlugosc; i++){ //wczytujemy tablice z pliku
    input>>tablica[i];
}

output<<"Podana tablica: [ "; //zapisujemy tablice z pliku, by byc pewnym ze program dziala
for(int i=0; i<dlugosc; i++){
    output<<tablica[i]<<" ";
}
output<<"]"<<endl<<endl;

steady_clock::time_point start ; //inicjujemy rzeczy potrzebne do liczenia czasu
steady_clock::time_point stop ;
std::chrono::duration<double> czas ;

start = steady_clock::now(); //mierzymy ile zajmuje posortowanie Gnomem
sortowanie_gnoma (tablica,dlugosc,0);
stop = steady_clock::now();
czas = stop-start;
output<<"Sortowanie Gnoma:"<<endl //zapisujemy czas dzialania algorytmu i posortowana przez niego tablice
<<"Czas dzialania: " <<setprecision(10)<<(czas.count())*10000000<<endl<<"Posortowana tablica: [ ";
for(int h=0; h<dlugosc; h++){
    output<<sortowanie_gnoma (tablica,dlugosc,h)<<" ";
}
output<<"]"<<endl<<endl;

start = steady_clock::now(); //mierzymy ile zajmuje posortowanie przez Zliczanie
sortowanie_przez_zliczanie (tablica,dlugosc,dlugosc,0);
stop = steady_clock::now();
czas = stop-start;
output<<"Sortowanie przez Zliczanie:"<<endl //zapisujemy czas dzialania algorytmu i posortowana przez niego tablice
<<"Czas dzialania: "<<setprecision(10)<<(czas.count())*10000000<<endl<<"Posortowana tablica: [ ";
for(int h=0; h<dlugosc; h++){
    output<<sortowanie_przez_zliczanie (tablica,dlugosc,dlugosc,h)<<" ";
}
output<<"]"<<endl<<endl;

input.close();
output.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int main (){

testy(10,100,10,0,0,1,10,100,10); //wywolujemy testy z wybranymi parametrami

posortuj_tablice(20); //sortujemy tablice z pliku znajac jej dlugosc

return 0;
}
