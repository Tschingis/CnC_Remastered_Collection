#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"

#include "GraphMap.h"
#include "BFS.h"
#include <chrono>

int main()
{
	const char* mapFileName = "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1.png";
	const char* pathFileName= "C:\\projects\\home\\c_c_remastered\\PathFinding\\data\\map1_path.png";

	int x, y, n;
	unsigned char *data = stbi_load(mapFileName, &x, &y, &n, 1);

	auto start_time = std::chrono::high_resolution_clock::now();

	GraphMap graph(x, y, data);
	BFS bfs(&graph);

	const int startNodeId = graph.getNodeId(30, 10);
	bfs.run(startNodeId);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	std::cout << "BFS took " << time / std::chrono::microseconds(1) << " us";

	const int* dists = bfs.getNodeDist();
	for (int i = 0; i < graph.getNumNodes(); ++i) {
		data[i] = dists[i] > 255 ? 255 : dists[i];
	}
	data[startNodeId] = 255;

	stbi_write_png(pathFileName, x, y, 1, data, x);

	stbi_image_free(data);


}

