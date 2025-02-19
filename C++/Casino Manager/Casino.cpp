#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>

using namespace std;

class Client
{
private:
    int idClient;
    char *nume;
    float balanta;
    bool este_VIP;
    int *varsta;
    double istoric_tranzactii;
    string caracteristici[6] = {"Id", "Nume", "Balanta", "este_VIP", "Varsta","Istoric tranzactii"};

public:

    Client(int id, const char *n, float b, bool vip, int *v, double is) // constructorul cu toti parametrii
    {
        idClient = id;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        balanta = b;
        este_VIP = vip;
        varsta = v;
        istoric_tranzactii = is;
    }

    Client(int id, const char *n, float b, bool vip) // constructorul cu 4 parametrii
    {
        idClient = id;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        balanta = b;
        este_VIP = vip;
        this -> varsta = NULL;
        istoric_tranzactii = 0;
    }

    Client(int id, const char *n) // constructorul cu 2 parametrii
    {
        idClient = id;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        balanta = 0;
        este_VIP = false;
        varsta = new int(0);
        istoric_tranzactii = 0;
    }

    Client() // constructor fără parametrii
    {
        idClient = 0;
        nume = new char[1];
        nume[0] = '\0';
        balanta = 0;
        este_VIP = false;
        varsta = new int(0);
        istoric_tranzactii = 0;
    }

    Client(const Client& client) // constructorul de copiere
    {
        idClient = client.idClient;
        nume = new char[strlen(client.nume) + 1];
        strcpy(nume, client.nume);
        balanta = client.balanta;
        este_VIP = client.este_VIP;
        varsta = new int(*client.varsta);
        istoric_tranzactii = client.istoric_tranzactii;
    }

    ~Client() // destructorul
    {
        delete[] nume;
        delete varsta;
    }

    Client& operator=(const Client& client) // supraincaracarea operatorului "="
    {
        if (this != &client)
        {
            this->idClient = client.idClient;
            this->balanta = client.balanta;
            this->este_VIP = client.este_VIP;
            this->istoric_tranzactii = client.istoric_tranzactii;
            delete[] this->nume;
            this->nume = new char[strlen(client.nume) + 1];
            strcpy(this->nume, client.nume);
            delete this->varsta;
            this->varsta = new int(*client.varsta);
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Client& client) // supraincarcarea operatorului >>
    {
        cout << "Introduceti idClient: ";
        in >> client.idClient;

        cout << "Introduceti numele: ";
        in >> *(client.nume);

        cout << "Introduceti balanta: ";
        in >> client.balanta;

        cout << "Este VIP? (1/0): ";
        in >> client.este_VIP;

        cout << "Introduceti varsta: ";
        in >> *(client.varsta);

        cout << "Introduceti istoricul tranzactiilor: ";
        in >> client.istoric_tranzactii;

        return in;
    }

    friend ostream& operator<<(ostream& out, const Client& client) // supraincarcare operatorului <<
    {
        out << "ID Client: " << client.idClient << endl;
        out << "Nume: " << client.nume << endl;
        out << "Balanta: " << client.balanta << endl;
        out << "VIP " << client.este_VIP << endl;
        out << "Varsta: " << *(client.varsta) << endl;
        out << "Istoricul tranzactiilor: " << client.istoric_tranzactii << endl;
        return out;
    }

    void afisare_client() // functie de afisare
    {
        cout<<"Id Client: "<<idClient<<endl;
        cout<<"Nume Client: "<< nume<<endl;
        cout<<"Balanta: "<<balanta<<endl;
        cout<<"VIP: "<<este_VIP<<endl;
        cout<<"varsta: "<<*varsta<<endl;
        cout<<"Pierderi: "<<istoric_tranzactii<<endl;
    }

    void set_id(int newid) // setter pt id
    {
        idClient = newid;
    }

    int get_id() const // getter pt id
    {
        return idClient;
    }

    void set_nume(const char* n) // setter pt nume
    {
        delete[] this -> nume;
        nume = new char[strlen(n) + 1];
        strcpy(this -> nume, n);
    }

    const char* get_nume() const // getter pt nume
    {
        return nume;
    }

    void set_balanta(float b) // setter pt balanta
    {
        balanta = b;
    }

    float get_balanta() const // getter pt balanta
    {
        return balanta;
    }

    void set_varsta(int *v) // setter pt varsta
    {
        if (varsta != nullptr)
        {
            delete varsta;
        }
        varsta = new int(*v);
    }

    int* get_varsta() const // getter pt varsta
    {
        return varsta;
    }

    void set_VIP(bool v) // setter pt "este_VIP"
    {
        este_VIP = v;
    }

    bool get_VIP() const // getter pt "este_VIP"
    {
        return este_VIP;
    }

    void set_is(double is) // setter pt istoric
    {
        istoric_tranzactii = is;
    }

    double get_is() const // getter pt istoric
    {
        return istoric_tranzactii;
    }

    string& operator[](int index) // operatorul de indexare
    {
        return caracteristici[index];
    }

    Client& operator++() // supraincarcarea operatorului ++
    {
        float valoare;
        cout << "Depunere in balanta: ";
        cin >> valoare;
        this -> balanta += valoare;
        return *this;
    }

    Client& operator--() // supraincarcarea operatorului --
    {
        float valoare;
        cout << "Retragere din balanta: ";
        cin >> valoare;
        this->balanta -= valoare;
        return *this;
    }

    Client operator+(const Client& c) // supraincaracarea operatorului +
    {
        Client result;
        result.balanta = this->balanta + c.balanta;
        return result;
    }

    Client operator*(const Client& c) // supraincarcarea operatorului *
    {
        Client result;
        result.balanta = this->balanta * c.balanta;
        return result;
    }

    operator float() const // supraincarcarea operatorului cast implicit
    {
        return this->balanta;
    }

    bool operator<(const Client& client) const //supraincarcarea operatorului conditional <
    {
        return this->balanta < client.balanta;
    }

    bool operator==(const Client& client) const //supraincarcarea operatorului de egalitate ==
    {
        return this->idClient == client.idClient &&
               strcmp(this->nume, client.nume) == 0 &&
               *this->varsta == *client.varsta &&
               this->balanta == client.balanta &&
               this->este_VIP == client.este_VIP &&
               this->istoric_tranzactii == client.istoric_tranzactii;
    }

    bool este_major()  // functie care verifica daca clientul are implinita varsta legala
    {
        int *v = get_varsta();
        if (*v >= 18)
        {
            cout << "Felicitari! Contul dvs a fost validat";
        }
        else
        {
            cout << "Contul dvs nu a fost validat!";
            cout << endl;
            cout << "Jocurile de noroc sunt interzise minorilor";
            set_id(0);
            set_balanta(0);
            set_is(0);
        }

        cout << endl;
        afisare_client();
    }

    bool vip() // functie care verifica daca clientul este VIP in functie de istoricul tranzactiilor
    {
        double is = get_is();
        if (is >= 5000)
            set_VIP(true);
        else
            set_VIP(false);
    }


};

class Angajat
{
private:
   char* nume;
   int varsta;
   char* departament;
   float salariu;
   float vechime;
   string caracteristici[5] = {"Nume", "Varsta", "Departament", "Salariu", "Vechime"};

public:

