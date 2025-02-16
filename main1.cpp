#include "shit.h" 


int main() {
    const string filename = "input.txt";

    int LF1[17], LF2[17];
    int EXP1, EXP2, T1, T2, E;

    if (readFile(filename, LF1, LF2, EXP1, EXP2, T1, T2, E))
    {
        cout << "File read successfully!\n";
    }
    else
    {
        cout << "Failed to read the file.\n";
    }
    cout << "Task 0: ...\n";
    cout << "[";
    for (int i = 0; i < 16; i++) {
        cout << LF1[i] << ",";
    }
    cout << LF1[16] << "]\n";
    cout << "[";
    for (int i = 0; i < 16; i++) {
        cout << LF2[i] << ",";
    }
    cout << LF2[16] << "]\n";
    cout << EXP1 << " " << EXP2 << endl;
    cout << T1 << " " << T2 << endl;
    cout << E << endl;
    cout << "Task 1: ...\n";
    int c = gatherForces(LF1, LF2);
    cout << c << endl;
    cout << "Task 2.1: ...\n";
    string str1 = "2skibidi";
    string str2 = determineRightTarget(str1);
    cout << str2 << endl;
    return 0;
}
