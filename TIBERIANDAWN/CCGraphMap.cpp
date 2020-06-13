#include "CCGraphMap.h"
#include "FOOT.H"

#define COSTSCALE_STRAIGHT		2
#define COSTSCALE_DIAGONAL		3
#define COSTSCALE_THREAT		1


CCGraphMap::CCGraphMap(FootClass* moveable, MoveType threshhold)
	: GraphMap(MAP_CELL_W, MAP_CELL_H)
	, mMoveable(moveable)
	, mThreshhold(threshhold)
{
	mRisk = (mMoveable->Team) ? mMoveable->Team->Risk : mMoveable->Risk();
}

int CCGraphMap::getEdges(Edge edges[MAX_EDGES], int nodeId) const
{
	int numEdges = 0;

	// straight movements, which can be issued with no problems
	for (int i = 0; i < FACING_COUNT; ++i) {
		FacingType dir = (FacingType)i;
		CELL next = Adjacent_Cell((CELL)nodeId, dir);

		// we set threat to -1 and build thread value into cost value
		auto cost = mMoveable->Passable_Cell(next, dir, -1, mThreshhold);
		if (cost) {
			// scale costs for different movement types
			cost= i % 2 ? cost * COSTSCALE_DIAGONAL : cost * COSTSCALE_STRAIGHT; // if even -> straight movement, uneven -> diagonal movement

			if (GameToPlay == GAME_NORMAL) {
				int cellThreat = Map.Cell_Threat(next, mMoveable->Owner());
				cellThreat *= COSTSCALE_THREAT;
				cellThreat -= mRisk;

				// only add positiv costs, otherwise dijstrak will freak out
				if (cellThreat > 0)
					cost += cellThreat;
			}

			edges[numEdges].cost = cost;
			edges[numEdges].targetNodeId = next;
			++numEdges;
		}
	}

	return numEdges;
}
