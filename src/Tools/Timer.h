#ifndef __TIMER_H
#define __TIMER_H

class CTimer
{
private:
    //Le temps quand le timer est lanc�
    int m_nStartTicks;
 
    //Le temps enregistr� quand le Timer a �t� mis en pause
    int m_nPausedTicks;
 
    //Le status du Timer
    bool m_bPaused;
    bool m_bStarted;
 
public:
    //Initialise les variables
    CTimer();
 
    //Les diff�rentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();
 
    //recup�re le nombre de millisecondes depuis que le timer a �t� lanc�
    //ou r�cup�re le nombre de millisecondes depuis que le timer a �t� mis en pause
    int getTicks();
 
    //Fonctions de v�rification du status du timer
    bool isStarted();
    bool isPaused();
};

#endif