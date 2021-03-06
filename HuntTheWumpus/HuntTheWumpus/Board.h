#include "Piece.h"
#include <string>
#ifndef BOARD_H
#define BOARD_H

namespace game {
	struct Slot {
		int x;
		int y;
		int id;
	};

	class Board {
		public:
			//Constants
			enum IDS { EMPTY_SPACE = -10, DISCOVERED_SPACE, PLAYER_ID = 0, WUMPUS_ID = 1 };
			enum EVENT_RESPONSE { NOTHING_HAPPENED, NO_ARROWS_LEFT, MISSED_WUMPUS, KILLED_WUMPUS, ATE_BY_WAMPUS, TELEPORTED, TRIGGERED_TRAP, GOT_ARROW,ITEM_DESTORYED };
			enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };

		private:
			static Board* Instance;
			void operator =(Board const&);
			Board(Board const&);
		protected:
			//Variables
			static int size;
			int players;
			int arrows;
			Slot** slots;
			Piece** pieces;
			Board::EVENT_RESPONSE event;

			//Constructor
			Board();
			~Board();

			//Functions
			bool const isValidLocation(Slot const, int, int);
			bool const isValidLocation(int, int, int);
			bool const moveNorth(int);
			bool const moveSouth(int);
			bool const moveEast(int);
			bool const moveWest(int);
			Slot* const getSlot(int);
			void setUp();

		public:
			//Singleton
			static Board* getInstance();
			
			static void setBoardSize(int);
			static int const getSize();
			static int const getRandomNum();

			//Functions
			bool const move(int, Board::DIRECTIONS);
			bool const isLocationFree(int, int);
			void placePiece(int, int, int);
			std::string printBoard(bool);
			void setEvent(Board::EVENT_RESPONSE);
			Board::EVENT_RESPONSE const getEvent();
			std::string const nearBy(int);
			void reset(int);
			std::string const __serialize();
			bool const __unserialize(std::string);
			Board::EVENT_RESPONSE const shootArrow(Board::DIRECTIONS,int);
			void pickupArrow();
			int const showArrowCount();
	};
}
#endif //BOARD_H