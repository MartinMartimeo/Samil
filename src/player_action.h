/* 
 * File:   player_action.h
 * Author: bastinat0r
 *
 */

#ifndef __PLAYER_ACTION_H
#define	__PLAYER_ACTION_H

/*
1 2 3

4 P 5

6 7 8

Number = direction

move = +0
hit = +10

*/

typedef enum {
    DoNothing = 0;

    Move_NW = 1,
    Move_N = 2,
    Move_NE = 3,
	Move_E = 5,
	Move_SE = 8,
	Move_S = 7,
	Move_SW = 6,
	Move_W = 4,

    Hit_NW = 11,
	Hit_N = 12,
	Hit_NE = 13,
	Hit_E = 15,
	Hit_SE = 18,
	Hit_S = 17,
	Hit_SW = 16,
	Hit_W = 14
} PlayerActionID;

typedef int PlayerAction;

#endif	/* __PLAYER_ACTION_H */
