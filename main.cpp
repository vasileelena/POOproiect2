#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Persoana{
protected:
    int id;
    string nume;
    string prenume;
public:
    Persoana(int id=0, string nume="", string prenume=""): id(id), nume(nume), prenume(prenume) {}
    Persoana(const Persoana &pers){ id = pers.id; nume = pers.nume; prenume = pers.prenume; }
    virtual ~Persoana(){}
    Persoana & operator =(const Persoana &pers){ if(this != &pers){id = pers.id; nume = pers.nume; prenume = pers.prenume; } return *this;}
    friend ostream & operator <<(ostream &, Persoana &);
    friend istream & operator >>(istream &, Persoana &);
    virtual void tip_persoana() = 0;
    int get_id() { return id ;}
    string get_nume() {return nume;}
    string get_prenume() {return prenume;}
};

class Abonat : public Persoana{
protected:
    string nr_tlf;
public:
    Abonat(int id=0, string nume="", string prenume="", string nr_tlf=""): Persoana(id, nume, prenume), nr_tlf(nr_tlf){}
    Abonat(const Abonat &ab): Persoana(ab) { nr_tlf = ab.nr_tlf; }
    ~Abonat() {}
    Abonat & operator =(const Abonat & ab){ if(this != &ab){ Persoana::operator =(ab); nr_tlf = ab.nr_tlf; } return *this;}
    friend istream & operator >>(istream &in, Abonat &ab) { in >> (Persoana&)ab; cout << "Introduceti numarul de telefon: "; in >> ab.nr_tlf; return in; }
    friend ostream & operator <<(ostream &out, Abonat &ab) { out << (Persoana&)ab; out << "Numar telefon: " << ab.nr_tlf << endl; return out; }
    void tip_persoana() { cout << "Neabonat Skype" ;}
    string get_nr_tlf() {return nr_tlf;}
};

class Abonat_Skype : public Abonat{
protected:
    string id_skype;
public:
    Abonat_Skype(int id=0, string nume="", string prenume="", string nr_tlf="", string id_sk=""): Abonat(id, nume, prenume, nr_tlf), id_skype(id_sk){}
    Abonat_Skype(const Abonat_Skype &ab): Abonat(ab) { id_skype = ab.id_skype; }
    virtual ~Abonat_Skype(){}
    Abonat_Skype & operator =(const Abonat_Skype & ab){ if(this != &ab){ Abonat::operator =(ab); id_skype = ab.id_skype; } return *this;}
    friend istream & operator >>(istream &in, Abonat_Skype &ab) { in >> (Abonat&)ab; cout << "Introduceti ID-ul de skype: "; in >> ab.id_skype; return in; }
    friend ostream & operator <<(ostream &out, Abonat_Skype &ab) { out << (Abonat&)ab; out << "Id skype: " << ab.id_skype << endl; return out; }
    virtual void tip_persoana() = 0;
    string get_id_skype() {return id_skype;}
    virtual string get_adr_mail() = 0;
    virtual string get_tara() = 0;

};

class Abonat_Skype_Ro : public Abonat_Skype{
protected:
    string adr_mail;
public:
    Abonat_Skype_Ro(int id=0, string nume="", string prenume="", string nr_tlf="", string id_sk="", string adr_mail=""): Abonat_Skype(id, nume, prenume, nr_tlf, id_sk), adr_mail(adr_mail){}
    Abonat_Skype_Ro(const Abonat_Skype_Ro &ab): Abonat_Skype(ab) { adr_mail = ab.adr_mail; }
    ~Abonat_Skype_Ro(){}
    Abonat_Skype_Ro & operator =(const Abonat_Skype_Ro & ab){ if(this != &ab){ Abonat_Skype::operator =(ab); adr_mail = ab.adr_mail; } return *this;}
    friend istream & operator >>(istream &in, Abonat_Skype_Ro &ab) { in >> (Abonat_Skype&)ab; cout << "Introduceti adresa de mail: "; in >> ab.adr_mail; return in; }
    friend ostream & operator <<(ostream &out, Abonat_Skype_Ro &ab) { out << (Abonat_Skype&)ab; out << "Adresa de mail: " << ab.adr_mail << endl; return out; }
    void tip_persoana() { cout << "Abonat Skype Romania";}
    string get_adr_mail() {return adr_mail;}
    string get_tara() {return NULL;}
};

class Abonat_Skype_Extern : public Abonat_Skype{
protected:
    string tara;
public:
    Abonat_Skype_Extern(int id=0, string nume="", string prenume="", string nr_tlf="", string id_sk="", string tara=""): Abonat_Skype(id, nume, prenume, nr_tlf, id_sk), tara(tara){}
    Abonat_Skype_Extern(const Abonat_Skype_Extern &ab): Abonat_Skype(ab) { tara = ab.tara; }
    ~Abonat_Skype_Extern(){}
    Abonat_Skype_Extern & operator =(const Abonat_Skype_Extern & ab){ if(this != &ab){ Abonat_Skype::operator =(ab); tara = ab.tara; } return *this;}
    friend istream & operator >>(istream &in, Abonat_Skype_Extern &ab) { in >> (Abonat_Skype&)ab; cout << "Introduceti tara: "; in >> ab.tara; return in; }
    friend ostream & operator <<(ostream &out, Abonat_Skype_Extern &ab) { out << (Abonat_Skype&)ab; out << "Tara: " << ab.tara << endl; return out; }
    void tip_persoana() { cout << "Abonat Skype Extern";}
    string get_tara() {return tara;}
    string get_adr_mail(){ return NULL; }
};

