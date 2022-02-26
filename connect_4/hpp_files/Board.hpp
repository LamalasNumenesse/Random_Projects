#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>

class Board {
  private:
    int x_length;
    int y_length;
    int** board;
    
    void fresh_board(){
      for (int y = 0; y < y_length; y++) {
	    	for (int x = 0; x < x_length; x++) {
	    		board[x][y] = 0;
	    	}
	    }
    }

    void print_board(){
    	for (int y = 0; y < y_length; y++) {
	    	for (int x = 0; x < x_length; x++) {
	    		std::cout << board[x][y];
	    	}
	    	std::cout << std::endl;
	    }
    }

  public:
    Board(){
      x_length = 0;
      y_length = 0;
      board = nullptr;
    }
    Board(int x, int y){
      x_length = x;
      y_length = y+1;
      board = new int*[x];
      for(int i = 0; i < x; i++){
        board[i] = new int[y+1];
      }
      fresh_board();
    }
    ~Board(){
      for(int i = 0; i < x_length; i++){
        delete[] board[i];
      }
      delete[] board;
    }

    int get_x_length(){
      return x_length;
    }

    int get_y_length(){
      return y_length;
    }

    int place_piece(int x_place, int piece){
      for(int i = y_length-1; i >= 0; i--){
        if (board[x_place-1][i] == 0){
          board[x_place-1][i] = piece;
          i == y_length+1;
          return 0;
        }
      }
      return 1;
    }

    void print_color_board(){
      for (int y = 0; y < y_length; y++) {
      	for (int x = 0; x < x_length; x++) {
      		if (y == 0) {
      			board[x][y] = x+1;
      			if (x <= 8) {
      				std::cout << "|\033[37;40m " << board[x][y] << "  ";
      				std::cout << "\033[0m";
      			}
      			if (x >= 9) {
      				std::cout << "|\033[37;40m " << board[x][y] << " ";
      				std::cout << "\033[0m";
      			}
      		}
      		else {
      			if (board[x][y] == 1) {
      				std::cout << "|\033[31;41m " << board[x][y] << "  ";
      			}
      			else if (board[x][y] == 2) {
      				std::cout << "|\033[34;44m " << board[x][y] << "  ";
      			}
      			else {
      				board[x][y] = 0;
      				if (x <= 8) {
      					if (y % 2 == 0 && x % 2 == 0) {
      						std::cout << "|\033[30;40m " << board[x][y] << "  ";
      					}
      					else if (y % 2 == 1 && x % 2 == 1) {
      						std::cout << "|\033[30;40m " << board[x][y] << "  ";
      					}
      					else if (!(y % 2 == 1 && x % 2 == 1)) {
      						std::cout << "|\033[37;47m " << board[x][y] << "  ";
      					}
      					else if (!(y % 2 == 0 && x % 2 == 0)) {
      						std::cout << "|\033[37;47m " << board[x][y] << "  ";
      					}
      					std::cout << "\033[0m";
      				}
      				else if (x >= 9) {
      					if (y % 2 == 0 && x % 2 == 0) {
      						std::cout << "|\033[30;40m " << board[x][y] << "  ";
      					}
      					else if (y % 2 == 1 && x % 2 == 1) {
      						std::cout << "|\033[30;40m " << board[x][y] << "  ";
      					}
      					else if (!(y % 2 == 1 && x % 2 == 1)) {
      						std::cout << "|\033[37;47m " << board[x][y] << "  ";
      					}
      					else if (!(y % 2 == 0 && x % 2 == 0)) {
      						std::cout << "|\033[37;47m " << board[x][y] << "  ";
      					}
      					std::cout << "\033[0m";
      				}
      			}
      			std::cout << "\033[0m";
      		}
      	}
      	std::cout << std::endl;
      }
    }

};

#endif
