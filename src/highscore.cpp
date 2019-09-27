#include <iostream>
#include <fstream>
using namespace std;

int getHighscore(){
    ifstream fileIn("bin/data.bin");
    string highScore;
    getline(fileIn, highScore);
    fileIn.close();
    cout << "Getting highscore " << highScore;
    return stoi(highScore);
}

int setHighscore(int newScore){
    string score2 = to_string(newScore);
    char* score = new char[sizeof(score2)];
    for(int i = 0; i < static_cast<int>(sizeof(score2)); i++){
        score[i] = score2[static_cast<unsigned long long>(i)];
    }
    ofstream fileOut("bin/data.bin", ios::out | ios::binary);
    fileOut.write(static_cast<char*>(score), sizeof(score));
    fileOut.close();
    cout << "Setting highscore " << newScore;
    return newScore;
}
