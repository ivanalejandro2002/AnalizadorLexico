#include <iostream>
#include <vector>
#include <cassert>
#include "TRIE.cpp"
using namespace std;

int main(int argc,char *argv[]){
    nodo_TRIE *arbol = new nodo_TRIE();
    int cantidadTokens=0;
    vector<string> reservadas = {"and","else","false","for","fun","if","null","or","print","return","true","var","while"};
    arbol->inicializa(cantidadTokens,reservadas);
    vector<string> simbolos = {"<","<=",">",">=", "!", "!=", "=", "==", "+","-","*","/","{","}","(",")",",",".",";"};
    arbol->inicializa(cantidadTokens, simbolos);
    arbol->saca_Tokens();
    for(int i =1;i<argc;i++){
        cout<<argv[i]<<"\n";
    }
}