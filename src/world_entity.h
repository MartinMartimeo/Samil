/* 
 * File:   world_entity.h
 * Author: martinmartimeo
 *
 * Created on 1. Juli 2011, 13:46
 */

#ifndef WORLD_ENTITY_H
#define	WORLD_ENTITY_H

#include <list>
using std::list;

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
    

private:



    unsigned int            m_iId;
    static unsigned int     c_iId;

};

typedef list<WorldEntity>                        WorldEntities;

#endif	/* WORLD_ENTITY_H */

