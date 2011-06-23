/* 
 * File:   world_field.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 23. Juni 2011, 11:40
 */

#ifndef WORLD_FIELD_H
#define	WORLD_FIELD_H

typedef enum {
    FieldEmpty = '0',
    FieldTree = 'T',
    FieldStone = 'S',
    FieldSea = '~',
    FieldMountain = 'M',
    FieldUnkown = '?'
} WorldMapField;

class WorldField {
    friend class World;

public:

    /**********************************************************************/
    // Konstruktor, Destruktor

    WorldField();
    virtual ~WorldField();

    /**********************************************************************/
    // Getter

    WorldMapField GetType();
    int GetWeight();  


private:

    /**********************************************************************/
    // private Setter

    void SetType(WorldMapField iValue);
    void SetWeight(int iValue);

protected:

    WorldMapField       m_iType;

    int                 m_iWeight;

};

#endif	/* WORLD_FIELD_H */

