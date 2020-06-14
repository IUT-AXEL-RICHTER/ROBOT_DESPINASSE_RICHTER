#include <xc.h>
#include "IO.h"
#include "main.h"

void InitIO()
 {  // IMPORTANT : désactiver les entrées analogiques, sinon on perd les entrées numériques
    //RAPPEL: 1=entrée 0=sortie (Pour les entrées numériques)
    ANSELA = 0; // 0 desactive
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;
    _TRISC10 = 0;   // LED Orange
    _TRISG6 = 0;    //LED Blanche
    _TRISG7 = 0;    // LED Bleue
    _TRISB14 = 0;   //moteur gauche
    _TRISB15 = 0;
    _TRISC6 = 0;    //moteur droit
    _TRISC7 = 0;
    _TRISE13 = 1;   // Jack (sparrow)
    /*_TRISC0 = 1;    //capteur
    _TRISC11 = 1;   //capteur
    _TRISG9 = 1;    //capteur
    _TRISB1 = 1;    //capteur
    _TRISE15 = 1;   //capteur*/
}

