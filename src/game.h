#pragma once
#ifndef __game_h
#define __game_h

/*
 * Klasse Game,
 * führt das update der Welt durch,
 * verwaltet und lädt Spielerkis.
 *
 * Author: bastinat0r
 *
 */

#include <vector>
#include <string>

#include "ai_interface.h"
#include "world.h"
#include "ki_handle.h"
#include "statistics.h"

class Game
{
public:
    /*******************************************************/
    // Constructors, Desructors
    Game(int height, int width);
    Game();                 // Game without World for testing
    ~Game();
    
    /********************************************************/
    // public methods
	int LoadKI(std::string sKIPath);	// Lädt eine KI in den KI-Vektor
	int LoadKI();	                    // Pfad Manuell eingeben
	
	int InitWorld(int width, int heigth);	// Initialisierung der Welt
	
	int ProcessRound();		// Abarbeitung einer Spielrunde
    int ProcessRound(int iRoundNum);

    World* GetWorldPointer();   // Gibt den Zeiger auf die Erstellte Spielwelt zurück.

private:
	int iRoundCount;
    World *m_pWorld;	// Spielwelt
	PlayerAction GetPlayerAction(KIHandle kiHandle, WorldMapView const &vvView, WorldEntityInformation const uEntityInformation);
	std::vector<KIHandle> *m_pvKIs; // Liste mit SpielerKIs
    Statistics *m_pStats;

    int ProcessPlayerAction(PlayerAction iPlayerAction, unsigned int iEntity);
};
#endif
