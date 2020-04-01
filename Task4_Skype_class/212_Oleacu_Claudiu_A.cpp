#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cctype>
#include <cstdlib>
using namespace std;
void print_menu();
int get_number();

class Persoana
{
protected:
    int id;
    string nume;
    static int nr_obj;

public:
    Persoana(int, string);
    Persoana(const Persoana &);
    virtual ~Persoana();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream &operator>>(istream &, Persoana &);
    friend ostream &operator<<(ostream &, Persoana &);
    Persoana &operator=(Persoana &);
    static void numarObiecte()
    {
        cout << nr_obj << '\n';
    }
    friend class Agenda;
    friend class vector_pers;
};

int Persoana ::nr_obj;
Persoana::Persoana(int id_Persoana = 0, string nume_Persoana = "")
{
    nr_obj++;
    try
    {
        for (unsigned int i = 0; i < nume_Persoana.length(); i++)
            if (nume_Persoana[i] >= '0' && nume_Persoana[i] <= '9')
                throw 1;
    }
    catch (int i)
    {
        cout << "Eroare constructor. Numele poate contine doar litere!";
        exit(EXIT_FAILURE);
    }

    id = id_Persoana;
    nume = nume_Persoana;
}

Persoana ::Persoana(const Persoana &pers)
{
    this->id = pers.id;
    this->nume = pers.nume;
}

Persoana::~Persoana()
{
}

void Persoana ::citire(istream &in)
{
    cout << "Introduceti ID : ";
    in >> id;
    cout << "Introduceti numele complet : ";
    in.get();
    string name;
    getline(in, name);
    try
    {
        for (unsigned int i = 0; i < name.length(); i++)
            if (name[i] >= '0' && name[i] <= '9')
                throw 1;
    }
    catch (int i)
    {
        cout << "Eroare la citire. Numele poate contine doar litere!";
        exit(EXIT_FAILURE);
    }
    nume = name;
}

istream &operator>>(istream &in, Persoana &p)
{
    p.citire(in);
    return in;
}

void Persoana ::afisare(ostream &out)
{
    out << nume << " are ID-ul : " << id << '\n';
}

ostream &operator<<(ostream &out, Persoana &p)
{
    p.afisare(out);
    return out;
}

Persoana &Persoana ::operator=(Persoana &p)
{
    id = p.id;
    nume = p.nume;
}

///---------------------------------------------------
class Abonat : public Persoana
{
protected:
    string nr_tel;

public:
    Abonat(int, string, string);
    Abonat(const Abonat &);
    ~Abonat();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream &operator>>(istream &, Abonat &);
    friend ostream &operator<<(ostream &, Abonat &);
    Abonat &operator=(Abonat &);
};

Abonat ::Abonat(int id_Persoana = 0, string nume_Persoana = "", string nr_telefon = "") : Persoana(id_Persoana, nume_Persoana)
{
    try
    {
        for (unsigned int i = 0; i < nr_telefon.length(); i++)
            if (nr_telefon[i] < '0' || nr_telefon[i] > '9')
                throw 1;
    }
    catch (int i)
    {
        cout << "Eroare constructor. Numarul de telefon poate contine doar cifre!";
        exit(EXIT_FAILURE);
    }
    nr_tel = nr_telefon;
}

Abonat ::Abonat(const Abonat &a) : Persoana(a)
{
    this->nr_tel = a.nr_tel;
}

Abonat ::~Abonat()
{
}

void Abonat ::citire(istream &in)
{
    Persoana ::citire(in);
    cout << "Numarul de telefon al abonatului : ";
    string nr_telefon;
    in >> nr_telefon;
    try
    {
        for (unsigned int j = 0; j < nr_telefon.length(); j++)
            if (nr_telefon[j] < '0' || nr_telefon[j] > '9')
                throw 1;
    }
    catch (int j)
    {
        cout << "Eroare la citire. Numarul de telefon poate contine doar cifre!";
        exit(EXIT_FAILURE);
    }
    nr_tel = nr_telefon;
}