ostream & operator <<(ostream &out, Persoana &P)
{
    out << endl;
    P.tip_persoana();
    out << endl;
    out << "Detalii persoana: "<< endl;
    out << "Id: " << P.id << endl << "Nume si prenume: " << P.nume << " " << P.prenume << endl;
    return out;
}

istream & operator >>(istream &in, Persoana &P)
{
    cout << endl << "Introduceti nume, prenume, Id persoana: "<<endl;
    srand(time(NULL));
    in >> P.nume >> P.prenume >> P.id;
    try{
        if(P.id > 9999999)
            throw(P.id);
        }catch(int){
            P.id = rand();
            cout << "Id-ul introdus nu este valid. Se va utiliza un id random." << endl;
        }
    return in;
}

class Agenda{
    vector < Abonat_Skype* > a;
public:
    ~Agenda (){ a.erase( a.begin(), a.end() ); }
    friend istream & operator >>(istream &, Agenda &);
    friend ostream & operator <<(ostream &, Agenda &);
    friend void cautareNume(Agenda);
    Abonat_Skype* operator [](string nume){ for( unsigned int i = 0; i < a.size(); i++)if(a[i]->get_nume() == nume) return a[i]; return NULL;}
};

istream & operator >>(istream &in, Agenda &Agenda)
{
    cout << "Introduceti numarul de persoane din agenda : ";
    int n, x;
    in >> n;
    cout << endl << "Tastati 1 pentru a adauga un Abonat Skype Romania, 0 pentru a adauga un Abonat Skype Extern: " << endl;
    in >> x;
    try{
        if(x != 0 && x != 1)
            throw(x);
        }catch(int){
            cout << "S-a introdus o valoare gresita. Va rugam introduceti 1 sau 0!" << endl;
            in >> x;
        }
    for(int i = 0; i < n; i++){
        if(x == 1){
                Abonat_Skype_Ro ab;
                cout << endl;
                ab.tip_persoana();
                in >> ab;
                Agenda.a.push_back(new Abonat_Skype_Ro(ab.get_id(), ab.get_nume(), ab.get_prenume(), ab.get_nr_tlf(), ab.get_id_skype(), ab.get_adr_mail()));
        }
        else if(x == 0){
                Abonat_Skype_Extern ab;
                cout << endl;
                ab.tip_persoana();
                in >> ab;
                Agenda.a.push_back(new Abonat_Skype_Extern(ab.get_id(), ab.get_nume(), ab.get_prenume(), ab.get_nr_tlf(), ab.get_id_skype(), ab.get_tara()));

        }
        else {
                i--;
        }
        if (i != n-1){
            cout << endl << "Tastati 1 pentru a adauga un Abonat Skype Romania, 0 pentru a adauga un Abonat Skype Extern: " << endl;
            in >> x;
            try{
            if(x != 0 && x != 1)
                throw(x);
                }catch(int){
                cout << "S-a introdus o valoare gresita. Va rugam introduceti 1 sau 0!" << endl;
                in >> x;

                }
        }
    }
    return in;

}

ostream & operator <<(ostream &out, Agenda &Agenda)
{
    out << endl << "Agenda:" << endl;
    for(unsigned int i = 0; i < Agenda.a.size(); i++){
           if(dynamic_cast < Abonat_Skype_Ro* > (Agenda.a[i]) ){
                    out << *(static_cast<Abonat_Skype_Ro*> (Agenda.a[i]) ) << endl;
            }
                else{
                    out << *(static_cast<Abonat_Skype_Extern*> (Agenda.a[i]) ) << endl;
                }
    }
    return out;
}

void cautareNume (Agenda a)
{
   string nume_cautat;
   cout << endl << "Introduceti numele abonatului cautat (prima litera majuscula): ";
   cin >> nume_cautat;
   if(a[nume_cautat] != NULL){
            cout << endl << "Detaliile abonatului cautat :" << endl;

            if(dynamic_cast < Abonat_Skype_Ro* > (a[nume_cautat]) ){
                    cout << *(static_cast<Abonat_Skype_Ro*> (a[nume_cautat]) );
            }
                else{
                    cout << *(static_cast<Abonat_Skype_Extern*> (a[nume_cautat]) );
                }
        }else cout << endl << "Nu exista un abonat cu numele cautat!" << endl;
}

int main()
{

   Agenda a;
   cin >> a;
   int x;
   while(x){
    cout << endl << "Introduceti optiunea dorita: " << endl << "(1) cautarea unui nume in agenda;" << endl << "(2) afisarea agendei;" << endl << "(0) inchiderea programului." << endl;
    cin >> x;
   switch(x){
        case 1: cautareNume(a);
                break;
        case 2: cout << a;
                break;
        case 0: cout << "Agenda s-a inchis. La revedere! " << endl;
                break;
        default : cout << "Va rugam introduceti una dintre valorile de mai sus!" << endl;
                  break;
    }
   }
    return 0;
}
