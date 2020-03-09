#include <iostream>
#include <cmath>
#include <cctype>
#include <cstdlib>
using namespace std;

void print_menu();
int get_number();

const int max_grad = 5;

class Polinom {
private :
    int grad;
    double coef[max_grad + 1];

public :
    Polinom ();                                                 ///CONSTRUCTOR
    Polinom (Polinom&);                                         ///COPIATOR
    ~Polinom ();                                                ///DESTRUCTOR
    void set_coef(int ,double);                                 ///SET COEFICIENT
    double get_coef (int) const;                                ///GET COEFICIENT
    int get_grad (int) const;                                   ///GET GRAD
    void citire (istream &in);                                  ///CITIREA
    friend istream& operator>>(istream &in, Polinom& p);        ///OPERATORUL >>
    void afisare (ostream &out);                                ///AFISAREA
    friend ostream& operator<<(ostream &out, Polinom& p);       ///OPERATORUL <<
    friend Polinom& operator+(Polinom&, Polinom&);              ///ADUNAREA A DOUA POLINOAME, OPERATORUL +
    Polinom& operator=(Polinom&);                               ///ATRIBUIREA POLINOAMELOR, OPERATORUL =
    friend Polinom& operator-(Polinom&, Polinom&);              ///SCADEREA A DOUA POLINOAME, OPERATORUL -
    friend Polinom& operator*(Polinom&, Polinom&);              ///PRODUSUL A DOUA POLINOAME, OPERATORUL *
    double evaluare_poly (Polinom& p, double&) const;           ///EVALUAREA UNUI POLINOM

};

///CONSTRUCTORUL
Polinom :: Polinom()
{
    this->grad = -1;
    for(int i = 0; i <= max_grad; i++)
        {
            this->coef[i] = 0.0;
        }
}

///FUNCTIE DE COPIERE A POLINOMULUI
Polinom :: Polinom(Polinom &P)
{
    this->grad = P.grad;
    for(int i = 0; i <= max_grad; i++)
        {
            this->coef[i] = P.coef[i];
        }
}

///DESTRUCTORUL
Polinom :: ~Polinom()
{
    for(int i = 0; i <= grad; i++)
        {
            this->coef[i] = 0.0;
        }
    this->grad = -1;
}

///SET COEFICIENT
void Polinom :: set_coef(int k, double val)
{
    if(val != 0.0 && k > grad)
        grad = k;
    int i = grad;
    while(i >= 0 && coef[i] == 0.0)
    {
        grad--;
        i--;
    }
}

///GET COEFICIENT
double Polinom :: get_coef(int k) const
{
    if(k <= grad)
        return coef[k];
    else
        return 0.0;
}

///GET GRAD
int Polinom :: get_grad(int k) const
{
    return grad;
}

///CITIREA
void Polinom :: citire(istream &in)
{
    cout<<"Introduceti gradul polinomului. Atentie valoarea trebuie sa fie <=5"<<'\n'
        <<"Gradul introdus este : ";
    in>>grad;
    bool ok = true;
    while(ok)
    {
        if(grad > max_grad)
        {
            cout<<" Nerespectare cerinta initiala!\n Introduceti o valoare <=5\n";
            in>>grad;
        }
        else ok = false;
    }

    for(int i = 0; i <= grad; i++)
    {
        cout<<"Introduceti valoarea coeficientului lui x^"<<i<<" : ";
        in>>coef[i];
    }
    for(int i = grad + 1; i <= max_grad; i++)
        coef[i] = 0.0;
}

///OPERATORUL >>
istream& operator>>(istream& in, Polinom& p)
{
    p.citire(in);
    return in;
}

///AFISAREA
void Polinom :: afisare(ostream &out)
{
    if(grad < 0)
    {
        cout<<0;
        return;
    }
    for(int i = grad; i >= 0; i--)
    {
        if(i > 0)
            cout<<coef[i]<<'*'<<"x^"<<i<<" + ";
        else
            cout<<coef[i]<<'*'<<"x^"<<i<<'.'<<endl;
    }
}

///OPERATORUL <<
ostream& operator<<(ostream& out, Polinom& p)
{
    p.afisare(out);
    return out;
}

///EVALUAREA UNUI POLINOM
double Polinom :: evaluare_poly(Polinom& p, double& val) const
{
    double rezultat = 0.0;
    for(int i = 0; i <= p.grad; i++)
        rezultat += pow(val,i) * p.coef[i];
    return rezultat;
}

///ADUNAREA A DOUA POLINOAME, OPERATORUL +
Polinom& operator+ (Polinom& p1, Polinom& p2)
{
    Polinom *P = new Polinom;
    int *grad_P = new int;
    if (p1.grad > p2.grad)
        *grad_P = p1.grad;
    else *grad_P = p2.grad;
    for(int i = 0; i <= *grad_P; i++)
        P->coef[i] = p1.coef[i] + p2.coef[i];
    P->grad = *grad_P;
    delete grad_P;
    return *P;
}

///SCADEREA A DOUA POLINOAME, OPERATORUL -
Polinom& operator- (Polinom& p1, Polinom& p2)
{
    Polinom *P = new Polinom;
    int *grad_P = new int;
    if (p1.grad > p2.grad)
        *grad_P = p1.grad;
    else *grad_P = p2.grad;
    for(int i = 0; i <= *grad_P; i++)
        P->coef[i] = p1.coef[i] - p2.coef[i];
    P->grad = *grad_P;
    delete grad_P;
    return *P;

}

