/* 
 * File:   world_entity.h
 * Author: martinmartimeo
 *
 * Created on 1. Juli 2011, 13:46
 */

#ifndef WORLD_ENTITY_H
#define	WORLD_ENTITY_H

#include <vector>
using std::vector;

#include "ki_interface.h"

class WorldEntity {
    friend class World;
    
public:

    /**********************************************************************/
    // Konstruktor, Destruktor
    WorldEntity();
    virtual ~WorldEntity();


    /**********************************************************************/
    // Getter
    unsigned int GetId();
    unsigned int GetMaxId();
    

private:

    /**********************************************************************/
    // Setter
    void IncrId();
    void SetPlayer(unsigned int iPlayer);
    void DoRelive();

    void SetPosX(unsigned int iPosX);
    void SetPosY(unsigned int iPosY);

    void InitHealer();
    void InitTerroist();
    void InitWarrior();


    unsigned int            m_iId;
    static unsigned int     c_iId;

    unsigned int            m_iPosX;
    unsigned int            m_iPosY;

    unsigned int            m_iPlayer;

    unsigned int            m_iHitpoints;
    unsigned int            m_iMaxHitpoints;

    bool                    m_bCanHeal;
    unsigned int            m_iHealRate;

    bool                    m_bCanBomb;
    bool                    m_bCanAttack;

    unsigned int            m_iBP;
    unsigned int            m_iBPMax;

    unsigned int            m_iRange;
    unsigned int            m_iDamage;

    WorldEntityType         m_eType;

};

typedef vector<WorldEntity>                        WorldEntities;

#endif	/* WORLD_ENTITY_H */

