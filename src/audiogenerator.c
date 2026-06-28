#include "audiogenerator.h"

double lfrequency;
double rfrequency;
int duration;
double amplitude;
double *lbuffer;
double *rbuffer;
int16_t *audio;


/*Obtain user input frequency*/
void getAudioParameters(){
    printf("Enter frequency of the audio signal for left ear in Hertz:\n");
    scanf("%lf", &lfrequency);
    printf("Enter frequency of the audio signal for right ear in Hertz:\n");
    scanf("%lf", &rfrequency);
    printf("Enter the duration in seconds:\n");
    scanf("%d",&duration);
    printf("Enter the volume:\n");
    scanf("%lf",&amplitude);

    generateSineWave(lfrequency, rfrequency, amplitude, duration);
}

void verifyAudioParameters(){
    if (lfrequency <= 0 || lfrequency > 20000){
        printf("Error: Invalid frequency %lf\n", lfrequency);
    } else {
        printf("The frequency input by the user is %lf\n", lfrequency);
    }
    if(duration<0){
        printf("Error:Invalid duration %d\n", duration);
    }
}

/*Sine Wave Generation*/
void generateSineWave(const double lfrequency, const double rfrequency, const double amplitude, const uint16_t duration){
    /*Figure out the number of samples*/
    uint32_t numSamples  = (uint32_t)(SAMPLE_RATE*duration);
    /*Create the buffer based on numSamples*/
    lbuffer = malloc(numSamples*sizeof(double));
    rbuffer = malloc(numSamples*sizeof(double));
    for(int n=0; n<numSamples;n++)
    {
        double time = (double)n / SAMPLE_RATE;
        lbuffer[n] = amplitude * sin(2*PI*lfrequency*time);
        rbuffer[n] = amplitude * sin(2*PI*rfrequency*time);
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
    return (int16_t)round(scaled);
}

void encodePCM(){
    uint32_t numSamples  = (uint32_t)(SAMPLE_RATE*duration);
    /*Create the buffer based on numSamples*/
    audio = malloc(2*numSamples*sizeof(int16_t));
    for(int n=0; n<numSamples;n++)
    {
        audio[(2*n)] = quantizeBits(lbuffer[n]);    
        audio[(2*n +1)] = quantizeBits(rbuffer[n]);   
    }
    free(lbuffer);
    free(rbuffer);
}

// void writeAudiotoFile(){
//     FILE *file_ptr = fopen("output.raw", "wb");
//     uint32_t numSamples  = (uint32_t)(SAMPLE_RATE*duration);
//     fwrite(audio, sizeof(int16_t), (2*numSamples), file_ptr);
//     fclose(file_ptr);
//     free(audio);
// }


void writeAudiotoFile(void) {
    uint32_t numSamples = (uint32_t)(SAMPLE_RATE * duration);
    uint16_t numChannels = 2;
    uint16_t bitsPerSample = 16;
    uint32_t dataSize = numSamples * numChannels * (bitsPerSample / 8);

    WavHeader header = {
        .riff          = {'R','I','F','F'},
        .fileSize      = 36 + dataSize,
        .wave          = {'W','A','V','E'},
        .fmt           = {'f','m','t',' '},
        .fmtChunkSize  = 16,
        .audioFormat   = 1,           // PCM
        .numChannels   = numChannels,
        .sampleRate    = SAMPLE_RATE,
        .byteRate      = SAMPLE_RATE * numChannels * (bitsPerSample / 8),
        .blockAlign    = numChannels * (bitsPerSample / 8),
        .bitsPerSample = bitsPerSample,
        .data          = {'d','a','t','a'},
        .dataSize      = dataSize,
    };

    FILE *file_ptr = fopen("output.wav", "wb");
    if (!file_ptr) {
        printf("Error: cannot open output.wav\n");
        return;
    }

    fwrite(&header, sizeof(WavHeader), 1, file_ptr);
    fwrite(audio, sizeof(int16_t), 2 * numSamples, file_ptr);

    fclose(file_ptr);
    free(audio);
}


void generateAudio(){
    getAudioParameters();
    verifyAudioParameters();
    encodePCM();
    writeAudiotoFile();
}