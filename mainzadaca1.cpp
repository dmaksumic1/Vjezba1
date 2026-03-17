#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
template <typename Tip>

class Iterator;
template <typename Tip>
class Lista
{
public:
    Lista() {};
    virtual int brojElemenata()const=0;
    virtual Tip& trenutni()=0;
    virtual bool prethodni()=0;
    virtual  bool sljedeci()=0;
    virtual  bool pocetak()=0;
    virtual bool kraj()=1;
    virtual  void obrisi()=0;
    virtual  void dodajIspred(const Tip& el)=0;
    virtual  void dodajIza(const Tip& el)=0;
    virtual  Tip& operator[](int i)=0;
    virtual const Tip& operator[](int i)const=0;
    Lista(const Lista&a)=default;

    Lista& operator=(const Lista&a)=default;
    Lista& operator=(Lista&&a)=default;
    Lista(Lista&&a)=default;
    virtual ~Lista() {};
};


template <typename Tip>
class DvostrukaLista:public Lista<Tip>
{
    protected:
    struct Cvor
    {
        Tip element;
        Cvor* sljedeci;
        Cvor* prethodni;
    };
    int duzina;
    Cvor*pocetakk;
    Cvor*krajj;

    Cvor* trenutnii;
public:
    DvostrukaLista():duzina(0),pocetakk(nullptr),krajj(nullptr),trenutnii(nullptr) {};
    int brojElemenata() const
    {
        return duzina;
    };
    Tip& trenutni()
    {
        if(duzina==0 ) throw std::domain_error("PRazna lista");

        return trenutnii->element;
    };
    bool prethodni()
    {        if(duzina==0 ) throw std::domain_error("PRazna lista");

        if(trenutnii==pocetakk) return false;

        trenutnii=trenutnii->prethodni;
        return true;
    }
    bool sljedeci()
    {        if(duzina==0 ) throw std::domain_error("PRazna lista");

        if(trenutnii==krajj) return false;
        trenutnii=trenutnii->sljedeci;
        return true;

    }

    bool pocetak()
    {
        if(duzina==0 ) throw std::domain_error("PRazna lista");
if(trenutnii==pocetakk) return false;
        trenutnii=pocetakk;
        return true;
    }
    bool kraj()
    {
        if(duzina==0 ) throw std::domain_error("PRazna lista");
if(trenutnii==krajj) return false;
        trenutnii=krajj;
        return true;
    }

    void obrisi()
    {
        if(duzina==0 ) throw std::domain_error("PRazna lista");
        if (trenutnii == pocetakk)
        {
            Cvor* brisanje = pocetakk;
            pocetakk = pocetakk->sljedeci;
            if(pocetakk != nullptr) //ako je jedan el
            pocetakk->prethodni=nullptr;
            trenutnii = pocetakk;
            if(pocetakk==nullptr) krajj=nullptr;
            delete brisanje;
        }



            else if(trenutnii == krajj)
{
    Cvor* prethodni = krajj->prethodni;
    delete krajj;
    krajj = prethodni;
    if(krajj) krajj->sljedeci = nullptr;
    trenutnii = krajj;
}

            else
            {
                Cvor* p=trenutnii;
                trenutnii->prethodni->sljedeci=trenutnii->sljedeci;
                trenutnii->sljedeci->prethodni=trenutnii->prethodni;
                trenutnii=trenutnii->sljedeci;
                delete p;
            }

        duzina--;


    };

    void dodajIspred(const Tip& el)
    {

        Cvor *novi=new Cvor{ el,nullptr,nullptr};
        if(duzina==0)
        {

            pocetakk=krajj=trenutnii=novi;
        }

        else if(trenutnii==pocetakk)
        {
            novi->sljedeci=pocetakk;
            pocetakk->prethodni=novi;
            pocetakk=novi;


        }
        else
        {

            novi->prethodni=trenutnii->prethodni;
            novi->sljedeci=trenutnii;
            trenutnii->prethodni->sljedeci=novi;
               trenutnii->prethodni = novi;

        }
        duzina++;

    };
    void dodajIza(const Tip& el)
    {
        Cvor*novi=new Cvor{el,nullptr,nullptr};
        if(duzina==0)
        {
            pocetakk=krajj=trenutnii=novi;
        }
        else
        {
            novi->sljedeci=trenutnii->sljedeci;
            novi->prethodni=trenutnii;

            if(trenutnii->sljedeci != nullptr)
    trenutnii->sljedeci->prethodni = novi;
            trenutnii->sljedeci=novi;


            if(trenutnii==krajj) krajj=novi;
        }
        duzina++;


    };