    // setteri si getteri

    void set_nume(const char* n)
    {
        delete[] this -> nume;
        nume = new char[strlen(n) + 1];
        strcpy(this -> nume, n);
    }

    const char* get_nume() const
    {
        return nume;
    }

    void set_varsta(int v)
    {
        varsta = v;
    }

    void set_departament(const char* d)
    {
        delete[] this -> departament;
        departament = new char[strlen(d) + 1];
        strcpy(this -> departament, d);
    }

    const char* get_departament() const
    {
        return departament;
    }

    void set_salariu(float s)
    {
        salariu = s;
    }

    float get_salariu() const
    {
        return salariu;
    }

    void set_vechime(float v)
    {
        vechime = v;
    }

    float get_vechime() const
    {
        return vechime;
    }

    // constructorii si destructorii
    Angajat(const char* n, int v, const char* d, float s, float vch)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        varsta = v;
        departament = new char[strlen(d) + 1];
        strcpy(departament,d);
        salariu = s;
        vechime = vch;
    }

    Angajat(const char *n, int v, const char* d)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        varsta = v;
        departament = new char[strlen(d) + 1];
        strcpy(departament,d);
        salariu = 0;
        vechime = 0;
    }

    Angajat(const char *n, int v)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        varsta = v;
        departament = new char[1];
        departament[0] = '\0';
        salariu = 0;
        vechime = 0;
    }

    Angajat()
    {
        nume = new char[1];
        nume[0] ='\0';
        varsta = 0;
        departament = new char[1];
        departament[0] = '\0';
        salariu = 0;
        vechime = 0;
    }

    Angajat(const Angajat& a)
    {
        nume = new char[strlen(a.nume) + 1];
        strcpy(nume,a.nume);
        varsta = a.varsta;
        departament = new char[strlen(a.departament) + 1];
        strcpy(departament,a.departament);
        salariu = a.salariu;
        vechime = a.vechime;
    }

    ~Angajat()
    {
        delete[] nume;
        delete[] departament;
    }

    // forma supraincarcata a operatorului =
    Angajat& operator=(const Angajat& angajat)
    {
        if (this != &angajat)
        {
            delete[] this->nume;
            this->nume = new char[strlen(angajat.nume) + 1];
            strcpy(this->nume, angajat.nume);
            delete[] this->departament;
            this->departament = new char[strlen(angajat.departament) + 1];
            strcpy(this->departament, angajat.departament);
            this->varsta = angajat.varsta;
            this->salariu = angajat.salariu;
            this->vechime = angajat.vechime;
        }
        return *this;
    }

    // supraincarcarea operatorului >>
    friend istream &operator>>(istream &in, Angajat &angajat)
    {
        char buffer[100];

        in.ignore();

        cout << "Introduceti numele: ";
        in.getline(buffer, 100);
        angajat.set_nume(buffer);

        cout << "Introduceti varsta: ";
        in >> angajat.varsta;

        in.ignore();

        cout << "Introduceti departamentul: ";
        in.getline(buffer, 100);
        angajat.set_departament(buffer);

        cout << "Introduceti salariul: ";
        in >> angajat.salariu;

        cout << "Introduceti vechimea: ";
        in >> angajat.vechime;

        return in;
    }

    // supraincarcarea operatorului <<
    friend ostream& operator<<(ostream& out, const Angajat& angajat)
    {
        out << "Nume: " << angajat.nume << endl;
        out << "Varsta: " << angajat.varsta << endl;
        out << "Departament: " << angajat.departament << endl;
        out << "Salariu: " << angajat.salariu << endl;
        out << "Vechime: " << angajat.vechime << endl;
        return out;
    }

    string& operator[](int index) // operatorul de indexare
    {
        return caracteristici[index];
    }

    Angajat& operator++(int marire) // supraincarcarea operatorului ++
    {
        marire = 2000;
        this -> salariu += marire;
        return *this;
    }

    Angajat operator+(const Angajat& a) // supraincaracarea operatorului +
    {
        Angajat result;
        result.salariu = this->salariu + a.salariu;
        return result;
    }

    Angajat operator*(const Angajat& a) // supraincaracarea operatorului *
    {
        Angajat result;
        result.salariu = this->salariu * a.salariu;
        return result;
    }

    operator float() const // supraincarcarea operatorului cast implicit
    {
        return this -> salariu;
    }

    bool operator >(const Angajat& a) const // supraincarcarea operatorului conditional >
    {
        return this->salariu > a.salariu;
    }

    bool operator==(const Angajat& a) const // supraincarcarea operatorului de egalitate ==
    {
        return strcmp(this->nume, a.nume) == 0 &&
               this->varsta == a.varsta &&
               this->salariu == a.salariu &&
               strcmp(this -> departament, a.departament) == 0 &&
               this->vechime == a.vechime;

    }

    void afisare_angajat() // afiseaza datele unui angajat
    {
        cout<<"Nume: "<< nume <<endl;
        cout<<"Varsta: "<< varsta <<endl;
        cout<<"Departament: "<< departament <<endl;
        cout<<"Vechime: "<< vechime <<endl;
    }

    void afisare_salariu()// afiseaza salariul (confidential) al unui angajat
    {
        cout<<nume<<"---"<<salariu<<endl;
    }

    void spor_vechime()// mareste slariul angajatului in functie de vechimea acestuia
    {
        float v = get_vechime();
        if(v>=5)
            set_salariu(get_salariu() + 2000);
        if(v>=10)
            set_salariu(get_salariu() + 2000);
        if(v>=15)
            set_salariu(get_salariu() + 2000);
        if(v>=20)
            set_salariu(get_salariu() + 4000);

    }

    void convertire_salariu()/* afiseaza pe ecran salariul net al angajatului tinand cont de cel brut
    si realizeaza un mini-raport (la alegere) al taxelor platite*/
    {
        float s = get_salariu();
        string d;
        bool ok = true;
        cout << "Raport taxe ? (DA / NU) "<<endl;;
        while (ok)
        {
            cin >> d;
            cout<<endl;
            if(d == "DA" || d == "NU")
            {
                cout << "Salariu brut: " << s << endl;
                cout<<endl;
                if(d == "DA")
                {
                    cout << "Impozit pe venit: -" << s * 0.065 << endl;
                    cout << "Asigurari sociale: -" << s * 0.25 << endl;
                    cout << "Asigurari de sanatate: -" << s * 0.1 << endl;
                }

                cout<<endl;
                cout << "Salariu net: " << s * 0.585 << endl;


                ok = false;

            }
            else
                cout << "Raspuns invalid" << endl;
        }

    }

};

