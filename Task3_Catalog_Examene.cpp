#include <iostream>
#include <string.h>
#include <cstdlib>
#include <unordered_map>
#include <iterator>
#include <map>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <limits>
#include <list>
using namespace std;
void print_menu();
int get_number();

map<unsigned, string> exams_list;
unsigned get_from_the_exams_list(string &s)
{
    exams_list.insert(pair<unsigned, string>(1, "POO"));
    exams_list.insert(pair<unsigned, string>(2, "LFA"));
    exams_list.insert(pair<unsigned, string>(3, "Baze de date"));
    exams_list.insert(pair<unsigned, string>(4, "Algebra"));
    exams_list.insert(pair<unsigned, string>(5, "Analiza Complexa"));
    exams_list.insert(pair<unsigned, string>(6, "Probabilitati"));
    for (auto itr = exams_list.begin(); itr != exams_list.end(); ++itr)
    {
        if (s == itr->second)
            return itr->first;
    }
    return 0;
}

class Exam
{
protected:
    unsigned id_exam;
    static int nr_obj;
    string name_exam;
    string date;
    double grade;

public:
    Exam(string, string, double);
    virtual ~Exam(){};
    virtual void citire(istream &);
    virtual void afisare(ostream &);
    friend istream &operator>>(istream &, Exam &);
    friend ostream &operator<<(ostream &, Exam &);
    friend unsigned get_from_the_exams_list(string &);
    virtual Exam &operator=(Exam &);
    static void nr_objects()
    {
        cout << nr_obj << '\n';
    }
};
int Exam ::nr_obj;

Exam::Exam(string name = "", string d = "", double g = 1.0)
{
    try
    {
        if (g > 10.0 || g < 1.0)
            throw 1;
    }
    catch (int i)
    {
        cout << "Eroare constructor " << i << ". Nota nu poate sa fie mai mare de 10 si mai mica de 1!";
        exit(EXIT_FAILURE);
    }
    id_exam = get_from_the_exams_list(name);
    name_exam = name;
    date = d;
    grade = g;
}

void Exam::citire(istream &in)
{
    nr_obj++;
    if (nr_obj > 1)
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " Sa se introduca denumirea materiei : ";
    string ne;
    bool k = true;
    while (k == true)
    {
        getline(in, ne);
        k = false;
        try
        {
            if (get_from_the_exams_list(ne) == 0)
                throw 2;
        }
        catch (int i)
        {
            cout << "\nEroare la citire " << i << "! Inroduceti o materie din lista de examene : ";

            k = true;
        }
    }
    cout << " Sa se introduca data examinarii : ";
    in >> date;
    double g;
    k = true;
    cout << " Sa se introduca nota obtinuta : ";
    while (k == true)
    {
        in >> g;
        k = false;
        try
        {
            if (g > 10.0 || g < 1.0)
                throw 3;
        }
        catch (int i)
        {
            cout << "\nEroare la citire " << i << "! Introduceti o nota intre 1 si 10 : ";
            k = true;
        }
    }
    id_exam = get_from_the_exams_list(ne);
    name_exam = ne;
    grade = g;
}

istream &operator>>(istream &in, Exam &e)
{
    e.citire(in);
    return in;
}

void Exam::afisare(ostream &out)
{
    out << " Id-ul examenului este " << id_exam << '\n';
    out << " Pe data de " << date << " elevul a obtinut la examenul scris de " << name_exam << " nota " << grade << '\n';
}

ostream &operator<<(ostream &out, Exam &e)
{
    e.afisare(out);
    return out;
}

Exam &Exam ::operator=(Exam &e)
{
    this->id_exam = e.id_exam;
    this->name_exam = e.name_exam;
    this->date = e.date;
    this->grade = e.grade;
}

///---------------------------------------------------
class Partial : protected Exam
{
protected:
    double oral_grade;

public:
    Partial(string, string, double, double);
    ~Partial(){};
    void citire(istream &);
    void afisare(ostream &);
    friend istream &operator>>(istream &, Partial &);
    friend ostream &operator<<(ostream &, Partial &);
    Partial &operator=(Partial &);
};

