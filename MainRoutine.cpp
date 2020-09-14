
#include "Grid.h"
#include "Player.h"
#include <conio.h>
#include <iostream>
using namespace std;


int main() {

	// INITIALIZE GAME
	char q = '0';
	Grid d;
	d.display(1);
	int turncount = 0;
	bool lost = false;

	// TAKING TURNS COMMENCING

	while (q != 'q') {
		turncount++;

		//////////// INDICATORS FOR MECHANICS ////////////

		int whosTurn = turncount % 2;
		Player* turn = nullptr;
		Player* notTurn = nullptr;
		Trap* temp = nullptr;
		int player = 0;
		int enemyTrap = 0;
		bool wait = false;
		bool cantWait = false;
		bool slowNextRound = false;
		bool alreadyAttacked = false;
		bool trapInPlace = false;

		//////////// TURN TAKING METHOD /////////////

		switch (whosTurn) {
		case 1:
			turn = d.p1();
			notTurn = d.p2();
			player = 1;
			break;
		case 0:
			turn = d.p2();
			notTurn = d.p1();
			player = 2;
			break;
		default:
			break;
		}

		while (turn->getMoves() > 0) {
			system("cls");
			d.display(player);

			///////////////// DASHBOARD UPDATES ////////////////

			if (enemyTrap == 2) {
				cout << "An enemy trap is blocking that spot!" << endl;
				enemyTrap = 0;
			}

			///////////////////
			if (enemyTrap == 1) {
				cout << "The enemy trap has slowed you down!" << endl;
				enemyTrap = 0;
			}
			//////////////////

			if (cantWait) {
				cout << "You cannot wait after making a move." << endl;
				cantWait = false;
			}

			if (alreadyAttacked) {
				cout << "You cannot attack the same trap twice in one round!" << endl;
				alreadyAttacked = false;
			}

			if (trapInPlace) {
				cout << "A trap already exists here!" << endl;
				trapInPlace = false;
			}
			
			if (lost) {
				cout << "Lost";
			}

			//////////////// TAKE PLAYER INPUT //////////////////

			q = _getch();
			if (q == 'q')
				break;

			/////////////// DECIFERING PLAYER INPUT ////////////////

			switch (q) {

			// WAIT //

			case 'w':
				if (turn->getMoves() == 2) {
					wait = true;
					turn->setMoves(0);
				}
				else {
					cantWait = true;
				}
				break;

			// BREAK A TRAP //

			case 'b':

				d.updateGrid(turn->getPointerX(), turn->getPointerY(), ' ');

				// CHECK IF TRAP HASNT ALREADY BEEN ATTACKED IN TURN //

				if (notTurn->checkAttacked(turn->getPointerX(), turn->getPointerY()) == nullptr) {

					// Attacking a trap 
					if (turn->getMoves() == 3) {
						if (notTurn->checkTraps(turn->getPointerX(), turn->getPointerY())) {
							temp = notTurn->returnTrap(turn->getPointerX(), turn->getPointerY());
							temp->m_health = 0;
							turn->setMoves(turn->getMoves() - 2);
						}
					}
					else {
						if (notTurn->checkTraps(turn->getPointerX(), turn->getPointerY())) {
							temp = notTurn->returnTrap(turn->getPointerX(), turn->getPointerY());
							temp->m_health = temp->m_health - 1;
							turn->setMoves(turn->getMoves() - 1);
						}
					}

					Trap* p = notTurn->checkAttacked(turn->getPointerX(), turn->getPointerY());
					notTurn->setAttacked(turn->getPointerX(), turn->getPointerY());

				}
				else
					alreadyAttacked = true;
				
				// Updating Grid
				turn->updateTraps();
				notTurn->updateTraps();
				d.updateGrid(turn->getX(), turn->getY(), 'O');
				d.updateGrid(notTurn->getX(), notTurn->getY(), 'O');

				turn->setPointerToCoords();

				break;

			// LAY A TRAP //

			case 't':		

				if (turn->checkTraps(turn->getX(), turn->getY()) == 0 && notTurn->checkTraps(turn->getX(), turn->getY()) == 0) {
					d.updateGrid(turn->getPointerX(), turn->getPointerY(), ' ');

					// Adding trap
					turn->addTrap();

					// Updating Grid
					turn->updateTraps();
					notTurn->updateTraps();
					d.updateGrid(turn->getX(), turn->getY(), 'O');
					d.updateGrid(notTurn->getX(), notTurn->getY(), 'O');

					turn->setMoves(turn->getMoves() - 1);
					turn->setPointerToCoords();
				}
				else
					trapInPlace = true;

				break;

			// MOVE PLAYER //

			case 'm':	

				// If the player or enemy is on the spot point is at
				if ((turn->getPointerX() == turn->getX() && turn->getPointerY() == turn->getY()) || 
					(turn->getPointerX() == notTurn->getX() && turn->getPointerY() == notTurn->getY()))
					break;
				// Block Movement
				else if (notTurn->checkTraps(turn->getPointerX(), turn->getPointerY()) == 2) {
					enemyTrap = 2;
					break;
				}
				// Remove one turn
				else if (notTurn->checkTraps(turn->getPointerX(), turn->getPointerY()) == 1) {
					enemyTrap = 1;

					////////// MOVE PLAYER //////////

					d.updateGrid(turn->getX(), turn->getY(), ' ');

					turn->setCoordsToPointer();

					// ReUpdate Grid //

					turn->updateTraps();
					notTurn->updateTraps();
					d.updateGrid(notTurn->getX(), notTurn->getY(), 'O');
					d.updateGrid(turn->getX(), turn->getY(), 'O');

					/////////////////////////////

					if (turn->getMoves() == 2) {
						turn->setMoves(0);
					}
					else if (turn->getMoves() == 3) {
						turn->setMoves(1);
					}
					else {
						turn->setMoves(0);
						slowNextRound = true;
					}

				}
				else {
					d.updateGrid(turn->getX(), turn->getY(), ' ');

					turn->setCoordsToPointer();
					turn->setMoves(turn->getMoves() - 1);

					// ReUpdate Grid //

					turn->updateTraps();
					notTurn->updateTraps();
					d.updateGrid(notTurn->getX(), notTurn->getY(), 'O');
					d.updateGrid(turn->getX(), turn->getY(), 'O');

				}
				break;

			// MOVING POINTER //

			case 'j':
			case 'k':
			case 'i':
			case 'l':		
				if (turn->getPointerX() == turn->getX() && turn->getPointerY() == turn->getY())
					d.updateGrid(turn->getX(), turn->getY(), 'O');
				else
					d.updateGrid(turn->getPointerX(), turn->getPointerY(), ' ');

				turn->movePointer(q);

				if (turn->getPointerX() != turn->getX() || turn->getPointerY() != turn->getY())
					d.updateGrid(turn->getPointerX(), turn ->getPointerY(), '.');

				turn->updateTraps();
				notTurn->updateTraps();

				d.updateGrid(notTurn->getX(), notTurn->getY(), 'O');
				d.updateGrid(turn->getX(), turn->getY(), 'O');
				break;
			default:
				break;
			}

			if (q == 'a')
				turn->setMoves(turn->getMoves() - 1);
			
		}

		// RESETING MOVES IN DIFFERENT CONDITIONS //

		if (wait) {
			turn->setMoves(3);
			wait = false;
		}
		else if (slowNextRound) {
			turn->setMoves(1);
			slowNextRound = false;
		}
		else
			turn->setMoves(2);

		/////// RESETTING ALL TRAPS TO UNATTACKED ///////

		notTurn->resetAttacked();

		// CHECKING IF THE OTHER PLAYER IS SURROUNDED //

		if (notTurn->isSurrounded(*turn)) {
			lost = true;
			break;
		}


		/////////////////////////////////////////////////

		if (q == 'q')
			break;
	}

	if (lost) {
		system("cls");
		d.display(1);
		cout << "GAME OVER!";
	}

}
