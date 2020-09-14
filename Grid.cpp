#include "Grid.h"
#include "Player.h"
#include <vector>
#include <stack>
#include <Windows.h>
#include <iostream>
using namespace std;

void SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

Grid::Grid() {
	m_p1 = new Player(5, 5);
	m_p2 = new Player(9, 9);
	m_p1->setGridPoint(*this);
	m_p2->setGridPoint(*this);
	emptyGrid();
	updateGrid(p1()->getX(), p1()->getY(), 'O');
	updateGrid(p2()->getX(), p2()->getY(), 'O');
}

void Grid::emptyGrid() {

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			m_grid[y][x] = ' ';
		}
	}

	for (int x = 0; x <= 7; x++) {
		for (int y = 0; y < 15; y++) {
			m_grid[y][2 * x] = '|';
		}
	}

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x < 15; x++) {
			m_grid[2 * y][x] = '-';
		}
	}

	for (int y = 0; y <= 7; y++) {
		for (int x = 0; x <= 7; x++) {
			m_grid[2 * y][2 * x] = '+';
		}
	}
}

void Grid::display(int player) {
	SetColor(15);
	cout << "Hunter's Game" << endl << "Player " << player << "'s turn." << endl;

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
			char c = m_grid[y][x];
			switch (c) {
			case ' ':
				cout << c;
				break;
			case '-':
			case '|':
			case '+':
				if (x > 3 && x < 11 && y > 3 && y < 11) {
					if (x > 5 && x < 9 && y > 5 && y < 9) {
						SetColor(3);
						cout << c;
						SetColor(15);
					}
					else {
						SetColor(6);
						cout << c;
						SetColor(15);
					}
				}
				else {
					cout << c;
				}
				break;
			case 'O':
				if (x == m_p1->getX() && y == m_p1->getY()) {
					SetColor(11);
					cout << c;
					SetColor(15);
				}
				else {
					SetColor(12);
					cout << c;
					SetColor(15);
				}
				break;
			case '.':
				if (x == m_p1->getPointerX() && y == m_p1->getPointerY()) {
					SetColor(11);
					cout << c;
					SetColor(15);
				}
				else {
					SetColor(12);
					cout << c;
					SetColor(15);
				}
				break;
			case 'X':
			case '/':
				if (m_p1->checkTraps(x, y) == 1 || m_p1->checkTraps(x, y) == 2) {
					SetColor(11);
					cout << c;
					SetColor(15);
				}
				else {
					SetColor(12);
					cout << c;
					SetColor(15);
				}
				break;
			default:
				break;
			}	
		}
		cout << endl;
	}

	// Printing number of moves left //

	if (player == 1) {
		cout << m_p1->getMoves();
	}
	else {
		cout << m_p2->getMoves();
	}
	cout << " moves left." << endl;
}

void Grid::updateGrid(int x, int y, char c) {
	m_grid[y][x] = c;
}

