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
#include "ki_interface.h"
#include "world.h"

class Game
{
public:
	Game();
	~Game();

	int LoadKI();	// Lädt eine KI in den KI-Vektor
	
	int InitWorld();	// Initialisierung der Welt
	
	int ProcessRound();		// Abarbeitung einer Spielrunde

private:
	//World m_world;	// Spielwelt
	
	std::vector<KI_Interface>* m_vKIs; // Liste mit SpielerKIs
};

#endif
