///Proiectul 8
///Murgu Diana
///Grupa 212

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

class Multime {
private:
    int n;
    int v[100];
public:
    Multime(int );         ///constructor initializare
    Multime(Multime&);     ///constructor copiere
    ~Multime ();           ///destructor
    void set_n(int);                       ///set
    void set_v(int v[100]);                ///set
    int get_n(){return n;};              ///get
    int get_v();                         ///get
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Multime& M);       ///supraincarcare pe >>
    friend ostream& operator<<(ostream &out, Multime& M);       ///supraincarcare pe <<
    void eliminare_duplicate();           ///fuctia care transforma un vector in multime, prin eliminarea duplicatelor
    friend Multime& operator+(Multime &M1, Multime &M2); ///supraincarcare operator +
    friend Multime& operator*(Multime &M1, Multime &M2); ///supraincarcare operator *
    friend Multime& operator-(Multime &M1, Multime &M2); ///supraincarcare operator -
};

Multime::Multime(int n=0){
    this->n = n;
    for(int i=0; i<n; i++)
       this->v[i] = 0;
}
Multime::Multime(Multime& M){
    this->n = M.n;
    for(int i=0; i<n; i++)
       this->v[i] = M.v[i];
}
Multime::~Multime(){
    this->n=0;
}
void Multime::set_n(int nr) {n = nr;}
void Multime::set_v(int v[100]) {
    for(int i=0; i<n; i++)
        v[i]=0;
}
int Multime::get_v(){
    return *v;
}
void Multime::citire(istream &in){
    cout<<"~Introduceti numarul de elemente ale multimii: ";
    in>>n;
    if(n<0)
    {
        while(n<0)
        {
            cout<<"~Numarul de elemente este invalid, introduceti un numar de elemente valid mai mare sau egal cu 0: ";
            in>>n;
        }
    }
    if(n==0) cout<<"Multime vida";
    if(n>0){
        cout<<"~Introduceti elementele multimii: ";
        for(int i=0; i<n; i++)
            in>>v[i];
        cout<< "{";
        for(int i=0; i<n-1; i++)
            cout<< v[i]<< ", ";
        cout<< v[n-1]<<"}";
    }
    cout<<endl<<endl;
}
istream& operator>>(istream& in, Multime& M){
    M.citire(in);
    return in;
}
void Multime::afisare(ostream &out){
    if (n==0)
        cout<<"Multime vida";
    if (n>0) {
        cout<< "{";
        for(int i=0; i<n-1; i++)
            cout<< v[i]<< ", ";
        cout<< v[n-1]<<"} \n";
    }
    cout<<endl<<endl;
}
ostream& operator<<(ostream& out, Multime& M){
    M.afisare(out);
    return out;
}
void Multime::eliminare_duplicate(){
    if(n>1){
       for(int i=0; i<n-1; i++)
         for(int j=i+1; j<n; j++)
            if(v[i]==v[j]) {
                for(int k=j; k<n; k++)
                    v[k]=v[k+1];
                n--;
                j--;
            }
    }
}

inline Multime& operator+(Multime &M1, Multime& M2){
    Multime *M = new Multime;
    for(int i=0; i<M1.n; i++)
        M->v[i] = M1.v[i];
    int k=M1.n;
    for(int i=0; i<M2.n; i++)
    {
        int gasit=0;
        for(int j=0; j<M1.n && !gasit; j++)
            if(M2.v[i]==M1.v[j]) gasit=1;
        if(!gasit) {
            M->v[k] = M2.v[i];
            k++;
        }
    }
    M->n = k;
    return *M;
}

inline Multime& operator*(Multime &M1, Multime& M2){
    Multime *M = new Multime;
    int k=0;
    for(int i=0; i<M1.n; i++)
        for(int j=0; j<M2.n; j++)
           if(M1.v[i]==M2.v[j]){
                M->v[k]=M1.v[i];
                k++;
            }
    M->n = k;
    return *M;
}

