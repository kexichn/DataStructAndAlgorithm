#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <memory>

using namespace std;

// 9.5.1 �г���������
void moveToStation(vector<queue<int>>& station, int car) {
	
	int tmp = INT_MAX, index = -1;
	for (int i = 0; i < station.size(); ++i) {
		if (station[i].empty()) {
			if (index == -1) {
				station[i].push(car);
				break;
			}
		}
		else if (station[i].back() < car && (car - station[i].back()) < tmp) {
			tmp = station[i].back() - car;
			index = i;
		}
	}

	if (index != -1) {
		station[index].push(car);
	}
}

void moveFromStation(vector<queue<int>>& station, vector<int>& output) {
	
	auto findSmallest = [&station]()->pair<int, int> {
		int smallest = INT_MAX, index = -1;
		for (int i = 0; i != station.size(); ++i) {
			if (!station[i].empty() && station[i].front() < smallest) {
				smallest = station[i].front();
				index = i;
			}
		}
		return make_pair(smallest, index);
	};

	auto [smallest, index] = findSmallest();

	while (smallest == output.back() + 1) {
		output.push_back(smallest);
		station[index].pop();
		auto [s, i] = findSmallest(); 
		smallest = s;
		index = i;
	}
}

vector<int> rearrangeTrainCarriages(vector<int>& input, int k) {
	vector<int> output(1, 0);

	vector<queue<int>> station(k);

	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == output.back() + 1) {
			output.push_back(input[i]);
			moveFromStation(station, output);
		}
		else {
			moveToStation(station, input[i]);
		}	
	}
	output.erase(output.begin());
	return output;
}

// 9.5.2 ��·����
struct Position {
	int x, y;
	bool operator==(const Position& p) const {
		return x == p.x && y == p.y;
	}

	Position operator+(const int i) {
		return { x + i, y + i };
	}

	Position operator-(const int i) {
		return { x - i, y - i };
	}

};

bool findPath(vector<vector<int>>& grid, Position& start, Position& end, vector<Position>& path) {
    
	bool find = false;

	// ��������յ��Ƿ��ںϷ���Χ��
	int m = grid.size(), n = grid[0].size();
	if (start.x < 0 || start.x >= m || start.y < 0 || start.y >= n) {
		return find;
	}
	if (end.x < 0 || end.x >= m || end.y < 0 || end.y >= n) {
		return find;
	}

	// ������Χ��ǽ
	vector<int> wall(n + 2, 1);
	grid.insert(grid.begin(), wall);
	grid.push_back(wall);
	for (int i = 1; i != grid.size()-1; ++i) {
		grid[i].insert(grid[i].begin(), 1);
		grid[i].push_back(1);
	}

	// ��������
	array<int, 4> dx = { 0, 0, 1, -1 };
	array<int, 4> dy = { 1, -1, 0, 0 };

	// �����������
	Position cur = start + 1;
	Position cend = end + 1;
	queue<Position> q;
	q.push(cur);
	grid[cur.x][cur.y] = 2;

	while (cur != cend && !q.empty()) {
		cur = q.front();
		q.pop();

		for (int i = 0; i != 4; ++i) {
			Position next = { cur.x + dx[i], cur.y + dy[i] };
			if (grid[next.x][next.y] == 0) {
				q.push(next);
				grid[next.x][next.y] = grid[cur.x][cur.y] + 1;
			}
		}
	}

	// ���ؽ��
	if (cur == cend) {
		find = true;
		// ���������ߣ��ҵ����·��
		path.push_back(cur-1);
		while (cur != start + 1) {
			for (int i = 0; i != 4; ++i) {
				Position next = { cur.x + dx[i], cur.y + dy[i] };
				if (grid[next.x][next.y] == grid[cur.x][cur.y] - 1) {
					path.push_back(next-1);
					cur = next;
					break;
				}
			}
		}

		reverse(path.begin(), path.end());
	}
	return find;
}


// 9.5.3 ͼԪʶ��
void labelPel(vector<vector<int>>& grid) {

	// ������Χ��ǽ
	int n = grid.size() + 2;
	vector<int> wall(n, 0);
	grid.insert(grid.begin(), wall);
	grid.push_back(wall);
	for (int i = 1; i != n - 1; ++i) {
		grid[i].insert(grid[i].begin(), 0);
		grid[i].push_back(0);
	}

	// ��������
	array<int, 4> dx = { 0, 0, 1, -1 };
	array<int, 4> dy = { 1, -1, 0, 0 };
	int id = 2;

	// ��ʼ���
	for (int i = 1; i != n; ++i) {
		for (int j = 1; j != n; ++j) {

			if (grid[i][j] != 1) {
				continue;
			}

			// �����������
			Position cur = { i, j };
			queue<Position> q;
			q.push(cur);

			while (!q.empty()) {
				cur = q.front();
				q.pop();
				grid[cur.x][cur.y] = id;
				int dir = 0;
				while (dir != 4) {
					Position next = { cur.x + dx[dir], cur.y + dy[dir] };
					if (grid[next.x][next.y] == 1) {
						q.push(next);					
					}
					++dir;
				}
			}
			++id;
		}
	}

	// ɾ��Χǽ
	grid.erase(grid.end() - 1);
	grid.erase(grid.begin());
	for (int i = 0; i != grid.size(); ++i) {
		grid[i].erase(grid[i].end() - 1);
		grid[i].erase(grid[i].begin());
	}
}

