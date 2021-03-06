#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class plata
{
protected:   ///membrii protected pt ca facem mostenire
    int index_plata;
    string data;
    double suma;
    static int nr_plati;    ///variabila statica folosita pt a numara cate plati sunt in total
public:
    plata(string, double);    ///constructor initializare
    plata(const plata&);   ///constructor de copiere
    virtual ~plata();   ///destrcutor virtual

    virtual void citire(istream &in);          ///citire
    virtual void afisare(ostream &out);        ///afisare

    friend istream& operator>>(istream&, plata&);
    friend ostream& operator<<(ostream&, plata&);

    plata& operator=(const plata &p);    ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)

    string get_data(){       ///get
        return data; }
    double get_suma(){
        return suma; }

    void set_data(string d){      ///set
        data=d; }
    void set_suma(double s){
        suma=s; }

    static void numarPlati(){
        cout<<nr_plati/2;
    }
    int get_nr_plati() const{
        return nr_plati;
    }
    void setIndexPlata(int x)
    {
        this->index_plata = x;
    }
    int getIndexPlata()
    {
        return index_plata;
    }
};

int plata::nr_plati;   ///declar variabila

plata::plata(string data="", double suma=0)    ///constructor initializare
{
    nr_plati++;

    this->index_plata = nr_plati/2;
    if(data.length()){
    try{
        if(data.length() != 10 || data[2]!= '.' || data[5]!= '.')
            throw 1;
        if(data[0]< '0' || data[0] > '3' || data[1] < '0')
            throw 2;
        else if(data[0] == '0' && data[1] == '0')
            throw 2;
        else if(data[0] == '3' && data[1] > '1')
            throw 2;
        else if(data[3] < '0' || data[3] > '1' || data[1] < '0')
            throw 2;
        else if(data[3]== '1' && data[4] > '2')
            throw 2;
    }
    catch(int i){
        if(i == 1)
        {
            cout<<"Eroare constructor, data trebuie sa aiba formatul 'DD.MM.YYYY'! \n";
            exit(EXIT_FAILURE);
        }
        if(i == 2)
        {
            cout<<"Eroare constructor, introduceti o data valida! \n";
            exit(EXIT_FAILURE);
        }
    }
    }
    this->data = data;
    try{
        if (suma < 0)
            throw 1;
    }
    catch(int i){
        cout<<"Eroare constructor, suma nu poate fi negativa.\n";
        exit(EXIT_FAILURE);
    }
    this->suma = suma;
}

plata::plata(const plata& p)    ///constructor de copiere
{
    nr_plati++;
    this->data = p.data;
    this->suma = p.suma;
    this->index_plata = p.index_plata;
}

plata::~plata()     ///destructor
{
    nr_plati--;
    this->data = "";
    this->suma = 0;
}

void plata::citire(istream &in)
{
    in.get(); //nu stiu ce i cu asta, trebuie pus
    int ok=0;
    while(ok==0)
    {
        cout<< "Introduceti data(DD.MM.YYYY): ";
        string z;
        ok=1;
        getline(in, z);
        if(z.length() != 10 || z[2]!= '.' || z[5]!= '.')
            ok=0;
        if(z[0]< '0' || z[0] > '3' || z[1] < '0')
            ok=0;
        else if(z[0] == '0' && z[1] == '0')
            ok=0;
        else if(z[0] == '3' && z[1] > '1')
            ok=0;
        else if(z[3] < '0' || z[3] > '1' || z[1] < '0')
            ok=0;
        else if(z[3]== '1' && z[4] > '2')
            ok=0;

        if(ok==1)
            data = z;
        else cout<< "Nu ati introdus o data valida!!!\n";
    }
    cout<< "Introduceti suma: ";
    double x;
    in>>x;
    while(x<=0)
    {
        cout<<"Suma trebuie sa fie mai mare ca 0!! \n";
        cout<<"Introduceti suma: ";
        in>>x;
    }
    suma = x;

}

void plata::afisare(ostream &out)
{
    out<< "Id plata: "<< this->index_plata<<endl;
    out<< "Data: "<< this->data<<endl;
    out<< "Suma: "<< this->suma<<endl;
}

istream& operator>>(istream& in, plata& p)
{
    p.citire(in);
    return in;
}
ostream& operator<<(ostream& out, plata& p)
{
    p.afisare(out);
    return out;
}

plata& plata::operator=(const plata& p)
{
    this->index_plata = p.index_plata;
    this->data = p.data;
    this->suma = p.suma;

}

///=============================================================