istream &operator>>(istream &in, Abonat &a)
{
    a.citire(in);
    return in;
}

void Abonat ::afisare(ostream &out)
{
    Persoana ::afisare(out);
    out << " - Numarul de telefon este : " << nr_tel << '\n';
}

ostream &operator<<(ostream &out, Abonat &a)
{
    a.afisare(out);
    return out;
}

Abonat &Abonat ::operator=(Abonat &a)
{
    Persoana ::operator=(a);
    nr_tel = a.nr_tel;
}

///---------------------------------------------------
class Abonat_Skype : public Abonat
{
protected:
    string id_Skype;

public:
    Abonat_Skype(int, string, string, string);
    Abonat_Skype(const Abonat_Skype &);
    ~Abonat_Skype();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream &operator>>(istream &, Abonat_Skype &);
    friend ostream &operator<<(ostream &, Abonat_Skype &);
    Abonat_Skype &operator=(Abonat_Skype &);
};

Abonat_Skype ::Abonat_Skype(int id_Persoana = 0, string nume_Persoana = "", string nr_telefon = "", string id_s = "") : Abonat(id_Persoana, nume_Persoana, nr_telefon)
{
    id_Skype = id_s;
}

Abonat_Skype ::Abonat_Skype(const Abonat_Skype &a_s) : Abonat(a_s)
{
    this->id_Skype = a_s.id_Skype;
}

Abonat_Skype ::~Abonat_Skype()
{
}

void Abonat_Skype ::citire(istream &in)
{
    Abonat ::citire(in);
    cout << "ID-ul Skype este : ";
    in >> id_Skype;
}

istream &operator>>(istream &in, Abonat_Skype &a_s)
{
    a_s.citire(in);
    return in;
}

void Abonat_Skype ::afisare(ostream &out)
{
    Abonat ::afisare(out);
    out << " - ID-ul Skype al abonatului este : " << id_Skype << '\n';
}

ostream &operator<<(ostream &out, Abonat_Skype &a_s)
{
    a_s.afisare(out);
    return out;
}

Abonat_Skype &Abonat_Skype ::operator=(Abonat_Skype &A_S)
{
    Abonat ::operator=(A_S);
    id_Skype = A_S.id_Skype;
}

///---------------------------------------------------
class Abonat_Skype_Romania : public Abonat_Skype
{
protected:
    string adresa_mail;

public:
    Abonat_Skype_Romania(int, string, string, string, string);
    Abonat_Skype_Romania(const Abonat_Skype_Romania &);
    ~Abonat_Skype_Romania();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream &operator>>(istream &, Abonat_Skype_Romania &);
    friend ostream &operator<<(ostream &, Abonat_Skype_Romania &);
    Abonat_Skype_Romania &operator=(Abonat_Skype_Romania &);
};

Abonat_Skype_Romania ::Abonat_Skype_Romania(int id_Persoana = 0, string nume_Persoana = "", string nr_telefon = "", string id_s = "", string mail = "")
    : Abonat_Skype(id_Persoana, nume_Persoana, nr_telefon, id_s)
{
    adresa_mail = mail;
}

Abonat_Skype_Romania ::Abonat_Skype_Romania(const Abonat_Skype_Romania &A_S_R) : Abonat_Skype(A_S_R)
{
    this->adresa_mail = A_S_R.adresa_mail;
}

Abonat_Skype_Romania ::~Abonat_Skype_Romania()
{
}

void Abonat_Skype_Romania ::citire(istream &in)
{
    Abonat_Skype ::citire(in);
    cout << "Adresa de e-mail este : ";
    in >> adresa_mail;
}

istream &operator>>(istream &in, Abonat_Skype_Romania &A_S_R)
{
    A_S_R.citire(in);
    return in;
}

