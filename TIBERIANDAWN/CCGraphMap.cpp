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

int CCGraphMap::getEdges(Edge edges[MAX_EDGES], int nodeId) const
{
	int numEdges = 0;
	int threat = 0;
	for (int i = 0; i < 8; ++i) {
		FacingType direction = (FacingType)i;
		CELL next = Adjacent_Cell((CELL)nodeId, direction);

		auto cost = mMoveable->Passable_Cell(next, direction, threat, mThreshhold);
		if (cost) {
			edges[numEdges].cost = cost;
			edges[numEdges].targetNodeId = next;
			++numEdges;
		}
	}

	return numEdges;
}
