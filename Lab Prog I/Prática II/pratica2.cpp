#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <numeric>
#include <set>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <ctime>
#include <regex>
#include <queue>
using namespace std;

float randf()
{
    return (rand() % 30 - 15) / 100. + 1;
}

// good side *************
class Soldado
{
protected:
    string nome;
    float saude, poder;

public:
    Soldado(string nome, float saude = 30, float poder = 5) : nome(nome), saude(saude), poder(poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        inimigo.defender(*this);
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        saude -= (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100);
    }
    float getSaude() const
    {
        return saude;
    }
    string getName() const
    {
        return nome;
    }
    float getPoder() const
    {
        return poder;
    }

    void change_saude(float change)
    {
        saude -= change;
    }
};
class Elfo : public Soldado
{
public:
    Elfo(string nome, float saude = 30, float poder = 9) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        inimigo.defender(*this, 1);
        cout << this->getName() << " realizou um ATAQUE SIMPLES em " << inimigo.getName() << ".\n";
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        if (rand() % 100 < 90)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "O ataque de " << inimigo.getName() << " em " << this->getName() << " foi com FORCA MAXIMA!\n";
            cout << this->getName() << " perdeu " << perda << " de saude!\n";
        }
        else
        {
            float perda = (float)((inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) / 2) * randf();
            saude -= perda;
            cout << "O ataque de " << inimigo.getName() << " em " << this->getName() << " foi com PARCIALMENTE DEFENDIDO!\n";
            cout << this->getName() << " perdeu " << perda << " de saude!\n";
        }
    }
};
class Anao : public Soldado
{
public:
    Anao(string nome, float saude = 30, float poder = 5) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        if (rand() % 10 < 6)
        {
            inimigo.defender(*this, 20);
            cout << this->getName() << " realizou um ATAQUE SIMPLES em " << inimigo.getName() << ".\n";
        }
        else
        {
            cout << "Que vergonha! " << this->getName() << " ERROU o ataque em " << inimigo.getName() << ".\n";
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        if (rand() % 100 < 70)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "O ataque de " << inimigo.getName() << " em " << this->getName() << " foi com FORCA MAXIMA!\n";
            cout << this->getName() << " perdeu " << perda << " de saude!\n";
        }
        else
        {
            cout << "MUITO AGIL! " << this->getName() << " conseguiu DESVIAR do ataque!\n";
        }
    }
};
class Humano : public Soldado
{
public:
    Humano(string nome, float saude = 30, float poder = 8) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        if (rand() % 10 == 0)
        {
            cout << "ATAQUE DUPLO de " << this->getName() << " em " << inimigo.getName() << "!\n";
            cout << "1o ataque:\n";
            inimigo.defender(*this);
            cout << "2o ataque:\n";
        }
        else
        {
            cout << "ATAQUE SIMPLES de " << this->getName() << " em " << inimigo.getName() << "!\n";
        }
        inimigo.defender(*this);
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 90)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "O ataque de " << inimigo.getName() << " em " << this->getName() << " foi com FORCA MAXIMA!\n";
            cout << this->getName() << " perdeu " << perda << " de saude!\n";
        }
        else if (x % 100 == 99)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * 2 * randf();
            saude -= perda;
            cout << "MEU DEUS! O ataque de " << inimigo.getName() << " em " << this->getName() << " foi com ODIO!\n";
            cout << this->getName() << " perdeu " << perda << " de saude!\n";
        }
        if (saude > 0)
        {
            cout << "Como sempre, " << this->getName() << " CONTRA-ATACA!\n";
            inimigo.change_saude(poder);
            cout << inimigo.getName() << " perdeu " << poder << " de saude com o contra-ataque.\n";
        }
    }
};
// savior
class Bulcola : public Soldado
{
public:
    Bulcola(string nome, float saude = 500, float poder = 300) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        int x = rand();
        if (x % 100 < 90)
        {
            cout << "O SALVADOR " << this->getName() << "com seu fiel cachorro little Bob!! Eles se unem para atacar!\n";
            cout << inimigo.getName() << " lamenta.\n";
            cout << "1o ataque:\n";
            inimigo.defender(*this);
            cout << "2o ataque:\n";
            inimigo.defender(*this);
            float ganho = (float)(x % 100) * 1.5;
            saude += ganho;
            cout << "HEROI! " << this->getName() << " ainda RECUPEROU SAUDE!\n";
            cout << this->getName() << " recuperou " << ganho << " de saude.\n";
        }
        else
        {
            float perda = (float)(x % 100) * 1.5;
            saude -= perda;
            cout << this->getName() << " sacrificou " << perda << " de sua saude e ativou o modo temporario THE SAVIOR para seu leal cachorro little Bob virar o BIG BOB!\n";
            inimigo.defender(*this, (x % 100) * 2, 50);
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 5)
        {
            cout << "O ataque de " << inimigo.getName() << " foi VERGONHOSO! Ele escorregou! " << this->getName() << "esta gargalhando!\n";
            float ganho = (float)((inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) / 2) * randf();
            saude += ganho;
            cout << "Essas boas gargalhadas aumentaram em " << ganho << " a saude de " << this->getName() << endl;
        }
        else
        {
            cout << "O ataque de " << inimigo.getName() << " bateu com forca! " << this->getName() << "esta sangrando.\n";
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << this->getName() << " perdeu " << perda << " de saude\n";
            if (saude > 0)
            {
                cout << "E CONTRA-ATACA!\n";
                inimigo.change_saude(poder);
                cout << inimigo.getName() << " perdeu " << poder << " de saude com o contra-ataque.\n";
            }
        }
    }
};