void Abonat_Skype_Romania ::afisare(ostream &out)
{
    Abonat_Skype ::afisare(out);
    out << " - Adresa de e-mail a abonatului este : " << adresa_mail << '\n';
}

ostream &operator<<(ostream &out, Abonat_Skype_Romania &A_S_R)
{
    A_S_R.afisare(out);
    return (out);
}

Abonat_Skype_Romania &Abonat_Skype_Romania ::operator=(Abonat_Skype_Romania &A_S_R)
{
    Abonat_Skype ::operator=(A_S_R);
    adresa_mail = A_S_R.adresa_mail;
}

///---------------------------------------------------
class Abonat_Skype_Extern : public Abonat_Skype
{
protected:
    string tara;

public:
    Abonat_Skype_Extern(int, string, string, string, string);
    Abonat_Skype_Extern(const Abonat_Skype_Extern &);
    ~Abonat_Skype_Extern();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream &operator>>(istream &, Abonat_Skype_Extern &);
    friend ostream &operator<<(ostream &, Abonat_Skype_Extern &);
    Abonat_Skype_Extern &operator=(Abonat_Skype_Extern &);
};

Abonat_Skype_Extern ::Abonat_Skype_Extern(int id_Persoana = 0, string nume_Persoana = "", string nr_telefon = "", string id_s = "", string T = "")
    : Abonat_Skype(id_Persoana, nume_Persoana, nr_telefon, id_s)
{
    tara = T;
}

Abonat_Skype_Extern ::Abonat_Skype_Extern(const Abonat_Skype_Extern &A_S_E) : Abonat_Skype(A_S_E)
{
    this->tara = A_S_E.tara;
}

Abonat_Skype_Extern ::~Abonat_Skype_Extern()
{
}

void Abonat_Skype_Extern ::citire(istream &in)
{
    Abonat_Skype ::citire(in);
    cout << "Tara : ";
    in.get();
    getline(in, tara);
}

istream &operator>>(istream &in, Abonat_Skype_Extern &A_S_E)
{
    A_S_E.citire(in);
    return in;
}

void Abonat_Skype_Extern ::afisare(ostream &out)
{
    Abonat_Skype ::afisare(out);
    out << " - Tara : " << tara << '\n';
}

ostream &operator<<(ostream &out, Abonat_Skype_Extern &A_S_E)
{
    A_S_E.afisare(out);
    return out;
}

Abonat_Skype_Extern &Abonat_Skype_Extern ::operator=(Abonat_Skype_Extern &A_S_E)
{
    Abonat_Skype ::operator=(A_S_E);
    tara = A_S_E.tara;
}

///---------------------------------------------------
void Type(Persoana *&pers, int &i, istream &in)
{
    int val;
    cout << "\nNumarul curent in agenda : " << i << '\n';
    cout << "Aveti de optat pentru una dintre variantele urmatoare :\n";
    cout << "1 - Abonat\n2 - Abonat Skype\n3 - Abonat Skype Romania\n4 - Abonat Skype Extern\nIntroduceti numarul corespunzator : ";
    in >> val;
    try
    {
        if (val == 1)
        {
            cout << "Se introduce un Abonat\n";
            pers = new Abonat;
            in >> *pers;
            i++;
        }
        else if (val == 2)
        {
            cout << "Se intorduce un Abonat Skype\n";
            pers = new Abonat_Skype;
            in >> *pers;
            i++;
        }
        else if (val == 3)
        {
            cout << "Se inroduce un Abonat Skype Romania\n";
            pers = new Abonat_Skype_Romania;
            in >> *pers;
            i++;
        }
        else if (val == 4)
        {
            cout << "se introduce un Abonat Skype Extern\n";
            pers = new Abonat_Skype_Extern;
            in >> *pers;
            i++;
        }
        else
            throw 6;
    }
    catch (bad_alloc mem)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch (int j)
    {
        cout << "Alegerea aleasa nu este disponibila. Incercati una din cele patru variante.\n";
    }
}

