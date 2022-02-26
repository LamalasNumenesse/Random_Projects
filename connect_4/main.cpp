#include <iostream>
#include <limits>
#include <typeinfo>
#include "./hpp_files/Player.hpp"

void da_rulez(){
  std::cout << "Players must connect 4 of the same colored discs in a row to win.\n"
            << "Only one piece is played at a time.\n"
            << "Players can be on the offensive or defensive.\n"
            << "The game ends when there is a 4-in-a-row or a stalemate.\n"
            << "The starter of the previous game goes second on the next game." << std::endl;
}

int question_prompt(std::string question){
  while(true){
    char input = '0';
    std::cout << question << " (y/n): ";
    std::cin >> input;
    if (input == 'y'){
      return 1;
    }else if (input == 'n'){
      return 0;
    }else{
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    std::cout << "Sorry that is wrong input, try again.\n" << std::endl;
    }
  }
}

int place_piece_promt(Board* board, Player* curr_player){
  while (true){
    int x_place = 0;
    std::cout << curr_player->get_name() << " What place would you like to place your piece: ";
    std::cin >> x_place;
    if(x_place > 0 and x_place <= board->get_x_length()){
      if (board->place_piece(x_place, curr_player->get_number()) == 0){
        if (curr_player->get_number() == 1){
          return 2;
        }else{
          return 1;
        }
      }else{
        std::cout << "Sorry but that column is full. Please try again! \n" << std::endl;
      }
    }else{
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    std::cout << "Sorry that is wrong input, try again.\n" << std::endl;
    }
  }
  
}

void game(Board* board, Player* p1, Player* p2){
  int current_player = 1;
  bool winner = false;
  while (!winner){
    if (current_player == 1) {
      board->print_color_board();
      current_player = place_piece_promt(board, p1);
		}
		if (current_player == 2) {
      board->print_color_board();
      current_player = place_piece_promt(board, p2);
		}
  }
}

int main(){
  Board board = Board(10, 7);
  Player p1 = Player(1);
  Player p2 = Player(2);

  if (question_prompt("Do you want to read the rules?") == 1){
    da_rulez();
    game(&board, &p1, &p2);
  }else{
    game(&board, &p1, &p2);
  }
  return 0;
}