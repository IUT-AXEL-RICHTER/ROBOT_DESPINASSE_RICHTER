#include <stdio.h>
#include <stdlib.h>
#include "ChipConfig.h"
#include "IO.h"
#include "xc.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"
#include "strategie.h"

int distance = 30; // distance en centimetre pour l'�clairage des LEDs uniquement
unsigned int* result;

int main(void) {

    InitOscillator();
    InitIO();
    InitTimer1();
    InitADC1();
    InitTimer23();
    InitTimer4();
    InitPWM();
    

    while (1) {
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();

            result = ADCGetResult();
            robotState.distanceTelemetreDroit = 34 / (((float) result[3])* 3.3 / 4096 * 3.2) - 5; //permet de convertir la valeur renvoy�e par le t�l�metre en metres 
            robotState.distanceTelemetreCentre = 34 / (((float) result[2])* 3.3 / 4096 * 3.2) - 5;
            robotState.distanceTelemetreGauche = 34 / (((float) result[0])* 3.3 / 4096 * 3.2) - 5;
            robotState.distanceTelemetreDroitExtreme = 34 / (((float) result[4])* 3.3 / 4096 * 3.2) - 5;
            robotState.distanceTelemetreGaucheExtreme = 34 / (((float) result[1])* 3.3 / 4096 * 3.2) - 5;
        }
        if (JACK) {
            if (robotState.distanceTelemetreGaucheExtreme < distance) { //la variable distanceTelemetreGauche provient de la fonction robotSate dans Robot.h
                LED_BLANCHE = 1;
                LED_BLEUE = 1;
                LED_ORANGE = 0;
            } else if (robotState.distanceTelemetreCentre < distance) {
                LED_BLANCHE = 0;
                LED_BLEUE = 1;
                LED_ORANGE = 0;
            } else if (robotState.distanceTelemetreDroit < distance) {
                LED_BLANCHE = 0;
                LED_BLEUE = 0;
                LED_ORANGE = 1;
            } else if (robotState.distanceTelemetreGauche < distance) {
                LED_BLANCHE = 1;
                LED_BLEUE = 0;
                LED_ORANGE = 0;
            } else if (robotState.distanceTelemetreDroitExtreme < distance) {
                LED_BLANCHE = 0;
                LED_BLEUE = 1;
                LED_ORANGE = 1;
            } else {
                LED_BLANCHE = 0;
                LED_BLEUE = 0;
                LED_ORANGE = 0;
            }
        } else {
            LED_BLANCHE = 0;
            LED_BLEUE = 0;
            LED_ORANGE = 0;
        }
    }
}

/*
Le 03/03/2020
Il manquait 1 r�sistance qui empechait le capteur droit extr�me de fonctionner
et une r�sistance qui entrainait une confusion entre le capteur centrale et le capteur extr�me gauche 
Le 04/03/2020
Nous avons essay� de mettre le OperatingSystemLoop dans le timer 1 car nous pensions que 
c'�tait le timer 4 qui ne fonctionnait pas cependant le robot ne roulait toujours pas donc le probl�me ne vient pas du timer
 Le 05/03/2020
 -On avait fais une erreur dans le PWM.c, on avait mis robotState.vitesseGaucheCommandeCourante = vitesseEnPourcents 
 au lieu de robotState.vitesseGaucheConsigne = vitesseEnPourcents.
 - Nous avons rajout� le jack en le d�finissant dans le main.h et comme nous l'a expliqu� le prof si le jack est "appuy�" le micro re�oit 1 donc les 3.3v
 et si le jack est relach� le micro est reli� � la masse avec la resistance de 10k et re�oit donc 0.
 ADC Gauche ne fonctionne plus il doit �tre cass�
 
 */