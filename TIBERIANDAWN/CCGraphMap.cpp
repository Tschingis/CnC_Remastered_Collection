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

	// straight movements, which can be issued with no problems
	for (int i = 0; i < FACING_COUNT; ++i) {
		FacingType dir = (FacingType)i;
		CELL next = Adjacent_Cell((CELL)nodeId, dir);

		auto cost = mMoveable->Passable_Cell(next, dir, threat, mThreshhold);
		if (cost) {
			edges[numEdges].cost = i % 2 ? cost * 3 : cost * 2; // if even -> straight movement, uneven -> diagonal movement
			edges[numEdges].targetNodeId = next;
			++numEdges;
		}
	}

	return numEdges;
}
