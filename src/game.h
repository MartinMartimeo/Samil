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

#include<vector>
#include"ki_interface.h"

class Game
{
public:
	Game();
	~Game();

	int LoadKI();
	
	int InitWorld();
	
	int ProcessRound();

private:
	std::vector<KI_Interface>* m_vKIs;
};

#endif
