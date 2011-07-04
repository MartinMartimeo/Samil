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

#include "ai_interface.h"

class WorldEntity {    
public:

    /**********************************************************************/
    // Konstruktor, Destruktor
    WorldEntity();
    virtual ~WorldEntity();


    /**********************************************************************/
    // Getter
    unsigned int GetId();
    unsigned int GetMaxId();

    unsigned int GetViewRange();
    unsigned int GetAttackRange();
    
    unsigned int GetPosX();
    unsigned int GetPosY();
    
    WorldEntityType GetType();
    
    unsigned int GetPlayer();
    
    unsigned int GetBp();
    unsigned int GetHealRate();
    unsigned int GetDamage();
    
    bool CanHeal();
    bool CanAttack();
    bool CanExplode();
    
    bool IsDead();
    
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
    
    void DecrBp(unsigned int iValue);
    void SetBp(unsigned int iValue);
    
    void IncrHitpoints(int iValue);
    void DecrHitpoints(int iValue);

private:



    unsigned int            m_iId;
    static unsigned int     c_iId;

    unsigned int            m_iPosX;
    unsigned int            m_iPosY;

    unsigned int            m_iPlayer;

    int                     m_iHitpoints;
    unsigned int            m_iMaxHitpoints;

    bool                    m_bCanHeal;
    unsigned int            m_iHealRate;

    bool                    m_bCanBomb;
    bool                    m_bCanAttack;

    unsigned int            m_iBp;
    unsigned int            m_iBpMax;

    unsigned int            m_iAttackRange;
    unsigned int            m_iDamage;
    unsigned int            m_iViewRange;

    WorldEntityType         m_eType;

};

typedef vector<WorldEntity>                        WorldEntities;

#endif	/* WORLD_ENTITY_H */

