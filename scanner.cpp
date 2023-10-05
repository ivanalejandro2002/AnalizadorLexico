#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "TRIE.cpp"
#include "automata.cpp"
#include "token.cpp"
using namespace std;

int main(int argc,char *argv[]){
    nodo_TRIE *arbol = new nodo_TRIE();
    token registro_Tokens = token();
    nodo_TRIE *it = arbol;
    int cantidadTokens = 0;
    vector< string > reservadas = {"and","else","false","for","fun","if","null","or","print","return","true","var","while"};
    vector<string> simbolos = {"<","<=",">",">=", "!", "!=", "=", "==", "+","-","*","/","{","}","(",")",",",".",";"};
    vector<string> nombres = {"","and","else","false","for","fun","if","null","or","print","return","true","var","while","LT","LE","GT","GE","BANG","NE","EQ","EQD","SUM","SUB","MUL","DIV","CO","CC","PO","PC","COMA","DOT","SEMICOLON"};
    nombres.push_back("NUMERO");
    nombres.push_back("IDENTIFICADOR");
    nombres.push_back("CADENA");
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
    //arbol -> saca_Tokens();
    bool existe_Error=0;
    bool comentariote = 0;
    if(argc>1){
        for(int i = 1; i < argc ;i++){
            existe_Error = evalua(argv[i],arbol,cantidadTokens,nombres,comentariote,registro_Tokens);
            if(existe_Error)continue;
            registro_Tokens.recorre();
        }
    }else{
        string lectura;
        while(1){
            getline(cin,lectura);
            existe_Error = evalua(lectura,arbol,cantidadTokens,nombres,comentariote,registro_Tokens);
            if(existe_Error)continue;
            registro_Tokens.recorre();
        }
    }
}