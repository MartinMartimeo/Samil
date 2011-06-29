/* 
 * File:   world_field.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 23. Juni 2011, 11:40
 */

#ifndef WORLD_FIELD_H
#define	WORLD_FIELD_H

typedef enum WorldMapField {
    FieldEmpty = '0',
    FieldTree = 'T',
    FieldStone = 'S',
    FieldSea = '~',
    FieldMountain = 'M',
    FieldUnkown = '?'
} WorldMapField;

typedef enum WorldFieldInformation {
    FieldBlocked = 0x1,
    FieldWay = 0x2,
    FieldFlag = 0x4,
    FieldWhite = 0x8,
    FieldGrey = 0x16,
    FieldBlack = 0x32
} WorldFieldInformation;

class WorldField;

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
    unsigned int GetDistance();
    WorldField& GetPreCursor();

    unsigned int GetPosX();
    unsigned int GetPosY();

    bool HasInformation(WorldFieldInformation fInformation);


private:

    /**********************************************************************/
    // private Setter

    void SetType(WorldMapField iValue);
    void SetDistance(unsigned int iValue);
    void SetWeight(int iValue);
    void SetPreCursor(WorldField& oPreCursor);

    void SetPosX(unsigned int iPosX);
    void SetPosY(unsigned int iPosY);

    void SetInformation(WorldFieldInformation fInformation);
    void UnSetInformation(WorldFieldInformation fInformation);

protected:

    WorldMapField           m_iType;

    WorldField*             m_pPreCursor;
    unsigned int            m_iDistance;
    int                     m_iWeight;

    WorldFieldInformation   m_fInformation;

    unsigned int            m_iPosX;
    unsigned int            m_iPosY;



};

#endif	/* WORLD_FIELD_H */

