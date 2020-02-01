// AI-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include "node.h"
#include "edge.h"

using namespace std;

vector<node> nodes;

string undiscoveredColor = "white";
string discoveredColor = "grey";
string traversedColor = "black";

int getNodeByName(vector<node> nodes, string name);

void openFile(string fileName) {
	ifstream inputFile;
	inputFile.open(fileName);
	string line;
	while (getline(inputFile, line) && line != "END OF INPUT") {
		stringstream parser;
	}
}

int main(int argc, char** argv)
{
	// If we don't have the required 3 inputs
	if (argc != 3)
		return -1;
	string filename, origin_city, destination_city;
	filename = argv[0];
	origin_city = argv[1];
	destination_city = argv[2];

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


void UCS(vector<node> graph, node start, node dest) {
	queue<node> list;
	start.color = "grey";
	list.push(start);

	while (!list.empty()) {

		for (edge nextEdge : list.front().edges) {
			int loc = getNodeByName(graph, nextEdge.destination);

			if (graph.at(loc).color == undiscoveredColor) {
				graph.at(loc).distance = nextEdge.cost + list.front().distance;
				graph.at(loc).color = discoveredColor;
				graph.at(loc).parent = &list.front();
				list.push(graph.at(loc));


			}
			else if (graph.at(loc).color == discoveredColor) {

				if (graph.at(loc).distance > nextEdge.cost + list.front().distance) {
					graph.at(loc).distance = nextEdge.cost + list.front().distance;
					graph.at(loc).parent = &list.front();
				}

			}

		}

		list.pop();

	}
	int distLoc = getNodeByName(graph, dest.name);


}

int getNodeByName(vector<node> nodes, string name) {
	for (int i = 0; i < (int) nodes.size(); i++) {
		if (nodes.at(i).name == name) {
			return i;
		}
	}
	return -1;
}