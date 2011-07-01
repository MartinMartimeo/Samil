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

    unsigned int            m_iId;
    static unsigned int     c_iId;

    unsigned int            m_iPlayer;

};

typedef vector<WorldEntity>                        WorldEntities;

#endif	/* WORLD_ENTITY_H */