// 9.5.4 ��������
// ���ݽṹ
struct Task {
	int machine;
	int time;

	Task(int m = 0, int t = 0) {
		machine = m;
		time = t;
	}
};

struct Job {
	int id = 0;
	int timeLength = 0;
	int finishedTime = 0;
	queue<Task> taskQueue;
	

	void addTask(int machine, int time) {
		taskQueue.emplace(machine, time);
	}

	void removeTask() {
		auto task = taskQueue.front();
		taskQueue.pop();
		timeLength += task.time;
	}
};

struct Machine {
	int id;
	int changeTime;
	int nextFinished = 0;
	int finishedNum = 0;
	queue<shared_ptr<Job>> jobptrQueue;
	shared_ptr<Job> currentJob = nullptr;;
};

// ȫ�ֱ���
vector<shared_ptr<Job>> jobVec;
vector<Machine> machineVec;
int largeTime = 100;


// �������
void inputData();
void assignTask();
void simulate();
void outputStatistics();

void factorySimulator() {
	//inputData();
	assignTask();
	simulate();
	outputStatistics();
}

// ����ʵ��
void inputData() {
	cout << "��������������";
	int n = 0;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		Job job;
		job.id = i + 1;
		cout << "��" << i + 1 << "����������Ĺ���������";
		int m = 0;
		cin >> m;
		for (int j = 0; j != m; ++j) {
			cout << "��" << j + 1 << "������Ļ�����ź����ʱ�䣺";
			int mid = 0, t = 0;
			cin >> mid >> t;
			job.addTask(mid, t);
		}

		jobVec.push_back(make_shared<Job>(job));
	}

	cout << "�������������";
	cin >> n;
	for (int i = 0; i != n; ++i) {
		Machine machine;
		machine.id = i + 1;
		cout << "��" << i + 1 << "��������ת��ʱ�䣺";
		int ct = 0;
		cin >>  ct;
		machine.changeTime = ct;
		machineVec.push_back(machine);
	}
}

void moveJobToMachine(shared_ptr<Job>& job, int time) {
	if (job->taskQueue.empty()) {
		job->finishedTime = time;
		return;
	}

	for (auto& m : machineVec) {
		if (job->taskQueue.front().machine == m.id) {
			m.jobptrQueue.push(job);
			break;
		}
	}
}

void assignTask() {
	for (auto& job : jobVec) {	
		moveJobToMachine(job, 0);	
	}
}

void simulate() {
	for (int time = 0; time != largeTime; ++time) {
		for (auto& m : machineVec) {
			// ���m���ڹ���̬��������
			// ���m�����ڹ���̬����ȡ��һ����������õ�ǰ����Ľ���ʱ��
			// �����ڹ���̬�������ǣ���ǰʱ����ڵ�����һ������ʱ��
			// ����ʱ����ڽ���ʱ�����ת��ʱ�䣬�������ʱ����0���򲻼�ת��ʱ��
			// ���ʱ����ڵ��ڵ�ǰ����Ľ���ʱ�䣬�򽫵�ǰ����ת����һ������
			int spare = m.nextFinished ? m.nextFinished + m.changeTime : 0;
			if (time >= m.nextFinished) {
				if (m.currentJob) {
					m.finishedNum++;
					m.currentJob->removeTask();
					moveJobToMachine(m.currentJob, time);
					m.currentJob = nullptr;
				}	
			}
			
			if (time >= spare) {
				if (!m.jobptrQueue.empty()) {
					auto job = m.jobptrQueue.front();
					m.jobptrQueue.pop();
					m.currentJob = job;
					m.nextFinished = time + job->taskQueue.front().time;
				}
				
			}
		}
	}
}

void outputStatistics() {
	cout << "machine:\n";
	for (auto& m : machineVec) {
		cout << "\tmachine ID:" << m.id \
			<< " finishedNum:" << m.finishedNum \
			<< " lastFinishedTime:" << m.nextFinished + m.changeTime << endl;
	}

	cout << "job:\n";
	for (auto& job : jobVec) {
		cout << "\tjob ID:" << job->id \
			<< " taskTime:" << job->timeLength \
			<< " finishedTime:" << job->finishedTime \
			<< " waitTime:" << job->finishedTime - job->timeLength << endl;
	}
}
