#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;
//armazenando as palavras nos vetores de String
int main(){
    string palavra;
    string aux;
    string vet1[10] ;
    ifstream arq("teste.txt");//abre o arquivo
    if (arq.is_open()){//verifica se está aberto
       int count = 0;
       int k = 0;
        while( getline(arq, palavra) ){//pega linha do arquivo
            if (k ==9){
                break;
            }
            vet1[k] = palavra;
            k++;               
        }
        // cout <<palavra<<endl;


        for(int r = 0; r<6 ;r++){
            cout<<vet1[r]<<endl;
        }

    }else{
        cout << "falha ao abrir arquivo!\n";
    }
    return 0;
}
//implementação dos métodos de ordenação a serem usados

