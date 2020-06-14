#ifndef ADC_H
#define	ADC_H

void InitADC1();
    void ADC1StartConversionSequence();
    unsigned char ADCIsConversionFinished();
    void ADCClearConversionFinishedFlag();
    unsigned int* ADCGetResult();

#endif

    
// RAPPEL : Dans les .h on déclare seulement les fonctions pas les variables