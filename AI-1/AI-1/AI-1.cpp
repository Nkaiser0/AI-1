// AI-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
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
		stringstream spaceSpliter(line);
		vector<string> container;
		string s;
		while (getline(spaceSpliter, s, ' ')) {
			container.push_back(s);
		}
		node n1 = node(container[0]);
		edge e1 = edge(container[1], (int)container[2]);
		node n2 = node(container[1]);
		edge e2 = edge(container[0], (int)container[2]);
		n1.edges.push_back(e1);
		n2.edges.push_back(e2);
		nodes.push_back(n1);
		nodes.push_back(n2);
}

	int main(int argc, char** argv)
{
	// If we don't have the required 3 inputs
	if (argc != 4)
		return -1;
	string filename, origin_city, destination_city;
	filename = argv[1];
	origin_city = argv[2];
	destination_city = argv[3];

	cout << filename << "\n" << origin_city << "\n" << destination_city << endl;

	openfile(filename);
	UCS(nodes, nodes[getNodeByName(origin_city)], nodes[getNodeByName(destination_city)]

	return 0;
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
		string name = list.front().name;
		int loc = getNodeByName(graph, name);

		graph.at(loc).color = traversedColor;
		list.pop();

	}
	int distLoc = getNodeByName(graph, dest.name);
	int totalDist = graph.at(distLoc).distance;
	node currentNode = graph.at(distLoc);
	stack<node> parents;

	parents.push(graph.at(distLoc));

	while (&currentNode) {
		if (&currentNode.parent) {
			parents.push(*currentNode.parent);
		}
	}

	cout << "Distance: " << totalDist << " km" << endl << "route: " << endl;
	
	while (!parents.empty) {
		node current = parents.top();
		parents.pop();
		node next = parents.top();
		if (&next) {
			cout << current.name << "to" << next.name << "," << totalDist - next.distance << " km" << endl;
		}
		
	}
}

int getNodeByName(vector<node> nodes, string name) {
	for (int i = 0; i < (int) nodes.size(); i++) {
		if (nodes.at(i).name == name) {
			return i;
		}
	}
	return -1;
}