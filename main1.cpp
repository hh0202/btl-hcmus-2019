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

void adjustValue(int LF1[], int LF2[], int& EXP1, int& EXP2, int& T1, int& T2, int& E) {
    for (int i = 0; i < 17; i++) {
        if (LF1[i] > 1000) {
            LF1[i] = 1000;
        }
        else if (LF1[i] < 0) {
            LF1[i] = 0;
        }
    }
    for (int i = 0; i < 17; i++) {
        if (LF2[i] > 1000) {
            LF2[i] = 1000;
        }
        else if (LF2[i] < 0) {
            LF2[i] = 0;
        }
    }
    if (EXP1 > 600) {
        EXP1 = 600;
    }
    else if (EXP1 < 0) {
        EXP1 = 0;
    }
    if (EXP2 > 600) {
        EXP2 = 600;
    }
    else if (EXP2 < 0) {
        EXP2 = 0;
    }
    if (T1 > 3000) {
        T1 = 3000;
    }
    else if (T1 < 0) {
        T1 = 0;
    }
    if (T2 > 3000) {
        T2 = 3000;
    }
    else if (T2 < 0) {
        T2 = 0;
    }
    if (E > 99) {
        E = 99;
    }
    else if (E < 0) {
        E = 0;
    }
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
    adjustValue(LF1, LF2, EXP1, EXP2, T1, T2, E);
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
    bool lastWasDigit = false;
    for (int i = 0; i < target.length(); i++) {
        if (isdigit(target[i])) {
            if (lastWasDigit) return "INVALID"; 
            number[count++] = target[i] - '0';
            lastWasDigit = true;
        }
        else {
            lastWasDigit = false;
        }
    }
    int ID;
    if (count == 1) { 
        if (number[0] >= 0 && number[0] <= 2) {
            return "DECOY";
        }
        else if (number[0] < 0 && number[0] > 7) {
            return "INVALID";
            }
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

int calcForce2(int arr[]) {
    int S = 0;
    for (int i = 0; i < 17; i++) {
        S += arr[i];
    }
    return S;
}
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int& T1, int& T2, int E) {

    double LF1d = double(LF1);
    double LF2d = double(LF2);
    double EXP1d = double(EXP1);
    double EXP2d = double(EXP2);
    double T1d = double(T1);
    double T2d = double(T2);

    if (LF1d + LF2d == 0) {
        T1 = 0;
        T2 = 0;
        return;
    }

    double delta_T1 = (LF1d / (LF1d + LF2d) * (T1d + T2d)) * (1 + (EXP1d - EXP2d) / 100.0);
    double delta_T2 = (T1d + T2d) - delta_T1;

    T1d = delta_T1;
    T2d = delta_T2;

    if (E >= 1 && E <= 9) {
        T1d -= (E * 1.0 / 100) * T1d;
        T2d -= (E * 0.5 / 100) * T2d;
    }
    else if (E >= 10 && E <= 29) {
        T1d += E * 50;
        T2d += E * 50;
    }
    else if (E >= 30 && E <= 59) {
        T1d += (E * 0.5 / 100) * T1d;
        T2d += (E * 0.2 / 100) * T2d;
    }
    else if (E >= 60 && E <= 99) {
        T1d = 0;
        T2d = 0;
    }
    if (T1d > 3000) T1d = 3000;
    else if (T1d < 0) T1d = 0;

    if (T2d > 3000) T2d = 3000;
    else if (T2d < 0) T2d = 0;

    T1 = int(T1d);
    T2 = int(T2d);
}



