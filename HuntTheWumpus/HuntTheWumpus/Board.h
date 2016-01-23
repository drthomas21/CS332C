#pragma once
namespace game {
	class Board {
		enum IDS { EMPTY_SPACE, PLAYER_ID, WAMPUS_ID, TELEPORT_ID, TRAP_ID, ARROW_ID };
		enum EVENT_RESPONSE { INVALID_MOVE, NOTHING_HAPPENED, KILLED_WAMPUS, ATE_BY_WAMPUS, TELEPORTED, TRIGGERED_TRAP, GOT_ARROW };
		enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };
	private:
		static Board& Instance;
		void operator = (Board const&);
		Board(Board const&);
	protected:
		Board();
		Board(int);
		int size;
		int** slots;
		bool isValidLocation(int, int);
		int moveNorth(int);
		int moveSouth(int);
		int moveEast(int);
		int moveWest(int);

	public:
		static Board getInstance(int);
		int move(int, int);
		int getSize();
	};
}