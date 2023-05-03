#include <iostream>
#include "dice.cpp" //We can access the drawed dice in this header file
#include <random> //We include this header file to access the mersenne twister function and the random device and uniform distribution and the seed sequence
#include <chrono> //We need this to use the system clock for our seed for our random number generator
#include <string>
#include <cctype> //this header allow us to access the tolower and is upper function
#include <windows.h> //to access sleep function

//Is a struct for the two player option
struct Player
{  
    //This member will be responsible for the players names
    std::string playerNameOne{};
    std::string playerNameTwo{};

    //This member will be resposible for the players seperate random number
    int randomNum{};
};

namespace PlayerScore
{
    int totalPlayerOneScore {};
    int totalPlayerTwoScore{};

    bool makeTurn = true;
}

int performRoll(std::string& playerName, Player plaYer, bool& pTurn);
void checkDiceRolled(int numRand, std::string& name, Player pliyir, bool& switchTurn);
bool askToRollAgain(bool& turn, Player p, std::string& name);
void checkWinner(Player pCheckWinner);

//This function clear the screen of the previous output
void clearScreen()
{
    std::cout << "\nLoading . . . . . ";
    Sleep(2000);
    system("cls");
}

//This funcftion will output the dice that the player rolled and it will be display using switch statement
void drawDice(int num)
{
    switch (num)
    {
        case 1:
            diceOne();
            break;
        case 2:
            diceTwo();
            break;
        case 3:
            diceThree();
            break;
        case 4:
            diceFour();
            break;
        case 5:
            diceFive();
            break;
        case 6:
            diceSix();
            break;
        default:
            std::cout << "Invalid!!!";
            break;
    }
}

//We are going to create a random numbere generator using mersenne twister
int randomNumGen(int min, int max)
{
    std::random_device rdNum{};

    //Adding systemclock and Random Device as our seed
    std::seed_seq ssNum {static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()), rdNum(), rdNum(), rdNum(), rdNum(), rdNum(), rdNum(), rdNum() ,rdNum()};
    
    //We seed our mersene twister with the variable ssNum
    std::mt19937 mt { ssNum };

    //We uses a uniform distribution to make a lower range of number that are between 1 to 6
    std::uniform_int_distribution diceRange{min, max};

    return diceRange(mt);
}

void playerTurn(Player playerr, bool& playerMakeTurn)
{   
    playerMakeTurn = { PlayerScore::makeTurn };

    clearScreen();

    while(true)
    {   
        if (playerMakeTurn)
        {   
            performRoll(playerr.playerNameOne, playerr, playerMakeTurn);
            checkWinner(playerr);
            askToRollAgain(playerMakeTurn, playerr, playerr.playerNameOne);
        }

        else
        {   
            performRoll(playerr.playerNameTwo, playerr, playerMakeTurn);
            checkWinner(playerr);
            askToRollAgain(playerMakeTurn, playerr, playerr.playerNameTwo);
        }   
    }
}

void chooseInAsk(std::string& pName, Player pNames)
{
    while (true)
    {
        if (pName == pNames.playerNameOne)
        {
            std::cout << "Your total points is: " << PlayerScore::totalPlayerOneScore << '\n';
            clearScreen();
            break;
        }

        if (pName == pNames.playerNameTwo)
        {
            std::cout << "Your total points is: " << PlayerScore::totalPlayerTwoScore << '\n';
            clearScreen();
            break;
        }
    }
}

bool askToRollAgain(bool& turn, Player p, std::string& name)
{   
    char continueChoice{};

    do 
    {
        std::cout << "\ndo you want to roll again? (y/n): ";
        std::cin >> continueChoice;

        if (continueChoice == 'y')
        {
            std::cout << "\nYou selected roll again\n";
            clearScreen();

            (turn) ? turn = true : turn = false;

            break;
        }

        if (continueChoice == 'n');
        {   
            //if the player enter n the program will print the total points of the player then will switch the control to other player
            chooseInAsk(name, p);

            (turn) ? turn = false : turn = true;

            break;
        }
    }
    while(!continueChoice == 'y' && !continueChoice == 'n');
}

//This function ask the player name
void askPlayerName(Player players)
{   
    //We define a variable whose data  type is a structure so in that way we can access the member inside of the structure named Player
    
    std::cout << "Player one name: ";
    //We use getline function to read the whole string even if it have a whitespace
    std::getline(std::cin >> std::ws, players.playerNameOne); //std::ws is a input manipulator that tell std::cin to ignore any leading whitespace before extraction

    std::cout << "Player two name: ";
    std::getline(std::cin >> std::ws, players.playerNameTwo);

    playerTurn(players, PlayerScore::makeTurn);
}

