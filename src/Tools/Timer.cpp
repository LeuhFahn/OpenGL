#include "GLCommon.h"
#include "Timer.h"

CTimer::CTimer()
{
    m_nStartTicks = 0;
    m_nPausedTicks = 0;
    m_bPaused = false;
    m_bStarted = false;
}

void CTimer::start()
{
    m_bStarted = true;
    m_bPaused = false;
 
    //On récupére le temps courant
    m_nStartTicks = SDL_GetTicks();
}

void CTimer::stop()
{
    m_bStarted = false;
    m_bPaused = false;
}

int CTimer::getTicks()
{
    if( m_bStarted == true )
    {
        if( m_bPaused == true )
        {
            return m_nPausedTicks;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - m_nStartTicks;
        }
    }
 
    return 0;
}

void CTimer::pause()
{
    //Si le timer est en marche et pas encore en pause
    if( ( m_bStarted == true ) && ( m_bPaused == false ) )
    {
        m_bPaused = true;
        m_nPausedTicks = SDL_GetTicks() - m_nStartTicks;
    }
}

void CTimer::unpause()
{
    if( m_bPaused == true )
    {
        m_bPaused = false;
        m_nStartTicks = SDL_GetTicks() - m_nPausedTicks;
        m_nPausedTicks = 0;
    }
}

bool CTimer::isStarted()
{
    return m_bStarted;
}

bool CTimer::isPaused()
{
    return m_bPaused;
}