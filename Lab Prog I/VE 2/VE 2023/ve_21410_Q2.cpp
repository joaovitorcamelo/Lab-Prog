#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdio.h>
#include <cstdlib>
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
using namespace std;

int randomType () {
    int x = rand();
    if(x % 100 < 10) return 2;
    if(x % 100 >= 10 and x % 100 < 30) return 1;
    return 0;
}

template <unsigned int T>
class Carta {

    template <unsigned int U>
    friend ostream& operator<<(ostream&, const Carta<U>&);

    private:
        string name;
        //0 -> comum  
        //1 ->  trunfo
        //2 -> super trunfo
        int tp;
        vector <float> valores;
    public:
        Carta <T> (string name = "", int tp = -1):name(name), tp(tp){
            for(int i = 0; i < T; i++){
                float valor = rand() / rand();
                while(valor >= 100) valor -= 100;
                valores.push_back(valor);
            }
        }
        int get_tp() const {
            return tp;
        }
        string get_name() const {
            return name;
        }
        vector <float> get_values() const {
            return valores;
        }

        const Carta <T>& operator>(const Carta <T>& oponente) const{
            if(tp > oponente.get_tp()) return *this;
            else if(tp < oponente.get_tp()) return oponente;

            vector <float> valores_oponente = oponente.get_values();
            cout << "As cartas: " << name << " e " << oponente.get_name() << " possuem os mesmo tipos.\n";
            cin.sync();
            int c;
            while(true){
                cout << "Defina a caracteristica de comparacao entre elas: (Valor entre 1 e " << T << "): ";
                cin >> c;
                if(c >= 1 and c <= T) break;
                else cout << "Insira um numero valido!\n";
            }
            c--;
            if(valores[c] >= valores_oponente[c]) return *this;
            return oponente;
        }
        
};

template <unsigned int T>
ostream& operator<<(ostream& output, const Carta<T>& carta){
    output << "Nome: " << carta.get_name() << endl;
    output << "Especializacao: " << T << endl;
    output << "Tipo: ";
    int tp = carta.get_tp();
    if(tp == 0) output << "Comum" << endl;
    else if(tp == 1) output << "Trunfo" << endl;
    else if(tp == 2) output << "SuperTrunfo" << endl;
    output << "Valores das caracteristicas: " << endl;
    vector <float> valores = carta.get_values();
    for(int i = 0; i < T; i++){
        output << "c" << i+1 << ":" << valores[i] << " ";
    }
    output << endl;
    return output;
}

int main(){
    srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector <Carta<6>> v1(4, Carta<6>());
    generate(v1.begin(), v1.end(), [n = 1, name = "Carta"]() mutable{
        string stArg = name + to_string(n);
        n++;
        return Carta <6>(stArg, randomType());
    });
    cout << (v1[1] > v1[2]);
    cout << v1[0];
    return 0;
}