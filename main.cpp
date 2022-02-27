#include <iostream>
#include <limits>
#include <typeinfo>
#include "./hpp_files/Player.hpp"

void da_rulez(){
  std::cout << "\nPlayers must connect 4 of the same colored discs in a row to win.\n"
            << "Only one piece is played at a time.\n"
            << "Players can be on the offensive or defensive.\n"
            << "The game ends when there is a 4-in-a-row or a stalemate.\n"
            << "The starter of the previous game goes second on the next game.\n" << std::endl;
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

void place_piece_promt(Board* board, Player* curr_player){
  while (true){
    int x_place = 0;
    std::cout << curr_player->get_name() << " what place would you like to place your piece: ";
    std::cin >> x_place;
    if(x_place > 0 and x_place <= board->get_x_length()){
      if (board->place_piece(x_place, curr_player->get_number()) == 0){
        break;
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

void game_over(Player* winner, Board* board, bool* running){
  std::cout << "Congratulations " << winner->get_name() << ", you won!\n" << std::endl;
  if (question_prompt("Would you like to play again") == 1){
    board->purge_pieces();
  }else{
    std::cout << "Alright quit! Have fun knowing that " << winner->get_name() << " is better than you!" << std::endl;
    *running = false;
  }
}

void game(Board* board, Player* p1, Player* p2){
  int current_player = 1;
  bool running = true;
  while (running){
    if (current_player == 1) {
      board->print_color_board();
      place_piece_promt(board, p1);
      if (board->determine_player_winner() == 1){
        game_over(p1, board, &running);
      }else{
        current_player = 2;
      }
    }else if (current_player == 2) {
      board->print_color_board();
      place_piece_promt(board, p2);
      if (board->determine_player_winner() == 2){
        game_over(p2, board, &running);
      }else{
        current_player = 1;
      }
		}else {
      current_player = 1;
    }
  }
}

int main(int argc, char *argv[]){
  Board board = Board(atoi(argv[1]), atoi(argv[2]));
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