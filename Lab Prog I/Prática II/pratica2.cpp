#include <bits/stdc++.h>
using namespace std;

//good side *************
class Soldado{
    protected:
        string nome;
        float saude, poder;
    public:
        Soldado(string nome, float saude=30, float poder=5): nome(nome), saude(saude), poder(poder){}
        virtual void atacar(Soldado &inimigo){
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
        }
        float getSaude() const{
            return saude;
        }
        string getName() const{
            return nome;
        }
        float getPoder() const{
            return poder;
        }
};
class Elfo: public Soldado{
    public:
        Elfo(string nome, float saude=30, float poder=9): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            inimigo.defender(*this, 1);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            if(rand() % 100 < 90) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2; 
        }
};
class Anao: public Soldado{
    public:
        Anao(string nome, float saude=30, float poder=5): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 < 6) inimigo.defender(*this, 20);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            if(rand() % 100 < 70) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
        }
};
class Humano: public Soldado{
    public:
        Humano(string nome, float saude=30, float poder=8): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 == 0) inimigo.defender(*this);
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            int x = rand();
            if(x % 100 < 90) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 == 99) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) * 2; 
            this->atacar(inimigo);
        }
};
//savior
class BulcTheBob : public Soldado {
public:
    BulcTheBob(string nome, float saude = 500, float poder = 300) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo){
        int x = rand();
        if(x % 100 < 90){
            inimigo.defender(*this);
            inimigo.defender(*this);
            saude += (float) (x % 100) * 1.5;
        }
        else{
            inimigo.defender(*this, (x % 100) * 2, 50);
            saude -= (float) (x % 100) * 1.5;
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0) {
        int x = rand();
        if(x % 100 < 5) {
            saude += (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2;
        }
        else {
            saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            inimigo.defender(*this, 35);
        }
    }
};
class Mago: public Soldado{
    public:
        Mago(string nome, float saude=50, float poder=10): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%20 < 1) inimigo.defender(*this, 0, 500), this->defender(*this, -5);
            else inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            int x = rand();
            if(x % 100 < 93) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else{
                inimigo.defender(*this, (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100));
            }
        }
};
//evil side **************
class Sauron: public Soldado{
    public:
        Sauron(string nome, float saude=300, float poder=8): Soldado(nome, saude, poder){}
        virtual void atacar(Soldado &inimigo){
            if(rand()%10 < 3) inimigo.defender(*this);
            inimigo.defender(*this);
        }
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            inimigo.defender(*this, 0, 23);
            int x = rand();
            if(x % 100 < 80) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 >= 80  and x % 100 < 90) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) / 1.5;
        }
};
class Orc: public Soldado{
    public:
        Orc(string nome, float saude=30, float poder=10): Soldado(nome, saude, poder){}
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
        virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            int x = rand();
            if(x % 100 < 97) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else{
                saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) * 1.79;
                inimigo.defender(*this, 5, 23);
                inimigo.defender(*this, 5, 23);
            }
        }
};
class Dromedario : public Soldado {
public:
    Dromedario(string nome, float saude = 600, float poder = 230) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo) {
        int x = rand();
        if(x % 100 < 3){
            saude += (x%100) * 23;
        }
        inimigo.defender(*this, 0, 40);
        inimigo.defender(*this, 0, 40);
        inimigo.defender(*this, 0, 40);
    }
    virtual void defender(Soldado &inimigo, float bonus_add=0, float bonus_mul=0){
            int x = rand();
            if(x % 100 < 75) saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
            else if(x % 100 >= 75 and x % 100 < 95){
                saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) / 2;
            }
            else {
                saude += (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100) / 15;
                inimigo.defender(*this, (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100), 150);
            }
    }
};
class Claviculario : public Soldado {
public:
    Claviculario(string nome, float saude = 1300, float poder = 5) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo) {
        int x = rand();
        if (x % 100 < 2) {
            inimigo.defender(*this, 100, 200);
            saude -= 150;
        } 
        else inimigo.defender(*this);  
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0){
        saude -= (float) (inimigo.getPoder() + bonus_add)*(1 + (bonus_mul*1.0)/100);
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
    vector<Soldado*> vg= {&gandalf, &anao1, &anao2, &anao3, &anao4, &anao5, &humano1, &humano3, &humano2, &humano4, &humano5, &elfo1, &elfo2, &elfo3, &elfo4, &elfo5};
    vector<Soldado*> ve = {&orc1, &orc2, &orc3, &orc4, &orc5, &orc6, &orc7, &orc8, &orc9, &orc10, &sauron};
    queue<Soldado*> qg;
    queue<Soldado*> qe;
    int m = 0;
    while(!m){
        cout << "escolha a opcao:" << endl << "a - adicionar personagem" << endl << "b - ler de arquivo" << endl << "c - iniciar simulacao" << endl ;
        char action;
        cin >> action;
        char side;
        string cl, no;
        float saude, ataque;
        if (action == 'a') {
            cout << "escolha o lado do personagem" << endl;
            cout << "a - good" << endl << "b - evil" << endl;
            if (side == 'a') {
                cout << "escolha a classe, nome, saude e ataque, separados por espaco\nLista de classes:\nElfo\nAnao\nMago\nSavior\n";
                cin >> cl >> no >> saude >> ataque; //checar tipos
                transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                if (cl[0] == 'e') {
                    Elfo temp(no, saude, ataque);
                    vg.push_back(&temp);
                } else if (cl[0] == 'a') {
                    Anao temp(no, saude, ataque);
                    vg.push_back(&temp);
                } else if (cl[0] == 'm') {
                    Mago temp(no, saude, ataque);
                    vg.push_back(&temp);
                } else if (cl[0] == 's') {
                    BulcTheBob temp(no, saude, ataque);
                    vg.push_back(&temp);
                } else {
                    cout << "classe invalida" << endl;
                }
            } else if (side == 'b') {
                cout << "escolha a classe, nome, saude e ataque, separados por espaco\nLista de classes:\nOrc\nSauron\nDromedario\nClaviculario\n";
                cin >> cl >> no >> saude >> ataque; //checar tipos
                transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                if (cl[0] == 'o') {
                    Orc temp(no, saude, ataque);
                    ve.push_back(&temp);
                } else if (cl[0] == 's') {
                    Sauron temp(no, saude, ataque);
                    ve.push_back(&temp);
                } else if (cl[0] == 'd') {
                    Dromedario temp(no, saude, ataque);
                    ve.push_back(&temp);
                } else if (cl[0] == 'c') {
                    Claviculario temp(no, saude, ataque);
                    ve.push_back(&temp);
                } else {
                    cout << "classe invalida" << endl;
                }
            } else {
                cout << "lado invalido" << endl;
            }
        } else if (action == 'b') {
            // leitura de arquivo
        } else if (action == 'c') {
            m = 1;
        } else {
            cout << "opcao invalida" << endl;
        }
    }
    random_shuffle(vg.begin(),vg.end());
    random_shuffle(vg.begin(),vg.end());
    while(vg.size()>0){
        qg.push(vg[vg.size()-1]);
        vg.pop_back();
    }
    while(ve.size()>0){
        qe.push(ve[ve.size()-1]);
        ve.pop_back();
    }
    int rodadas = 1;
    while(!qg.empty() and !qe.empty()){
        int i = min(qe.size(),qg.size());
        cout << "RODADA " << rodadas << endl;
        while(i--){
            int r = rand()%2;
            Soldado* good = qg.front();
            Soldado* evil = qe.front();
            qg.pop();
            qe.pop();
            if(r == 0){
                cout << good->getName() << " atacou " << evil->getName() << endl;
                good->atacar(*evil);
                //cout << " causando " << dano << " de dano\n"; ALTERAR PARA OS CASOS DE DEFESA, EVASAO, COUNTER
                cout << "Saudes atuais:\n" << good->getName() << ": " << good->getSaude() <<"\n"<< evil->getName() << ": " << evil->getSaude() << endl;
            }
            else {
                cout << evil->getName() << " atacou " << good->getName() << endl;
                evil->atacar(*good);
                //cout << " causando " << dano << " de dano\n"; ALTERAR PARA OS CASOS DE DEFESA, EVASAO, COUNTER
            cout << "Saudes atuais:\n" << good->getName() << ": " << good->getSaude() <<"\n"<< evil->getName() << ": " << evil->getSaude() << endl;
            }
            if(good->getSaude()>0)qg.push(good);
            if(evil->getSaude()>0)qe.push(evil);
        }
        rodadas++;
    }
    if(!qg.empty())cout << "\n\n\n\n\nO BEM VENCEU (CULPA DO BULCAO)";
    else if(!qe.empty())cout << "\n\n\n\n\nO MAL VENCEU (CULPA DO KEMEL)";
    else cout << "\n\n\n\n\nTODO MUNDO MORREU, A GUERRA NUNCA LEVA A NADA (CLAVICULARIO RINDO AO FUNDO)";
    return 0;
}