#pragma once
#include "Piece.h"
namespace game {
	class Board {
		enum IDS { EMPTY_SPACE, PLAYER_ID, WAMPUS_ID, TELEPORT_ID, TRAP_ID, ARROW_ID };
		enum EVENT_RESPONSE { INVALID_MOVE, NOTHING_HAPPENED, KILLED_WAMPUS, ATE_BY_WAMPUS, TELEPORTED, TRIGGERED_TRAP, GOT_ARROW };
		enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };
	private:
		static Board* Instance;
		void operator =(Board const&);
		Board(Board const&);
	protected:
		Board();
		Board(Board const&);
		static int size;
		int players;
		int** slots;
		Piece* pieces;
		bool const isValidLocation(int, int);
		bool const moveNorth(int);
		bool const moveSouth(int);
		bool const moveEast(int);
		bool const moveWest(int);
		void placePiece(int, int, int);
		void setUp();
	public:
		static Board* getInstance();
		static void setBoardSize(int);
		bool const move(int, int);
		int const getSize();
	};
}