/* 
 * File:   world_map.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 22. Juni 2011, 19:12
 */

#pragma once
#ifndef WORLD_MAP_H
#define	WORLD_MAP_H

#include <vector>
using std::vector;

#include "world_field.h"

typedef vector< vector<WorldField> >::iterator    WorldMapIterator;
typedef vector<WorldField>                        WorldMapFields;
typedef vector<WorldField>::iterator              WorldMapFieldsIterator;
typedef vector< vector<WorldField> >              WorldMap;

#endif	/* WORLD_MAP_H */