class numerar:public plata
{
public:
    numerar(string data="", double suma=0):plata(data, suma) {}
    numerar(const numerar& n):plata(n) {}
    ~numerar() {}

    void citire(istream &in) {
        plata::citire(in); }
    void afisare(ostream &out) {
        plata::afisare(out); }

    friend istream& operator>>(istream&, numerar&);
    friend ostream& operator<<(ostream&, numerar&);

    numerar& operator=(const numerar &n);
};

istream& operator>>(istream& in, numerar& n)
{
    n.citire(in);
    return in;
}
ostream& operator<<(ostream& out, numerar& n)
{
    n.afisare(out);
    return out;
}
numerar& numerar::operator=(const numerar& n)
{
    plata::operator=(n);
}

///=============================================================

class cec: public plata
{
private:
    string nume_titular;
public:
    cec(string, double, string);
    cec(const cec&);
    ~cec();

    void citire(istream &in);
    void afisare(ostream &out);

    friend istream& operator>>(istream&, cec&);
    friend ostream& operator<<(ostream&, cec&);

    cec& operator=(const cec &c);
};

cec::cec(string data="", double suma=0, string nume_titular=""):plata(data, suma)
{
    this->nume_titular = nume_titular;
}

cec::cec(const cec& c):plata(c)
{
    this->nume_titular = c.nume_titular;
}

cec::~cec()
{
    this->nume_titular = "";
}

void cec::citire(istream& in)
{
    plata::citire(in);
    cout<<"Nume titular cec: ";
    in.get();
    getline(in, nume_titular);
}

void cec::afisare(ostream& out)
{
    plata::afisare(out);

    out<< "Nume titular cec: "<<this->nume_titular<<endl;
}

istream& operator>>(istream& in, cec& c)
{
    c.citire(in);
    return in;
}
ostream& operator<<(ostream& out, cec& c)
{
    c.afisare(out);
    return out;
}
cec& cec::operator=(const cec& c)
{
    plata::operator=(c);
    this->nume_titular = c.nume_titular;
}

///=======================================================================

class card:public plata
{
private:
    string nr_card;
public:
    card(string, double, string);
    card(const card&);
    ~card();

    void citire(istream &in);
    void afisare(ostream &out);

    friend istream& operator>>(istream&, card&);
    friend ostream& operator<<(ostream&, card&);

    card& operator=(const card &c);
};

card::card(string data="", double suma=0, string nr_card=""):plata(data, suma)
{
    if(nr_card.length()){
     try{
        for(int c = 0; c<nr_card.length(); c++)
        {
            if(nr_card[c] > '9' || nr_card[c] < '0')
                throw 1;
        }
        if(nr_card.length() != 16)
            throw 2;
     }
     catch(int i){
        if(i == 1)
        {
            cout<<"Eroare constructor, numarul trebuie sa fie compus doar din cifre!\n";
            exit(EXIT_FAILURE);
        }
        if(i == 2)
        {
            cout<<"Eroare constructor, numarul de card trebuie sa aiba 16 cifre!\n";
            exit(EXIT_FAILURE);
        }
     }
    }
    this->nr_card = nr_card;
}

card::card(const card& c):plata(c)
{
    this->nr_card = c.nr_card;
}

card::~card()
{
    this->nr_card = "";
}

void card::citire(istream& in)
{
    plata::citire(in);

    in.get(); //nu stiu ce i cu asta, trebuie pus
    int ok=0;
    while(ok==0)
    {
        cout<<"Introduceti numar card (16 cifre): ";
        string w;
        getline(in, w);
        ok=1;
        for(int i = 0; i<w.length(); i++)
        {
            if(w[i] > '9' || w[i] < '0')
                ok=0;
        }
        if(w.length() != 16)
            ok=0;
        if(ok==1)
            nr_card = w;
        else cout<< "Nu ati introdus un numar de card valida!!!\n";
    }
}

void card::afisare(ostream& out)
{
    plata::afisare(out);

    out<< "Numar card: "<<nr_card<<endl;
}

istream& operator>>(istream& in, card& c)
{
    c.citire(in);
    return in;
}
ostream& operator<<(ostream& out, card& c)
{
    c.afisare(out);
    return out;
}
card& card::operator=(const card& c)
{
    plata::operator=(c);
    this->nr_card = c.nr_card;
}


///===============================================================

