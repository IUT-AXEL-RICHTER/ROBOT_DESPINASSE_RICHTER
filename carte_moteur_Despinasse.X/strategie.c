#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"
#include "strategie.h"

unsigned char nextStateRobot = 0;
unsigned char stateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;

    //Détermination de la position des obstacles en fonction des télémètres
    /*if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30)
        positionObstacle = OBSTACLE_A_DROITE;

    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 30)
        positionObstacle = OBSTACLE_A_GAUCHE;*/


    if (robotState.distanceTelemetreCentre < 25)
        positionObstacle = OBSTACLE_EN_FACE;

    else if (robotState.distanceTelemetreDroitExtreme > 20 &&
            robotState.distanceTelemetreDroit > 35 &&
            robotState.distanceTelemetreCentre > 50 &&
            robotState.distanceTelemetreGauche > 35 &&
            robotState.distanceTelemetreGaucheExtreme > 20)
        positionObstacle = PAS_D_OBSTACLE_PROCHE;

    else if (robotState.distanceTelemetreDroitExtreme > 10 &&
            robotState.distanceTelemetreDroit > 25 &&
            robotState.distanceTelemetreCentre > 20 && robotState.distanceTelemetreCentre < 50 &&
            robotState.distanceTelemetreGauche > 25 &&
            robotState.distanceTelemetreGaucheExtreme > 10)
        positionObstacle = PAS_D_OBSTACLE;

    else if (robotState.distanceTelemetreDroitExtreme < 40 &&
            robotState.distanceTelemetreDroit < 35 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreGaucheExtreme > 35)
        positionObstacle = OBSTACLE_A_DROITE;

    else if (robotState.distanceTelemetreDroitExtreme > 35 &&
            robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 35 &&
            robotState.distanceTelemetreGaucheExtreme < 40)
        positionObstacle = OBSTACLE_A_GAUCHE;

    //Détermination de l'état à venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == PAS_D_OBSTACLE_PROCHE)
        nextStateRobot = STATE_AVANCE_VITE;
    else if ((positionObstacle == OBSTACLE_A_DROITE))
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if ((positionObstacle == OBSTACLE_A_GAUCHE))
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
    else
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;

    if (nextStateRobot != stateRobot - 1)//Si l'on n'est pas dans la transition de l'étape en cours
        stateRobot = nextStateRobot;
}

void OperatingSystemLoop(void) {
    if (JACK) {
        if (timestamp > 2000) {
            switch (stateRobot) {
                case STATE_ATTENTE:
                    PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                    stateRobot = STATE_ATTENTE_EN_COURS;
                case STATE_ATTENTE_EN_COURS:
                        stateRobot = STATE_AVANCE;
                    break;
                case STATE_AVANCE:
                    PWMSetSpeedConsigne(8, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(8, MOTEUR_GAUCHE);
                    stateRobot = STATE_AVANCE_EN_COURS;
                    break;
                case STATE_AVANCE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                case STATE_AVANCE_VITE:
                    PWMSetSpeedConsigne(40, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(40, MOTEUR_GAUCHE);
                    LED_BLANCHE = 1;
                    LED_BLEUE = 1;
                    LED_ORANGE = 1;
                    stateRobot = STATE_AVANCE_VITE_EN_COURS;
                    break;
                case STATE_AVANCE_VITE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                case STATE_TOURNE_DROITE:
                    PWMSetSpeedConsigne(20, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(-5, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_DROITE_EN_COURS;
                    break;
                case STATE_TOURNE_DROITE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                case STATE_TOURNE_GAUCHE:
                    PWMSetSpeedConsigne(-5, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
                    break;
                case STATE_TOURNE_GAUCHE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;

                    //if ((timestamp % 2) == 0) {
                case STATE_TOURNE_SUR_PLACE_GAUCHE:
                    PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
                    break;
                case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                    //    } else {
                case STATE_TOURNE_SUR_PLACE_DROITE:
                    PWMSetSpeedConsigne(15, MOTEUR_DROIT);
                    PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
                    break;
                case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                    //    }
                default:
                    stateRobot = STATE_ATTENTE;
                    break;
            }
        }
    } else {
        timestamp = 0;
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        stateRobot = STATE_ATTENTE_EN_COURS;
    }
}