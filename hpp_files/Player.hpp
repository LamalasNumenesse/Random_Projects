#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "./Board.hpp"

class Player{
  private:
    int number;
    std::string name;

  public:
    Player(){
      number = 0;
      name = "";
    }
    Player(int player_number){
      number = player_number;
      std::cout << "Player " << player_number << " What is your name: ";
      std::cin >> name;
    }

    int get_number(){
      return number;
    }

    std::string get_name(){
      return name;
    }

};

#endif