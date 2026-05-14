#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanho 5009

typedef struct CPF{
    long long cpf;
    int ocupado;
} Hash;

long long colisoes =0;
long long insercoes = 0;

/*
Eu iria realizar as operações a cada leitura de linha, mas como o tempo de execução não será
avaliado, optei por realizar a leitura do arquivo e guardar em um vetor.*/
void retorna_vetor(char * caminho_arquivo, long long * vetor_destino) {
    char auxiliar[20];
    char cpf_tratado[13];
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
            cpf_tratado[contador++] = auxiliar[i];
            }       
        }
        cpf_tratado[contador] = '\0';
        vetor_destino[indice] = atoll(cpf_tratado);
        indice++;
    }
    
    fclose(arquivo);
    return;
} 

long long determinante(long long cpf_completo, int * verificador) {
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
        det = det ^ (verificadores * 31337);
    }
    *verificador = verificadores;
    return det;
}

unsigned long long mistura(unsigned long long numero) {
    numero ^= numero >> 33; // baseei esse método no murmurhash3
    numero *= 0xff51afd7ed558ccd;
    numero ^= numero >> 33;
    numero *= 0xc4ceb9fe1a85ec53;
    numero ^= numero >> 33;
    return numero;
}

long long retorna_indice(long long cpf) {
    int verificadores;
    long long det = determinante(cpf, &verificadores);
    unsigned long long hash_unida = det ^ cpf;
    unsigned long long hash = mistura(hash_unida);
    return hash % tamanho;
}

void aloca(Hash * tabela_hash, long long cpf, FILE * arquivo) {
    if (arquivo == NULL) {
        printf("O arquivo não pôde ser aberto.");
        return;
    }
    int verificadorAuxiliar;
    long long indice  = retorna_indice(cpf);

    if(tabela_hash[indice].ocupado) {
        unsigned long long semente_salto = cpf ^ 0x9e3779b9; // constante de fibonacci
        unsigned long long h2 = mistura(semente_salto);
        int salto = 1 + (h2 % (tamanho - 1));
        while(tabela_hash[indice].ocupado) {
            colisoes++;
            indice = (indice + salto) % tamanho;
        }
    }

    tabela_hash[indice].cpf = cpf;
    tabela_hash[indice].ocupado = 1;
    insercoes++;
    if(insercoes % 100 == 0) {
        printf("Insercoes: %lld\n", insercoes);
        printf("Colisoes: %lld\n", colisoes);
        fprintf(arquivo, "%lld; %lld\n", colisoes, insercoes);
    }
    if(insercoes == 4096) {
        printf("Insercoes: %lld\n", insercoes);
        printf("Colisoes: %lld\n", colisoes);
        fprintf(arquivo, "%lld; %lld\n", colisoes, insercoes);
    }
}

int main(void) {
    Hash *tabela = (Hash *)malloc(tamanho * sizeof(Hash));
    FILE * arquivo = fopen("dados.csv", "w");
    if (tabela == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    fprintf(arquivo, "Colisões; Inserções\n");
    for (int i = 0; i < tamanho; i++) {
        tabela[i].ocupado = 0;
        tabela[i].cpf = 0;
    }
    
    long long lista_cpfs[4096];

    retorna_vetor("cpfs.txt", lista_cpfs);

    for(int i = 0; i < 4096; i++) {
        aloca(tabela, lista_cpfs[i], arquivo);
    }

    printf("Total de colisoes: %lld\n", colisoes);
    free(tabela);
    fclose(arquivo);
    return 0;
}