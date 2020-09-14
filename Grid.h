#ifndef H_GRID
#define H_GRID

#include <iostream>
using namespace std;

class Player;

class Grid
{
public:
	Grid();
	void emptyGrid();
	void updateGrid(int x, int y, char c);
	void display(int player);

	Player* p1() { return m_p1; }
	Player* p2() { return m_p2; }

private:
	char m_grid[15][15];
	Player* m_p1 = nullptr;
	Player* m_p2 = nullptr;

};





#endif // !H_GRID

