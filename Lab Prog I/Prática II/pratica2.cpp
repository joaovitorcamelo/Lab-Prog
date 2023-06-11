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
            saude -= (int) (inimigo.poder + bonus_add)*(1 + (bonus_mul*1,0)/100);
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
        void atacar(Soldado &inimigo) override{
            inimigo.defender(*this, 1);
        }
};

class Anao: public Soldado{
    public:
        Anao(string nome, int saude=30, int poder=5): Soldado(nome, saude, poder){}
        void atacar(Soldado &inimigo) override{
            if(rand()%10 < 6) inimigo.defender(*this, 20);
        }
};

class Humano: public Soldado{
    public:
        Humano(string nome, int saude=30, int poder=8): Soldado(nome, saude, poder){}
        void atacar(Soldado &inimigo) override{
            if(rand()%10 == 0) inimigo.defender(*this);
            inimigo.defender(*this);
        }
};

class Sauron: public Soldado{
    public:
        Sauron(string nome, int saude=300, int poder=8): Soldado(nome, saude, poder){}
        void atacar(Soldado &inimigo) override{
            if(rand()%10 < 3) inimigo.defender(*this);
            inimigo.defender(*this);
        }
};

class Orc: public Soldado{
    public:
        Orc(string nome, int saude=30, int poder=10): Soldado(nome, saude, poder){}
        void atacar(Soldado &inimigo) override{
            if(rand()%10 < 2) {
                inimigo.defender(*this, 0, 10);
                inimigo.defender(*this, 0, 10);
            }
            else{
                inimigo.defender(*this);
                inimigo.defender(*this);
            }
        }
};

class Mago: public Soldado{
    public:
        Mago(string nome, int saude=50, int poder=10): Soldado(nome, saude, poder){}
        void atacar(Soldado &inimigo){
            if(rand()%20 < 1) inimigo.defender(*this, 0, 500), this->defender(*this, -5);
            else inimigo.defender(*this);
        }
};

class CameloDeFogo : public Soldado {
public:
    CameloDeFogo(string nome, int saude = 30, int poder = 7) : Soldado(nome, saude, poder) {}
    void atacar(Soldado &inimigo) override {
        inimigo.defender(*this, 2);  
    }
};

class Bulcola : public Soldado {
public:
    Bulcola(string nome, int saude = 35, int poder = 6) : Soldado(nome, saude, poder) {}
    void defender(Soldado &inimigo, int bonus_add = 0, int bonus_mul = 0) override {
        if (rand() % 10 < 4) { 
            //defesa realizada
        } else {
            int dano = rand() % 5 + 1;  
            saude -= dano;
        }
    }
};

class Claviculario : public Soldado {
public:
    Claviculario(string nome, int saude = 25, int poder = 9) : Soldado(nome, saude, poder) {}
    void atacar(Soldado &inimigo) override {
        if (rand() % 10 < 2) {
            inimigo.defender(*this, 0, 10);  
            inimigo.defender(*this, 0, 10);  
        } else {
            inimigo.defender(*this);  
        }
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