Partial::Partial(string name = "", string d = "", double g = 1.0, double og = 1.0) : Exam(name, d, g)
{
    try
    {
        if (og > 10.0 || og < 1.0)
            throw 4;
    }
    catch (int i)
    {
        cout << "\nEroare constructor " << i << ". Nota nu poate sa fie mai mare de 10 si mai mica de 1!";
        exit(EXIT_FAILURE);
    }
    oral_grade = og;
}

void Partial::citire(istream &in)
{
    Exam::citire(in);
    bool k1 = true;
    double og;
    cout << " Sa se introduca nota obtinuta la examenul oral: ";
    while (k1 == true)
    {
        in >> og;
        k1 = false;
        try
        {
            if (og > 10 || og < 1)
                throw 5;
        }
        catch (int i)
        {
            cout << "\nEroare la citire " << i << "! Introduceti o nota intre 1 si 10 : ";
            k1 = true;
        }
    }
    oral_grade = og;
}

istream &operator>>(istream &in, Partial &p)
{
    p.citire(in);
    return in;
}

void Partial::afisare(ostream &out)
{
    out << " Elevul a obtinut la examenul oral de " << name_exam << " nota " << oral_grade << '\n';
}

ostream &operator<<(ostream &out, Partial &p)
{
    p.afisare(out);
    return out;
}

Partial &Partial::operator=(Partial &p)
{
    Exam::operator=(p);
    this->oral_grade = p.oral_grade;
}

///---------------------------------------------------
class Quiz : private Exam
{
private:
    unsigned nr_items;

private:
    Quiz(string, string, double, unsigned);
    ~Quiz(){};
    void citire(istream &);
    void afisare(ostream &);
    friend istream &operator>>(istream &, Quiz &);
    friend ostream &operator<<(ostream &, Quiz &);
    Quiz &operator=(Quiz &);
    void set_grade(double qg) { grade = qg; };
    unsigned get_grade() { return grade; };
    friend class Final_Exam;
};

Quiz::Quiz(string name = "", string d = "", double g = 1.0, unsigned ni = 0) : Exam(name, d, g)
{
    nr_items = ni;
}

void Quiz::citire(istream &in)
{
    Exam::citire(in);
    cout << " Sa se introduca numarul de itemi din quiz : ";
    in >> nr_items;
}

istream &operator>>(istream &in, Quiz &q)
{
    q.citire(in);
    return in;
}

void Quiz::afisare(ostream &out)
{
    out << " Nota obtinuta la quiz-ul de " << name_exam << " este " << grade << '\n';
}

ostream &operator<<(ostream &out, Quiz &q)
{
    q.afisare(out);
    return out;
}

Quiz &Quiz::operator=(Quiz &q)
{
    Exam::operator=(q);
    this->nr_items = q.nr_items;
}

///---------------------------------------------------
class Final_Exam : protected Partial
{
private:
    double extra_points;
    double final_grade;
    Quiz *q;

public:
    Final_Exam(string, string, double, double, double, Quiz *);
    ~Final_Exam(){};
    void citire(istream &);
    void afisare(ostream &);
    friend istream &operator>>(istream &, Final_Exam &);
    friend ostream &operator<<(ostream &, Final_Exam &);
    Final_Exam &operator=(Final_Exam &);
    int get_quiz()
    {
        if (q->grade == 0.0)
            return 0;
        else
            return 1;
    };
    friend unordered_map<unsigned, vector<string>> restante(const unsigned &);
};

Final_Exam::Final_Exam(string name = "", string d = "", double g = 1.0, double og = 1.0, double ep = 0.0, Quiz *Q = new Quiz) : Partial(name, d, g, og)
{
    try
    {
        if (ep < 0.0 || ep > 1.0)
            throw 6;
    }
    catch (int i)
    {
        cout << "\nEroare constructor " << i << " Punctele extra sunt intre 0 si 1!\n";
        exit(EXIT_FAILURE);
    }

    extra_points = ep;
    q = Q;
    final_grade = (grade + oral_grade) / 2 + extra_points + q->grade / 10;
    if (final_grade >= 10.0)
        final_grade = 10.0;
}

