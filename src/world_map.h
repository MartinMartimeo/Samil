/* 
 * File:   world_map.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 22. Juni 2011, 19:12
 */

#ifndef WORLD_MAP_H
#define	WORLD_MAP_H

#include <vector>
using std::vector;

typedef enum {
    FieldEmpty = '0',
    FieldTree = 'T',
    FieldStone = 'S',
    FieldSea = '~',
    FieldMountain = 'M',
    FieldUnkown = '?'
} WorldMapField;
typedef vector< vector<WorldMapField> >::iterator    WorldMapIterator;
typedef vector<WorldMapField>                        WorldMapRow;
typedef vector<WorldMapField>::iterator              WorldMapRowIterator;
typedef vector< vector<WorldMapField> >              WorldMap;

#endif	/* WORLD_MAP_H */

