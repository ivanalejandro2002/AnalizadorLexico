#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
struct nodo_TRIE;
struct lista{
    int valor;
    lista *siguiente;
    lista(char v):valor(v),siguiente(nullptr){};
};
struct nodo_TRIE{
    int token;
    lista *elementos;
    lista *ultimo;
    vector<nodo_TRIE*> hijos;
    nodo_TRIE():token(0),elementos(new lista(1)),ultimo(elementos),hijos(vector<nodo_TRIE*>(256,nullptr)){};
};
void ingresa_token(nodo_TRIE *TRIE,string &cadena, int pos, int &cantidadTokens){
    if(pos==cadena.size()){
        if(TRIE->token){
            cantidadTokens--;
            return;
        }
        TRIE->token = cantidadTokens;
        return;
    }
    if(TRIE->hijos[(int)cadena[pos]]==nullptr){
        TRIE->hijos[(int)cadena[pos]]=new nodo_TRIE();
        TRIE->ultimo->siguiente=new lista(cadena[pos]);
        TRIE->ultimo = TRIE->ultimo->siguiente;
    }
    ingresa_token(TRIE->hijos[(int)cadena[pos]],cadena,pos+1,cantidadTokens);
}
void inicializa(nodo_TRIE *TRIE,int &cantidadTokens, vector<string> &tokens){
    for(string lectura: tokens)
        ingresa_token(TRIE,lectura,0,++cantidadTokens);
}
vector<char> construyo;
void saca_Tokens(nodo_TRIE *actual){
    if(actual->token){
        cout<<actual->token<<",";
        for(char co: construyo)cout<<co;
        cout<<"\n";
    }
    lista *it = actual->elementos;
    while(it!=nullptr){
        it = it->siguiente;
        if(it==nullptr)continue;
        construyo.push_back(it->valor);
        saca_Tokens(actual->hijos[(int)it->valor]);
    }
    construyo.pop_back();
}
int main(int argc,char *argv[]){
    nodo_TRIE *TRIE = new nodo_TRIE();
    int cantidadTokens=0;
    vector<string> reservadas = {"and","else","false","for","fun","if","null","or","print","return","true","var","while"};
    inicializa(TRIE,cantidadTokens,reservadas);
    vector<string> simbolos = {"<","<=",">",">=", "!", "!=", "=", "==", "+","-","*","/","{","}","(",")",",",".",";"};
    inicializa(TRIE, cantidadTokens, simbolos);
    saca_Tokens(TRIE);
    for(int i =1;i<argc;i++){
        cout<<argv[i]<<"\n";
    }
}