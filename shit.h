#ifndef SHIT_H
#define SHIT_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_LINES = 5;
const int MAX_LINE_LENGTH = 100;

// task 0

bool extractArray(char* str, int arr[], int size);
bool readFile(const string& filename, int LF1[], int LF2[], int& EXP1, int& EXP2, int& T1, int& T2, int& E);


// task 1
int calcForce(int array1[], int array2[]);
int gatherForces(int LF1[], int LF2[]);

#endif

