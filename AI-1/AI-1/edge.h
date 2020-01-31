#pragma once
#include <string>

using namespace std;

class edge {

public:
	edge(string dest, int cst);
	string destination;
	int cost;
};