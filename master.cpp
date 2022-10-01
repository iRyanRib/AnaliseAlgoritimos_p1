#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <ctime>
using namespace std;
// void imprime(string *vet, int tam);
void preenche( string *vet, int tam );
void bubble(string *vet, int tam);
void selection(string *vet, int tam);
void insertion(string *vet, int tam);
void shellSort(string *vet, int tam);
void quick(string *vet, int esq,int dir);
int particiona(string *vet,int esq, int dir);
void mergeIntercala(string *vet, string *aux,int ini, int meio,int fin);
void mergeDivide(string *vet, string *aux, int ini,int fin);
void merge(string *vet, int tam);
int main(int argc, char *argv[]){
    int tam ;
    int op = 0 ;
    while(op != 9 ){
        cout << "which the number of elemts do you want test:"<<endl;
        cin >> tam;
        string *vet = new string[tam];
        preenche(vet ,tam);
        // imprime(vet,tam);
        //etapa de escolha do algoritimo de ordenação
        
        cout << "which selection algorithm do you want to use"<<endl;
        cout << "1 - Bubble Sort\n";
        cout << "2 - Selection Sort\n";
        cout << "3 - Insertion Sort\n";
        cout << "4 - Shell Sort\n";
        cout << "5 - Merge Sort\n";
        cout << "6 - Quick Sort\n";
        cin >> op;
        //pegando o tempo inicio
        float tempo_ini, tempo_fin,tempo_ms;
        tempo_ini = (int)clock();//tempo anterior a chamada
        switch (op)
        {
        case 1:
            bubble(vet,tam);
            break;
        case 2:
            selection(vet,tam);
            break;
        case 3:
            insertion(vet,tam);
            break;
        case 4:
            shellSort(vet,tam);
            break;
        case 5:
            merge(vet,tam);
            break;
        case 6:
            quick(vet,0,tam-1);
            break;                 
        default:
            break;
        }
        tempo_fin = (int)clock();//pega o tempo final
        //calculo diferença do tempo em milissegundos
        tempo_ms = ((tempo_fin - tempo_ini)*1000/CLOCKS_PER_SEC);
        // imprime(vet,tam);
        cout << "Vetor de tamanho "<<tam<<" apos ordenacao"<<endl;
        cout << "Tempo gasto para ordenacao:"<<tempo_ms<<endl;

        delete vet;
    }
    return 0;
}
//armazenando as palavras nos vetores de String
// void imprime(string *vet, int tam){
//     for(int l = 0; l < tam; l ++){
//         cout << vet[l]<<endl;
//     }
// }
void preenche( string *vet, int tam ){
    string palavra;
    ifstream arq("aurelio40000.txt");//abre o arquivo
    if (arq.is_open()){//verifica se está aberto
       int k = 0;
        while(k < tam ){
            getline(arq, palavra);//pega linha do arquivo
            vet[k] = palavra;
            k++;               
        }
    }else{
        cout << "falha ao abrir arquivo!\n";
    }
}

//implementação dos métodos de ordenação a serem usados

// Após a primeira iteração, o maior elemento estará posicionado 
// na última posição do vetor: sua posição definitiva. Da mesma 
// forma, após cada uma das iterações seguintes
// O(n²)
void bubble(string *vet, int tam){
    string aux;
    // vveteduras
    for( int i = 0; i < tam; i++){
        //troca elementos
        for(int j = 0;j < tam -1-i; j++){
            if(vet[j+1] < vet[j]){//ordem trocada
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;//troca finalizada
            }
        }
    }
}
// Buscam, a cada iteração, o maior (ou menor) elemento 
// do vetor e o colocam na sua posição definitiva
//O(n²)
void selection(string *vet, int tam){
    string aux;
    int menor;
    //externo faz n-1 vveteduras
    for(int i =0; i < tam-1; i++){//tam -1 pq quando penultimo acha seu lugar o ultimo tbm
        menor = i;//inicialização
        //interno encontra menor
        for(int j = (i+1); j < tam; j++){
            if ( vet[j]< vet[menor]){
                menor = j;               
            }
        //troca menor elem com o da inicial i
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
        }
    }
}
// tomará cada elemento de um vetor não 
// ordenado e o inserirá exatamente no lugar devido 
// em outro vetor, sempre ordenado.
void insertion(string *vet, int tam){
    string aux;
    int j;  
    for(int k=1; k<tam; k++)   
    {  
        aux = vet[k];  
        j= k-1;  
        while(j>=0 && aux <= vet[j])  
        {  
            vet[j+1] = vet[j];   
            j = j-1;  
        }  
        vet[j+1] = aux;  
    }  
}
// Ao invés de comparar os elementos adjacentes, compara 
// elementos distantes, o que possibilita a movimentação mais 
// rápida dos elementos até suas posições corretas.
void shellSort(string *vet, int tam) {
  // Rearrange elements at each n/2, n/4, n/8, ... intervals
  for (int interval = tam / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < tam; i += 1) {
      string aux = vet[i];
      int j;
      for (j = i; j >= interval && vet[j - interval] > aux; j -= interval) {
        vet[j] = vet[j - interval];
      }
      vet[j] = aux;
    }
  }
}
// dividir uma dada lista em duas metades, 
// ordenar cada metade e fundir (merge) as metades ordenadas
//mais eficiente porém com gasto de memória
void merge(string *vet, int tam){
    string *aux = new string[tam];
    mergeDivide(vet,aux,0,tam-1);
}
void mergeDivide(string *vet, string *aux, int ini,int fin){
    int meio;

    if(fin > ini){
        meio = (fin+ini)/2;
        //divide problema em 2
        mergeDivide(vet,aux,ini,meio);
        mergeDivide(vet,aux,meio+1,fin);
        //intercala metades
        mergeIntercala(vet,aux,ini,meio+1,fin);
    }
}
void mergeIntercala(string *vet, string *aux,int ini, int meio,int fin){
    int atual,fimesq,tam;
    atual = ini;//indice atual no vetor aux - começa em ini
    fimesq = meio-1;//fim primeira metade
    tam = fin - ini +1;//tamanho vetor

    //intercala vetores,tiomando o elemento em ini ou meio,
    // até que uma das metades acabe
    while((ini <= fimesq) && (meio <=fin)){
        if(vet[ini]<=vet[meio]){
            aux[atual++] = vet[ini++];//recebe primeira metade
        }else{
            aux[atual++] = vet[meio++];//segunda metade
        }
    }
    while(ini <= fimesq){
        aux[atual++] = vet[ini++];
    }while(meio <= fin){
        aux[atual++] = vet[meio++];
    }
    for(int i = 0; i < tam; i++){
        vet[fin] = aux[fin];
        fin--;
    }
}
void quick(string *vet, int esq,int dir){
    if(esq<dir){//tem 2+ elem
        int pivo = particiona(vet,esq,dir);
        quick(vet,esq,pivo-1);//metade menor
        quick(vet,pivo+1,dir);//metade maior
    }
}
int particiona(string *vet,int esq, int dir){
    int i, j;
    string pivo,aux;
    i = esq; j = dir;
    pivo = vet[esq];

    while(i<j){
        while((vet[i] <= pivo)&&(i < dir)){
            i++;
        }
        while((vet[j]>= pivo) && (j > esq)){
            j--;
        }
        if(i < j){
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;            
        }
    }
    vet[esq] = vet[j];
    vet[j] = pivo;
    return j;
}