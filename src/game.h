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

#include "ki_interface.h"
#include "world.h"
#include "ki_handle.h"

class Game
{
public:
	Game(int height, int width);
	~Game();

	int LoadKI(std::string sKIPath);	// Lädt eine KI in den KI-Vektor
	
	int InitWorld(int width, int heigth);	// Initialisierung der Welt
	
	int ProcessRound();		// Abarbeitung einer Spielrunde

    World* GetWorldPointer();

private:
	World *m_pWorld;	// Spielwelt
	PlayerAction GetPlayerAction(KIHandle kiHandle, WorldMap const & view);
	std::vector<KIHandle> *m_pvKIs; // Liste mit SpielerKIs
};
#endif
