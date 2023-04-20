
#include <iostream>
#include <map>
#include "Player.h"
#include "inputValidation.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "RandomAI.h"
#include "CheatingAI.h"
#include "SearchAndDestroyAI.h"

namespace BattleShip {
// Game constructor that will build players, their placement and target boards, dimensions of each board, and a ship map
    BattleShip::Game::Game(const int &rows, const int &cols, const std::map<char, int> &shipMap,
                           const int &seed) : player1(), player2(),
                                              Rows(rows),
                                              Cols(cols),
                                              ShipsMap(shipMap), Seed(seed) {}

    // Function definition to allow user to pick which game to play
    void BattleShip::Game::pickGame() {
        int gameNumber;
        bool gotValidInt = false;
        std::string line;
        do {
            std::cout << "What type of game do you want to play?" << std::endl;
            std::cout << "1. Human vs Human" << std::endl << "2. Human vs AI" << std::endl << "3. AI vs AI"
                      << std::endl;
            std::cout << "Your choice: ";
            std::getline(std::cin, line);
            gotValidInt = getValidInt(line, gameNumber);
        } while (!gotValidInt || (gameNumber < 1 || gameNumber > 3));
        addPlayers(gameNumber); // Function call to addPlayers to user's game
    }


    // Function definition to allow user to pick which AI's are apart of their game
    int BattleShip::Game::pickAI() {
        int aiNumber;
        bool gotValidInt = false;
        std::string line;
        do {
            std::cout << "What AI do you want?" << std::endl;
            std::cout << "1. Cheating AI" << std::endl << "2. Random AI" << std::endl << "3. Hunt Destroy AI"
                      << std::endl;
            std::cout << "Your choice: ";
            std::getline(std::cin, line);
            gotValidInt = getValidInt(line, aiNumber);
        } while (!gotValidInt || (aiNumber < 1 || aiNumber > 3));
        return aiNumber;  // returns an ai number that will correspond to an AI
    }

    // Function that plays the game
    void BattleShip::Game::playGame() {
        pickGame();
        player1->set_opponent(*player2);
        player2->set_opponent(*player1);
        while (!game_over()) {  // While the game is not over
            // player 1 plays a round
            playRound(*player1);
            if (game_over()) {
                std::cout << player1->getName() << " won the game!" << std::endl;
                return;
            }
            // player 2 plays a round
            playRound(*player2);
            if (game_over()) {
                std::cout << player2->getName() << " won the game!" << std::endl;
                return;
            }
        }
    }

    // Function to check whether the game is over
    bool BattleShip::Game::game_over() const {
        // Checks both player's ship maps to see if they are empty
        if (player1->getShipsMap().empty() || player2->getShipsMap().empty()) {
            return true; // If empty, then this signifies the game is over
        } else {
            return false; // otherwise, game is not over
        }
    }

    // Function for playing a round
    void BattleShip::Game::playRound(Player &player) const {
        int rowInput, colInput; // Create two variables to hold rows and cols
        char shipName = '1'; // Create and declare an error variable
        player.getMove(rowInput, colInput, Rows, Cols); // Ask for player's move
        shipName = player.get_opponent()->getPlacementBoard().obtainShipSpace(shipName, rowInput, colInput); // locate the area on the board
        player.fire(shipName, rowInput, colInput); // Fire using player's input
    }

    // Function to addPlayers
    void Game::addPlayers(const int &gameNumber) {
        int playerNumber = 1;  //playerNumber set to 1
        int ai; // ai variable to hold which ai number user picks
        BattleShip::AIPlayer::seedGenerator(Seed);  // initialize seed
        // If statement structure that corresponds with game number
        if (gameNumber == 1) { // For human vs human, call makePlayer to make human players
            makePlayer(playerNumber); // Make human player
            playerNumber++; // increment playerNumber to 2
            makePlayer(playerNumber); // Make human player
        } else if (gameNumber == 2) { // For human vs ai, call makePlayer first then makeAIPlayer
            makePlayer(playerNumber); // Make human player
            ai = pickAI(); // Call to user for which ai they want
            makeAIPlayer(playerNumber, ai); // Make ai player
        } else { // For ai vs ai, call makeAIPlayer to make ai players
            ai = pickAI(); // Call to user for which ai they want
            makeAIPlayer(playerNumber, ai); // Make ai player
            playerNumber++; // Increment playerNumber
            ai = pickAI(); // Call to user for which ai they want
            makeAIPlayer(playerNumber, ai); // Make ai player
        }
    }

    // Function to make human players
    void Game::makePlayer(const int &playerNumber) {
        // Check to see which playerNumber
        if (playerNumber == 1) { // For playerNumber 1
            player1 = std::make_unique<HumanPlayer>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of Human type
            player1->place_ships(player1->getPlacementBoard(), Rows, Cols); // Call to set up player's board
        } else { // For playerNumber 2
            player2 = std::make_unique<HumanPlayer>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of Human type
            player2->place_ships(player2->getPlacementBoard(), Rows, Cols); // Call to set up player's board
        }
    }

    // Function to make ai players
    void Game::makeAIPlayer(const int &playerNumber, int aiNum) {
        // Check to see which ai the user picked
        if (aiNum == 1) { // For cheating AI's
            // Check playerNumber
            if (playerNumber == 1) { // For playerNumber 1
                player1 = std::make_unique<CheatingAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of CheatingAI type
                player1->place_ships(player1->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            } else { // For playerNumber 2
                player2 = std::make_unique<CheatingAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of CheatingAI type
                player2->place_ships(player2->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            }
        } else if (aiNum == 2) { // For random AI's
            if (playerNumber == 1) { // For playerNumber 1
                player1 = std::make_unique<RandomAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of RandomAI type
                player1->place_ships(player1->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            } else { // For random AI's
                player2 = std::make_unique<RandomAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of RandomAI type
                player2->place_ships(player2->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            }
        } else { // For SearchAndDestroyAI AI's
            if (playerNumber == 1) { // For playerNumber 1
                player1 = std::make_unique<SearchAndDestroyAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of SearchAndDestroyAI type
                player1->place_ships(player1->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            } else {
                player2 = std::make_unique<SearchAndDestroyAI>(Rows, Cols, ShipsMap, playerNumber); // Create a unique pointer of SearchAndDestroyAI type
                player2->place_ships(player2->getPlacementBoard(), Rows, Cols); // Call to set up player's board
            }
        }
    }

}
