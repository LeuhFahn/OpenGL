#ifndef __TIMER_H
#define __TIMER_H

class CTimer
{
private:
    //Le temps quand le timer est lancé
    int m_nStartTicks;
 
    //Le temps enregistré quand le Timer a été mis en pause
    int m_nPausedTicks;
 
    //Le status du Timer
    bool m_bPaused;
    bool m_bStarted;
 
public:
    //Initialise les variables
    CTimer();
 
    //Les différentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();
 
    //recupére le nombre de millisecondes depuis que le timer a été lancé
    //ou récupére le nombre de millisecondes depuis que le timer a été mis en pause
    int getTicks();
 
    //Fonctions de vérification du status du timer
    bool isStarted();
    bool isPaused();
};

#endif