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



string determineRightTarget(const string& target) {
    int count = 0;
    int number[10];
    for (int i = 0; i < target.length(); i++) {
        if (target[i] >= '0' && target[i] <= '9') {
            number[count] = target[i] - '0';
            count++;
        }
    }
    int ID;
    if (count == 1) { 
        ID = number[0];
    }
    else if (count == 2) { 
        ID = ((number[0] + number[1]) % 5) + 3;
    }
    else if (count == 3) { 
        int max = number[0];
        if (number[1] > max) max = number[1];
        if (number[2] > max) max = number[2];
        ID = (max % 5) + 3;
    }
    else { 
        return "INVALID";
    }

    string targetList[] = { "Kon Tum", "Pleiku", "Gia Lai", "Buon Ma Thuot", "Duc Lap", "Dak Lak", "National Route 21", "National Route 14" };
    if (ID < 0 || ID > 7) {
        return "INVALID";
    }
    else {
        return targetList[ID];
    }
    return "INVALID";
}

bool isUpper(char a) {
    return a >= 'A' && a <= 'Z';
}

bool isLower(char a) {
    return a >= 'a' && a <= 'z';
}

char caesarCipher(char a, int shift) {
    if (isLower(a)) {
        return (a - 'a' - shift + 26) % 26 + 'a';
    }
    else if (isUpper(a)) {
        return (a - 'A' - shift + 26) % 26 + 'A';
    }
    else {
        return a;
    }
}

string reverseString(string s) {
    int len = s.length();
    for (int i = 0; i < len / 2; i++) {
        int temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    return s;
}

string decodeTarget(const string& message, int EXP1, int EXP2){
    string temp = message;
    if (EXP1 < 300 || EXP2 < 300) {
        string decoded = reverseString(message);
        return decoded;
    }
    else {
        int shift = (EXP1 + EXP2) % 26;
        for (int i = 0; i < temp.length(); i++) {
            temp[i] = caesarCipher(temp[i], shift);
        }
        return temp;
    }
    return "INVALID";
}

void bigAssMathProblem(int LF1, int LF2, int EXP1, int EXP2, int& T1, int& T2, double& T1change, double& T2change) {
    T1change = (LF1 / (LF1 + LF2)) * (T1 + T2) * (1 + ((EXP1 - EXP2) / 100));
    T2change = T1 + T2 - T1change;
}

void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int& T1, int& T2, int E)
{
    double T1change = 0, T2change = 0;

    if (E == 0)
    {
        double ratio = double(LF1) / (LF1 + LF2);
        double expFactor = 1.0 + double(EXP1 - EXP2) / 100.0;

        T1change = ratio * (T1 + T2) * expFactor;
        T2change = (T1 + T2) - T1change;

        T1 = round(T1change);
        T2 = round(T2change);
    }
    else
    {
        if (E >= 1 && E <= 9)
        {
            T1 -= round(T1 * (E / 100.0));
            T2 -= round(T2 * (E / 200.0)); 
        }
        else if (E >= 10 && E <= 29)
        {
            T1 += E * 50;
            T2 += E * 50;
        }
        else if (E >= 30 && E <= 59)
        {
            T1 += round(T1 * (E / 200.0)); 
            T2 += round(T2 * (E / 500.0)); 
        }
        else if (E >= 60 && E <= 99)
        {
            return;
        }
    }
    if (T1 < 0)
        T1 = 0;
    if (T1 > 3000)
        T1 = 3000;

    if (T2 < 0)
        T2 = 0;
    if (T2 > 3000)
        T2 = 3000;
}
