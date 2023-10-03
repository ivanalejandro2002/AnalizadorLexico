#include<iostream>
#include<vector>
#include<ctype.h>
#include "TRIE.cpp"
using namespace std;
bool evalua(string &mens, nodo_TRIE *arbol,int cantidadTokens, vector<string> &nombres,bool comentariote){
    nodo_TRIE *it;
    for(int i = 0; i < mens.size() ; i++){
        if(comentariote){
            if(i<mens.size()-1 && mens[i]=='*' && mens[i+1]=='/'){
                comentariote=0;
            }
            i++;
            continue;
        }
        char caracter = mens[i];
        if(caracter==' ')continue;
        if(isalpha(caracter)){
            it = arbol;
            while( i < mens.size() && (isalpha(caracter) || isdigit(caracter))){
                cout<<caracter;
                i++;
                it = it -> pasito(caracter);
                caracter = mens[i];
            }
            cout<<":: Numero de Token: "<<it->asigna_Token(cantidadTokens+1)<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
        }else if(isdigit(caracter)){
            it = arbol;
            while(i< mens.size() && isdigit(caracter) ){
                cout<<caracter;
                i++;
                it = it->pasito(caracter);
                caracter = mens[i];
            }
            if(i>=mens.size())continue;
            if(caracter!='.' && caracter!='E'){
                i--;
                cout<<":: Numero de Token: "<<it->asigna_Token(cantidadTokens)<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
                continue;
            }
            if(caracter=='.'){
                cout<<".";
                it = it->pasito(caracter);
                i++;
                caracter = mens[i];
                if(i>=mens.size() || !isdigit(caracter)){
                    cout<<"Error: Los numeros deben tener fomrato D.DESD\nD=Digitos\nS=signo\n";
                    return 0;
                }
                while(i< mens.size() && isdigit(caracter)){
                    cout<<caracter;
                    i++;
                    it = it->pasito(caracter);
                    caracter = mens[i];
                }
            }

            if(i>=mens.size())continue;
            if(caracter!='E'){
                i--;
                cout<<":: Numero de Token: "<<it->asigna_Token(cantidadTokens)<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
                continue;
            }
            cout<<"E";
            it = it->pasito(caracter);
            i++;
            if(i>=mens.size()){
                cout<<":::Error: Los numeros deben tener fomrato D.DESD\nD=Digitos\nS=signo\n";
                return 0;
            }
            caracter = mens[i];
            if(caracter!='+' && caracter!='-' && caracter<'0' && caracter>'9'){
                i--;
                cout<<":: Numero de Token: "<<it->asigna_Token(cantidadTokens)<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
                continue;
            }
            if(caracter=='+' || caracter == '-'){
                cout<<caracter;
                it = it->pasito(caracter);
                i++;
                caracter = mens[i];
                if(i>=mens.size() || !isdigit(caracter)){
                    cout<<":::Error: Los numeros deben tener fomrato D.DESD\nD=Digitos\nS=signo\n";
                    return 0;
                }
            }
            while(i< mens.size() && isdigit(caracter)){
                cout<<caracter;
                i++;
                it = it->pasito(caracter);
                caracter = mens[i];
            }
            cout<<":: Numero de Token: "<<it->asigna_Token(cantidadTokens)<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
            if(i>=mens.size())continue;
            i--;
            continue;
        }else{
            it = arbol;
            if(it->mov_seguro(caracter)==nullptr){
                cout<<"No existe un operador que inicie con "<<caracter<<"\n";
                return 0;
            }
            string paso = "";
            while(i<mens.size() && it->mov_seguro(caracter)!=nullptr){
                paso+=caracter;
                it = it->mov_seguro(caracter);
                i++;
                caracter = mens[i];
                if(it->trabado==1)return 0;
                if(it->trabado==2){
                    comentariote=1;
                    continue;
                }
                if(it->trabado==3){
                    cout<<"::Error Para un comentario grande, debes de colocar /*comentario multilinea*/\n";
                    return 0;
                }
            }
            cout<<paso<<"::Numero de Token "<<it->token<<"; Tipo de Token: "<<nombres[it->token]<<"\n";
            if(i<mens.size())i--;
        }
    }
    return comentariote;
}
bool evalua(char *mens,nodo_TRIE *arbol,int cantidadTokens, vector<string> &nombres,bool comentariote){
    int i=0;
    string traductor = "";
    while(mens[i] != '\0')traductor += mens[i++];
    cout<<traductor<<"\n";
    return evalua(traductor,arbol,cantidadTokens,nombres,comentariote);
}