template <class t> class Gestiune
{
    int numar;  ///numar total de plati
    vector<t> plati;
    static int np;

public:
    Gestiune(vector<t> plati = {}, int numar=0)
    {
        np++;
        this->numar = np;
        for(unsigned int i=0; i<plati.size();i++){
            this->plati.push_back(plati[i]);
        }
    };

    Gestiune(const Gestiune& g)
    {
        np++;
        this->numar = g.numar;
        for(unsigned int i=0; i<g.plati.size();i++){
            this->plati.push_back(g.plati[i]);
        }
    };
    ~Gestiune()
    {
        np--;
    };
    Gestiune& operator=(const Gestiune&  g)
    {
        if(this != &g)
        {
        	this->numar = g.numar;
        	plati.clear();
            for(unsigned int i=0; i<g.plati.size();i++){
                this->plati.push_back(g.plati[i]);
            }
		}
		return *this;
    }
    Gestiune& operator+=(t& nou)
    {
        this->plati.push_back(nou);
        this->numar++;
        return *this;
    }

    friend istream& operator >>(istream &in, Gestiune<t> &g)
    {
        cout<< "Introduceti datele platii: \n\n";
        t a;
        int i=1;
        cout<< "Chitanta "<< i<< ":";
        cout<< "\n-------------------------------------------\n";
        in >>a;
        g.plati.push_back(a);
        cout<< "-------------------------------------------\n";
        string z;
        cout<< "\nDoriti sa mai faceti o introducere? (DA/NU): ";
        in>>z;
        while(z=="DA" || z=="da")
        {
            i++;
            cout<< "\nChitanta "<< i<< ":\n";
            cout<< "-------------------------------------------\n";
            in>>a;
            g.plati.push_back(a);
            cout<< "-------------------------------------------\n";
            cout<< "\nDoriti sa mai cititi? Introduceti DA sau NU: ";
            in>>z;
         }
         cout<< "\n___________________________________________\n";

        g.numar=i;
        return in;
    }

    friend ostream& operator <<(ostream &out, Gestiune<t> &g)
    {
        cout<< "___________________________________________\n\n";
        out<<"Numarul total de plati: "<<g.numar<<endl;
        out<<"In gestiune se gasesc urmatoarele chitante: \n\n";
        for(int i=0;i<g.numar;i++)
        {
            out<< "Chitanta "<< i+1<< ":\n";
            out<< "-------------------------------------------\n";
            out<< g.plati[i];
            out<< "\n";
        }
        return out;
    }
};
template <class t> int Gestiune<t>::np; //declarare variabila

