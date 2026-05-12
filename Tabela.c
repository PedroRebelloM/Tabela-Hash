#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanho (4096 + 0.2 *4096) 
/*
Eu iria realizar as operações a cada leitura de linha, mas como o tempo de execução não será
avaliado, optei por realizar a leitura do arquivo e guardar em um vetor.*/
void retorna_vetor(char * caminho_arquivo, long long * vetor_destino) {
    char auxiliar[20];
    char cpfTratado[13];
    int indice = 0;
    FILE * arquivo = fopen(caminho_arquivo, "r");
    if(arquivo == NULL) {
        printf("O arquivo não pôde ser aberto.");
        return;
    }

    while(fscanf(arquivo, "%15s", auxiliar) == 1) {
        int contador = 0;
        for(int i = 0; auxiliar[i]!=0; i++){
            if (isdigit(auxiliar[i])) {
            cpfTratado[contador++] = auxiliar[i];
            }       
        }
        cpfTratado[contador] = '\0';
        vetor_destino[indice] = atoll(cpfTratado);
        indice++;
    }
    
    fclose(arquivo);
    return;
} 

int determinante(long long *vetor_cpfs, long long * vetor_verificadores) {
    int nove_digitos;
    int verificadores;
    for(int i =0; i<4096; i++) {
        nove_digitos = vetor_cpfs[i]/100;
        verificadores  = vetor_cpfs[i]%100;
        vetor_verificadores[i] = verificadores;
        a11 = (nove_digitos / 100000000) % 10;
        a12 = (nove_digitos / 10000000) % 10;
        a13 = (nove_digitos / 1000000) % 10;
        a21 = (nove_digitos / 100000) % 10;
        a22 = (nove_digitos / 10000) % 10;
        a23 = (nove_digitos / 1000) % 10;
        a31 = (nove_digitos / 100) % 10;
        a32 = (nove_digitos / 10) % 10;
        a33 = (nove_digitos / 1) % 10;
        det  = a11*a22*a33 + a12*a23*a31 + a13*a21*a32 -(a13*a22*a31 + a11*a23*a32 + a12*a21*a33); 
        if(det == 0) {
            det = a11*a22*a33 + (verificadores/10)*(verificadores%10);
        }
    } 
}

int main(void) {

}