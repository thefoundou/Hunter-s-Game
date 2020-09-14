#ifndef H_PLAYER
#define H_PLAYER

#include <iostream>
#include <vector>
using namespace std;

const char ARROW_LEFT = 'h';
const char ARROW_RIGHT = 'l';
const char ARROW_UP = 'k';
const char ARROW_DOWN = 'j';

class Grid;

struct Trap
{
public:
	Trap(int x, int y)
		: m_x(x), m_y(y) {}
	int m_x = 0;
	int m_y = 0;
	int m_health = 2;
	bool m_wasAttacked = false;
};

class Player
{
public:
	Player(int x = 5, int y = 5)
		: m_x(x), m_y(y), m_pointerX(x), m_pointerY(y) {};

	void setGridPoint(Grid& d);

	int getX() { return m_x; }
	int getY() { return m_y; }

	void setCoordsToPointer() { m_x = m_pointerX;  m_y = m_pointerY;}
	void setPointerToCoords() { m_pointerX = m_x;   m_pointerY = m_y; }

	int getPointerX() { return m_pointerX; }
	int getPointerY() { return m_pointerY; }

	int getMoves() { return m_moves; }
	void setMoves(int n) { m_moves = n; }

	bool movePointer(char dir);

	void addTrap() {
		m_traps.push_back(new Trap(m_x, m_y));
	}

	int newTrapX() { return m_traps.back()->m_x; }
	int newTrapY() { return m_traps.back()->m_y; }

	vector<Trap*>::iterator trapList();
	bool TrapListEmpty();
	int checkTraps(int x, int y);

	void updateTraps();
	Trap* returnTrap(int x, int y);

	Trap* checkAttacked(int x, int y);
	void setAttacked(int x, int y);
	void resetAttacked();

	bool isSurrounded(Player enemy);

private:

	vector<Trap*> m_traps;
	int m_x = 0;
	int m_y = 0;
	int m_pointerX = 0;
	int m_pointerY = 0;
	int m_moves = 2;
	char m_char = 'O';
	Grid* m_d = nullptr;
};



#endif // !H_PLAYER