void Final_Exam::citire(istream &in)
{
    Partial::citire(in);
    cout << " Sa se introduca punctajul extra de la proiect : ";
    bool k = true;
    while (k == true)
    {
        in >> extra_points;
        k = false;
        try
        {
            if (extra_points < 0.0 || extra_points > 1.0)
                throw 7;
        }
        catch (int i)
        {
            cout << "\nEroare la citire " << i << "! Punctele extra sunt intre 0 si 1! Reintroduceti : ";
            k = true;
        }
    }
    try
    {
        if (oral_grade < 5.0)
            throw 8;
    }
    catch (int i)
    {
        cout << " Partialul nu a fost luat! Se da din nou la examenul final!\n";
        cout << " Partialul a fost dat a doua oara! Sa se introduca nota obtinuta : ";
        in >> oral_grade;
    }
    final_grade = (grade + oral_grade) / 2 + extra_points;
    if (final_grade >= 10.0)
    {
        final_grade = 10.0;
        q->set_grade(0.0);
    }
    else
    {
        cout << " Nota finala este " << final_grade << '\n';
        cout << " Doreste elevul sa primeasca un quiz? D sau N?\t";
        char ans;
        in >> ans;
        switch (ans)
        {
        case 'D':
            cout << " Elevul a ales sa dea un quiz pentru marirea notei finale.\n Acestea sunt datele despre quiz :\n";
            in >> *q;
            break;

        default:
            q->set_grade(0.0);
            break;
        }
        final_grade += q->grade / 10;
        if (final_grade >= 10.0)
            final_grade = 10.0;
    }
}

istream &operator>>(istream &in, Final_Exam &f)
{
    f.citire(in);
    return in;
}

void Final_Exam::afisare(ostream &out)
{
    Exam::afisare(out);
    Partial::afisare(out);
    if (q->grade != 0.0)
        out << *q;
    out << " Nota finala la materia " << name_exam << " este " << final_grade << '\n';
}

ostream &operator<<(ostream &out, Final_Exam &f)
{
    f.afisare(out);
}

Final_Exam &Final_Exam::operator=(Final_Exam &f)
{
    Partial::operator=(f);
    this->extra_points = f.extra_points;
    this->final_grade = f.final_grade;
    this->q = f.q;
}

///---------------------------------------------------

class Student
{
private:
    static int nr_obj1;
    string first_name;
    string last_name;
    unsigned nr_exams;
    vector<Final_Exam> student_exams;

public:
    Student(string, string, unsigned);
    ~Student(){};
    void citire(istream &);
    void afisare(ostream &);
    friend istream &operator>>(istream &, Student &);
    friend ostream &operator<<(ostream &, Student &);
    Student &operator=(Student &);
    friend unordered_map<unsigned, vector<string>> restante(const unsigned &);
    template <class T>
    friend class CatalogIndividual;
};

int Student::nr_obj1;
Student::Student(string fn = "", string ln = "", unsigned nr = 0)
{
    first_name = fn;
    last_name = ln;
    nr_exams = nr;
}