class Joc
{
private:
    char *nume;
    char *tip;
    double balanta_joc;
    float miza_minima;
    float miza_maxima;
    int maxwin;
    float sanse;
    string caracterisitici[7] = {"Nume", "Tip", "Balanta joc", "Miza minima", "Miza maxima", "MAXWIN", "Sanse de castig"};

public:

    // setteri si getteri
    void set_nume(const char* n)
    {
        delete[] this->nume;
        this->nume = new char[strlen(n) + 1];
        strcpy(this -> nume, n);
    }

    const char* get_nume()
    {
        return nume;
    }

    void set_tip(const char* t)
    {
        delete[] this ->tip;
        this -> tip = new char[strlen(t) + 1];
        strcpy(this -> tip, t);
    }

    const char* get_tip()
    {
        return tip;
    }

    void set_balanta_joc(double b)
    {
        balanta_joc = b;
    }

    double get_balanta_joc() const
    {
        return balanta_joc;
    }

    void set_miza_minima(float mmin)
    {
        miza_minima = mmin;
    }

    float get_miza_minima() const
    {
        return miza_minima;
    }

    void set_miza_maxima(float mmax)
    {
        miza_maxima = mmax;
    }

    float get_miza_maxima() const
    {
        return miza_maxima;
    }

    void set_sanse(float s)
    {
        sanse = s;
    }

    float get_sanse() const
    {
        return sanse;
    }

    void set_maxwin(int m)
    {
        maxwin = m;
    }

    int get_maxwin() const
    {
        return maxwin;
    }

    // constructor cu toti parametrii
    Joc(const char *n, const char *t, double b, float mmin, float mmax, int mw, float s)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume, n);
        tip = new char[strlen(t) + 1];
        strcpy(tip, t);
        balanta_joc = b;
        miza_minima = mmin;
        miza_maxima = mmax;
        maxwin = mw;
        sanse = s;
    }

    // constructor cu 2 parametrii
    Joc(const char *n, const char *t)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume, n);
        tip = new char[strlen(t) + 1];
        strcpy(tip, t);
        balanta_joc = 0;
        miza_minima = 0.20;
        miza_maxima = 100;
        maxwin = 10000;
        sanse = 0;
    }

    // constructor cu 4 parametrii
    Joc(const char *n, const char *t, float mmin, float mmax)
    {
        nume = new char[strlen(n) + 1];
        strcpy(nume, n);
        tip = new char[strlen(t) + 1];
        strcpy(tip, t);
        balanta_joc = 0;
        miza_minima = mmin;
        miza_maxima = mmax;
        maxwin = 10000;
        sanse = 0;
    }

    // constructor de copiere
    Joc(const Joc &joc)
    {
        nume = new char[strlen(joc.nume) + 1];
        strcpy(nume, joc.nume);
        tip = new char[strlen(joc.tip) + 1];
        strcpy(tip, joc.tip);
        balanta_joc = joc.balanta_joc;
        miza_minima = joc.miza_minima;
        miza_maxima = joc.miza_maxima;
        maxwin = joc.maxwin;
        sanse = joc.sanse;
    }

    // destructor
    ~Joc()
    {
        delete[] nume;
        delete[] tip;
    }

    // constructor fara parametrii
    Joc()
    {
        nume = new char[1];
        nume[0] = '\0';
        tip = new char[1];
        tip[0] = '\0';
        balanta_joc = 0.0;
        miza_minima = 0.2;
        miza_maxima = 100;
        maxwin = 10000;
        sanse = 0;
    }

    // forma supraincarcata a operatorului =
    Joc& operator=(const Joc& joc)
    {
        if (this != &joc)
        {
            delete[] this->nume;
            this->nume = new char[strlen(joc.nume) + 1];
            strcpy(this->nume, joc.nume);
            delete[] this -> tip;
            this -> tip =new char[strlen(joc.tip) + 1];
            strcpy(this -> tip, joc.tip);
            this -> balanta_joc = joc.balanta_joc;
            this -> miza_minima = joc.miza_minima;
            this -> miza_maxima = joc.miza_maxima;
            this -> maxwin = joc.maxwin;
            this -> sanse = joc.sanse;
        }
        return *this;
    }

    // supraincarcarea operatorului <<
    friend ostream& operator<<(ostream& out, const Joc& joc)
    {
        out << "Nume joc: " << joc.nume << endl;
        out << "Tip joc: " << joc.tip << endl;
        out << "Balanta joc: " << joc.balanta_joc << endl;
        out << "Miza minima: " << joc.miza_minima << endl;
        out << "Miza maxima: " << joc.miza_maxima << endl;
        out << "Maximul de castig: " << joc.maxwin << endl;
        out << "Sanse: " << joc.sanse << endl;
        return out;
    }

    // supraincarcarea operatorului >>
    friend istream& operator>>(istream& in, Joc& joc)
    {
        char buffer[100];

        in.ignore();

        cout << "Introduceti numele jocului: ";
        in.getline(buffer, 100);
        joc.set_nume(buffer);

        in.ignore();

        cout << "Introduceti tipul jocului: ";
        in.getline(buffer, 100);
        joc.set_tip(buffer);

        cout << "Introduceti balanta jocului: ";
        in >> joc.balanta_joc;

        cout << "Introduceti miza minima a jocului: ";
        in >> joc.miza_minima;

        cout << "Introduceti miza maxima a jocului: ";
        in >> joc.miza_maxima;

        cout << "Introduceti castigul maxim al jocului: ";
        in >> joc.maxwin;

        cout << "Introduceti sansele de castig ale jocului: ";
        in >> joc.sanse;

        return in;
    }

    string& operator[](int index) // operatorul de indexare
    {
        return caracterisitici[index];
    }

    Joc& operator++(int marire) // supraincarcarea operatorului ++
    {
        marire = 100;
        this -> balanta_joc += marire;
        return *this;
    }

    Joc operator+(const Joc& j) // supraincaracarea operatorului +
    {
        Joc result;
        result.balanta_joc = this->balanta_joc + j.balanta_joc;
        return result;
    }

    Joc operator*(const Joc& j) // supraincaracarea operatorului *
    {
        Joc result;
        result.balanta_joc = this->balanta_joc * j.balanta_joc;
        return result;
    }

    operator float() const // supraincarcarea operatorului cast implicit
    {
        return this -> balanta_joc;
    }

    bool operator >(const Joc& j) const // supraincarcarea operatorului conditional >
    {
        return this->balanta_joc > j.balanta_joc;
    }

    bool operator==(const Joc& j) const // supraincarcarea operatorului de egalitate ==
    {
        return strcmp(nume,j.nume) == 0 &&
        strcmp(tip,j.tip) == 0 &&
        balanta_joc == j.balanta_joc &&
        miza_minima == j.miza_minima &&
        miza_maxima == j.miza_maxima &&
        maxwin == j.maxwin &&
        sanse == j.sanse;
    }

    void afisare_joc() // functie care afiseza date despre joc
    {
        cout << "Nume: " << nume <<endl;
        cout << "Tip joc: " << tip <<endl;
        cout << "Miza minima: " << miza_minima <<endl;
        cout << "Miza maxima: " << miza_maxima <<endl;
        cout << "MAXWIN: " << maxwin <<endl;
        //cout << "Sanse: " << sanse * 100 << "%" <<endl;
    }

    void afisare_balanta_joc() // functie care afiseaza balanta jocului(confidential)
    {
        cout<< nume << "---" << balanta_joc;
    }

    void verifica_tip_joc() // verifica tipul jocului
    {
       string t = get_tip();
       bool ok = false;
       string cuvinte_perimse[] = {"Slots" , "Ruleta"};

       for(string cuvant : cuvinte_perimse)
       {
            if(t == cuvant)
                ok = true;
       }

       if (ok == false)
       {
           string joc = get_nume();
           throw invalid_argument("Tipul jocului " + joc + " nu este valid");
       }
    }

    void update() // functie care calculeaza maxwin-ul  in functie de miza si in functie de tipul jocului
    {
        string t = get_tip();
        int m;
        float s = get_sanse();

        if(t == "Slots")
        {
            m = get_miza_maxima() * 30;
            s *= 100;
        }

        if(t == "Ruleta")
        {
            m = get_miza_maxima() * 36;
            s = 36;
        }

        set_sanse(s);
        set_maxwin(m);
    }

};

