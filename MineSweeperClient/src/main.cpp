#include "game.h"

int main(int argc, char** argv){
    int difficulty;
    if(argc > 1){
        difficulty = atoi(argv[1]);
    } else difficulty = 1;
    int boardSize, nBombs;
    std::string difficulty_str;
    switch(difficulty){
        case 1:
            boardSize = 10;
            nBombs = 15;
            difficulty_str = "Easy";
            break;
        case 2:
            boardSize = 15;
            nBombs = 50;
            difficulty_str = "Normal";
            break;
        case 3:
            boardSize = 20;
            nBombs = 100;
            difficulty_str = "Hard";
            break;
        default:
            std::cout << "Invalid difficulty number: " << difficulty << std::endl;
            std::exit(EXIT_FAILURE);
    }
    Game game(difficulty_str, boardSize, nBombs);
    game.run();
}
