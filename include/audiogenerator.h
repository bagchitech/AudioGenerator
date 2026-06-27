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

//I want a pointer to the buffer that will be created


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
#endif // AUDIOGENERATOR_H