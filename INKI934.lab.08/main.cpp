#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct student{
    string ime;
    string prezime;
    string indeks;
};

    char tochniPrvi[4]={'b', 'a', 'b', 'c'};
    char tochniVtori[4]={'a', 'b', 'd', 'c'};
    char tochniTreti[4][2]={{'b', 'e'}, {'b', 'd'}, {'a', 'c'}, {'a', 'e'}};

string StartTime() {
    time_t t = time(nullptr);
    char start_time[20];
    strftime(start_time, sizeof(start_time), "%d.%m.%Y %H:%M:%S", localtime(&t));
    return start_time;
}

string StopTime() {
    time_t t = time(nullptr);
    char stop_time[20];
    strftime(stop_time, sizeof(stop_time), "%d.%m.%Y %H:%M:%S", localtime(&t));
    return stop_time;
}

bool checkFileExists(string file1){
        ifstream infile(file1.c_str());
        return infile.good();
}

  // Funkcija koja se koristi za primanje na vlez

void studentInput(student &lice){
    cout<<"Vnesete go imeto na studentot: ";
        cin>>lice.ime;
    cout<<"Vnesete go prezimeto na studentot: ";
        cin>>lice.prezime;
    do {
        cout<<"Vnesete go indeksot na studentot: ";
        cin>>lice.indeks;
    }
    while(lice.indeks.size()!=3);
}
  // Funkcija koja se koristi za zapishuvanje na odgovorot vo datoteka

void writeOdgovor(fstream &file, char odg, char odg2, int br) {
    file << br << ". " << odg << " " << odg2 << endl;
}

  // Funkcija koja se koristi za proverka na odgovorot i boduvanje

float checkOdgovor(int brojnaprashanje, char answer, char answer2){
    if (brojnaprashanje <= 4){
        if (answer == tochniPrvi[brojnaprashanje-1])
        return 5;
    }
    else if (brojnaprashanje > 4 && brojnaprashanje <= 8){
        if (answer == tochniVtori[brojnaprashanje-5])
        return 8;
    }
    else if (brojnaprashanje > 8 && brojnaprashanje <= 12){
        if (((answer == tochniTreti[brojnaprashanje-9][0]) && (answer2 == tochniTreti[brojnaprashanje-9][1])) || ((answer == tochniTreti[brojnaprashanje-9][1]) && (answer2 == tochniTreti[brojnaprashanje-9][0])))
        return 12;
    }
}

  // Funkcija koja ovozmozuva proverka na vnes kaj odgovorot i ispishuvanje na odgovorot vo datoteka

float handleInput(int brojprashanje, fstream &file){
    char odgovor,odgovor2;

    if (brojprashanje <= 4){
        do{
            cout<<"Vashiot odgovor: ";
            cin>>odgovor;
        }
            while(odgovor != 'a' && odgovor != 'b' && odgovor != 'c');
                    writeOdgovor(file, odgovor, ' ', brojprashanje);
    }
    else if (brojprashanje > 4 && brojprashanje <= 8 ){
        do{
            cout<<"Vashiot odgovor: ";
            cin>>odgovor;
        }
        while( odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' );
                    writeOdgovor(file, odgovor, ' ', brojprashanje);
    }
    else if (brojprashanje > 8 && brojprashanje <= 12 ){
        do{
            cout<<"Vashiot odgovor: ";
            cin>>odgovor;
        }
        while(odgovor != 'a' && odgovor != 'b' && odgovor != 'c' && odgovor != 'd' && odgovor != 'e');
        do{
            cout<<"Vashiot odgovor: ";
            cin>>odgovor2;
        }
        while((odgovor2 == odgovor)  || (odgovor2 != 'a' && odgovor2 != 'b' && odgovor2 != 'c' && odgovor2 != 'd' && odgovor2 != 'e'));
            writeOdgovor(file, odgovor, odgovor2, brojprashanje);
    }
      return checkOdgovor(brojprashanje, odgovor, odgovor2);
}

  // Funkcija koja se koristi za proverka na poeni i vrakanje na vrednosta na ocenkata

int score(float poeni){
    if (poeni >= 0 && poeni <= 50)
        return 5;
    else if (poeni >= 51 && poeni <= 60)
        return 6;
    else if (poeni >= 61 && poeni <= 70)
        return 7;
    else if (poeni >= 71 && poeni <= 80)
        return 8;
    else if (poeni >= 81 && poeni <= 90)
        return 9;
    else if (poeni >= 91 && poeni <= 100)
        return 10;
}

  // Funkcija za pechatenje na tabela so tochnite odgovori

void answersTable(){
    cout<<"Tochni odgovori na prashanjata se:"<<endl;
    for(int i=1;i<=12;i++){
        if (i <= 4)
            cout<<i<<". "<<tochniPrvi[i-1]<<endl;
        else if (i > 4 && i <= 8)
            cout<<i<<". "<<tochniVtori[i-5]<<endl;
        else if (i > 8 && i <= 12)
            cout<<i<<". "<<tochniTreti[i-9][0] << " " <<tochniTreti[i-9][1]<<endl;
    }
}

int main(){

    fstream file,test;
    student lice;
    string prashanje;
    int brojnaprashanje=1;
    float poeni = 0;
    studentInput(lice);

    int count = 0;
    string file3 = "brojach.txt";
    file.open(file3.c_str(), ios::in);
        if (file.is_open()) {
            file >> count;
        }
    file.close();
    count++;

    file.open(file3.c_str(), ios::out);
        if (file.is_open()) {
            file << count;
        }
    file.close();

    const string file2 = "Students.log";
    file.open(file2.c_str(), ios::app);
    file<<count<<". "<< StartTime() << "; " << lice.ime << ", " << lice.prezime << ", " << "INKI" << lice.indeks <<  "\n";
    file.close();

    // Kreiranje na datotekata so ime i prezime na studentot

    const string file1 = lice.ime + lice.prezime + "INKI" + lice.indeks;
        if (checkFileExists(file1)) {
            cout << "Veke ste go reshile testot." ;
            return 0;
        }

    file.open(file1.c_str(),ios::out);
    file<<"Ime: "<<lice.ime<<"\nPrezime: "<<lice.prezime<<"\nIndeks: INKI"<<lice.indeks<<"\nVreme na start: "<<StartTime()<<"\n";
    file<<"----------------------"<<"\n";
    file<<"Vashite odgovori:\n";
    file.close();

    // Otvoranje na datotekata so prasanja i prezemanje na soodvetnoto prashanje i negovite odgovori

    test.open("prashanja.txt", ios::in);
        while(getline( test , prashanje )){
            for (int i=0; i < prashanje.size();i++){
                if (prashanje[i] == ';'){
                    cout<<endl;
                    i++;
                }
                else
                    cout<<prashanje[i];
            }
            cout<<endl;
            file.open(file1.c_str(), ios::app);
            poeni += handleInput(brojnaprashanje, file);
            file.close();
            brojnaprashanje++;
        }
    test.close();

    file.open(file1.c_str(), ios::app);
    file<<"----------------------";
    file<<"\nVreme na kraj: "<<StopTime()<<"\nPoeni: "<<poeni<<"\nVashata ocenka: " <<score(poeni);
    file.close();

    cout<<"Vashata ocenka: "<<score(poeni)<<endl;
    answersTable();
   return 0;
}