#define _CRT_SECURE_NO_WARNINGS
#include "shit.h" 

bool extractArray(char* str, int arr[], int size)
{
    int count = 0;
    char* token = strtok(str, "[],");
    while (token && count < size)
    {
        arr[count++] = atoi(token);
        token = strtok(NULL, "[], ");
    }
    return count == size;
}

bool readFile(const string& filename, int LF1[], int LF2[], int& EXP1, int& EXP2, int& T1, int& T2, int& E)
{
    char data[MAX_LINES][MAX_LINE_LENGTH];
    int numLines = 0;

    ifstream ifs(filename);
    if (!ifs.is_open()) return false;

    while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
    {
        numLines++;
    }
    ifs.close();

    if (numLines < MAX_LINES) return false;

    if (!extractArray(data[0], LF1, 17)) return false;
    if (!extractArray(data[1], LF2, 17)) return false;
    if (sscanf(data[2], "%d %d", &EXP1, &EXP2) != 2) return false;
    if (sscanf(data[3], "%d %d", &T1, &T2) != 2) return false;
    if (sscanf(data[4], "%d", &E) != 1) return false;

    return true;
}

int calcForce(int arr1[], int arr2[]){
    int S = 0;
    for (int i = 0; i < 17; i++) {
        int strengthLevel = arr1[i] * arr2[i];
        S += strengthLevel;
    }
    return S;
}

int gatherForces(int LF1[], int LF2[]) {
    int strength[17] = { 1, 2, 3, 4 , 5, 7, 8, 9, 10, 12 ,15, 18, 20, 30, 40 , 50, 70};
    int strengthOfArmy1 = 0;
    int strengthOfArmy2 = 0;
    strengthOfArmy1 = calcForce(LF1, strength);
    strengthOfArmy2 = calcForce(LF2, strength);
    int totalStrength = strengthOfArmy1 + strengthOfArmy2;
    return totalStrength;
}