#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Avocat
{
protected:
    int cod;
    string nume;
    int nr_procese;
    int *vector_procese;
    static int nr;
public:
    Avocat(int, string, int );     ///constructor initializare
    Avocat(Avocat&);                   ///constructor de copiere
    virtual ~Avocat ();                ///destrcutor virtual
    virtual void citire(istream &in);          ///citire
    virtual void afisare(ostream &out);        ///afisare
    friend istream& operator>>(istream&, Avocat&);          ///supraincarcare pe >>
    friend ostream& operator<<(ostream&, Avocat&);          ///supraincarcare pe <<
    virtual Avocat& operator=(Avocat &avoc);    ///supraincarcarea operatorului de atribuire
    int get_cod(){      ///get
        return cod; }
    int get_nr_procese(){
        return nr_procese;}
    string get_nume(){
        return nume; }
    int get_vector_procese(){
        return *vector_procese;}

    void set_cod(int x){               ///set
        cod=x;}
    void set_nr_procese(int numar){
        nr_procese=numar;}
    void set_nume(string num){
        nume=num;}
    void set_vector_procese(int *vector_procese) {
        for(int i=0; i<nr_procese; i++)
            vector_procese[i]=0;
    }
    bool operator>(Avocat& avoc1)               ///supraincarcare operator >
    {
        if(nr_procese > avoc1.nr_procese)
            return true;
        else
            return false;
    }
    bool operator<(Avocat& avoc1)              ///supraincarcare operator <
    {
        if(nr_procese < avoc1.nr_procese)
            return true;
        else
            return false;
    }
    static void numarObiecte(){
        cout<<nr;
    }
};

int Avocat::nr=0;

Avocat::Avocat(int cod=0, string nume="", int nr_procese=0)   ///constructor initializare
{
    nr++;
    this->cod = cod;
    this->nume= nume;
    this->nr_procese = nr_procese;
    vector_procese = new int[nr_procese];
    for(int i=0; i<nr_procese; i++)
        this->vector_procese[i] = 0;
}

Avocat::Avocat(Avocat& avoc)                   ///constructor de copiere
{
    this->cod = avoc.cod;
    this->nume = avoc.nume;
    this->nr_procese = avoc.nr_procese;
    vector_procese = new int[nr_procese];
    for(int i=0; i<nr_procese; i++)
        this->vector_procese[i] = avoc.vector_procese[i];
}

Avocat::~Avocat()                         ///destructor
{
    this->cod = 0;
    this->nume = "";
    this->nr_procese = 0;
    delete[]vector_procese;
}

void Avocat::citire(istream &in)         ///citire
{
    cout<< "~Introduceti cod: ";
    in>>cod;
    cout<< "~Introduceti nume: ";
    in.get();
    getline(in, nume);
    cout<< "~Introduceti numar de procese: ";
    in>> nr_procese;
    if(nr_procese>0)
        cout<< "~Introduceti suma primita pentru fiecare proces: ";
    for(int i=0; i<nr_procese; i++)
        in>>vector_procese[i];
}

istream& operator>>(istream& in, Avocat& avoc)     ///supraincarcare pe operatoul >>
{
    avoc.citire(in);
    return in;
}

void Avocat::afisare(ostream &out)
{
    out<< "Cod: "<< cod<<endl;
    out<< "Nume: "<< nume<< endl;
    if(nr_procese==0)
        out<< "Fara procese";
    if(nr_procese>0)
    {
        out<< "Numar de procese: "<< nr_procese<<endl;
        out<< "Suma primita pentru fiecare proces: ";
        for(int i=0; i<nr_procese; i++)
          out<< vector_procese[i]<< " ";
    }
    out<<endl;
}

ostream& operator<<(ostream& out, Avocat& avoc)      ///supraincarcare pe operatoul <<
{
    avoc.afisare(out);
    return out;
}


Avocat& Avocat::operator=(Avocat &avoc)
{
    this->cod = avoc.cod;
    this->nume = avoc.nume;
    this->nr_procese = avoc.nr_procese;
    vector_procese = new int[nr_procese];
    for(int i=0; i<nr_procese; i++)
        this->vector_procese[i] = avoc.vector_procese[i];
}

//=====================================================

class Avocat_Oficiu:public Avocat
{
private:
    string nume_client;
    int durata;
    static int duratamax;
public:
    Avocat_Oficiu(int, string, int, string, int);    ///constructor initializare
    Avocat_Oficiu(Avocat_Oficiu&);                  ///constructor copiere
    ~Avocat_Oficiu();                               ///destructor
    string get_nume_cliecte(){       ///get
        return nume_client;}
    int get_durata(){
        return durata;}
    void set_nume_client(string num){     ///set
        nume_client=num;}
    void set_durata(int d){
        durata=d;}
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, Avocat_Oficiu&);
    friend ostream& operator<<(ostream&, Avocat_Oficiu&);
    Avocat_Oficiu& operator=(Avocat_Oficiu &o);
    static void duratamaxima(){ /// metoda statica de afisare a duratei max
        cout<<duratamax;
    }
};

int Avocat_Oficiu::duratamax=0;

Avocat_Oficiu::Avocat_Oficiu(int cod=0, string num="", int nr_procese=0, string nume_client="", int durata=0)    ///constructor initializare
{
    this->nume_client = nume_client;
    this->durata = durata;
}
Avocat_Oficiu::Avocat_Oficiu(Avocat_Oficiu &avoc)
{
    this->nume_client = avoc.nume_client;
    this->durata = avoc.durata;
}

Avocat_Oficiu::~Avocat_Oficiu()         ///destructor
{
    this->nume_client = "";
    this->durata=0;
}

