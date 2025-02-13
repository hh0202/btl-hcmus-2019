#include "shit.h" 

int main() {
    const string filename = "tnc_tc_01_input";

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

    int S = 0;
    S = gatherForces(LF1, LF2);
    cout << S;

    return 0;
}
