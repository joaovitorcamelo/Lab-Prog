#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <numeric>
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

bool cmp (pair<string, float> a, pair<string, float> b){
    return a.second < b.second;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector <string> names;
    map <string, vector<float>> notas;
    map <string, float> media;
    ifstream arquivoEntrada("alunos.txt");
    if(arquivoEntrada.is_open()){
        string nome;
        while(getline(arquivoEntrada, nome)){
            names.push_back(nome);
            ifstream arquivoNome(nome + ".txt");
            if(arquivoNome.is_open()){
                string nota;
                while(getline(arquivoNome, nota)){
                    stringstream in(nota);
                    float valor_nota = 0.0;
                    in >> valor_nota;
                    notas[nome].push_back(valor_nota);
                }
            }
            if(notas[nome].size()) media[nome] = 1.0*accumulate(notas[nome].begin(), notas[nome].end(), 0.0) / (int)(notas[nome].size());
            else media[nome] = 1.0 * accumulate(notas[nome].begin(), notas[nome].end(), 0);
            arquivoNome.close();
        }
    }
    arquivoEntrada.close();
    for(auto it = names.begin(); it != names.end(); it++){
        cout << "----------------------------------------------" << endl;
        cout << "Nome do aluno: " << *it << "\n";
        cout << "Notas do aluno: ";
        for(auto it2 = notas[*it].begin(); it2 != notas[*it].end(); it2++){
            cout << fixed << setprecision (3) << *it2 << " ";
        }
        cout << "\n";
        cout << "Media do aluno: " << fixed << setprecision(3) << media[*it] << "\n";
    }
    cout << "----------------------------------------------" << endl;

    auto it = max_element(media.begin(), media.end(), cmp);
    cout << "O aluno com maior media: " << it->first << "\n\n";

    cout << "Fim do programa.";
    return 0;
}