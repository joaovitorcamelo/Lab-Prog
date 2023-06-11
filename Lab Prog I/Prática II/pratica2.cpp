#include <bits/stdc++.h>
using namespace std;

class Soldado{
    protected:
        string nome;
        int saude, poder;
    public:
        Soldado(string nome, int saude=30, int poder=5): nome(nome), saude(saude), poder(poder){}
        virtual void atacar(Soldado &inimigo){
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
        }
        int getSaude() const{
            return saude;
        }
        string getName() const{
            return nome;
        }
};

class Elfo: public Soldado{
    public:
        Elfo(string nome, int saude=30, int poder=9): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            inimigo.defender(*this, 1);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            if(rand() % 100 < 90) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2; 
        }
};

class Anao: public Soldado{
    public:
        Anao(string nome, int saude=30, int poder=5): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 < 6) inimigo.defender(*this, 20);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            if(rand() % 100 < 70) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
        }
};

class Humano: public Soldado{
    public:
        Humano(string nome, int saude=30, int poder=8): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 == 0) inimigo.defender(*this);
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            int x = rand();
            if(x % 100 < 90) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 == 99) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) * 2; 
            this->atacar(inimigo);
        }
};

class Sauron: public Soldado{
    public:
        Sauron(string nome, int saude=300, int poder=8): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 < 3) inimigo.defender(*this);
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            int x = rand();
            if(x % 100 < 80) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 >= 80  and x % 100 < 90) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) / 1.5;

            inimigo.defender(*this, 0, 23);
        }
};

class Orc: public Soldado{
    public:
        Orc(string nome, int saude=30, int poder=10): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 < 2) {
                inimigo.defender(*this, 0, 10);
                inimigo.defender(*this, 0, 10);
            }
            else{
                inimigo.defender(*this);
                inimigo.defender(*this);
            }
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            int x = rand();
            if(x % 100 < 97) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else{
                saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) * 1.79;
                inimigo.defender(*this, 5, 23);
                inimigo.defender(*this, 5, 23);
            }
        }
};

class Mago: public Soldado{
    public:
        Mago(string nome, int saude=50, int poder=10): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%20 < 1) inimigo.defender(*this, 0, 500), this->defender(*this, -5);
            else inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            int x = rand();
            if(x % 100 < 93) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else{
                inimigo.defender(*this, (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100));
            }
        }
};

//evil
class Dromedario : public Soldado {
public:
    Dromedario(string nome, int saude = 600, int poder = 230) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo) {
        int x = rand();
        if(x % 100 < 3){
            saude += (x%100) * 23;
        }
        inimigo.defender(*this, 0, 40);
        inimigo.defender(*this, 0, 40);
        inimigo.defender(*this, 0, 40);
    }
    virtual void defender(Soldado &inimigo, int bonus_add=0, int bonus_mul=0){
            int x = rand();
            if(x % 100 < 75) saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 >= 75 and x % 100 < 95){
                saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2;
            }
            else {
                saude += (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) / 15;
                inimigo.defender(*this, (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100), 150);
            }
    }
};

//savior
class BulcTheBob : public Soldado {
public:
    BulcTheBob(string nome, int saude = 500, int poder = 300) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo){
        int x = rand();
        if(x % 100 < 90){
            inimigo.defender(*this);
            inimigo.defender(*this);
            saude += (int) (x % 100) * 1.5;
        }
        else{
            inimigo.defender(*this, (x % 100) * 2, 50);
            saude -= (int) (x % 100) * 1.5;
        }
    }
    virtual void defender(Soldado &inimigo, int bonus_add = 0, int bonus_mul = 0) {
        int x = rand();
        if(x % 100 < 5) {
            saude += (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2;
        }
        else {
            saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
            inimigo.defender(*this, 35);
        }
    }
};

//evil
class Claviculario : public Soldado {
public:
    Claviculario(string nome, int saude = 1300, int poder = 5) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo) {
        int x = rand();
        if (x % 100 < 2) {
            inimigo.defender(*this, 100, 200);
            saude -= 150;
        } 
        else inimigo.defender(*this);  
    }
    virtual void defender(Soldado &inimigo, int bonus_add = 0, int bonus_mul = 0){
        saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1.0)/100);
        int x = rand();
        if(x % 100 < 60) inimigo.defender(*this, 50);
    }
};


int main(){
    srand(time(nullptr));
    int n=2;
    Orc orc1("Rokblorggor"), orc2("Wortsnaga"), orc3("Bagul"), orc4("Snaglak"), orc5("Naznob"), orc6("Orknack"), orc7("Mekuz"), orc8("Throdrok"), orc9("Wazgut"), orc10("Ugrag");
    Sauron sauron("Sauron");
    Mago gandalf("Gandalf");
    Anao anao1("Oriddaeg Leathermantle"), anao2("Rursumli Beastcoat"), anao3("Baghumli Brightdigger"), anao4("Babroug Axepike"), anao5("Nokhamli Plateriver");
    Humano humano1("Eutharic"), humano2("Eberwolf"), humano3("Theodoric"), humano4("Eraric"), humano5("Ricimer");
    Elfo elfo1("Khiiral Dorstina"), elfo2("Rennyn Sylmoira"), elfo3("Wyrran Qikian"), elfo4("Alinar Yllafaren"), elfo5("Gormer Valee");
    //vector<Soldado*> v = {&orc1, &orc2, &orc3, &orc4, &orc5, &orc6, &orc7, &orc8, &orc9, &orc10, &sauron, &gandalf, &anao1, &anao2, &anao3, &anao4, &anao5, &humano1, &humano3, &humano2, &humano4, &humano5, &elfo1, &elfo2, &elfo3, &elfo4, &elfo5};
    vector<Soldado*> v = {&anao1, &orc1};
    int m = n;
    while(n>1){
        int p1 = rand()%m;
        while(v[p1]->getSaude()<=0) p1 = rand()%m;
        int p2 = rand()%m;
        while(v[p2]->getSaude()<=0 or p1 == p2) p2 = rand()%m;
        cout << v[p1]->getName() << " ataca " << v[p2]->getName() << "!" << endl;
        long double vida = v[p2]->getSaude();
        v[p1]->atacar(*v[p2]);
        cout << "Dano: " << vida - v[p2]->getSaude() << "  Vida Restante: " << v[p2]->getSaude() << endl;
        if(v[p2]->getSaude()<=0) n--;
    }
    for(int i=0;i<27;i++) if(v[i]->getSaude()>0) cout << v[i]->getName() << endl;
}