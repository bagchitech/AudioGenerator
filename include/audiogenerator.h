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

extern double frequency;
extern double amplitude;
extern int duration;

//I want a pointer to the buffer that will be created


/*Obtain user input frequency*/
void getAudioParameters();

void verifyAudioParameters();

/*Sine Wave Calculation*/
//Formula y(t) = A*sin(2*pi*f*t)
void generateSineWave(const double frequency, const double amplitude, const uint16_t duration);

#endif // AUDIOGENERATOR_H