void Avocat_Oficiu::citire(istream &in)       ///citire
{
    Avocat::citire(in);
    cout<< "~Introduceti nume client: ";
    in.get();
    getline(in, nume_client);
    cout<< "~Introduceti durata petrecuta cu clientul: ";
    in>>durata;
    if(durata > duratamax) duratamax = durata;
}

void Avocat_Oficiu::afisare(ostream &out)         ///afisare
{
    Avocat::afisare(out);
    out<< "Nume client: "<< nume_client<<endl;
    out<< "Durata petrecuta cu clientul: "<< durata<<endl;
}

istream& operator>>(istream& in, Avocat_Oficiu& avoc)
{
    avoc.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Avocat_Oficiu& avoc)
{
    avoc.afisare(out);
    return out;
}

Avocat_Oficiu& Avocat_Oficiu::operator=(Avocat_Oficiu& avoc)
{
    Avocat::operator=(avoc);
    this->nume_client = avoc.nume_client;
    this->durata = avoc.durata;
}

void tip(Avocat *&x, int &i)
{
    string s;
    cout<<endl;
    cout<< "Se citeste avocat sau avocat_oficiu? ";
        cin>> s;
    try{
        if(s=="avocat") {
            x=new Avocat;
            cin>>*x;
            i++;
        }
        else if(s=="avocat_oficiu") {
            x=new Avocat_Oficiu;      ///upcast
            cin>>*x;
            i++;
        }
        else
            throw 10;
    }
    catch (bad_alloc var) {
        cout<< "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j){
        cout<< "Trebuie sa introduceti avocat/avocat_oficiu!\n";
    }
}
//==========================================
void menu_output()
{
    cout<<"Murgu Diana - Grupa 212 \n";
    cout<<"\n\t\t\tMENIU:";
    cout<<"\n==============================================================\n";
    cout<<"\n";
    cout<<" 1. Citire avocati\n";
    cout<<" 2. Afisare avocati\n";
    cout<<" 3. Ordonare crescatoare in functie de numarul de procese\n";
    cout<<" 4. Ordonarea descrescatoare in fuctie de numarul de procese\n";
    cout<<" 5. Gasirea avocatului care a petrecut timpul maxim cu un client\n";
    cout<<" 6. Afisarea numarului de obiecte create\n";
    cout<<" 0. Iesire\n\n";
    cout<<endl;

}
/*
Avocat gaseste (Oficiu_Avocat *o,int n)
{
    int numar = 0;
    Oficiu_Avocat avo;
    for (int p = 0 ; p <n ;p++){


       int x = o[p].get_durata();
       if (x > numar)
       {

            avo = o[p];
            numar =x;
       }
    }
   return avo;

}
*/
int main()
{
    int n=0;             ///cate obiecte se citesc
    Avocat **a;
    //Avocat_Oficiu **o;
    int optiune=0;
    do
    {
        menu_output();
        cout<< "Introduceti numarul actiunii: ";
        cin>> optiune;
        cout<<endl;
        if(optiune==1)
        {
            system("CLS");
            while(n<=0) {
                cout<< "Cate obiecte se citesc? ";
                cin>>n;
                if(n<=0) cout<< "Numarul nu este valid, trebuie introdus un numar natural mai mare decat 0! \n";
            }
            a= new Avocat*[n];
            //o= new Avocat_Oficiu*[n];
            for(int i=0; i<n; )
            {
               tip(a[i], i);
            }
        }
        if(optiune==2)
        {
            system("CLS");
            if(n==0) cout<< "Trebuie sa se citeasca obiectele!";
            if(n>0)
                for(int i=0; i<n; i++)
                {
                cout<< "-------------------------------\n\n";
                cout<< *a[i]<<endl;
                }
            cout<< "-------------------------------\n\n";
        }

        if(optiune==3)
        {
            system("CLS");
            if(n==0) cout<< "Trebuie sa se citeasca obiectele!";
            if(n>0)
            {
                Avocat aux;
                for(int i=0; i<n-1; i++)
                    for(int j=i+1; j<n; j++)
                        if(*a[i] > *a[j])
                        {
                          aux = *a[i];
                          *a[i] = *a[j];
                          *a[j] = aux;
                        }
                cout<< "Dupa ordonarea crescatoare: \n\n";
                for(int i=0; i<n; i++)
                {
                    cout<< "-------------------------------\n\n";
                    cout<< *a[i]<<endl;
                }
                cout<< "-------------------------------\n\n";
            }
        }
        if(optiune==4)
        {
            system("CLS");
            if(n==0) cout<< "Trebuie sa se citeasca obiectele!";
            if(n>0)
            {
                Avocat aux;
                for(int i=0; i<n-1; i++)
                    for(int j=i+1; j<n; j++)
                        if(*a[i] < *a[j])
                        {
                          aux = *a[i];
                          *a[i] = *a[j];
                          *a[j] = aux;
                        }
                cout<< "Dupa ordonarea descrescatoare: \n\n";
                for(int i=0; i<n; i++)
                {
                    cout<< "-------------------------------\n\n";
                    cout<< *a[i]<<endl;
                }
                cout<< "-------------------------------\n\n";
            }
        }
        if(optiune==5)
        {
            system("CLS");
            if(n==0) cout<< "Trebuie sa se citeasca obiectele!";
            if(n>0)
            {
                cout<< "Avocatul care e petrecut timpul maxim cu un client \n";
                //Avocat_Oficiu::duratamaxima();


            }
        }
        if(optiune==6)
        {
            cout<< "Numarului de obiecte create este ";
            Avocat::numarObiecte();
            cout<< endl<<endl;
        }
        if(optiune==0)
        {
            cout<< "\nEXIT!\n";
        }
        if(optiune<0 || optiune>6)
        {
            cout<< "\nSelectie invalida\n";
        }
        cout<<endl;
    }while(optiune != 0);

    return 0;
}