///===============================================================
/*
template <> class Gestiune <card>{
    int nr_clienti;
    vector<string> nume_clienti;

public:
	Gestiune(int nr_clienti = 0,vector<string> nume_clienti = {})
	{
		for(unsigned int i=0;i<nume_clienti.size();i++){
            this->nume_clienti.push_back(nume_clienti[i]);
        }
		this->nr_clienti = nr_clienti;

	}
	Gestiune(const Gestiune& g)
	{
        for(unsigned int i=0;i<g.nume_clienti.size();i++){
            this->nume_clienti.push_back(g.nume_clienti[i]);
        }
		this->nr_clienti = g.nr_clienti;

	}
	~Gestiune(){
	}
	Gestiune& operator=(const Gestiune& g){
		if(this != &g){
			for(unsigned int i=0;i<g.nume_clienti.size();i++){
                this->nume_clienti.push_back(g.nume_clienti[i]);
            }
		this->nr_clienti = g.nr_clienti;
		}
		return *this;
	}

	Gestiune& operator+=(string nou)
    {
        this->nume_clienti.push_back(nou);
        this->nr_clienti++;
        return *this;
    }

	friend istream& operator >>(istream &in, Gestiune<card> &g){
		cout <<"Introduceti numarul de clienti:";
		in >> g.nr_clienti;
		if (g.nr_clienti != 0){
			g.nume_clienti.clear();
        	cout << "Introduceti numele fiecarui client:\n";
        	string a;
       		for(int i=0;i<g.nr_clienti;i++){
				cout<<"Clientul " << i+1 <<":\n";
				in.get();
            	in >> a;
            	g.nume_clienti.push_back(a);
				cout<<"-------------------------\n";
       		}

    	}
    	else{
        	cout<<"Numarul de clienti trebuie sa fie mai mare decat 0.";
        	exit(EXIT_FAILURE);
		}
		return in;
	}
	friend ostream& operator <<(ostream &out, Gestiune<card> &g){
		out<<"In gestiune se gasesc urmatorii "<<g.nr_clienti<<" clienti:"<<"\n";
		for(int i=0;i<g.nr_clienti;i++){
        	out << "Clientul " << i+1 << ":\n";
        	out << g.nume_clienti[i];
			out << "-------------------------\n";
		}
		return out;
	}

};
*/
///===============================================================
void tip(plata *&x, int &i)
{
    string s;
    cout<<endl;
    cout<< "Introduceti modul de plata: ";
    cin>> s;
    try{
        if(s=="numerar") {
            x=new numerar;
            cin>>*x;
            i++;
        }
        else if(s=="cec") {
            x=new cec;      ///upcast?
            cin>>*x;
            i++;
        }
        else if(s=="card") {
            x=new card;
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
        cout<< "Trebuie sa introduceti numerar, cec sau card!\n";
    }
}


void menu_output()
{
    cout<<"\nFIRMA X\n\n";
    cout<<"\n\t\t\tMENIU:";
    cout<<"\n====================================================\n";
    cout<<"\n";
    cout<<" 1. Citire plati\n";
    cout<<" 2. Afisare plati\n";
    cout<<" 3. Afisare numar plati declarate\n";
    cout<<" 4. Gestiune --- TEMPLATE (numerar).\n";
    cout<<" 5. Gestiune --- TEMPLATE (cec). \n";
    cout<<" 6. Gestiune --- TEMPLATE (card). \n";
    cout<<" 7. Adaugarea unei plati. \n";
    cout<<" 8. Contorizare plati --- DYNAMIC_CAST (DOWNCAST). \n";
    cout<<" 0. Iesire\n\n";
    cout<<endl;

}
int main()
{
    int n=0;           ///cate obiecte se citesc
    //unorder_map<int, plata*> P;
    vector<plata*> v_plati;
    Gestiune <numerar> N;
    Gestiune <cec> C;
    Gestiune <card> CR;
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
            for(int i=0; i<n; )
            {
                v_plati.push_back(new plata);
                tip(v_plati[i], i);  ///etichetez tipul, citesc, retin fiind transmis prin adresa
            }
        }
        if(optiune==2)
        {
            system("CLS");
            if(n==0) cout<< "Trebuie sa se citeasca obiectele!";
            if(n>0) {
                for(int i=0; i<n; i++)
                {
                cout<< "-------------------------------\n\n";
                cout<< *v_plati[i]<<endl;
                }
            cout<< "-------------------------------\n\n";
            }
        }
        if(optiune==3)
        {
            cout<< "Numarul de plati declarate: ";
            plata::numarPlati();
            cout<<endl;
        }
        if(optiune==4)
        {
            cin>>N;
            cout<<N;
        }
        if(optiune==5)
        {
            cin>>C;
            cout<<C;
        }
        if(optiune==6)
        {
            cin>>CR;
            cout<<CR;
        }
        if(optiune==7)
        {
            cout<< "Ce tip nou de plata vreti sa adaugati? (numerar/cec/card) ";
            string z;
            numerar num;
            cec c;
            card cr;
            cin>>z;
            try
            {
                if(z=="numerar")
                {
                    cin>>num;
                    N+=num;
                    cout<<N;
                }
                else if(z=="cec")
                {
                    cin>>c;
                    C+=c;
                    cout<<C;
                }
                else if(z=="card")
                {
                    cin>>cr;
                    CR+=cr;
                    cout<<CR;
                }
                else
                    throw 10;
            }
            catch (bad_alloc var){
        			cout << "Eroare de alocare\n";
        			exit(EXIT_FAILURE);
    			}
    			catch(int j){
        		cout<<"Invalid. Incercati numerar, cec sau card\n ";
    			}
        }
        if(optiune==8)
        {
            int nr_num, nr_c, nr_cr;
            nr_num = nr_c = nr_cr = 0;
            if (n>0){
            for(int i=0;i<n;i++)
            {
                ///incerc cast catre numerar
                numerar *p1=dynamic_cast<numerar*>(v_plati[i]);
                ///incerc cast catre cec
                cec *p2=dynamic_cast<cec*>(v_plati[i]);
                ///incerc cast catre card
                card *p3=dynamic_cast<card*>(v_plati[i]);
                ///daca sunt nenuli atunci incrementez corespunzator
                if (p1)
                    nr_num++;
                if (p2)
                    nr_c++;
                if (p3)
                    nr_cr++;
            }
            cout<<"Numarul de plati facute numerar: "<<nr_num<<"\n";
            cout<<"Numarul de plati facute cu cec: "<<nr_c<<"\n";
            cout<<"Numarul de plati facute cu card: "<<nr_cr<<"\n";}
            else{
                cout<<"Nu s-au citit persoane. Reveniti la actiunea 1.\n";
            }
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
