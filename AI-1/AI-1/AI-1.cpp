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

int getNodeByName(string name);

void openFile(string fileName);
void UCS(node start, node dest);

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

	openFile(filename);
	int originLoc = getNodeByName(origin_city);
	node origin = nodes.at(originLoc);
	node destin = nodes.at(getNodeByName(destination_city));
	UCS(origin, destin);

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


void UCS(node start, node dest) {
	if (nodes.size() == 0) {
		return;
	}
	queue<node> list;
	start.color = "grey";
	list.push(start);

	while (!list.empty()) {

		for (edge nextEdge : list.front().edges) {
			int loc = getNodeByName(nextEdge.destination);

			if (nodes.at(loc).color == undiscoveredColor) {
				nodes.at(loc).distance = nextEdge.cost + list.front().distance;
				nodes.at(loc).color = discoveredColor;
				nodes.at(loc).parent = &list.front();
				list.push(nodes.at(loc));


			}
			else if (nodes.at(loc).color == discoveredColor) {

				if (nodes.at(loc).distance > nextEdge.cost + list.front().distance) {
					nodes.at(loc).distance = nextEdge.cost + list.front().distance;
					nodes.at(loc).parent = &list.front();
				}

			}

		}
		string name = list.front().name;
		int loc = getNodeByName(name);

		nodes.at(loc).color = traversedColor;
		list.pop();

	}
	int distLoc = getNodeByName(dest.name);
	int totalDist = nodes.at(distLoc).distance;
	node currentNode = nodes.at(distLoc);
	stack<node> parents;

	parents.push(nodes.at(distLoc));

	while (&currentNode) {
		if (&currentNode.parent) {
			parents.push(*currentNode.parent);
		}
	}

	cout << "Distance: " << totalDist << " km" << endl << "route: " << endl;
	
	while (!parents.empty()) {
		node current = parents.top();
		parents.pop();
		node next = parents.top();
		if (&next) {
			cout << current.name << "to" << next.name << "," << totalDist - next.distance << " km" << endl;
		}
		
	}
}

int getNodeByName(string name) {
	for (int i = 0; i < (int) nodes.size(); i++) {
		if (nodes.at(i).name.compare(name) == 0) {
			return i;
		}
	}
	return -1;
}

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
		if (nodes.size() == 0) {
			node n = node(container[0]);
			n.edges.push_back(edge(container[1], stoi(container[2])));
			nodes.push_back(n);
		}
		bool node1Found = false;
		bool node2Found = false;
		for (int i = 0; i < nodes.size(); i++) {
			node n = nodes[i];
			if (node1Found == false && n.name == container[0]) {
				nodes[i].edges.push_back(edge(container[1], stoi(container[2])));
				node1Found = true;
			}
			else if (node2Found == false && n.name == container[1]) {
				nodes[i].edges.push_back(edge(container[0], stoi(container[2])));
					node2Found = true;
			}
		}
		if (node1Found == false) {
			node n = node(container[0]);
			n.edges.push_back(edge(container[1], stoi(container[2])));
			nodes.push_back(n);
		}
		if (node2Found == false) {
			node n = node(container[1]);
			n.edges.push_back(edge(container[0], stoi(container[2])));
			nodes.push_back(n);
		}
	}

}