///---------------------------------------------------
class Agenda
{
private:
    Persoana **p;
    int nr_ag;

public:
    Agenda();
    ~Agenda();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream &operator>>(istream &, Agenda &);
    friend ostream &operator<<(ostream &, Agenda &);
    Persoana &operator[](const string &numele);
};

Agenda ::Agenda()
{
    this->nr_ag = 0;
    this->p = new Persoana *[nr_ag];
}

Agenda ::~Agenda()
{
    nr_ag = 0;
    delete[] p;
}

void Agenda ::citire(istream &in)
{
    cout << "Numarul de persoane din agenda este ";
    in >> nr_ag;
    p = new Persoana *[nr_ag];
    try
    {
        if (nr_ag > 0)
        {
            for (int i = 0; i < nr_ag;)
                Type(p[i], i, in);
        }
        else
            throw 1;
    }
    catch (int k)
    {
        cout << "Agenda nu poate avea un numar negativ de persoane!\n";
    }
}

istream &operator>>(istream &in, Agenda &A)
{
    A.citire(in);
    return in;
}

void Agenda ::afisare(ostream &out)
{
    out << "\nAgenda contine urmatoarele date :\n";
    out << "--------------------------\n";
    for (int i = 0; i < nr_ag; i++)
    {
        out << "Pe pozitia " << i + 1 << " se afla :\n";
        out << *p[i];
        out << "--------------------------\n";
    }
}

ostream &operator<<(ostream &out, Agenda &A)
{
    A.afisare(out);
    return out;
}

Persoana &Agenda ::operator[](const string &numele)
{
    for (int j = 0; j < nr_ag; j++)
    {
        if ((*p[j]).nume == numele)
            return *p[j];
    }
    cout << " Numele nu se gaseste in lista\n";
    exit(0);
}
int main()
{
    Abonat_Skype_Romania *asr = (Abonat_Skype_Romania *)new Abonat;
    string s;
    char choice;
    Agenda A;
    do
    {
        print_menu();
        cout << " Introduceti alegerea : ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'S': ///initializare agendei
            cout << "\n Ati ales optiunea de a scrie in agenda!\n";
            cin >> A;
            break;

        case 'A': ///afisarea agendei
            cout << "\n Ati ales optiunea de a afisa continutul agendei!\n";
            cout << A;
            break;

        case 'N': ///afisare dupa nume
            cout << "\n Ati ales optiunea de a afisa un abonat.\n Introduceti numele complet aici : ";
            cin.get();
            getline(cin, s);
            cout << '\n';
            cout << A[s];
            break;

        case 'D': ///downcasting
            cout << " Ati ales optiunea de a downcasting!\n";
            cin >> *asr;
            cout << *asr;
            delete asr;
            break;

        case 'Q':
            cout << " Testarea programului s-a incheiat." << endl;
            break;

        default:
            cout << choice << " nu este valida. " << endl;
        }
    } while ((choice != 'Q'));

    return EXIT_SUCCESS;
}
void print_menu()
{
    cout << endl;
    cout << " Urmatoarele alegeri sunt disponibile: " << endl;
    cout << " S -> Scrieti in agenda!" << endl;
    cout << " A -> Afisati agenda!" << endl;
    cout << " N -> Cautati abonatul dupa nume!" << endl;
    cout << " D -> Downcasting!" << endl;
    cout << " Q -> Iesim din program!" << endl
         << endl;
}

char get_user_command()
// Library facilities used: iostream
{
    char command;

    cout << "Introduceti alegerea: ";
    cin >> command; // Input of characters skips blanks and newline character

    return command;
}

int get_number()
// Library facilities used: iostream
{
    int result;

    cout << "Please enter an integer number for the list: ";
    cin >> result;
    cout << result << " has been read." << endl;
    return result;
}