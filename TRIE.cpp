
#include <iostream>
#include <vector>
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
    void ingresa_token(string &cadena, int pos, int &cantidadTokens){
        if(pos==cadena.size()){
            if(token){
                cantidadTokens--;
                return;
            }
            token = cantidadTokens;
            return;
        }
        if(hijos[(int)cadena[pos]]==nullptr){
            hijos[(int)cadena[pos]]=new nodo_TRIE();
            ultimo->siguiente=new lista(cadena[pos]);
            ultimo = ultimo->siguiente;
        }
        this->hijos[(int)cadena[pos]]->ingresa_token(cadena,pos+1,cantidadTokens);
    }
    void dfs(vector<char> &construyo){
        if(token){
            cout<<token<<",";
            for(char co: construyo)cout<<co;
            cout<<"\n";
        }
        lista *it = elementos;
        while(it!=nullptr){
            it = it->siguiente;
            if(it==nullptr)continue;
            construyo.push_back(it->valor);
            hijos[(int)it->valor]->dfs(construyo);
        }
        construyo.pop_back();
    }
    void saca_Tokens(){
        vector<char> construyo;
        this->dfs(construyo);
    }
    void inicializa(int &cantidadTokens, vector<string> &tokens){
        for(string lectura: tokens)
            this->ingresa_token(lectura,0,++cantidadTokens);
    }
};

