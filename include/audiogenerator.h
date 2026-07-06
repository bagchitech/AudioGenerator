#pragma once

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include<stdint.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>


/*Audio Parameters*/
#define SAMPLE_RATE 44100 // Audio CD quality with 16 bit depth
#define PI 3.14
#define BIT_DEPTH 16

extern double lfrequency;
extern double rfrequency;
extern double amplitude;
extern int duration;
extern double *lbuffer;
extern double *rbuffer;
extern int16_t *audio;
extern double lfreq[2];
extern double rfreq[2];

/*Struct to encompass the audio information*/
typedef struct { //kept in mind the memory optimization
    double amplitude;
    double *lbuffer;
    double *rbuffer;
    double lfreq[8];
    double rfreq[8];

    int16_t *audio;
    uint16_t numChannels;
    uint16_t bitsPerSample;

    int duration;
    int lnum;
    int rnum;
    uint32_t numSamples;
    
} AudioInfo;

#pragma pack(push, 1)
typedef struct {
    char     riff[4];           // "RIFF"
    uint32_t fileSize;          // total file size − 8
    char     wave[4];           // "WAVE"
    char     fmt[4];            // "fmt "
    uint32_t fmtChunkSize;      // 16 for PCM
    uint16_t audioFormat;       // 1 for PCM
    uint16_t numChannels;       // 1 mono, 2 stereo
    uint32_t sampleRate;        // 44100
    uint32_t byteRate;          // sampleRate * numChannels * bitsPerSample/8
    uint16_t blockAlign;        // numChannels * bitsPerSample/8
    uint16_t bitsPerSample;     // 16
    char     data[4];           // "data"
    uint32_t dataSize;          // numSamples * numChannels * bitsPerSample/8
} WavHeader;
#pragma pack(pop)

/*Obtain user input frequency*/
void getAudioParameters();

void verifyAudioParameters();

/*Sine Wave Calculation - Sample Stage - Followed Nyquist Rule*/
//Formula y(t) = A*sin(2*pi*f*t)
void generateSineWave(const double lfrequency, const double rfrequncy, const double amplitude, const uint16_t duration);

/*Quantization Stage - Bit depth 16 - To be called by encodePCM*/
int16_t quantizeBits(double sample);

/*Encode signal - PCM*/
void encodePCM(void);

/*Store audio in file*/
void writeAudiotoFile(void);

/*Function to act as mother function*/
void generateAudio(void);

/*Function for chord generation*/
void generateChord(void);

/*Function to generate WAV format audio file*/
void writeWAVFile(void);

/*Get Chord parameters*/
void getChordParameters(void);

/*generate sine wave for the chord*/
void generateChordSineWave(const double* lfreq, const double* rfreq, const double amplitude, const uint16_t duration);

/*Get parameters for the audio*/
void getAudioInfoParameters(AudioInfo *info);

/*generate audio sine wave*/
void generateAudioInfoSineWave(AudioInfo *info);

/*encode Audio Info PCB*/
void encodeAudioInfoPCM(AudioInfo *info);

/*write to the WAV file*/
void writeAudioInfoTofile(AudioInfo *info);

/*Wrapper function to be called*/
void generateSound(AudioInfo *info);

#endif // AUDIOGENERATOR_H
