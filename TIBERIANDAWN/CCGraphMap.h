#pragma once
#include "GraphMap.h"
#include "FUNCTION.H"

class FootClass;

class CCGraphMap : public GraphMap
{
	FootClass*	mMoveable;
	MoveType	mThreshhold;
	int			mRisk;
public:
	CCGraphMap(FootClass* moveable, MoveType threshhold);

	virtual int getEdges(Edge edges[MAX_EDGES], int nodeId) const;
};

