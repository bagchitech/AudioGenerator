#include "audiogenerator.h"

double frequency;

/*Obtain user input frequency*/
void getFrequency(){
    printf("Enter frequency of the audio signal in Hertz:");
    scanf("%lf", &frequency);
}

void verifyFrequency(){
    if (frequency <= 0 || frequency > 20000){
        printf("Error: Invalid frequency %lf\n", frequency);
    } else {
        printf("The frequency input by the user is %lf\n", frequency);
    }
}