int performRoll(std::string& playerName, Player plaYer, bool& pTurn)
{   
    char playerChoice{};
    
    plaYer.randomNum = randomNumGen(1, 6);

    int randomNumber = plaYer.randomNum;

    while (true)
    {
        //Add validating input here using do while loop
        std::cout << '\n' << playerName << " it's your turn\n";
        std::cout << "Press ([R] to roll, Press [H] to hold): ";
        std::cin >> playerChoice;
    
        if (playerChoice == 'r')
        {   
            //This will create a little effect of dice rollling
            std::cout << "\nDice is rolling. . . . . . . .\n";
            Sleep(3000); //Sleep function allow us to do that and we can access sleep function when windows.h is included in the header

            std::cout << "\nYou rolled\n";
            drawDice(randomNumber); //When the dice rolled called the draw function and display the dice base on the randomNumber
            checkDiceRolled(randomNumber, playerName, plaYer, pTurn);
            break;
        }

        else
        {   
            //If the player hold the dice the player will swithc to playerOne to playerTwo or playerTwo to playerOne
            if (playerName == plaYer.playerNameOne)
            {   
                std::cout << "Your total score is: " << PlayerScore::totalPlayerOneScore << '\n';

                if (pTurn)
                {
                    pTurn = false;
                    playerTurn(plaYer, pTurn);
                }

                else
                {   
                    pTurn = true;
                    playerTurn(plaYer, pTurn);
                }
                break;
            }

            else
            {
                std::cout << "Your total score is: " << PlayerScore::totalPlayerTwoScore << '\n';
                
                if (pTurn)
                {
                    pTurn = false;
                    playerTurn(plaYer, pTurn);
                }

                else
                {
                    pTurn = true;
                    playerTurn(plaYer, pTurn);
                }
                break;
            }
        }
    }
    
    return randomNumber;
}

void checkDiceRolled(int numRand, std::string& name, Player pliyir, bool& switchTurn)
{   
    while(true)
    {   
        //If the dice rolled of the player are greater than 1 the player will get points if not the player will get 0 points
        if (numRand > 1)
        {   
            std::cout << "You get " << numRand << " points";

            if (name == pliyir.playerNameOne)
            {
                PlayerScore::totalPlayerOneScore += numRand;
            }

            else
            {
                PlayerScore::totalPlayerTwoScore += numRand;
            }

            break;
        }

        else
        {   
            std::cout << "You get 0 points\n";

            if (name == pliyir.playerNameOne)
            {   
                if (switchTurn)
                {
                    switchTurn = false;
                    playerTurn(pliyir, switchTurn);
                }

                else
                {   
                    switchTurn = true;
                    playerTurn(pliyir, switchTurn);
                }
                break;
            }

            else
            {
                if (switchTurn)
                {
                    switchTurn = false;
                    playerTurn(pliyir, switchTurn);
                }

                else
                {
                    switchTurn = true;
                    playerTurn(pliyir, switchTurn);
                }
                break;
        
            }   
        }
    }
}

void checkWinner(Player pCheckWinner)
{
    if (PlayerScore::totalPlayerOneScore >= 100)
    {
        std::cout << "\n=-=-=-=- Congrats You win!! -=-=-=-=";
        std::exit(0);
    }
    
    if (PlayerScore::totalPlayerTwoScore >= 100)
    {
        std::cout << "\n=-=-=-=- Congrats You win!! -=-=-=-=";
        std::exit(0);
    }
}

int main()
{   
    Player playerGetName;

    system("cls");

    std::cout << R"(
   _ \ _ _|   ___|      __ \ _ _|   ___|  ____|       ___|     \      \  |  ____| 
  |   |  |   |          |   |  |   |      __|        |        _ \    |\/ |  __|   
  ___/   |   |   |      |   |  |   |      |          |   |   ___ \   |   |  |     
 _|    ___| \____|     ____/ ___| \____| _____|     \____| _/    _\ _|  _| _____| 
                                                          
----------------------------------------------By: Mark Ghian Francis---------------------------------------
    )" << "\n";

    int menuChoice{};
    
    std::cout << "\n[1] Start game";
    std::cout << "\n[2] Exit\n";
    std::cout << "\nChoice: ";
    std::cin >> menuChoice;

    switch (menuChoice)
    {
        case 1:
            system("cls");
            askPlayerName(playerGetName);
            break;
        case 2:
            return 0; //if user choice exit the program will exit

        default:
            break;
    }

    return 0;
}