class Cheltuieli
{
private:

    int ID;
    char *nume;
    float valoare;
    float discount;
    char *mod_plata;
    static int count;
    string caracteristici[5] = {"ID", "Nume", "Valoare", "Discount", "Mod de plata"};

public:

    // setteri si getteri
    void set_id(int id)
    {
        ID = id;
    }

    int get_id() const
    {
        return ID;
    }

    void set_nume(const char* n)
    {
        delete[] this -> nume;
        nume = new char[strlen(n) + 1];
        strcpy(this -> nume, n);
    }

    const char* get_nume() const
    {
        return nume;
    }

    void set_valoare(float v)
    {
        valoare = v;
    }

    float get_valoare() const
    {
        return valoare;
    }

    void set_discount(float d)
    {
        discount = d;
    }

    float get_discount() const
    {
        return discount;
    }

    void set_mod_plata(const char* mp)
    {
        delete[] this -> mod_plata;
        mod_plata = new char[strlen(mp) + 1];
        strcpy(this -> mod_plata, mp);
    }

    const char* get_mod_plata() const
    {
        return mod_plata;
    }

    // constructorii si destructorul
    Cheltuieli(int id, char* n, float v, float d, char* mp)
    {
        ID = id;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        valoare = v;
        discount = d;
        mod_plata = new char[strlen(mp) + 1];
        strcpy(mod_plata,mp);

    }

    Cheltuieli(int id, char* n, float v)
    {
        ID = id;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        valoare = v;
        discount = 0;
        mod_plata = "cash";

    }

    Cheltuieli(char* n, float v)
    {
        ID = 0;
        nume = new char[strlen(n) + 1];
        strcpy(nume,n);
        valoare = v;
        discount = 0;
        mod_plata = "cash";

    }

    Cheltuieli()
    {
        ID = 0;
        nume = new char[1];
        nume[0] = '\0';
        valoare = 0;
        discount = 0;
        mod_plata = new char[1];
        mod_plata[0] = '\0';

    }

    ~Cheltuieli()
    {
        delete[] nume;
        delete[] mod_plata;
    }

    Cheltuieli(const Cheltuieli& c)
    {
        ID = c.ID;
        nume = new char[strlen(c.nume) + 1];
        strcpy(nume,c.nume);
        valoare = c.valoare;
        discount = c.discount;
        mod_plata = new char[strlen(c.mod_plata) + 1];
        strcpy(mod_plata,c.mod_plata);

    }

