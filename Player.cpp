#include "Player.h"
#include "Grid.h"
#include <iostream>
using namespace std;

// ALLOWS FOR POINTER TO MOVE AROUND FREELY IN ANY OF THE 8 SPACES AROUND THE PLAYER //

bool Player::movePointer(char dir) {
	bool moved = true;
	switch (dir) {
	case 'j':
		if (m_pointerX - 2 > 0 && (m_pointerX == m_x || m_pointerX == m_x + 2)) {
			m_pointerX -= 2;
		}
		break;
	case 'l':
		if (m_pointerX + 2 < 14 && (m_pointerX == m_x || m_pointerX == m_x - 2)) {
			m_pointerX += 2;
		}
		break;
	case 'i':
		if (m_pointerY - 2 > 0 && (m_pointerY == m_y || m_pointerY == m_y + 2)) {
			m_pointerY -= 2;
		}
		break;
	case 'k':
		if (m_pointerY + 2 < 14 && (m_pointerY == m_y || m_pointerY == m_y - 2)) {
			m_pointerY += 2;
		}
		break;
	default:
		moved = false;
		break;
	}
	return moved;
}

void Player::setGridPoint(Grid& d) { m_d = &d; }

vector<Trap*>::iterator Player::trapList() { return m_traps.begin(); }

bool Player::TrapListEmpty() {
	if (m_traps.empty())
		return true;
	else
		return false;
}

int Player::checkTraps(int x, int y) {
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;

	while (p != m_traps.end()) {
		temp = *p;
		if (temp->m_x == x && temp->m_y == y)
			return temp->m_health;
		p++;
	}

	return 0;
}

Trap* Player::returnTrap(int x, int y) {
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;

	while (p != m_traps.end()) {
		temp = *p;
		if (temp->m_x == x && temp->m_y == y)
			return temp;
		p++;
	}

	return nullptr;
}

void Player::updateTraps() {
	
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;
	bool deletedTrap = false;

	while (p != m_traps.end()) {
		temp = *p;
		
		switch (temp->m_health) {
		case 0:
			m_d->updateGrid(temp->m_x, temp->m_y, ' ');
			if (m_traps.size() > 1 && *p != m_traps.back()) {
				swap(*p, m_traps.back());
				m_traps.pop_back();
			}
			else
				m_traps.pop_back();
			delete temp;
			deletedTrap = true;
			break;
		case 1:
			m_d->updateGrid(temp->m_x, temp->m_y, '/');
			p++;
			break;
		case 2:
			m_d->updateGrid(temp->m_x, temp->m_y, 'X');
			p++;
			break;
		default:
			break;
		}
		if (deletedTrap)
			break;

	}
}

Trap* Player::checkAttacked(int x, int y) {
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;

	while (p != m_traps.end()) {
		temp = *p;

		if (temp->m_x == x && temp->m_y == y) {
			if (temp->m_wasAttacked)
				return temp;
		}

		p++;
	}

	return nullptr;

}

void Player::setAttacked(int x, int y) {
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;

	while (p != m_traps.end()) {
		temp = *p;

		if (temp->m_x == x && temp->m_y == y) {
			temp->m_wasAttacked = true;
			return;
		}

		p++;
	}
}

void Player::resetAttacked() {
	vector<Trap*>::iterator p = m_traps.begin();
	Trap* temp = nullptr;

	while (p != m_traps.end()) {
		temp = *p;

		temp->m_wasAttacked = false;

		p++;
	}
}

bool Player::isSurrounded(Player enemy) {
	
	bool test = true;
	
	// ROW ABOVE PLAYER //
	if (enemy.checkTraps(m_x - 2, m_y - 2) == 0) {
		if (enemy.getX() != (m_x - 2) || enemy.getY() != (m_y - 2))
			test = false;
	}
	
	if (enemy.checkTraps(m_x, m_y - 2) == 0) {
		if (enemy.getX() != m_x || enemy.getY() != (m_y - 2))
			test = false;
	}

	if (enemy.checkTraps(m_x + 2, m_y - 2) == 0) {
		if (enemy.getX() != (m_x + 2) || enemy.getY() != (m_y - 2))
			test = false;
	}

	// TWO SPACES SAME LEVEL AS PLAYER //
	if (enemy.checkTraps(m_x - 2, m_y) == 0) {
		if (enemy.getX() != (m_x - 2) || enemy.getY() != m_y)
			test = false;
	}

	if (enemy.checkTraps(m_x + 2, m_y) == 0) {
		if (enemy.getX() != (m_x + 2) || enemy.getY() != m_y)
			test = false;
	}

	// ROW BELOW PLAYER //
	if (enemy.checkTraps(m_x - 2, m_y + 2) == 0) {
		if (enemy.getX() != (m_x - 2) || enemy.getY() != (m_y + 2))
			test = false;
	}
	if (enemy.checkTraps(m_x, m_y + 2) == 0) {
		if (enemy.getX() != m_x || enemy.getY() != (m_y + 2))
			test = false;
	}
	if (enemy.checkTraps(m_x + 2, m_y + 2) == 0) {
		if (enemy.getX() != (m_x + 2) || enemy.getY() != (m_y + 2))
			test = false;
	}

	return test;
}