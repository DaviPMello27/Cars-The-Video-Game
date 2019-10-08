//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 30/09/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <iostream>
#include <fstream>
using namespace std;


///getHighscore():
///
///Opens the "bin/data.bin" file and returns the value that's in it.

//getHighscore():
//
//Abre o arquivo "bin/data.bin" e retorna o valor que está nele.


///setHighscore():
///
///Opens the "bin/data.bin" file and prints the player's highscore.

//setHighscore():
//
//Abre o arquivo "bin/data.bin" e escreve o recorde do jogador.

int getHighscore(){
    ifstream fileIn("bin/data.bin");
    string highScore;
    getline(fileIn, highScore);
    fileIn.close();
    return stoi(highScore);
}

int setHighscore(int newScore){
    ofstream file("bin/data.bin");
    file << newScore;
    file.close();
    return newScore;
}