class Mago : public Soldado
{
public:
    Mago(string nome, float saude = 50, float poder = 10) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        if (rand() % 20 < 1)
        {
            cout << "O mago, " << this->getName() << "com todos seus misterios fez sua MAGIA ESPECIAL contra " << inimigo.getName() << ".\n";
            cout << "Como de costume, seu ataque ricocheteou.\n";
            inimigo.defender(*this, 0, 500);
            this->defender(*this, -5);
        }
        else
        {
            cout << "Magia simples de " << this->getName() << " em " << inimigo.getName() << ".\n";
            inimigo.defender(*this);
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 93)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "O ataque bateu forte. A saude do " << this->getName() << " caiu " << perda << ".\n";
        }
        else
        {
            cout << "A magia dele eh incomparavel. DESVIOU DO ATAQUE E CONTRA-ATACA!\n";
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            inimigo.change_saude(perda);
            cout << inimigo.getName() << " perdeu " << perda << " de saude.\n";
        }
    }
};
// evil side **************
class Sauron : public Soldado
{
public:
    Sauron(string nome, float saude = 100, float poder = 8) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        if (rand() % 10 < 3)
        {
            cout << "ATAQUE DUPLAMENTE SOMBRIO de " << this->getName() << " em " << inimigo.getName() << "!\n";
            cout << "1o ataque:\n";
            inimigo.defender(*this);
            cout << "2o ataque:\n";
        }
        else
        {
            cout << "ATAQUE SOMBRIO de " << this->getName() << " em " << inimigo.getName() << "!\n";
        }
        inimigo.defender(*this);
    }

    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 80)
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "O poderoso Sauron foi atingido em cheio!\n";
            cout << this->getName() << " perdeu " << perda << " de saude.\n";
        }
        else if (x % 100 >= 80 and x % 100 < 90)
        {
            float perda = (float)((inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) / 1.5) * randf();
            saude -= perda;
            cout << "O poderoso Sauron defendeu parcialmente o ataque!\n";
            cout << this->getName() << " perdeu " << perda << " de saude.\n";
        }
        else
        {
            cout << "O poderoso Sauron fez " << inimigo.getName() << " de gato e sapato! DESVIOU E CONTRA-ATACOU!\n";
            inimigo.change_saude(poder);
            cout << inimigo.getName() << " sofreu com o poder do Sauron e perdeu " << poder << " de saude.\n";
        }
    }
};
class Orc : public Soldado
{
public:
    Orc(string nome, float saude = 30, float poder = 10) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        if (rand() % 10 < 2)
        {
            cout << "O leal ORC, " << this->getName() << ", com MUITA RAIVA, prepara o seu ATAQUE DUPLO ESPECIAL em " << inimigo.getName() << "!\n";
            cout << "1o ataque:\n";
            inimigo.defender(*this, 0, 10);
            cout << "2o ataque:\n";
            inimigo.defender(*this, 0, 10);
        }
        else
        {
            cout << "O leal ORC, " << this->getName() << ", parecendo um pouco cansado, prepara o seu simples ATAQUE DUPLO em " << inimigo.getName() << "!\n";
            cout << "1o ataque:\n";
            inimigo.defender(*this);
            cout << "2o ataque:\n";
            inimigo.defender(*this);
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 97)
        {
            cout << this->getName() << " foi atingido!\n";
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << this->getName() << " perdeu " << perda << " de saude.\n";
        }
        else
        {
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * 1.79 * randf();
            saude -= perda;
            cout << this->getName() << " foi atingido pelas costas e caiu de cara em uma pedra! Perdeu " << perda << " de saude\n";
            if (saude > 0)
            {
                cout << this->getName() << " odeia covardes! Esta enfurecido e ativou o modo DUPLA VINGANCA BRUTAL\n";
                float dano = (float)(this->getPoder() + 5) * (1 + (23 * 1.0) / 100) * randf();
                cout << "1a vinganca:\n";
                inimigo.change_saude(dano);
                cout << "2a vinganca:\n";
                inimigo.change_saude(dano);
            }
        }
    }
};
class Dromedario : public Soldado
{
public:
    Dromedario(string nome, float saude = 600, float poder = 230) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        int x = rand();
        if (x % 100 < 8)
        {
            cout << "O dromedario " << this->getName() << " acabou de beber uma aguinha e ta motivado.";
            cout << "Ganhou " << (x % 100) * 23 << " de saude.\n";
            saude += (x % 100) * 23;
        }
        cout << "O dromedario prepara o GOLPE DO TRIPLO CUSPE\n";
        cout << "1o cuspe:\n";
        inimigo.defender(*this, 0, 40);
        cout << "2o cuspe:\n";
        inimigo.defender(*this, 0, 40);
        cout << "3o cuspe:\n";
        inimigo.defender(*this, 0, 40);
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        int x = rand();
        if (x % 100 < 75)
        {
            cout << "O dromedario " << this->getName() << " teve sua duas corcovas atingidas! Agoniza de dor!\n";
            float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            saude -= perda;
            cout << "Perdeu " << perda << " de saude!\n";
        }
        else if (x % 100 >= 75 and x % 100 < 95)
        {
            cout << "O dromedario " << this->getName() << " teve uma de suas corcovas atingida! Agoniza de dor!\n";
            float perda = (float)((inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) / 2) * randf();
            saude -= perda;
            cout << "Perdeu " << perda << " de saude!\n";
        }
        else
        {
            cout << "O ataque de " << inimigo.getName() << " atingiu o dromedario " << this->getName() << "...\n";
            cout << "... Mas nao atingiu nenhuma corcova. O ataque foi refletido de volta e o dromedario vai beber um pouco de agua.\n";
            float ganho = (float)((inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) / 10) * randf();
            saude += ganho;
            cout << this->getName() << " GANHOU " << ganho << " de saude.\n";
            float dano = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
            inimigo.change_saude(dano);
            cout << inimigo.getName() << " PERDEU " << dano << " de saude.\n";
        }
    }
};
class Claviculario : public Soldado
{
public:
    Claviculario(string nome, float saude = 1300, float poder = 5) : Soldado(nome, saude, poder) {}
    virtual void atacar(Soldado &inimigo)
    {
        int x = rand();
        if (x % 100 < 5)
        {
            cout << "Claviculario " << this->getName() << " prepara o sacrificio para ABRIR O PORTAO DA ESCURIDAO!\n";
            cout << "O portao libera o monstro CHAVE GIGANTE que ataca o " << inimigo.getName() << ".\n";
            inimigo.defender(*this, 100, 200);
            cout << "O Claviculario perdeu 150 de saude com o sacrificio.\n";
            saude -= 150;
        }
        else
        {
            cout << "Claviculario " << this->getName() << " ataca o " << inimigo.getName() << " com um molho de chaves flamejantes\n";
            inimigo.defender(*this);
        }
    }
    virtual void defender(Soldado &inimigo, float bonus_add = 0, float bonus_mul = 0)
    {
        cout << "Claviculario " << this->getName() << " nao consegue se defender com suas chaves!\n";
        float perda = (float)(inimigo.getPoder() + bonus_add) * (1 + (bonus_mul * 1.0) / 100) * randf();
        saude -= perda;
        cout << "Claviculario perdeu " << perda << " de saude.\n";
        int x = rand();
        if (x % 100 < 60 and saude > 0)
        {
            cout << "Claviculario prepara seu molho de chaves flamejantes especiais para CONTRA-ATACAR!\n";
            inimigo.change_saude((poder + 50) * randf());
            cout << inimigo.getName() << " perdeu " << poder + 50 << " de saude.\n";
        }
    }
};

