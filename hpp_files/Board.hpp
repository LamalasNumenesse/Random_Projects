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

		int columnWin() {
			int scout1 = 0;
			int scout2 = 0;
			for (int y = 1; y < y_length; y++) {
				for (int x = 0; x < x_length; x++) {
					if (board[x][y] == 1) {
						scout1 += 1;
						scout2 = 0;
						if (scout1 >= 4) {
							return 1;
						}
					}
					else if (board[x][y] == 2) {
						scout2 += 1;
						scout1 = 0;
						if (scout2 >= 4) {
							return 2;
						}
					}
					else if (board[x][y] == 0) {
						scout1 = 0;
						scout2 = 0;
					}
				}
			}
			return 0;
		}

		int rowWin() {
			int scout1 = 0;
			int scout2 = 0;
			for (int x = 0; x < x_length; x++) {
				for (int y = 1; y < y_length; y++) {
					if (board[x][y] == 1) {
						scout1 += 1;
						scout2 = 0;
						if (scout1 >= 4) {
							return 1;
						}
					}
					else if (board[x][y] == 2) {
						scout2 += 1;
						scout1 = 0;
						if (scout2 >= 4) {
							return 2;
						}
					}
					else if (board[x][y] == 0) {
						scout1 = 0;
						scout2 = 0;
					}
				}
			}
			return 0;
		}

		int diagonalUp() {
			int scout1 = 0;
			int scout2 = 0;
			for (int w = 0; w < x_length; w++) {
				for (int z = 0; z < y_length-1; z++) {
					for (int x = w, y = z; x < x_length && y >= 0; x++, y--) {
						if (y != 0) {
							if (board[x][y] == 1) {
								scout1 += 1;
								scout2 = 0;
								if (scout1 >= 4) {
									return 1;
								}
							}
							if (board[x][y] == 2) {
								scout2 += 1;
								scout1 = 0;
								if (scout2 >= 4) {
									return 2;
								}
							}
							else {
								scout1 = 0;
								scout2 = 0;
							}
						}
						else {
							scout1 = 0;
							scout2 = 0;
						}
					}
				}
			}
			return 0;
		}

		int diagonalDown() {
			int scout1 = 0;
			int scout2 = 0;
			for (int w = 0; w < x_length; w++) {
				for (int z = 0; z < y_length-1; z++) {
					for (int x = w, y = z; x < x_length && y < y_length; x++, y++) {
						if (y != 0) {
							if (board[x][y] == 1) {
								scout1 += 1;
								scout2 = 0;
								if (scout1 >= 4) {
									return 1;
								}
							}
							if (board[x][y] == 2) {
								scout2 += 1;
								scout1 = 0;
								if (scout2 >= 4) {
									return 2;
								}
							}
							else {
								scout1 = 0;
								scout2 = 0;
							}
						}
						else {
							scout1 = 0;
							scout2 = 0;
						}
					}
				}
			}
			return 0;
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
			board = 0;
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

		int determine_player_winner(){
			int WinnerC = columnWin();
			int WinnerR = rowWin();
			int WinnerDU = diagonalUp();
			int WinnerDD = diagonalDown();
			if (WinnerC != 0) {
				return WinnerC;
			}else if(WinnerR != 0){
				return WinnerR;
			}else if(WinnerDU != 0){
				return WinnerDU;
			}else if(WinnerDD != 0){
				return WinnerDD; 
			}else{
				return 0;
			}
		}

		void purge_pieces(){
			for (int y = 0; y < y_length; y++) {
				for (int x = 0; x < x_length; x++) {
					if (y == 0) {
						board[x][y] = x+1;
					}
					else {
						if (board[x][y] == 1) {
							board[x][y] = 0;
						}
						else if (board[x][y] == 2) {
							board[x][y] = 0;
						}
						else {
							board[x][y] = 0;
						}
					}
				}
			}
		}

};

#endif
