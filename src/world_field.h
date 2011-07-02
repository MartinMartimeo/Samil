/* 
 * File:   world_field.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 23. Juni 2011, 11:40
 */

#ifndef WORLD_FIELD_H
#define	WORLD_FIELD_H

#include "ki_interface.h"


typedef enum WorldFieldType {
    WorldFieldTypeUnkown = FieldUnkown,
    WorldFieldTypeEmpty = FieldEmpty,

    WorldFieldTypeTree = FieldTree,
    WorldFieldTypeStone = FieldStone,
    WorldFieldTypeSea = FieldSea,
    WorldFieldTypeMountain = FieldMountain
} WorldFieldType;


typedef enum WorldFieldInformation {
    WorldFieldInformationBlocked = 1,
    WorldFieldInformationWay = 2,
    WorldFieldInformationFlag = 4,
    WorldFieldInformationRecruit = 64,

    WorldFieldInformationWhite = 8,
    WorldFieldInformationGrey = 16,
    WorldFieldInformationBlack = 32
} WorldFieldInformation;



class WorldField;

class WorldField {
public:

    /**********************************************************************/
    // Konstruktor, Destruktor

    WorldField();
    virtual ~WorldField();
    
    /**********************************************************************/
    // Operatoren
    
    void Print();

    /**********************************************************************/
    // Getter

    WorldFieldType GetType();
    int GetWeight();
    unsigned int GetDistance();
    WorldField& GetPreCursor();

    unsigned int GetPosX();
    unsigned int GetPosY();

    bool HasInformation(WorldFieldInformation fInformation);

    /**********************************************************************/
    // private Setter

    void SetType(WorldFieldType iValue);
    void SetDistance(unsigned int iValue);
    void SetWeight(int iValue);
    void IncrWeight(int iValue);
    void SetPreCursor(WorldField& oPreCursor);

    void SetPosX(unsigned int iPosX);
    void SetPosY(unsigned int iPosY);

    void SetInformation(WorldFieldInformation fInformation);
    void UnSetInformation(WorldFieldInformation fInformation);


private:

protected:

    WorldFieldType          m_iType;

    WorldField*             m_pPreCursor;
    unsigned int            m_iDistance;
    int                     m_iWeight;

    WorldFieldInformation   m_fInformation;

    unsigned int            m_iPosX;
    unsigned int            m_iPosY;



};

#endif	/* WORLD_FIELD_H */