inline Multime& operator-(Multime &M1, Multime& M2){
    Multime *M = new Multime;
    int k=0;
    for(int i=0; i<M1.n; i++)
    {
        int gasit=0;
        for(int j=0; j<M2.n && !gasit; j++)
            if(M1.v[i]==M2.v[j]) gasit=1;
        if(!gasit){
            M->v[k]=M1.v[i];
            k++;
        }
    }
    M->n = k;
    return *M;
}
void menu_output()
{
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Citire multimi "); printf("\n");
    printf("2. Afisare multimi"); printf("\n");
    printf("3. Eliminarea duplicatelor"); printf("\n");
    printf("4. Reuniunea a doua multimi"); printf("\n");
    printf("5. Intersectia a doua multimi"); printf("\n");
    printf("6. Diferenta a doua multimi"); printf("\n");
    printf("0. Iesire."); printf("\n");
}
void menu()
{
    int option; ///optiunea aleasa din meniu
    option=0;
    int nr=0;
    Multime *M;
    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        scanf("%d", &option);

        cout<<endl;

        ///citire de n obiecte
        if(option==1)
        {
            while(nr<=0) {
                cout<< "Cate multimi se citesc? ";
                cin>>nr;
                if(nr<=0) cout<< "Numarul nu este valid, trebuie introdus un numar natural mai mare decat 0! \n";
            }
            M= new Multime[nr];
            cout<<endl;
            for(int i=0; i<nr; i++)
            {
                cout<< "Se citeste multimea "<<i+1<<endl;
                cin>>M[i];
            }
        }
        ///afisare de n obiecte
        if(option==2)
        {
            if(nr>0)
              for(int i=0; i<nr; i++)
              {
                cout<<"Se afiseaza multimea "<<i+1<<":\n";
                cout<<M[i];
              }
            else
                cout<<"Nu s-au citit multimi!";
        }
        ///eliminarea duplicatelor din vector
        if(option==3)
        {
            cout<<"Se citeste multimea: \n";
            Multime M;
            cin>>M;
            cout<<"Prin eliminarea duplicatelor, multimea va fi: \n";
            M.eliminare_duplicate();
            cout<< M ;
        }
        ///Reuniunea a doua multimi
        if (option==4)
        {
            cout<<"Se citeste prima multime: \n";
            Multime M1;
            cin>>M1;
            M1.eliminare_duplicate();
            cout<<"Se citeste a doua multime: \n";
            Multime M2;
            cin>>M2;
            M2.eliminare_duplicate();
            Multime M;
            M=M1+M2;
            cout<<"Multimea rezultata prin reuniune este: \n";
            cout<<M;
        }
        ///Intersectia a doua multimi
        if (option==5)
        {
            cout<<"Se citeste prima multime: \n";
            Multime M1;
            cin>>M1;
            M1.eliminare_duplicate();
            cout<<"Se citeste a doua multime: \n";
            Multime M2;
            cin>>M2;
            M2.eliminare_duplicate();
            Multime M;
            M=M1*M2;
            cout<<"Multimea rezultata prin intersectie este: \n";
            cout<<M;
        }
        ///Diferenta a doua multimi
        if (option==6)
        {
            cout<<"Se citeste prima multime: \n";
            Multime M1;
            cin>>M1;
            M1.eliminare_duplicate();
            cout<<"Se citeste a doua multime: \n";
            Multime M2;
            cin>>M2;
            M2.eliminare_duplicate();
            Multime M;
            M=M1-M2;
            cout<<"Multimea rezultata prin diferenta este: \n";
            cout<<M;
        }
        if (option==0)
        {
            printf("\nEXIT!\n");
        }
        if (option<0||option>6)
        {
            printf("\nSelectie invalida\n");
        }
        printf("\n");
    }while(option!=0);
}
int main()
{
    menu();
    return 0;
}
