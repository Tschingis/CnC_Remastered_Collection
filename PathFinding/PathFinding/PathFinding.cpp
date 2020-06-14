#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"

#include "ImageGraphMap.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "PathBuilder.h"
#include "DebugMap.h"
#include <chrono>

#define MAX_PATHLEN		255

int main()
{
	const char* mapFileName = "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1.png";
	const char* pathFileName= "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1_path.png";


	ImageGraphMap graph(mapFileName);
	DebugMap debug(pathFileName, &graph);

	Dijkstra costMap(&graph);

	//const int startNodeId = graph.getNodeId(30, 10);
	//const int endNodeId = graph.getNodeId(4, 50);
	const int startNodeId = graph.getNodeId(24, 53);
	const int endNodeId = graph.getNodeId(24, 53);
	//const int endNodeId = graph.getNodeId(49, 41);
	//const int endNodeId = graph.getNodeId(45, 0);

	auto start_time = std::chrono::high_resolution_clock::now();

	costMap.run(startNodeId, endNodeId);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	std::cout << "Costcomputation took " << time / std::chrono::microseconds(1) << " us";

	debug.writeCosts(costMap.getNodeDist());

	PathBuilder pathBuilder(costMap.getParentNodes());

	int path[MAX_PATHLEN];
	int pathLen= pathBuilder.build(path, MAX_PATHLEN, endNodeId);
	
	debug.writePath(path, pathLen);

	debug.writeToFile();
}