void Student::citire(istream &in)
{
    nr_obj1++;
    if (nr_obj1 > 1)
    {
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "\tSa se introduca numele studentului : ";
    getline(in, last_name);
    cout << "\tSa se introduca prenumele studentului : ";
    getline(in, first_name);
    cout << "\tSa se introduca numarul de examene ale studentului : ";
    in >> nr_exams;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    Final_Exam *f = new Final_Exam[nr_exams];
    for (int i = 0; i < nr_exams; i++)
    {
        cin >> f[i];
        student_exams.push_back(f[i]);
    }
}

istream &operator>>(istream &in, Student &s)
{
    s.citire(in);
    return in;
}

void Student::afisare(ostream &out)
{
    out << "\t- Studentul cu numle " << last_name << ' ' << first_name << " are un numar de " << nr_exams << " examene pentru aceasta sesiune!\n";
    out << "\t- Informatii examene : \n\n";
    for (int i = 0; i < nr_exams; i++)
    {
        out << student_exams[i] << '\n';
    }
}

ostream &operator<<(ostream &out, Student &s)
{
    s.afisare(out);
    return out;
}

Student &Student::operator=(Student &s)
{
    this->first_name = s.first_name;
    this->last_name = s.last_name;
    this->nr_exams = s.nr_exams;
    for (int i = 0; i < s.student_exams.size(); i++)
        this->student_exams[i] = s.student_exams[i];
}
///---------------------------------------------------
unordered_map<unsigned, vector<string>> restante(const unsigned &nr_students)
{
    Student *s = new Student[nr_students];
    unordered_map<unsigned, vector<string>> res;
    vector<string> vec;
    for (int i = 0; i < nr_students; i++)
    {
        cout << "Se introduce date despre studentul cu numarul " << i + 1 << " din " << nr_students << '\n';
        cin >> s[i];
    }
    for (auto itr = exams_list.begin(); itr != exams_list.end(); ++itr) //in lista de examene
    {
        for (int i = 0; i < nr_students; i++) //in vectorul de studenti
        {
            for (int j = 0; j < s[i].student_exams.size(); j++) //in vectorul de examene al studentului i
            {
                if (s[i].student_exams[j].id_exam == itr->first) //verificam id ul examenului in lista de examene
                {
                    if (s[i].student_exams[j].final_grade < 5) //daca id ul a fost gasit cautam daca nota examenului este mai mica decat 5
                    {
                        string a = s[i].last_name + ' ' + s[i].first_name;
                        vec.push_back(a);
                    }
                }
            }
        }
        res.insert(pair<unsigned, vector<string>>(itr->first, vec));
        vec.clear();
    }
    return res;
}

///---------------------------------------------------

template <class T>
class CatalogIndividual
{
private:
    static int nr_obj2;
    unsigned nr_matricol;
    T stud;
    list<vector<string>> list_fisa_exam;

public:
    CatalogIndividual(unsigned nr = 0, T *s = new T)
    {
        nr_matricol = nr;
        stud = *s;
    };
    ~CatalogIndividual(){};
    void citire(istream &in)
    {
        nr_obj2++;
        nr_matricol = nr_obj2;
        cout << "Se intorduce in catalogul virtual al elevului cu numarul matricol : " << nr_matricol << '\n';
        in >> stud;
    };
    void afisare(ostream &out)
    {
        out << "Informatii catalog individual :\n";
        out << "\t- Numarul matricol : " << nr_matricol << '\n';
        out << stud;
        if (list_fisa_exam.size() == 0)
        {
            out << "\t* Nu exista fise de observatii pentru examenele din acest catalog individual.\n";
        }
        else
        {
            out << "\t- Informatii fise de observatie :\n";
            for (auto i = list_fisa_exam.begin(); i != list_fisa_exam.end(); ++i)
            {
                for (int j = 0; j < i->size(); j++)
                {
                    out << i->at(j);
                }
            }
        }
    };
    friend istream &operator>>(istream &in, CatalogIndividual<T> &s)
    {
        s.citire(in);
        return in;
    };
    friend ostream &operator<<(ostream &out, CatalogIndividual<T> &s)
    {
        s.afisare(out);
        return out;
    };
    //CatalogIndividual &operator=(CatalogIndividual &);
    list<vector<string>> &operator+=(const vector<string> &fisa)
    {
        list_fisa_exam.push_back(fisa);
        return list_fisa_exam;
    };
};
template <class T>
int CatalogIndividual<T>::nr_obj2;

void add_fisa(CatalogIndividual<Student> &S)
{
    vector<string> vs;
    string temp_s1, ans, s;
    int i = 0, n = 1;
    cout << "Ati ales optiunea de a adauga o fisa de observatie pentru un examen.\n"
         << "Specificati denumirea examenului : ";
    vs.push_back("Fisa de observatii pentru examenul : ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, temp_s1);
    vs.push_back(temp_s1);
    vs.push_back("\nAvem urmatoarele observatii : \n");
    cout << "Sa se introduca observatiile.\n";
    while (i < n)
    {
        getline(cin, s);
        cout << "Doriti sa mai adaugati o observatie? Da sau Nu : ";
        getline(cin, ans);
        if (ans == "Da")
            n++;
        i++;
        vs.push_back(s);
        vs.push_back(" \n");
    }
    S += vs;
}

///---------------------------------------------------
template <>
class CatalogIndividual<Quiz>
{
private:
    unsigned int nr_stud_quiz;
    unsigned nr_stud;
    Student *S;

public:
    CatalogIndividual(unsigned nr_s = 0)
    {
        nr_stud = nr_s;
        S = new Student[nr_stud];
    };
    ~CatalogIndividual(){};
    void citire(istream &in)
    {
        cout << "Introduceti numarul de studenti : ";
        in >> nr_stud;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        S = new Student[nr_stud];
        cout << "Introduceti studentii : \n";
        for (int i = 0; i < nr_stud; i++)
        {
            cout << "Se introduce date despre studentul cu numarul " << i + 1 << " din " << nr_stud << '\n';
            in >> S[i];
        }
    };
    void afisare(ostream &out)
    {
        out << " Numarul de studentii care au dat cel putin doua quiz-uri este : ";
        nr_stud_quiz = 0;
        for (int i = 0; i < nr_stud; i++)
        {
            int val = 0;
            for (int j = 0; j < S[i].student_exams.size(); j++)
            {
                if (S[i].student_exams[j].get_quiz() == 1)
                {
                    val++;
                }
            }
            if (val >= 2)
                nr_stud_quiz++;
        }
        out << nr_stud_quiz << '\n';
    };
    friend istream &operator>>(istream &in, CatalogIndividual<Quiz> &Q)
    {
        Q.citire(in);
        return in;
    };
    friend ostream &operator<<(ostream &out, CatalogIndividual<Quiz> &Q)
    {
        Q.afisare(out);
        return out;
    };
};
int main()
{
    string s;
    char choice;
    CatalogIndividual<Student> cis;
    CatalogIndividual<Quiz> qs;
    unordered_map<unsigned, vector<string>> Rest;
    unordered_map<unsigned, vector<string>>::iterator itr;
    do
    {
        print_menu();
        cout << " Introduceti alegerea : ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'I':
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> cis;
            break;

        case 'A':
            cout << cis;
            break;

        case 'R':
            unsigned n;
            cout << "Sa se introduca numarul de studenti :";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Rest = restante(n);
            break;

        case 'T':
            cout << "---------------------------------------\n";
            for (itr = Rest.begin(); itr != Rest.end(); itr++)
            {
                cout << "\t\t" << itr->first << '\n';
                //cout<<"---------------------------------------\n";
                for (int j = 0; j < itr->second.size(); j++)
                {
                    cout << '\t' << itr->second[j] << '\n';
                }
                cout << "---------------------------------------\n";
            }
            break;

        case 'Q':
            cin >> qs;

        case 'Z':
            cout << qs;

        case 'E':
            cout << " Testarea programului s-a incheiat." << endl;
            break;

        default:
            cout << choice << " nu este valida. " << endl;
        }
    } while ((choice != 'E'));

    return EXIT_SUCCESS;
}

void print_menu()
{
    cout << endl;
    cout << " Urmatoarele alegeri sunt disponibile: " << endl;
    cout << " I -> Introduceti un elev in catalogul individual!" << endl;
    cout << " A -> Afisati datele din catalogul individual al elevului introdus!" << endl;
    cout << " R -> Selectarea restantierilor!" << endl;
    cout << " T -> Afisare tabel cu restantieri!" << endl;
    cout << " Q -> Introduceti studenti pentru selectarea quiz-urilor!" << endl;
    cout << " Z -> Afisarea pentru quiz!" << endl;
    cout << " E -> Iesim din program!" << endl
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