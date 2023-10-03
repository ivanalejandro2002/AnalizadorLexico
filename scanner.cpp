#include <iostream>
#include <vector>
#include <cassert>
#include "TRIE.cpp"
#include "automata.cpp"
using namespace std;

int main(int argc,char *argv[]){
    nodo_TRIE *arbol = new nodo_TRIE();
    nodo_TRIE *it = arbol;
    int cantidadTokens = 0;
    vector< string > reservadas = {"and","else","false","for","fun","if","null","or","print","return","true","var","while"};
    vector<string> simbolos = {"<","<=",">",">=", "!", "!=", "=", "==", "+","-","*","/","{","}","(",")",",",".",";"};
    vector<string> nombres = {"","and","else","false","for","fun","if","null","or","print","return","true","var","while","LT","LE","GT","GE","BANG","NE","EQ","EQD","SUM","SUB","MUL","DIV","CO","CC","PO","PC","COMA","DOT","SEMICOLON"};
    nombres.push_back("NUMERO");
    nombres.push_back("IDENTIFICADOR");
    arbol->inicializa(cantidadTokens , reservadas);
    arbol -> inicializa(cantidadTokens , simbolos);
    
    /*for(int i = 1; i < argc ; i++){
        cout << argv[i] << "\n";
    }*/
    arbol->pasito('/')->pasito('/')->trabado=1;
    arbol->pasito('/')->pasito('*')->trabado=2;
    arbol->pasito('*')->pasito('/')->trabado=3;
    cantidadTokens++;
    nodo_TRIE actual;
    arbol -> saca_Tokens();
    bool comentariote=0;
    if(argc>0){
        for(int i = 1; i < argc ;i++){
            comentariote = evalua(argv[i],arbol,cantidadTokens,nombres,comentariote);
        }
    }
}