///ATRIBUIREA POLINOAMELOR, OPERATORUL =
Polinom& Polinom :: operator= (Polinom& p)
{
    grad = p.grad;
    for(int i = 0; i <= grad; i++)
        coef[i] = p.coef[i];
    return p;

}

///PRODUSUL A DOUA POLINOAME, OPERATORUL *
inline Polinom& operator* (Polinom& p1, Polinom& p2)
{
    Polinom *p = new Polinom;
    double A[p2.grad+1][p1.grad+1];
    p->grad = p1.grad + p2.grad;
    for(int i = 0; i <= p2.grad; i++)
        {for(int j = 0; j <= p1.grad; j++)
            A[i][j] = p2.coef[i] * p1.coef[j];}

    for(int k = 0; k <= p->grad; k++)
    {
        p->coef[k] = 0.0;
    }

    for(int k = 0; k <= p->grad; k++)
    {
        for(int i = 0; i <= p2.grad; i++)
            for(int j = 0; j <= p1.grad; j++)
                if(i + j == k)
                    p->coef[k] += A[i][j];
    }
    return *p;

}
int main()
{
    char choice;    ///Command entered by the user
    int num, n;
    double *x = new double;
    Polinom p1 , p2;
    Polinom * P = new Polinom [n];

    do
    {
        print_menu();
        cout<<" Introduceti alegerea : ";
        cin>>choice;
        choice = toupper(choice);

        switch(choice)
        {
            case 'I' : ///initializare n-polinoame
                cout<<" Introduceti numarul de polinoame : ";
                cin>>n;
                for(int i = 0; i < n; i++)
                    cin>>P[i];
                break;

            case 'E' : ///evaluare
                cout<<" Care polinom trebuie evaluat : ";
                cin>>num;
                if(num == 1)
                {
                    cout<<" Evaluarea polinomului 1 in valoarea : ";
                    cin>>*x;
                    cout<<" Valoarea polinomului in "<<*x<<" este : "
                        <<p1.evaluare_poly(p1,*x)<<endl;
                }
                else if(num == 2)
                {
                    cout<<" Evaluarea polinomului 2 in valoarea : ";
                    cin>>*x;
                    cout<<" Valoarea polinomului in "<<*x<<" este : "
                        <<p2.evaluare_poly(p2,*x)<<endl;
                }
                else
                    cout<<" Exista doar doua polinoame : 1 si 2. Nu mai multe!"<<endl;
                    delete x;
                break;

            case 'A' : ///afisarea polinomului
                cout<<" Se afiseaza polinomul 1 sau 2: ";
                cin>>num;
                if(num == 1)
                    cout<<" Polinomul 1 este "<<p1<<endl;
                else if(num == 2)
                    cout<<" Polinomul 2 este "<<p2<<endl;
                else
                    cout<<" Exista doar doua polinoame : 1 si 2. Nu mai multe!"<<endl;
                break;

            case 'Q' : cout<<" Testarea programului s-a incheiat."<<endl;
                delete [] P;
                break;

            case 'C' : ///citirea unui polinom
                cout<<" Se citeste polinomul 1 sau 2: ";
                cin>>num;
                if(num == 1)
                    {cout<<" Se initializeaza primul polinom. "<<endl;
                    cin>>p1;}
                else if(num == 2)
                    {cout<<" Se initializeaza al doilea polinom. "<<endl;
                    cin>>p2;}
                else
                    cout<<" Exista doar doua polinoame : 1 si 2. Nu mai multe!"<<endl;
                break;
            case 'S' : ///adunarea a doua polinoame
                cout<<" Se va afisa suma dintre cele doua polinoame : "<<p1+p2<<endl;
                break;

            case 'D' : ///scaderea a doua polinoame

                cout<<" Se ca scadea polinomul ";
                cin>>num;
                cout<<" din polinomul "<< 3 - num<<endl;
                if(num == 1)
                {
                    cout<<" Se va afisa diferenta dintre polinomul 1 si polinomul 2 : "<<p1-p2<<endl;
                }
                else if(num == 2)
                {
                    cout<<" Se va afisa diferenta dintre polinomul 2 si polinomul 1 : "<<p2-p1<<endl;
                }
                else
                    cout<<" Exista doar doua polinoame : 1 si 2. Nu mai multe!"<<endl;
                break;

            case 'P' : ///produsul dintre doua polinoame
                cout<<" Se va afisa produsul dintre cele doua polinoame : "<<p1*p2<<endl;
                break;

            default: cout<<choice<<" nu este valida. "<<endl;

        }
    }
    while((choice != 'Q'));

    return EXIT_SUCCESS;
}
void print_menu( )
{
    cout << endl;
    cout << " Urmatoarele alegeri sunt disponibile: " << endl;
    cout << " I -> Initializare a n - polinoame! "<< endl;
    cout << " C -> Citim un polinom!" << endl;
    cout << " E -> Evaluam un polinom!" << endl;
    cout << " A -> Afisarea unui polinom!" <<endl;
    cout << " S -> Afisarea suma dintre cele doua polinoame!"<<endl;
    cout << " D -> Afisarea diferenta dintre cele doua polinoame!"<<endl;
    cout << " P -> Afisarea produsul dintre cele doua polinoame!"<<endl;
    cout << " Q -> Iesim din program!"<<endl<<endl;
}

char get_user_command( )
// Library facilities used: iostream
{
    char command;

    cout << "Introduceti alegerea: ";
    cin >> command; // Input of characters skips blanks and newline character

    return command;
}

int get_number( )
// Library facilities used: iostream
{
    int result;

    cout << "Please enter an integer number for the list: ";
    cin  >> result;
    cout << result << " has been read." << endl;
    return result;
}

