#include <stdio.h>
#include <time.h>

int main() {
    int opc=0;

    while(opc==0){
    time_t agora;
    time(&agora);

    struct tm *tempoLocal = localtime(&agora);

    // Extrai horas, minutos e segundos
    int horas = tempoLocal->tm_hour;
    int minutos = tempoLocal->tm_min;
    int segundos = tempoLocal->tm_sec;

    printf("Hora: %02d:%02d:%02d\n", horas, minutos, segundos);
}
    return 0;
}