int main()
{
    srand(time(nullptr));
    cout << setprecision(2) << fixed;
    Orc orc1("Rokblorggor"), orc2("Wortsnaga"), orc3("Bagul"), orc4("Snaglak"), orc5("Naznob"), orc6("Orknack"), orc7("Mekuz"), orc8("Throdrok"), orc9("Wazgut"), orc10("Ugrag");
    Sauron sauron("Sauron");
    Mago gandalf("Gandalf");
    Anao anao1("Oriddaeg Leathermantle"), anao2("Rursumli Beastcoat"), anao3("Baghumli Brightdigger"), anao4("Babroug Axepike"), anao5("Nokhamli Plateriver");
    Humano humano1("Eutharic"), humano2("Eberwolf"), humano3("Theodoric"), humano4("Eraric"), humano5("Ricimer");
    Elfo elfo1("Khiiral Dorstina"), elfo2("Rennyn Sylmoira"), elfo3("Wyrran Qikian"), elfo4("Alinar Yllafaren"), elfo5("Gormer Valee");
    vector<Soldado *> tempg = {&gandalf, &anao1, &anao2, &anao3, &anao4, &anao5, &humano1, &humano3, &humano2, &humano4, &humano5, &elfo1, &elfo2, &elfo3, &elfo4, &elfo5};
    vector<Soldado *> tempe = {&orc1, &orc2, &orc3, &orc4, &orc5, &orc6, &orc7, &orc8, &orc9, &orc10, &sauron};
    vector<Soldado *> vg(0);
    vector<Soldado *> ve(0);
    queue<Soldado *> qg;
    queue<Soldado *> qe;

    int m = 0;
    while (!m)
    {
        std::cout << "\nEscolha a opcao:" << endl
                  << "a - Adicionar personagem" << endl
                  << "b - Ler de arquivo" << endl
                  << "c - Adicionar personagens default" << endl
                  << "d - Iniciar simulacao" << endl;
        char action;
        std::cin >> action;
        char side, modo;
        action = tolower(action);
        if (action == 'a')
        {
            std::cout << "\nEscolha o lado do personagem" << endl;
            std::cout << "a - Good" << endl
                      << "b - Evil" << endl;
            cin >> side;
            side = tolower(side);
            if (side == 'a')
            {
                std::cout << "\nDeseja personalizar os atributos ou usar o balanceamento padrao?\na - Padrao\nb - Personalizar" << endl;
                cin >> modo;
                modo = tolower(modo);
                if (modo == 'b')
                {
                    string cl, no;
                    float saude, ataque;
                    std::cout << "\n\nLista de classes:\nElfo\nAnao\nMago\nSavior\n\n\nEscolha a classe: ";
                    cout.flush();
                    cin >> cl;
                    transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                    if (cl[0] != 'e' and cl[0] != 'a' and cl[0] != 'm' and cl[0] != 's')
                    {
                        cout << "Classe invalida!" << endl;
                    }
                    else
                    {
                        cout << "\nEscolha a saude: ";
                        cout.flush();
                        cin >> saude;
                        cout << "\nEscolha o ataque: ";
                        cout.flush();
                        cin >> ataque;
                        cout << "\nEscolha o nome: ";
                        cout.flush();
                        getline(cin, no);
                        getline(cin, no);
                        if (cl[0] == 'e')
                        {
                            Elfo *temp = new Elfo(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'a')
                        {
                            Anao *temp = new Anao(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'm')
                        {
                            Mago *temp = new Mago(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Bulcola *temp = new Bulcola(no, saude, ataque);
                            vg.push_back(temp);
                        }
                    }
                }
                else if (modo == 'a')
                {
                    string cl, no;
                    float saude, ataque;
                    std::cout << "\n\nLista de classes:\nElfo\nAnao\nMago\nSavior\n\n\nEscolha a classe: ";
                    cout.flush();
                    cin >> cl;
                    transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                    if (cl[0] != 'e' and cl[0] != 'a' and cl[0] != 'm' and cl[0] != 's')
                    {
                        cout << "Classe invalida!" << endl;
                    }
                    else
                    {
                        cout << "\nEscolha o nome: ";
                        cout.flush();
                        getline(cin, no);
                        getline(cin, no);
                        if (cl[0] == 'e')
                        {
                            Elfo *temp = new Elfo(no);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'a')
                        {
                            Anao *temp = new Anao(no);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'm')
                        {
                            Mago *temp = new Mago(no);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Bulcola *temp = new Bulcola(no);
                            vg.push_back(temp);
                        }
                    }
                }
            }
            else if (side == 'b')
            {
                std::cout << "\nDeseja personalizar os atributos ou usar o balanceamento padrao?\na - Padrao\nb - Personalizar" << endl;
                cin >> modo;
                modo = tolower(modo);
                if (modo == 'b')
                {
                    string cl, no;
                    float saude, ataque;
                    std::cout << "\n\nLista de classes:\nOrc\nSauron\nDromedario\nClaviculario\n\nEscolha a classe: ";
                    cout.flush();
                    cin >> cl;
                    transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                    if (cl[0] != 'o' and cl[0] != 's' and cl[0] != 'd' and cl[0] != 'c')
                    {
                        cout << "Classe invalida!" << endl;
                    }
                    else
                    {
                        cout << "\nEscolha a saude: ";
                        cout.flush();
                        cin >> saude;
                        cout << "\nEscolha o ataque: ";
                        cout.flush();
                        cin >> ataque;
                        cout << "\nEscolha o nome: ";
                        cout.flush();
                        getline(cin, no);
                        getline(cin, no);
                        if (cl[0] == 'o')
                        {
                            Orc *temp = new Orc(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Sauron *temp = new Sauron(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'd')
                        {
                            Dromedario *temp = new Dromedario(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'c')
                        {
                            Claviculario *temp = new Claviculario(no, saude, ataque);
                            ve.push_back(temp);
                        }
                    }
                }
                else if (modo == 'a')
                {
                    string cl, no;
                    float saude, ataque;
                    std::cout << "\n\nLista de classes:\nOrc\nSauron\nDromedario\nClaviculario\n\nEscolha a classe: ";
                    cout.flush();
                    cin >> cl;
                    transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                    if (cl[0] != 'o' and cl[0] != 's' and cl[0] != 'd' and cl[0] != 'c')
                    {
                        cout << "Classe invalida!" << endl;
                    }
                    else
                    {
                        cout << "\nEscolha o nome: ";
                        cout.flush();
                        getline(cin, no);
                        getline(cin, no);
                        if (cl[0] == 'o')
                        {
                            Orc *temp = new Orc(no);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Sauron *temp = new Sauron(no);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'd')
                        {
                            Dromedario *temp = new Dromedario(no);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'c')
                        {
                            Claviculario *temp = new Claviculario(no);
                            ve.push_back(temp);
                        }
                    }
                }
            }
            else
            {
                std::cout << "Lado invalido" << endl;
            }
        }
        else if (action == 'b')
        {
            ifstream input;
            input.open("lotr.txt");
            if (input.is_open())
            {
                while (!input.eof())
                {
                    input >> side;
                    if (side == 'g')
                    {
                        string cl, no;
                        float saude, ataque;
                        input >> cl >> saude >> ataque;
                        input.seekg(sizeof(char), ios_base::cur);
                        getline(input, no);
                        transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                        if (cl[0] == 'e')
                        {
                            Elfo *temp = new Elfo(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'a')
                        {
                            Anao *temp = new Anao(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 'm')
                        {
                            Mago *temp = new Mago(no, saude, ataque);
                            vg.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Bulcola *temp = new Bulcola(no, saude, ataque);
                            vg.push_back(temp);
                        }
                    }
                    else if (side == 'e')
                    {
                        string cl, no;
                        float saude, ataque;
                        input >> cl >> saude >> ataque;
                        input.seekg(sizeof(char), ios_base::cur);
                        getline(input, no);
                        transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
                        if (cl[0] == 'o')
                        {
                            Orc *temp = new Orc(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 's')
                        {
                            Sauron *temp = new Sauron(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'd')
                        {
                            Dromedario *temp = new Dromedario(no, saude, ataque);
                            ve.push_back(temp);
                        }
                        else if (cl[0] == 'c')
                        {
                            Claviculario *temp = new Claviculario(no, saude, ataque);
                            ve.push_back(temp);
                        }
                    }
                }
            }
        }
        else if (action == 'c')
        {
            for (int i = 0; i < tempg.size(); i++)
            {
                vg.push_back(tempg[i]);
            }
            for (int i = 0; i < tempe.size(); i++)
            {
                ve.push_back(tempe[i]);
            }
        }
        else if (action == 'd')
        {
            m = 1;
        }
        else
        {
            std::cout << "Opcao invalida" << endl;
        }
    }
    random_shuffle(vg.begin(), vg.end());
    random_shuffle(ve.begin(), ve.end());
    while (true)
    {
        static int tamanho = vg.size() - 1;
        qg.push(vg[tamanho--]);
        if (tamanho < 0)
            break;
    }
    while (true)
    {
        static int tamanho = ve.size() - 1;
        qe.push(ve[tamanho--]);
        if (tamanho < 0)
            break;
    }
    int rodadas = 1;
    while (!qg.empty() and !qe.empty())
    {
        int i = min(qe.size(), qg.size());
        std::cout << "RODADA " << rodadas << "\n\n"
                  << endl;
        vector<string> deadg;
        vector<string> deade;
        while (i--)
        {
            int r = rand() % 2;
            Soldado *good = qg.front();
            Soldado *evil = qe.front();
            qg.pop();
            qe.pop();
            if (r == 0)
            {
                good->atacar(*evil);
            }
            else
            {
                evil->atacar(*good);
            }
            std::cout << "\nSaudes atuais:\n";
            if (good->getSaude() > 0)
            {
                qg.push(good);
                std::cout << good->getName() << ": " << good->getSaude() << "\n";
            }
            else
            {
                std::cout << good->getName() << " pereceu na batalha\n";
                deadg.push_back(good->getName());
            }
            if (evil->getSaude() > 0)
            {
                qe.push(evil);
                std::cout << evil->getName() << ": " << evil->getSaude() << "\n\n";
            }
            else
            {
                std::cout << evil->getName() << " pereceu na batalha\n\n";
                deade.push_back(evil->getName());
            }
        }
        if (deadg.size())
        {
            std::cout << "\n\nTributo aos herois caidos em batalha nesta rodada:";
            for (int i = 0; i < deadg.size(); i++)
            {
                cout << " " << deadg[i] << (i == deadg.size() - 1 ? "." : ",");
            }
            cout << endl;
        }
        if (deade.size())
        {
            std::cout << "\nVassalos do mal expurgados do campo de batalha nesta rodada:";
            for (int i = 0; i < deade.size(); i++)
            {
                cout << " " << deade[i] << (i == deade.size() - 1 ? "." : ",");
            }
            cout << endl;
        }
        if (!deade.size() and !deadg.size())
        {
            cout << "Os guerreiros restantes permanecem de pe e VIVOS!\n";
        }
        cout << endl;
        std::system("pause");
        std::cout << endl;
        rodadas++;
    }
    if (!qg.empty())
    {
        std::cout << left << setw(8) << "\n\nO" << left << setw(8) << "MAL" << left << setw(8) << "VENCEU!\n\n";
        qg.size() > 1 ? cout << qg.size() << " Sobreviventes: " : cout << 1 << " Sobrevivente: ";
        while (qg.size())
        {
            std::cout << qg.front()->getName() << (qg.size() == 1 ? "." : ",") << " ";
            qg.pop();
        }
    }
    else if (!qe.empty())
    {
        std::cout << left << setw(8) << "\n\nO" << left << setw(8) << "MAL" << left << setw(8) << "VENCEU!\n\n";
        qe.size() > 1 ? cout << qe.size() << " Sobreviventes: " : cout << 1 << " Sobrevivente: ";
        while (qe.size())
        {
            std::cout << qe.front()->getName() << (qe.size() == 1 ? "." : ",") << " ";
            qe.pop();
        }
    }
    else
    {
        std::cout << left << setw(10) << "\n\nTODOS" << left << setw(10) << "MORTOS\n\n";
        std::cout << "\n\nO CAMPO DE BATALHA SE ENCONTRA EM SILENCIO TOTAL, NAO SE VE UMA ALMA VIVA PERAMBULANDO POR ESSAS TERRAS (EMPATE)";
    }

    for (auto evil : ve)
    {
        delete evil;
    }
    ve.clear();
    for (auto good : vg)
    {
        delete good;
    }
    vg.clear();
    return 0;
}