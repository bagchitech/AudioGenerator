#include "audiogenerator.h"

double frequency;
int duration;
double amplitude;
double *buffer;
int16_t *audio;


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
    if(duration<0){
        printf("Error:Invalid duration %d\n", duration);
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
    printf("Info:Sine wave stored in buffer\n");
     
}

/*Quantization Stage - Bit depth 16 - To be called by encodePCM*/
int16_t quantizeBits(double sample){
    double scaled = sample * 32767.0;
    if (scaled < -32768.0){
        scaled = -32768.0;
    }
    if(scaled > 32767.0){
        scaled = 32767.0;
    }
    return (int16_t)scaled;
}

void encodePCM(int16_t *audio){
    uint32_t numSamples  = (uint32_t)(SAMPLE_RATE*duration);
    /*Create the buffer based on numSamples*/
    audio = malloc(numSamples*sizeof(int16_t));
    for(int n=0; n<numSamples;n++)
    {
        audio[n] = quantizeBits(buffer[n]);       
    }
    free(buffer);
}

