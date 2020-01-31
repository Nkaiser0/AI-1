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
};