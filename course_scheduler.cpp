#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <float.h>
#include <fstream>
#include <chrono>
#include <queue>

using namespace std;
using namespace chrono;

int minSemesters(vector<pair<int, int>>& pairs){
	int classes = 15;
	
	vector<vector<int>> adjMatrix(16); //adjacency matrix
	vector<int> pre(16, 0); //marks number of prereq a class needs
	vector<int> semesterNumber(16, 0); //marks what semester a class needs to be taken
	
	for(auto& p : pairs){ //adding to the adjacency matrix
		int a = p.first;
		int b = p.second;
		adjMatrix.at(a).push_back(b);
		pre.at(b) = pre.at(b) + 1;
	}
	
	//mark which classes can be taken right away
	queue<int> firstSemester;
	//stack<int> firstSemester;
	for(int i = 1; i <= classes; i++){
		if(pre.at(i) == 0){
			firstSemester.push(i);
			semesterNumber.at(i) = 1;
		}
	}
	
	int minSem = 0; //keeps track of current minimum amount of semesters to complete classes
	while(firstSemester.empty() == false){ 
		int c = firstSemester.front(); //first class
		firstSemester.pop();
		
		int i = 0;
		while(i < adjMatrix.at(c).size()){
			int next = adjMatrix.at(c).at(i);
			pre.at(next) = pre.at(next) - 1;
			semesterNumber.at(next) = max(semesterNumber.at(next), semesterNumber.at(c)+1);
			minSem = max(minSem, semesterNumber.at(next));
			
			if(pre.at(next) == 0){
				firstSemester.push(next);
			}
			i++;
		}
	}
	return minSem;
}



void topologicalSort(int course, int prereq, int advanceCourse, vector<vector<int>>& adjMatrix, vector<bool>& visit, vector<bool>& finish, vector<int>& order, ofstream& outputFile, bool& cycle){
	visit.at(course) = true; //marks node as visited
	for(int i = 0; i < adjMatrix.at(course).size(); i++){
		int nextCourse = adjMatrix.at(course).at(i);
		
		//determine edge types 
		if(visit.at(advanceCourse) == false){ //tree edge
		outputFile << "Edge (" << prereq << ", " << advanceCourse << ")  Type (T)\n";
		}
		else if(finish.at(advanceCourse) == false){ //back edge
			outputFile << "Edge (" << prereq << ", " << advanceCourse << ")  Type (B)\n";
			cycle = true; //if there is a back edge then there is a cycle
		}
		else if(finish.at(advanceCourse) == true){ //forward edge
			outputFile << "Edge (" << prereq << ", " << advanceCourse << ")  Type (F)\n";
		}
		else{ //cross edge
			outputFile << "Edge (" << prereq << ", " << advanceCourse << ")  Type (C)\n";
		}
		
		
		
		if(visit.at(nextCourse) == false){
			topologicalSort(nextCourse, prereq, advanceCourse, adjMatrix, visit, finish, order, outputFile, cycle);
		}
	}
	
	finish.at(course) = true;
	order.push_back(course);
}

int main(int argc, char *argv[]){
	//inputFile and outputFile handling
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	
	auto start = steady_clock::now(); //starts the time
	
	int prereq;
	int advanceCourse;
	vector<pair<int, int>> classPairs;
	int courses = 15;
	
	while(inputFile >> prereq >> advanceCourse){
		classPairs.push_back({prereq, advanceCourse});
	}
	//determines if there is a cycle
	bool cycle = false;
	if(cycle == true){
		outputFile << "Has Cycle" << endl;
	}
	else{
		outputFile << "No Cycle" << endl;
	}
	//outputFile << "No Cycle" << endl;
	outputFile << endl;
	
	//makes the graph
	vector<vector<int>> adjMatrix(16);
	for(const auto& [prereq, advanceCourse] : classPairs){
		adjMatrix.at(prereq).push_back(advanceCourse);
	}
	
	//does topological sort and prints edge type
	vector<bool> visit(16, false); 
	vector<bool> finish(16, false);
	vector<int> order;
	
	for(int i = 1; i < 16; i++){
		if(visit.at(i) == false){ //makes sure we don't repeat nodes
			topologicalSort(i, prereq, advanceCourse, adjMatrix, visit, finish, order, outputFile, cycle);
		}
	}
	
	outputFile << endl;
	
	//reverse order
	for(int i = 0; i < order.size() / 2; i++){
		swap(order.at(i), order.at(order.size()-1-i));
	}
	
	//print topological order
	outputFile << "Topological Order: ";
	outputFile << order.at(0);
	for(int i = 1; i < order.size(); i++){
		outputFile << ", " << order.at(i);
	}
	outputFile << endl;
	outputFile << endl;
	//outputFile << endl;
	
	//print minimum amount of semesters
	outputFile << "Minimum amount of semesters needed: " << minSemesters(classPairs) << endl;
	outputFile << endl;
	
	//print running time
	outputFile << "Running time: " << duration<double, milli>(steady_clock::now() - start).count() << " ms" << endl;
	
	
	inputFile.close();
	outputFile.close();
	
	return 0;
}
