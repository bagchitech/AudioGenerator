#pragma once

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include<stdint.h>
#include<math.h>
#include<stdio.h>


/*Audio Parameters*/
#define SAMPLE_RATE 44100 // Audio CD quality with 16 bit depth
#define PI 3.14
#define BIT_DEPTH 16

extern double frequency;



/*Obtain user input frequency*/
void getFrequency();

void verifyFrequency();

#endif // AUDIOGENERATOR_H