    Tip& operator[](int i)
    {
        if(i<0 ||i>=duzina ) throw std::domain_error("Nevazeci index");
        int brojac=0;

        Cvor*p=pocetakk; Cvor*k=krajj;

         if(i<duzina/2)
            {


        while(brojac<i)
        {
            p=p->sljedeci;
            brojac++;
        }
         return p->element;
        }
        else{
            for(int j=duzina-1;j>i;j--)
            {

                k=k->prethodni;
            }



        }
       return k->element;
    };

    const Tip& operator[](int i)const
   {
        if(i<0 ||i>=duzina ) throw std::domain_error("Nevazeci index");
        int brojac=0;

        Cvor*p=pocetakk; Cvor*k=krajj;

         if(i<duzina/2)
            {


        while(brojac<i)
        {
            p=p->sljedeci;
            brojac++;
        }
         return p->element;
        }
        else{
            for(int j=duzina-1;j>i;j--)
            {

                k=k->prethodni;
            }



        }
       return k->element;
    };

    DvostrukaLista(const DvostrukaLista &a):duzina(0), pocetakk(nullptr), krajj(nullptr), trenutnii(nullptr)
    {
        Cvor* stari = a.pocetakk;
        Cvor* zadnji = nullptr;

        while(stari != nullptr)
        {
            Cvor* novi = new Cvor{stari->element, nullptr,nullptr};
            if(!pocetakk) pocetakk = novi;
            else {zadnji->sljedeci = novi;
            novi->prethodni=zadnji;
            }
            zadnji = novi;

            if(stari == a.trenutnii) trenutnii = novi;

            stari = stari->sljedeci;
        }
        krajj = zadnji;
        duzina = a.duzina;
    };


    DvostrukaLista& operator=(const DvostrukaLista &a)
    {
        if(this == &a) return *this;
        Cvor* t = pocetakk;
        while(t != nullptr)
        {
            Cvor* sljedeci = t->sljedeci;
            delete t;
            t = sljedeci;
        }

        Cvor* stari = a.pocetakk;
        Cvor* zadnji = nullptr;
pocetakk = krajj = trenutnii = nullptr;
        while(stari != nullptr)
        {
            Cvor* novi = new Cvor{stari->element, nullptr,nullptr};
            if(!pocetakk) pocetakk = novi;
            else {zadnji->sljedeci = novi;
            novi->prethodni=zadnji;}
            zadnji = novi;

            if(stari == a.trenutnii) trenutnii = novi;

            stari = stari->sljedeci;
        }
        krajj = zadnji;
        duzina = a.duzina;

        return *this;
    }


    DvostrukaLista& operator=(DvostrukaLista&&a)
    {

 if(this != &a)
    {
        while(duzina) obrisi();
        duzina = a.duzina;
        pocetakk = a.pocetakk;
        krajj = a.krajj;
        trenutnii = a.trenutnii;
        a.duzina = 0;
        a.pocetakk = a.krajj = a.trenutnii = nullptr;
    }
    return *this;

    }
    DvostrukaLista(DvostrukaLista&&a)
    {
 duzina = 0;
    pocetakk = nullptr;
    krajj = nullptr;
    trenutnii = nullptr;

std::swap(pocetakk,a.pocetakk);
std::swap(krajj,a.krajj);
std::swap(duzina,a.duzina);
std::swap(trenutnii,a.trenutnii);

    };
    ~DvostrukaLista()
    {
        Cvor* t = pocetakk;
        while(t != nullptr)
        {
            Cvor* sljedeci = t->sljedeci;
            delete t;
            t = sljedeci;
        }
    };

friend class Iterator<Tip>;


};
template<typename Tip>
class Iterator
{

