#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"

#include "GraphMap.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "PathBuilder.h"
#include <chrono>

#define MAX_PATHLEN		255

int main()
{
	const char* mapFileName = "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1.png";
	const char* pathFileName= "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1_path.png";

	int x, y, n;
	unsigned char *data = stbi_load(mapFileName, &x, &y, &n, 1);


	GraphMap graph(x, y, data);
	Dijkstra costMap(&graph);

	//const int startNodeId = graph.getNodeId(30, 10);
	//const int endNodeId = graph.getNodeId(4, 50);
	const int startNodeId = graph.getNodeId(24, 53);
	const int endNodeId = graph.getNodeId(49, 41);

	auto start_time = std::chrono::high_resolution_clock::now();

	costMap.run(startNodeId);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	std::cout << "Costcomputation took " << time / std::chrono::microseconds(1) << " us";

	const int* dists = costMap.getNodeDist();
	for (int i = 0; i < graph.getNumNodes(); ++i) {
		auto cost = dists[i] / 2;
		data[i] = cost > 255 ? 255 : cost;
	}

	PathBuilder pathBuilder(costMap.getParentNodes());

	int path[MAX_PATHLEN];
	int pathLen= pathBuilder.build(path, MAX_PATHLEN, endNodeId);

	for (int i = 0; i < pathLen; ++i) {
		data[path[i]] = 200;
	}

	stbi_write_png(pathFileName, x, y, 1, data, x);

	stbi_image_free(data);


}

