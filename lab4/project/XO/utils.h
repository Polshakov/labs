//#pragma once
#ifndef XO_H
#define XO_H


	enum Status {
		PLAY,
		USER_WIN,
		BOT_WIN,
		NOT_WIN
	};

	struct Game {
		char board[3][3] = {};
		bool isUserTurn;
		char userChar;
		char botChar;
		int playerScore = 0;
		int botScore = 0;
		Status status;
	};

	Game initGame(char);
	void updateDisplay(const Game);
	bool updateGame(Game*);

#endif