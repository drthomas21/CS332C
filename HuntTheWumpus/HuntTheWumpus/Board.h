#include "Piece.h"
#include <string>
#pragma once

namespace game {
	class Board {
		private:
			static Board* Instance;
			void operator =(Board const&);
			Board(Board const&);
		protected:
			//Variables
			static int size;
			int players;
			int** slots;
			Piece* pieces;

			//Constructor
			Board();
			~Board();

			//Functions
			bool const isValidLocation(int, int);
			bool const isValidLocation(int, int, int);
			bool const moveNorth(int);
			bool const moveSouth(int);
			bool const moveEast(int);
			bool const moveWest(int);
			void setUp();
		public:
			//Constants
			enum IDS { EMPTY_SPACE = -10, DISCOVERED_SPACE };
			enum EVENT_RESPONSE { INVALID_MOVE, NOTHING_HAPPENED, KILLED_WAMPUS, ATE_BY_WAMPUS, TELEPORTED, TRIGGERED_TRAP, GOT_ARROW };
			enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };

			//Singleton
			static Board* getInstance();
			static void setBoardSize(int);
			static int const getSize();
			static int const getRandomNum();

			//Functions
			bool const move(int, int);			
			bool const isLocationFree(int, int);
			void placePiece(int, int, int);
			std::string printBoard(bool);
	};
}