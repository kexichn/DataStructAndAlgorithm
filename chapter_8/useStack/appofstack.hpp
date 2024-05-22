#pragma once

#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// 8.5.1 括号匹配
bool printMatchedPairs(string& expr) {
	stack<int> s;

	bool res = true;

	for (int i = 0; i < expr.size(); ++i) {
		if (expr[i] == '(') {
			s.push(i);
		} else if (expr[i] == ')') {
			if (s.empty()) {
				res = false;
				break;
			} else {
				s.pop();
			}
		}
	}

	return res;
}

// 8.5.2 汉诺塔
// 递归思路
void moveDish(int n, int d1, int d2, int d3) {
	if (n > 0) {
		moveDish(n - 1, d1, d3, d2);
		// move a dish from d1 to d2
		moveDish(n - 1, d3, d2, d1);
	}
}

// 8.5.3 列车车厢重排
int smallestIndex = -1;

void moveFromStationToOutput(vector<stack<int>>& station, vector<int>& output) {

	while (smallestIndex >= 0 && station[smallestIndex].top() == output.back() + 1) {
	    output.push_back(station[smallestIndex].top());
		station[smallestIndex].pop();
	    
		// find the next smallest index
		smallestIndex = -1;
		int tmp = INT_MAX;
		for (int i = 0; i < station.size(); ++i) {
			if (!station[i].empty() && station[i].top() < tmp) {
				smallestIndex = i;
				tmp = station[i].top();
			}
		}
	}
}

bool moveFromInputToStation(int value, vector<stack<int>>& station) {
	
	int tmp = INT_MAX;
	int tmpIndex = -1;
	for (int i = 0; i < station.size(); ++i) {
		if (station[i].empty()) {
			tmpIndex = i;
			if (smallestIndex >= 0 && value < station[smallestIndex].top()) {
			    smallestIndex = i;
			} else if (smallestIndex < 0) {
			    smallestIndex = i;
			}
			break;
		} else if (station[i].top() > value && (station[i].top() - value) < tmp) {
			tmp = station[i].top() - value;
			tmpIndex = i;
		}	
	}

	bool result = false;
	if (tmpIndex != -1) {
	    station[tmpIndex].push(value);
		result = true;
	} 

	return result;
}

vector<int> rerangeTrain(vector<int>& input, int k) {
	
	vector<int> output(1, 0);

	vector<stack<int>> station(k);

	bool res = true;

	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == output.back() + 1) {
			output.push_back(input[i]);
			moveFromStationToOutput(station, output);
		} else {
			res = moveFromInputToStation(input[i], station);
		}

		if (!res) {
			break;
		}
	}

	output.erase(output.begin());
	return output;
}

// 8.5.4 开关盒布线
bool checkBox(vector<int>& net) {
    stack<int> s;

	for (int i = 0; i < net.size(); ++i) {
		if (s.empty() || s.top() != net[i]) {
			s.push(net[i]);
		}
		else {
			s.pop();
		}
	}

	return s.empty();
}

// 8.5.5 离线等价类问题
vector<vector<int>> equivalenceClass(vector<stack<int>>& input) {
	vector<vector<int>> res;
	int n = input.size();
	
	vector<int> parent(n, -1);
	parent[0] = 0;
	auto lambda = [](int n) { return n == -1; };
	auto p = find_if(parent.begin(), parent.end(), lambda);
	while (p != parent.end()) {
		
		queue<int> q;
		vector<int> tmp;
		q.push(p - parent.begin());
		while (!q.empty()) {
			int t = q.front();
			q.pop();
			tmp.push_back(t);
			parent[t] = t;
			while (!input[t].empty()) {
				int v = input[t].top();
				input[t].pop();
				if (parent[v] == -1) {
					parent[v] = v;
					q.push(v);
				}
			}
		}
		sort(tmp.begin(), tmp.end());
		res.push_back(tmp);

		p = find_if(parent.begin(), parent.end(), lambda);

	}
	
	return res;
}

// 8.5.6 迷宫老鼠
using pos = pair<int, int>;
using intv = vector<int>;
using intvv = vector<intv>;
stack<pos> findPath(intvv& maze) {
    // 给迷宫的外围加上一圈墙
    int m = maze.size();
	intv tmp(maze[0].size() + 2, 1);
	maze.insert(maze.begin(), tmp);
	maze.push_back(tmp);
	for (int i = 1; i < maze.size() - 1; ++i) {
		maze[i].insert(maze[i].begin(), 1);
		maze[i].push_back(1);
	}

	// 用栈来保存路径
	int dirx[4] = { 0, 1, 0, -1 };
	int diry[4] = { 1, 0, -1, 0 };
	
	stack<pos> s;	
	pos here(1, 1);

	// 开始查找路径
	while (here.first != m || here.second != m) {
		int x = here.first;
		int y = here.second;
		
		int d = 0;
		while (d < 4) {
			int i = x + dirx[d];
			int j = y + diry[d];
			if (maze[i][j] == 0) {
				maze[i][j] = 1;
				s.push(here);
				here.first = i;
				here.second = j;
				break;
			}
			++d;
		}

		if (d == 4 ) {
			s.pop();
			if (s.empty()) {
				break;
			}
			else {
				here = s.top();
			}
		}
	}

	return s;
}