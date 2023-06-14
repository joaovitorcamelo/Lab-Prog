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

template <typename T>
class vetorOrdenado {

    template <typename U>
    friend ostream& operator<<(ostream&, const vetorOrdenado<U>&);

    private:
        int maxsize;
        vector <T> lista;
    public:
        vetorOrdenado(int sz):maxsize(sz) {}

        vetorOrdenado& operator>>(string nomeDoArquivo) {
            ifstream arquivoEntrada(nomeDoArquivo);
            string linha;
            while(getline(arquivoEntrada, linha)){
                stringstream ss(linha);
                string elemento;
                while(getline(ss, elemento, ',') and lista.size() < maxsize){
                    stringstream converter(elemento);
                    T valor;
                    converter >> valor;
                    lista.push_back(valor);
                }
                sort(lista.begin(), lista.end());
            }
            return *this; 
        }

        int operator+(T valor){
            auto it = find(lista.begin(), lista.end(), valor);
            if(it != lista.end()) return (int)(it - lista.begin());
            return -1;
        }

        int operator-(T valor){
            auto it = lower_bound(lista.begin(), lista.end(), valor);
            if(it == lista.end()) return lista.size();
            return it - lista.begin();
        }
};

template <typename T>
ostream& operator<<(ostream& output, const vetorOrdenado<T>& vo){
    for(int i = 0; i < vo.lista.size(); i++){
        if(i != vo.lista.size() - 1) output << vo.lista[i] << ", ";
        else output << vo.lista[i] << "\n";
    }
    return output;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vetorOrdenado<int> vetor(10);
    vetor >> "./lista.txt";
    cout << vetor + 7 << endl;
    cout << vetor + 4 << endl;
    cout << vetor - 3 << endl;
    cout << vetor - 9 << endl;
    cout << vetor - 10 << endl;
    cout << vetor;

    return 0;
}


