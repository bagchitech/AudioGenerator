#include "audiogenerator.h"

double frequency;
uint16_t duration;
double amplitude;
double *buffer;

/*Obtain user input frequency*/
void getAudioParameters(){
    printf("Enter frequency of the audio signal in Hertz:\n");
    scanf("%lf", &frequency);
    printf("Enter the duration in seconds:\n");
    scanf("%d",&duration);
    printf("Enter the volume:\n");
    scanf("%lf",&amplitude);

    generateSineWave(frequency, amplitude, duration);
}

void verifyAudioParameters(){
    if (frequency <= 0 || frequency > 20000){
        printf("Error: Invalid frequency %lf\n", frequency);
    } else {
        printf("The frequency input by the user is %lf\n", frequency);
    }
}

/*Sine Wave Generation*/
void generateSineWave(const double frequency, const double amplitude, const uint16_t duration){
    /*Figure out the number of samples*/
    uint32_t numSamples  = (uint32_t)(SAMPLE_RATE*duration);
    /*Create the buffer based on numSamples*/
    buffer = malloc(numSamples*sizeof(double));
    for(int n=0; n<numSamples;n++)
    {
        double time = (double)n/numSamples;
        buffer[n] = amplitude * sin(2*PI*frequency*time);
    }
    printf("Sine wave stored in buffer\n");
     
}