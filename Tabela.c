#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanho (4096 + 0.2 *4096) 
/*
Eu iria realizar as operações a cada leitura de linha, mas como o tempo de execução não será
avaliado, optei por realizar a leitura do arquivo e guardar en um vetor.*/

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



int main(void) {

}