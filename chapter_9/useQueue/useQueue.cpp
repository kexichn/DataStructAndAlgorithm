#include <iostream>
#include "appofqueue.h"

using namespace std;

struct Test {
	int a = 1;
	int b = 2;
};

int main()
{
	Machine m = { };
	m.id = 1;
	m.changeTime = 2;
	machineVec.push_back(m);

	m.id = 2;
	m.changeTime = 3;
	machineVec.push_back(m);

	m.id = 3;
	m.changeTime = 1;
	machineVec.push_back(m);

	Job job1 = { 1 };
	Task task1 = { };
	task1.machine = 1;
	task1.time = 2;
	job1.taskQueue.push(task1);
	task1.machine = 2;
	task1.time = 4;
	job1.taskQueue.push(task1);
	task1.machine = 1;
	task1.time = 1;
	job1.taskQueue.push(task1);
	jobVec.push_back(make_shared<Job>(job1));

	Job job2 = { 2 };
	Task task2 = { };
	task2.machine = 3;
	task2.time = 4;
	job2.taskQueue.push(task2);
	task2.machine = 1;
	task2.time = 2;
	job2.taskQueue.push(task2);
	jobVec.push_back(make_shared<Job>(job2));

	Job job3 = { 3 };
	Task task3 = { };
	task3.machine = 1;
	task3.time = 4;
	job3.taskQueue.push(task3);
	task3.machine = 2;
	task3.time = 4;
	job3.taskQueue.push(task3);
	jobVec.push_back(make_shared<Job>(job3));

	Job job4 = { 4 };
	Task task4 = { };
	task4.machine = 3;
	task4.time = 1;
	job4.taskQueue.push(task4);
	task4.machine = 2;
	task4.time = 3;
	job4.taskQueue.push(task4);
	jobVec.push_back(make_shared<Job>(job4));

	int a = alignof(Test);
	factorySimulator();

}
