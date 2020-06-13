#include "CCGraphMap.h"
//#include "DEFINES.H"
//#include "FUNCTION.H"
#include "FOOT.H"

CCGraphMap::CCGraphMap(FootClass* moveable, MoveType threshhold)
	: GraphMap(MAP_CELL_W, MAP_CELL_H)
	, mMoveable(moveable)
	, mThreshhold(threshhold)
{

}

//typedef enum FacingType : char {
//	FACING_NONE = -1,
//	FACING_N,			// North
//	FACING_NE,			// North-East
//	FACING_E,			// East
//	FACING_SE,			// South-East
//	FACING_S,			// South
//	FACING_SW,			// South-West
//	FACING_W,			// West
//	FACING_NW,			// North-West
//
//	FACING_COUNT,			// Total of 8 directions (0..7).
//	FACING_FIRST = 0
//} FacingType;

int CCGraphMap::getEdges(Edge edges[MAX_EDGES], int nodeId) const
{
	int numEdges = 0;
	int threat = 0;
	int straight[4] = { 0, 2, 4, 6 };
	int diagonal[4] = { 1, 3, 5, 7 };
	unsigned char walkable[8];
	memset(walkable, 0, sizeof(walkable));

	// straight movements, which can be issued with no problems
	for (int i = 0; i < 4; ++i) {
		FacingType dir = (FacingType)straight[i];
		CELL next = Adjacent_Cell((CELL)nodeId, dir);

		auto cost = mMoveable->Passable_Cell(next, dir, threat, mThreshhold);
		if (cost) {
			walkable[dir] = 1;
			edges[numEdges].cost = cost*2;
			edges[numEdges].targetNodeId = next;
			++numEdges;
		}
	}
	// diagonal movements, which can only be issued if left AND right neighbors are walkable
	for (int i = 0; i < 4; ++i) {
		FacingType dir = (FacingType)diagonal[i];
		if (!(walkable[dir - 1] && walkable[dir + 1 % 8]))
			continue;

		CELL next = Adjacent_Cell((CELL)nodeId, dir);

		auto cost = mMoveable->Passable_Cell(next, dir, threat, mThreshhold);
		if (cost) {
			edges[numEdges].cost = cost * 3;
			edges[numEdges].targetNodeId = next;
			++numEdges;
		}
	}

	return numEdges;
}
