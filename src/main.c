#include "audiogenerator.h"

int main(){
    int val;
    printf("Do you want to generate a chord(0) or a monotone(1)?\n");
    scanf("%d",&val);
    if(val==0){
        generateChord();
    }else if(val==1){
        generateAudio();
    }

    AudioInfo info = {0};
    generateSound(&info);
    return 0;
}