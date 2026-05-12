#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanho 4917

typedef struct CPF{
    long long cpf;
    int ocupado;
} Hash;

long long colisoes =0;

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

long long determinante(long long cpf_completo) {
    int a11,a12,a13,a21,a22,a23,a31,a32,a33,det;
    int nove_digitos;
    int verificadores;
    nove_digitos = cpf_completo/100;
    verificadores  = cpf_completo%100;
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
    return det
}

long long retorna_indice(long long det) {
    long long resultado = (det * 103) % tamanho;
    if(resultado < 0) {
        resultado += tamanho;
    }
    return (unsigned int)resultado;
}

void aloca(Hash * tabela_hash, long long cpf) {
    long long det = determinante(cpf);
    long long indice  = retorna_indice(determinante);

    while(tabela_hash[indice].ocupado) {
        colisoes++;
        indice = (indice + 1) % tamanho;
    }

    tabela_hash[indice].cpf = cpf;
    tabela_hash[indice].ocupado = 1;
}

int main(void) {
    Hash tabela[tamanho] = {0}; 
    long long lista_cpfs[4096];

    retorna_vetor("cpfs.txt", lista_cpfs);

    for(int i = 0; i < 4096; i++) {
        aloca(tabela, lista_cpfs[i]);
    }

    printf("Total de colisoes: %lld\n", colisoes);
    return 0;
}