   typename  DvostrukaLista<Tip>::Cvor* tren;
  const DvostrukaLista<Tip>*lista;
    public:
      Iterator(const  DvostrukaLista<Tip>&  l) {
        lista = &l;//jer lista*
        tren = lista->pocetakk;
   };
    void pocetak() {         if (lista->brojElemenata()==0) throw std::domain_error("Prazna lista");
 tren = lista->pocetakk; }
    void kraj() {    if (lista->brojElemenata()==0) throw std::domain_error("Prazna lista");tren = lista->krajj; }
    bool sljedeci()
    {
         if (!tren || tren->sljedeci == nullptr) return false;
        tren= tren->sljedeci;
        return true;
    }
    bool prethodni()
    {
         if (!tren|| tren->prethodni == nullptr) return false;
        tren = tren->prethodni;
        return true;
    }
Tip& trenutni() const {
        if (!lista || !tren) throw std::domain_error("Prazna lista");
        return tren->element;
    }

};
void testKonstruktora()
{
    DvostrukaLista<int>a;
    a.dodajIspred(2);
    a.dodajIza(4);
    a.dodajIspred(9);
  DvostrukaLista<int>c(std::move(a));
    std::cout<<"nakon c(move(a)):  c:";            for(int i=0;i<c.brojElemenata();i++) std::cout << c[i] << " ";
std::cout<<"\n a: ";            for(int i=0;i<a.brojElemenata();i++) std::cout << a[i] << " ";
DvostrukaLista<int>h(c);
    std::cout<<"nakon h(c):  c:";            for(int i=0;i<c.brojElemenata();i++) std::cout << c[i] << " ";
std::cout<<"\n h: ";            for(int i=0;i<h.brojElemenata();i++) std::cout << h[i] << " ";

}
void testOpdodjele()
{
    DvostrukaLista<int>a;
    a.dodajIspred(2);
    a.dodajIza(4);
    a.dodajIspred(9);
    DvostrukaLista<int>b;
b=a;
    std::cout<<"a: ";
            for(int i=0;i<a.brojElemenata();i++) std::cout << a[i] << " ";
                std::cout<<"b: ";
            for(int i=0;i<b.brojElemenata();i++) std::cout << b[i] << " ";

DvostrukaLista<int>g;
g=std::move(b);
std::cout<<"nakon g(move(b)):  g:";            for(int i=0;i<g.brojElemenata();i++) std::cout << g[i] << " ";
std::cout<<"\n b: ";            for(int i=0;i<b.brojElemenata();i++) std::cout << b[i] << " ";
}
void testDodajIspred()
{
    DvostrukaLista<int>l;
    l.dodajIspred(1);l.pocetak();
    l.dodajIspred(2);
    l.dodajIspred(3);
        for(int i=0;i<l.brojElemenata();i++) std::cout << l[i] << " ";

}
    void testDodajIza() {
    DvostrukaLista<int> l;
    l.dodajIza(1);
    l.pocetak();
    l.dodajIza(3);
    l.pocetak();
    l.dodajIza(2);
    for(int i=0;i<l.brojElemenata();i++) std::cout << l[i] << " ";

}
void testObrisi() {
    DvostrukaLista<int> l;
    l.dodajIza(1);
    l.pocetak();
    l.dodajIza(2);
    l.dodajIza(3);
    l.pocetak();
    l.sljedeci();
    l.obrisi();
    for(int i=0;i<l.brojElemenata();i++) std::cout << l[i] << " ";
    std::cout<<std::endl;

}

void testNavigacije()
{
    DvostrukaLista<int> lista;

    try {
        lista.trenutni();
    } catch (const std::domain_error& e) {
        std::cout << "OK" << std::endl;
    }

    lista.dodajIspred(10);
    lista.dodajIza(20);
    lista.dodajIza(30);

    lista.pocetak();
    std::cout << lista.trenutni() << " ";

    lista.kraj();
    std::cout << lista.trenutni() << " ";

    lista.pocetak();


    std::cout << lista.prethodni() << " ";

    lista.kraj();
    std::cout << lista.sljedeci() << " ";
}

template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n)
{
    if (n.brojElemenata() == 0)
        throw std::domain_error("Prazna lista");
    const DvostrukaLista<Tip>& lista = dynamic_cast<const DvostrukaLista<Tip>&>(n);

    Iterator<Tip> it(lista);
    Tip maximum=it.trenutni() ;

    while (it.sljedeci()) {
        if (it.trenutni() > maximum) maximum = it.trenutni();
    }

    return maximum;
}
int main()
{testObrisi();std::cout<<"\n";
    testDodajIspred();
    testDodajIza();
    std::cout<<"\n";
    testKonstruktora();
        std::cout<<"\n";

    testOpdodjele();
    std::cout<<std::endl;
    testNavigacije();
DvostrukaLista<int> lista;
    lista.dodajIza(10);
    lista.dodajIza(5);
    lista.dodajIza(20);
    lista.dodajIza(155);

    try {
        int maxi = dajMaksimum(lista);
        std::cout << "Maksimum u ovoj listi je: " << maxi << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << "Greska: " << e.what() << std::endl;
    }    return 0;
}