    Cheltuieli& operator=(const Cheltuieli& c) // supraincarcarea operatorului =
    {
        if (this != &c)
        {
            ID = c.ID;
            delete[] nume;
            nume = new char[strlen(c.nume) + 1];
            strcpy(nume, c.nume);
            valoare = c.valoare;
            discount = c.discount;
            delete[] mod_plata;
            mod_plata = new char[strlen(c.mod_plata) + 1];
            strcpy(mod_plata, c.mod_plata);
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Cheltuieli& c) // supraincarcarea operatorului >>
    {
        char buffer[100];
        cout << "Introduceti ID: ";
        in >> c.ID;
        cout << "Introduceti nume: ";
        in >> buffer;
        c.set_nume(buffer);
        cout << "Introduceti valoare: ";
        in >> c.valoare;
        cout << "Introduceti discount: ";
        in >> c.discount;
        cout << "Introduceti mod plata: ";
        in >> buffer;
        c.set_mod_plata(buffer);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Cheltuieli& c) // supraincarcarea operatorului <<
    {
        out << "ID: " << c.ID << endl;
        out << "Nume: " << c.nume << endl;
        out << "Valoare: " << c.valoare << endl;
        out << "Discount: " << c.discount << endl;
        out << "Mod plata: " << c.mod_plata << endl;
        return out;
    }

    string& operator[](int index) // operatorul de indexare
    {
        return caracteristici[index];
    }

    Cheltuieli& operator++(int penalitati) // supraincarcarea operatorului ++
    {
        penalitati = 500;
        this -> valoare += penalitati;
        return *this;
    }

    Cheltuieli operator+(const Cheltuieli& c) // supraincaracarea operatorului +
    {
        Cheltuieli result;
        result.valoare = this->valoare + c.valoare;
        return result;
    }

    Cheltuieli operator*(const Cheltuieli& c) // supraincaracarea operatorului *
    {
        Cheltuieli result;
        result.valoare = this->valoare * c.valoare;
        return result;
    }

    operator float() const // supraincarcarea operatorului cast implicit
    {
        return this->valoare;
    }

    bool operator<(const Cheltuieli& c) const //supraincarcarea operatorului conditional <
    {
        return this->valoare < c.valoare;
    }

    bool operator==(const Cheltuieli& c) const //supraincarcarea operatorului de egalitate ==
    {
        return this->ID == c.ID &&
               strcmp(this -> nume, c.nume) == 0 &&
               this->valoare == c.valoare &&
               this->discount == c.discount &&
               strcmp(this -> mod_plata, c.mod_plata) == 0;
    }

    void afisare_cheltuieli()
    {
        cout << "ID: " << ID << endl;
        cout << "Nume: " << nume << endl;
        cout << "Valoare: " << valoare << endl;
        cout << "Discount: " << discount << endl;
        cout << "Modalitate de plata: " << mod_plata << endl;
    }

    void aplicare_discount()
    {
        float v = get_valoare();
        float d = get_discount();
        d = 100 - d;
        v = v * d;
        v = v / 100;
        set_valoare(v);
    }

    void aplicare_commision()
    {
        float v = get_valoare();
        string mp = get_mod_plata();
        if(mp == "Card")
            v = v + (3*v/100);

        set_valoare(v);
    }
};

int random_number(int x, int y)
{
  return rand() % (y - x + 1) + x;
}

void joaca(Client& client,Joc& joc) // functie care ruleaza jocurile
{   
    joc.update();
    float miza;
    bool fonduri = true;
    double is = client.get_is();
    cout << "Pentru cash out,va rugam introduceti miza '0' " << endl;
    while (fonduri)
    {
        cout << "Introduceti miza: ";
        cin >> miza;

        if(miza > client.get_balanta())
            miza = client.get_balanta();

        if(miza == 0) // optiunea de cash out
        {
            cout << "CASH OUT!,Call Attendant! --- " << client.get_balanta() << " RON" << endl;
            break;
        }

        if (miza < joc.get_miza_minima())
        {
            cout << "Miza este prea mica !" << endl;
            cout << "Miza dvs a fost actualizata - Miza curenta: " << joc.get_miza_minima() << endl;
            miza = joc.get_miza_minima();
        }

        if (miza > joc.get_miza_maxima())
        {
            cout << "Miza este prea mare !" << endl;
            cout << "Miza dvs a fost actualizata - Miza curenta: " << joc.get_miza_maxima() << endl;
            miza = joc.get_miza_maxima();
        }

        string const tip = joc.get_tip();

        if(tip == "Slots")
        {
            float bjoc = joc.get_balanta_joc();
            float bclient = client.get_balanta();
            int nr = random_number(1,100);
            if (nr <= joc.get_sanse())
            {
                int multiplicator = random_number(1,30);
                cout << "WIN!! --- x" << multiplicator << " --- Balanta curenta: " << bclient + miza*multiplicator << endl;
                cout << "Gamble ?" << endl;
                cout << "Yes - 1" << endl;
                cout << "No - any other number" << endl;
                int gamble;
                cin>>gamble;
                if(gamble == 1) // optiunea de gamble
                {
                    while(gamble == 1 || gamble == 2)
                    {
                        int gam = random_number(1,2);
                        cout << "BLACK - 1" << endl;
                        cout << "RED - 2" << endl;
                        cout << "TAKE WIN - any other number" <<endl;
                        cin >> gamble;
                        if (gamble != 1 && gamble != 2)
                        {
                            bjoc -= miza*multiplicator;
                            bclient += miza*multiplicator;
                        }
                        else
                        {
                            if (gamble == gam)
                            {
                                multiplicator *= 2;
                                cout << "WIN!! --- Balanta curenta: " << bclient + miza*multiplicator << endl;
                            }
                            else
                            {
                                cout<<"LOSE --- ";
                                bjoc += miza;
                                bclient -= miza;
                                cout << "Balanta curenta: " << bclient << endl;
                                gamble = 3;
                            }
                        }

                    }
                }
                else
                {
                    bjoc -= miza*multiplicator;
                    bclient += miza*multiplicator;
                }
            }
            else
            {
                cout<<"LOSE --- ";
                bjoc += miza;
                bclient -= miza;
                cout << "Balanta curenta: " << bclient << endl;
            }

            cout<<endl;
            joc.set_balanta_joc(bjoc);
            client.set_balanta(bclient);


        }

        if(tip == "Ruleta")
        {
            cout << "Alege numarul: ";
            int n;
            cin >> n;
            while (n < 0 || n > 36)
            {
                cout << "Ne pare rau,numarul introdus nu se afla pe ruleta !";
                cin >> n;
            }
            float bjoc = joc.get_balanta_joc();
            float bclient = client.get_balanta();
            int nr = random_number(0,36);
            cout << nr << "-/-";
            if (nr == n)
            {
                cout << "WIN!!" << " --- ";
                bjoc -= miza*36;
                bclient += miza*36;
            }
            else
            {
                cout<<"LOSE --- ";
                bjoc += miza;
                bclient -= miza;
            }

            cout << "Balanta curenta: " << bclient << endl;
            cout<<endl;
            joc.set_balanta_joc(bjoc);
            client.set_balanta(bclient);

        }

        is += miza;
        if(client.get_balanta() < joc.get_miza_minima())
        {
            fonduri = false;
            cout << "Fonduri insuficiente!"<<endl;
        }
    }

    client.set_is(is);
}

int main()
{

    // initializare lista clienti
    vector <Client> lista_clienti;
    Client David(11,"David", 100, 1, new int(19), 1500);
    Client Robert(13, "Robert", 100, 0, new int(20), 1200);
    Client Theodor(20, "Theodor", 100, 0,new int(15), 1000);
    lista_clienti.push_back(David);
    lista_clienti.push_back(Robert);
    lista_clienti.push_back(Theodor);


    // initializare lista angajati
    vector <Angajat> lista_angajati;
    Angajat Madalina("Madalina" , 38, "Bucatarie" , 7000 , 11);
    Angajat Leana("Leana" , 40, "Bucatarie" , 6500 , 5);
    Angajat Laurentiu("Laurentiu" , 35, "Securitate" , 6200 , 3);
    Angajat Ioana("Ioana" , 25, "Dealer" , 6400 , 2);
    Angajat Miruna("Miruna" , 22, "Dealer" , 6400 , 1);
    Angajat Monica("Monica" , 27, "Receptie" , 8000 , 3);
    Angajat Andreea("Andreea" , 32, "Contabilitate" , 11000 , 5);
    lista_angajati.push_back(Madalina);
    lista_angajati.push_back(Leana);
    lista_angajati.push_back(Laurentiu);
    lista_angajati.push_back(Ioana);
    lista_angajati.push_back(Miruna);
    lista_angajati.push_back(Monica);
    lista_angajati.push_back(Andreea);


    // initializare lista jocuri
    vector <Joc> lista_jocuri;
    Joc Shining("Shining" , "Slots" , 0 , 0.2 , 200 , 10000 ,0.1);
    Joc Burning("Burning", "Slots", 0, 0.2, 200, 10000, 0.15);
    Joc Dice("Dice" , "Slots", 0, 0.2, 100, 10000, 0.05);
    Joc Ruleta("Ruleta", "Ruleta" ,0 , 0.5 , 500, 10000, 0.1);
    lista_jocuri.push_back(Shining);
    lista_jocuri.push_back(Burning);
    lista_jocuri.push_back(Dice);
    lista_jocuri.push_back(Ruleta);


    //initializare lista cheltuieli
    vector <Cheltuieli> lista_cheltuieli;
    Cheltuieli Utilitati(2,"Utilitati", 25000, 7, "Cash");
    Cheltuieli Salarii(4,"Salarii", 10000, 0, "Cash");
    Cheltuieli Marketing(10, "Marketing", 20000, 15, "Card");
    Cheltuieli Mentenanta(12,"Mentenanta", 30000, 23, "Cash");
    lista_cheltuieli.push_back(Utilitati);
    lista_cheltuieli.push_back(Salarii);
    lista_cheltuieli.push_back(Marketing);
    lista_cheltuieli.push_back(Mentenanta);

    int x = -1;

    while(x != 0) // meniul interactiv
    {
        cout << "Bine ati venit in meniul principal !" << endl;
        cout << "Tastati cifra corespunzatoare pentru a parcurge o anumita clasa: " << endl;
        cout << endl;
        cout << "Clasa Client - 1" << endl;
        cout << "Clasa Angajat - 2" << endl;
        cout << "Clasa Joc - 3" << endl;
        cout << "Clasa Cheltuieli - 4" << endl;
        cout << "Inchidere program - 0" << endl;

        cout << "Introduceti tasta: " ;
        cin >> x;
        cout << endl;

        while(x < 0 || x > 4)
        {
            cout << "Tasta introdusa este incorecta !" << endl;
            cout << "Introduceti tasta: " ;
            cin >> x;
        }

        if(x == 1) // clasa Client
        {
            int x1 = 1;
            while(x1 != 0)
            {
                cout << "Clasa Client" << endl;
                cout<< "////////////// " << endl;
                cout << endl;

                cout << "Afisare lista clienti - 1" << endl;
                cout << "Introducere client nou - 2" << endl;
                cout << "Stergere client - 3" << endl;
                cout << "Diverse functionalitati ale clasei Client - 4" << endl;
                cout << endl;
                cout << "Introduceti tasta: " ;
                int cli;
                cin >> cli;


                if(cli == 0)
                    x1 = 0;

                while(cli < 0 || cli > 4)
                {
                    cout << "Tasta introdusa este incorecta !" << endl;
                    cout << "Introduceti tasta: " ;
                    cin >> cli;
                }

                if (cli == 1)
                {
                   for(int i = 0; i < lista_clienti.size(); i++)
                   {
                       lista_clienti[i].afisare_client();
                       cout<<endl;
                       cout<<endl;
                   }
                }

                if(cli == 2)
                {
                    int ok = 0;
                    while(ok != 1)
                    {
                        Client nou;
                        cin >> nou;

                        nou.afisare_client();
                        cout << endl;
                        cout << "Datele au fost introduse corect ?" << endl;
                        cout << "Da - 1" << endl;
                        cout << "Nu - orice alta cifra" << endl;
                        cout << "Introduceti tasta: " ;
                        cin >> ok;
                        cout<<endl;

                        if(ok == 1)
                        {
                            lista_clienti.push_back(nou);
                            cout << "Clientul dvs a fost adaugat cu succes !" << endl;
                        }

                    }
                }

                if(cli == 3)
                {

                    cout << "Introduceti ID-ul clientilor pe care doriti sa ii stergeti din lista: ";
                    int idd;
                    bool ok = false;
                    cin >> idd;
                    cout << endl;
                    for (int i = lista_clienti.size() - 1; i >= 0; i--)
                    {
                        int id = lista_clienti[i].get_id();
                        if(id == idd)
                        {
                            lista_clienti.erase(lista_clienti.begin() + i);
                            cout << "Clientii dvs au fost stersi cu succes !" << endl;
                            ok = true;
                        }
                    }

                    if(ok == false)
                        cout << "Nu s-a gasit nicun client cu ID-ul introdus de dvs !" << endl;
                }

                if(cli == 4)
                {
                    int y;
                    cout << endl;
                    cout << "Functia VIP (acorda toti clielntilor ce au istoricul tranzactiilor peste suma de 5000 calitatea de VIP) - 1" << endl;
                    cout << "Functia MAJOR (valideaza varsta clientilor si reduce balanta,istoricul,si id-ul de client la 0 pentru cei minori - 2" << endl;
                    cout << "Introduceti tasta: ";
                    cin >> y;
                    cout << endl;

                    if(y != 1 && y != 2)
                        cout << "Tasta incorecta" << endl;

                    if(y == 1)
                    {
                        for(int i = 0; i < lista_clienti.size(); i++)
                            lista_clienti[i].vip();

                        cout << "Lista de clienti a fost actualizata !" << endl;
                    }

                    if(y == 2)
                    {
                        for(int i = 0; i < lista_clienti.size(); i++)
                            lista_clienti[i].este_major();

                        cout << "Lista de clienti a fost actualizata !" << endl;
                    }
                }

                cout << "Pentru revenire la meniul principal introduceti tasta '0' / orice alta cifra pentru a ramane in clasa curenta:" ;
                cin >> x1;
                cout << endl;
            }
        }

        if(x == 2) // clasa Angajat
        {
            int x2 = 1;
            while(x2 != 0)
            {
                cout << "Clasa Angajat" << endl;
                cout<< "////////////// " << endl;
                cout << endl;

                cout << "Afisare lista angajati - 1" << endl;
                cout << "Introducere angajat nou - 2" << endl;
                cout << "Stergere angajat - 3" << endl;
                cout << "Diverse functionalitati ale clasei angajat - 4" << endl;
                cout << endl;
                cout << "Introduceti tasta: " ;
                int ang;
                cin >> ang;

                if(ang == 0)
                    x2 = 0;

                while(ang < 0 || ang > 4)
                {
                    cout << "Tasta introdusa este incorecta !" << endl;
                    cout << "Introduceti tasta: " ;
                    cin >> ang;
                }

                if (ang == 1)
                {
                    for(int i = 0; i < lista_angajati.size(); i++)
                    {
                        lista_angajati[i].afisare_angajat();
                        cout<<endl;
                        cout<<endl;
                    }
                }

                if(ang == 2)
                {
                    int ok = 0;
                    while(ok != 1)
                    {
                        Angajat nou;
                        cin >> nou;

                        cout << endl;
                        nou.afisare_angajat();
                        cout << endl;
                        cout << "Datele au fost introduse corect ?" << endl;
                        cout << "Da - 1" << endl;
                        cout << "Nu - orice alta cifra" << endl;
                        cout << "Introduceti tasta: " ;
                        cin >> ok;
                        cout<<endl;

                        if(ok == 1)
                        {
                            lista_angajati.push_back(nou);
                            cout << "Angajatul dvs a fost adaugat cu succes !" << endl;
                        }

                    }
                }

                if(ang == 3)
                {

                    cout << "Introduceti numele angajatilor pe care doriti sa ii stergeti din lista: ";
                    string n;
                    bool ok = false;
                    cin >> n;
                    cout << endl;
                    for (int i = lista_angajati.size() - 1; i >= 0; i--)
                    {
                        string nn = lista_angajati[i].get_nume();
                        if(n == nn)
                        {
                            lista_angajati.erase(lista_angajati.begin() + i);
                            ok = true;
                        }
                    }

                    if(ok == false)
                        cout << "Nu s-a gasit nicun angajat cu numele introdus de dvs !" << endl;
                    else
                        cout << "Angajatii dvs au fost stersi cu succes !" << endl;
                }

                if(ang == 4)
                {
                    int y;
                    cout << endl;
                    cout << "Functia AFISARE SALARIU (afiseaza doar numele si salariul angajatilor) - 1" << endl;
                    cout << "Functia SPOR VECHME(aplica angajatilor mariri de salariu in functie de vechimea acestora,criteriile se pot gasi in codul sursa) - 2" << endl;
                    cout << "Functia COVERTIRE SALARIU (afiseaza un raportul de coversie dintre salariul BRUT si cel NET al angajatilor) - 3" << endl;
                    cout << "Introduceti tasta: ";
                    cin >> y;
                    cout << endl;

                    if(y != 1 && y != 2 && y != 3)
                        cout << "Tasta incorecta" << endl;

                    if(y == 1)
                    {
                        string n;
                        cout << "Introduceti numele salariatului: ";
                        cin >> n;
                        cout << endl;
                        bool ok = false;
                        for(int i = 0; i < lista_angajati.size(); i++)
                        {
                            string nn = lista_angajati[i].get_nume();
                            if(n == nn)
                            {
                                ok = true;
                                lista_angajati[i].afisare_salariu();
                                cout << endl;
                            }

                        }

                        if (ok == false)
                            cout << "Nu a fost gasit in lista salariatul cerut !";
                    }

                    if(y == 2)
                    {
                        for(int i = 0; i < lista_angajati.size(); i++)
                            lista_angajati[i].spor_vechime();

                        cout << "Salariile angajatilor au fost actualizate !" << endl;
                    }

                    if(y == 3)
                    {
                        string n;
                        cout << "Introduceti numele salariatului: ";
                        cin >> n;
                        cout << endl;
                        bool ok = false;
                        for(int i = 0; i < lista_angajati.size(); i++)
                        {
                            string nn = lista_angajati[i].get_nume();
                            if(n == nn)
                            {
                                ok = true;
                                lista_angajati[i].convertire_salariu();
                                cout << endl;
                            }

                        }

                        if (ok == false)
                            cout << "Nu a fost gasit in lista salariatul cerut !";
                    }
                }

                cout << "Pentru revenire la meniul principal introduceti tasta '0' / orice alta cifra pentru a ramane in clasa curenta:" ;
                cin >> x2;
                cout << endl;
            }
        }

        if(x == 3) // clasa Joc
        {
            int x3 = 1;
            while(x3 != 0)
            {
                cout << "Clasa Joc" << endl;
                cout<< "////////////// " << endl;
                cout << endl;

                cout << "Afisare lista jocuri- 1" << endl;
                cout << "Introducere joc nou - 2" << endl;
                cout << "Stergere joc - 3" << endl;
                cout << "Diverse functionalitati ale clasei joc - 4" << endl;
                cout << endl;
                cout << "Introduceti tasta: " ;
                int j;
                cin >> j;

                if(j == 0)
                    x3 = 0;

                while(j < 0 || j > 4)
                {
                    cout << "Tasta introdusa este incorecta !" << endl;
                    cout << "Introduceti tasta: " ;
                    cin >> j;
                }

                if (j == 1)
                {
                    for(int i = 0; i < lista_jocuri.size(); i++)
                    {
                        lista_jocuri[i].afisare_joc();
                        cout<<endl;
                        cout<<endl;
                    }
                }

                if(j == 2)
                {
                    int ok = 0;
                    while(ok != 1)
                    {
                        Joc nou;
                        cin >> nou;

                        cout << endl;
                        nou.afisare_joc();
                        cout << endl;
                        cout << "Datele au fost introduse corect ?" << endl;
                        cout << "Da - 1" << endl;
                        cout << "Nu - orice alta cifra" << endl;
                        cout << "Introduceti tasta: " ;
                        cin >> ok;
                        cout<<endl;

                        if(ok == 1)
                        {
                            lista_jocuri.push_back(nou);
                            cout << "Jocul dvs a fost adaugat cu succes !" << endl;
                        }

                    }
                }

                if(j == 3)
                {

                    cout << "Introduceti numele jocului pe care doriti sa ii stergeti din lista: ";
                    string n;
                    bool ok = false;
                    cin >> n;
                    cout << endl;
                    for (int i = lista_jocuri.size() - 1; i >= 0; i--)
                    {
                        string nn = lista_jocuri[i].get_nume();
                        if(n == nn)
                        {
                            lista_jocuri.erase(lista_jocuri.begin() + i);
                            cout << "Jocurile dvs au fost stersi cu succes !" << endl;
                            ok = true;
                        }
                    }

                    if(ok == false)
                        cout << "Nu s-a gasit nicun joc cu numele introdus de dvs !" << endl;
                }

                if(j == 4)
                {
                    int y;
                    cout << endl;
                    cout << "Functia AFISARE BALANTA JOC - 1" << endl;
                    cout << "Functia PLAY - 2"  << endl;
                    cout << "Introduceti tasta: ";
                    cin >> y;
                    cout << endl;

                    if(y != 1 && y != 2)
                        cout << "Tasta incorecta" << endl;

                    if(y == 1)
                    {
                        string n;
                        cout << "Introduceti numele jocului: ";
                        cin >> n;
                        cout << endl;
                        bool ok = false;
                        for(int i = 0; i < lista_jocuri.size(); i++)
                        {
                            string nn = lista_jocuri[i].get_nume();
                            if(n == nn)
                            {
                                ok = true;
                                lista_jocuri[i].afisare_balanta_joc();
                                cout << endl;
                            }

                        }

                        if(ok == false)
                            cout << "Jocul introdus nu a fost gasit !";


                    }

                    if (y == 2)
                    {
                        int xclient = -1, xjoc = -1;

                        int idclient;
                        cout << "Introduceti id-ul cleintului: "; // cautam clientul
                        cin >> idclient;
                        cout << endl;
                        bool okclient = false;

                        string njoc;
                        cout << "Introduceti numele jocului: "; // cautam jocul
                        cin >> njoc;
                        cout << endl;
                        bool okjoc = false;

                        for(int i = 0; i < lista_clienti.size(); i++)
                        {
                            int nn = lista_clienti[i].get_id();
                            if(idclient == nn)
                            {
                                okclient = true;
                                xclient = i;
                                cout << endl;
                            }

                        }

                        for(int i = 0; i < lista_jocuri.size(); i++)
                        {
                            string nn = lista_jocuri[i].get_nume();
                            if(njoc == nn)
                            {
                                okjoc = true;
                                xjoc = i;
                                cout << endl;
                            }

                        }

                        if(okclient == false)
                            cout << "Clientul introdus nu a fost gasit !" << endl;

                        if(okjoc == false)
                            cout << "Jocul introdus nu a fost gasit !" << endl;

                        if(okclient == true && okjoc == true)
                        {
                            cout << endl;
                            joaca(lista_clienti[xclient],lista_jocuri[xjoc]);
                        }

                    }


                    cout << "Pentru revenire la meniul principal introduceti tasta '0' / orice alta cifra pentru a ramane in clasa curenta:" ;
                    cin >> x3;
                    cout << endl;
                }
            }
        }

        if(x == 4) // clasa Cheltuieli
        {

            int x4 = 1;
            while(x4 != 0)
            {
                cout << "Clasa Cheltuieli" << endl;
                cout<< "////////////// " << endl;
                cout << endl;

                cout << "Afisare lista cheltuieli - 1" << endl;
                cout << "Introducere cheltuiala noua - 2" << endl;
                cout << "Stergere cheltuiala - 3" << endl;
                cout << "Diverse functionalitati ale clasei Cheltuieli - 4" << endl;
                cout << endl;
                cout << "Introduceti tasta: " ;
                int ch;
                cin >> ch;

                if(ch == 0)
                    x4 == 0;

                while(ch < 0 || ch > 4)
                {
                    cout << "Tasta introdusa este incorecta !" << endl;
                    cout << "Introduceti tasta: " ;
                    cin >> ch;
                }

                if (ch == 1)
                {
                    for(int i = 0; i < lista_cheltuieli.size(); i++)
                    {
                        lista_cheltuieli[i].afisare_cheltuieli();
                        cout<<endl;
                        cout<<endl;
                    }
                }

                if(ch == 2)
                {
                    int ok = 0;
                    while(ok != 1)
                    {
                        Cheltuieli nou;
                        cin >> nou;

                        nou.afisare_cheltuieli();
                        cout << endl;
                        cout << "Datele au fost introduse corect ?" << endl;
                        cout << "Da - 1" << endl;
                        cout << "Nu - orice alta cifra" << endl;
                        cout << "Introduceti tasta: " ;
                        cin >> ok;
                        cout<<endl;

                        if(ok == 1)
                        {
                            lista_cheltuieli.push_back(nou);
                            cout << "Cheltuiala dvs a fost adaugat cu succes !" << endl;
                        }

                    }
                }

                if(ch == 3)
                {

                    cout << "Introduceti ID-ul cheltuielilor pe care doriti sa le stergeti din lista: ";
                    int idd;
                    bool ok = false;
                    cin >> idd;
                    cout << endl;
                    for (int i = lista_cheltuieli.size() - 1; i >= 0; i--)
                    {
                        int id = lista_cheltuieli[i].get_id();
                        if(id == idd)
                        {
                            lista_cheltuieli.erase(lista_cheltuieli.begin() + i);
                            cout << "Cheltuielile dvs au fost sterse cu succes !" << endl;
                            ok = true;
                        }
                    }


                    if(ok == false)
                        cout << "Nu s-a gasit nicio cheltuiala cu ID-ul introdus de dvs !" << endl;
                }

                if(ch == 4)
                {
                    int y;
                    cout << endl;
                    cout << "Functia APLICARE DISCOUNT - 1" << endl;
                    cout << "Functia APLICARE COMMISION - 2"  << endl;
                    cout << "Functia TOTAL CHELTUIELI - 3"  << endl;
                    cout << "Introduceti tasta: ";
                    cin >> y;
                    cout << endl;

                    if(y != 1 && y != 2 && y != 3)
                        cout << "Tasta incorecta" << endl;

                    if(y == 1)
                    {
                        for(int i = 0; i < lista_cheltuieli.size(); i++)
                            lista_cheltuieli[i].aplicare_discount();

                        cout << "Discount-urile au fost aplicate cu succes !" << endl;
                    }

                    if(y == 2)
                    {
                        for(int i = 0; i < lista_cheltuieli.size(); i++)
                            lista_cheltuieli[i].aplicare_commision();

                        cout << "Commisioanele au fost aplicate cu succes !" << endl;
                    }

                    if(y == 3)
                    {
                        float total = 0;
                        for(int i = 0; i < lista_cheltuieli.size(); i++)
                        {
                            total = total + lista_cheltuieli[i].get_valoare();
                        }

                        cout << "Totalul cheltuielilor este de " << total << " lei" << endl;
                    }
                }

                cout << "Pentru revenire la meniul principal introduceti tasta '0' / orice alta cifra pentru a ramane in clasa curenta:" ;
                cin >> x4;
                cout << endl;
            }

        }



    }

    cout << "Program finalizat !";
    return 0;
}
