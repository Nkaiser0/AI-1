#pragma once
#include <string>
#include <vector>
#include "edge.h"

using namespace std;

class node {


public:
	node(string);
	string name;
	vector<edge> edges;
	string color = "white";
	int distance = 0;
	node *parent;
};