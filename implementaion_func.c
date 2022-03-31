void interactivePlay()
{
	int board[GRID_SIZE][GRID_SIZE];
	int row, column, winner;
	unsigned int seed = SEED;

	createBoard(board);
	displayBoard(board);

	printf("\nWelcome to the most magnificent Reversi Game!\n");

	/* Seed for the random player */
	srand(seed);

	printf("You are player 1... \n");

	/* Check whether the game is not over */
	while (!gameOver(board))
	{
		/* If player 1 has no moves - skip to player 2 */
		if (hasMoves(board, FIRST))
		{
			printf("\nPlay:\n");
			printf("Enter row and column: ");
			scanf("%d %d", &row, &column);

			while (!(isLegal(board, FIRST, row, column)))
			{
				printf("Not a legal move! Please try again...\n");
				printf("Enter row and column: ");
				scanf("%d %d", &row, &column);
			}

			play(board, FIRST, row, column);
			displayBoard(board);
		}
		else
			printf("You can't play, there are no legal moves. Player 2 will play again\n");

		printf("May I (player 2) play? (press ENTER for Yes)\n");
		getchar();
		getchar();

		/* If player 2 has no moves - skip to player 1 */
		if (hasMoves(board, SECOND))
		{
			randomPlayer(board, SECOND);
			displayBoard(board);
		}
		else
			printf("I can't play, there are no legal moves. Player 1 will play again\n");
	} /* End of while(!gameOver(board....) */

	/* Declare the winner */
	winner = findTheWinner(board);

	if (winner == FIRST)
	{
		printf("\n\t *************************");
		printf("\n\t * You are the winner !! *");
		printf("\n\t *************************\n");
	}
	else if (winner == SECOND)
		printf("\nYou lost :( \n");
	else
		printf("\nThe game ended in a tie...\n");
} /* End of interactivePlay */

void randomPlayer(int board[][GRID_SIZE], int player)
{
	/* Define the parameters and their initial values */
	int movesArray[GRID_SIZE*GRID_SIZE][2];
	int numOfMoves, chosenMove;
	int row, column;

	/* number of possible moves */
	numOfMoves = validMoves(board, player, movesArray); /* Gets the possible moves of <player> */

	/* The chosen move out of all the possible moves */
	chosenMove = (int)((double)rand() / ((double)RAND_MAX + 1) * (numOfMoves)); /* The index (in movesArray) of the move */

	printf("Move %d out of %d\n", chosenMove, numOfMoves);

	if (chosenMove != -1)
	{ /* There is a possible move (with benefit > 0) */
		row = movesArray[chosenMove][0];
		column = movesArray[chosenMove][1];
		play(board, player, row, column);
	}
	/* Else - we didn't change the board */
} /* End of randomPlayer */

//maya
void createBoard(int board[][GRID_SIZE])
{
	int row, column;
	int indexBeggin;
	indexBeggin = (GRID_SIZE + 1) / 2;
	indexBeggin = indexBeggin - 1;

	for (row = 0; row < GRID_SIZE; row++)
	{
		for (column = 0; column < GRID_SIZE; column++)
		{
			board[row][column] = 0;
			board[indexBeggin][indexBeggin] = 1;
			board[indexBeggin][indexBeggin + 1] = 2;
			board[indexBeggin + 1][indexBeggin] = 2;
			board[indexBeggin + 1][indexBeggin + 1] = 1;
		}
	}
}

//maya
void displayBoard(int board[][GRID_SIZE])
{
	int row, column;

	/* First row */
	printf("   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf(" %d ", column);

	/* Second row */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");

	/* The board */
	for (row = 0; row < GRID_SIZE; row++)
	{
		printf("\n%d |", row);
		for (column = 0; column < GRID_SIZE; column++)
		{
			if (board[row][column] != EMPTY)
				printf(" %d ", board[row][column]);
			else
				printf("   ");
		} /* End of for column */
		printf("|");
	} /* End of for row */

	/* Last row) */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");
	printf("\n");
} /* End of displayBoard */

//naor
int isLegal(int board[][GRID_SIZE], int player, int row, int column)
{
	int i, j, x, y;
	if (board[row][column] == EMPTY)
	{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				x = row + i;
				y = column + j;
				if (x < 0 || x >= GRID_SIZE)
					continue;
				if (y < 0 || y >= GRID_SIZE)
					continue;
				if (board[x][y] == 3 - player)
				{
					while (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE && board[x][y] == 3 - player)
					{
						x += i;
						y += j;
					}
					if (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE && board[x][y] == player)
						return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//doron
int play(int board[][GRID_SIZE], int player, int row, int column)
{

	int i;
	if (board[row - 1][column] != player && board[row - 1][column] != 0)
	{
		while (board[row - 1][column] != player && board[row - 1][column] != 0)
		{
			HelpPlay(board, player, row - 1, column);
			row++;

		}
		board[row - 1][column] = player;
	}
	if (board[row][column - 1] != player && board[row][column - 1] != 0)
	{
		while (board[row][column - 1] != player && board[row][column - 1] != 0)
		{
			HelpPlay(board, player, row, column - 1);
			column++;

		}
		board[row][column - 1] = player;
	}
	if (board[row + 1][column] != player && board[row + 1][column] != 0)
	{
		while (board[row + 1][column] != player && board[row + 1][column] != 0)
		{
			HelpPlay(board, player, row + 1, column);
			row--;

		}
		board[row + 1][column] = player;
	}
	if (board[row][column + 1] != player && board[row][column + 1] != 0)
	{
		while (board[row][column + 1] != player && board[row][column + 1] != 0)
		{
			HelpPlay(board, player, row, column + 1);
			column--;

		}
		board[row][column + 1] = player;
	}
	if (board[row - 1][column - 1] != player && board[row - 1][column - 1] != 0)
	{
		while (board[row - 1][column - 1] != player && board[row - 1][column - 1] != 0)
		{
			HelpPlay(board, player, row - 1, column - 1);
			column++;
			row++;

		}
		board[row - 1][column - 1] = player;
	}
	if (board[row + 1][column - 1] != player && board[row + 1][column - 1] != 0)
	{
		while (board[row + 1][column - 1] != player && board[row + 1][column - 1] != 0)
		{
			HelpPlay(board, player, row + 1, column - 1);
			column++;
			row--;

		}
		board[row + 1][column - 1] = player;
	}
	if (board[row + 1][column + 1] != player && board[row + 1][column + 1] != 0)
	{
		while (board[row + 1][column + 1] != player && board[row + 1][column + 1] != 0)
		{
			HelpPlay(board, player, row + 1, column + 1);
			column--;
			row--;

		}
		board[row + 1][column + 1] = player;
	}
	if (board[row + 1][column - 1] != player && board[row + 1][column - 1] != 0)
	{
		while (board[row + 1][column - 1] != player && board[row + 1][column - 1] != 0)
		{
			HelpPlay(board, player, row + 1, column - 1);
			column++;
			row--;

		}
		board[row + 1][column - 1] = player;
	}

}

//doron
void HelpPlay(int board[][GRID_SIZE], int player, int row, int column)//switch players
{
	int i;
	if (board[row][column] != player && board[row][column] != 0)
	{
		for (i = 0; board[row][column] != player; i++)
		{
			board[row][column] = player;
		}
	}
}

//maya
int findTheWinner(int board[][GRID_SIZE])
{
	int i, j;
	int counterP1 = 0;
	int counterP2 = 0;
	int leader;

	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++) {
			if (board[i][j] == FIRST) {
				counterP1++;
			}
			else {
				if (board[i][j] == SECOND) {
					counterP2++;
				}
			}
		}
	}
	if (counterP1 > counterP2) {
		leader = FIRST;
	}
	else
	{
		if (counterP2 > counterP1) {
			leader = SECOND;
		}
	}
	if (counterP1 == counterP2) {
		leader = EMPTY;
	}

	return leader;
}

//maya
int gameOver(int board[][GRID_SIZE])
{
	int i, j;
	int counter1 = 0;
	int counter2 = 0;
	int sizeAllBoard;

	sizeAllBoard = GRID_SIZE * GRID_SIZE;

	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (board[i][j] == 1) {
				counter1++;
			}
			if (board[i][j] == 2) {
				counter2++;
			}
		}
		if (counter2 == sizeAllBoard)
			return TRUE;
		if (counter1 + counter2 == sizeAllBoard)
			return TRUE;
		if (counter1 == sizeAllBoard)
			return TRUE;
	}

	return FALSE;
}

//naor+maya
int validMoves(int board[][GRID_SIZE], int player, int movesArr[][2])
{
	int i, j, x, y;
	int counter = 0;
	int check = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			check=isLegal(board, player, i, j);
			if (check == TRUE)
			{
				
				movesArr[counter][0] = i;
				movesArr[counter][1] = j;
				counter++;
			}
		}
	}
	return counter;
}

//doron
int HelpBenfit(int board[][GRID_SIZE], int player, int row, int column)
{
	int i, count = 0;
	if (board[row][column] != player && board[row][column] != EMPTY)
	{

		for (i = 0; board[row][column] != player; i++)
		{
			board[row][column] = player;
			count++;
		}
	}
	return count;
}

//doron
int benefit(int board[][GRID_SIZE], int player, int row, int column)
{
	int i, j, x, y;
	int counter = 0;
	if (board[row][column] == EMPTY)
	{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				x = row + i;
				y = column + j;
				if (x < 0 || x >= GRID_SIZE)
					continue;
				if (y < 0 || y >= GRID_SIZE)
					continue;
				if (board[x][y] == 3 - player)
				{
					while (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE && board[x][y] == 3 - player)
					{
						x += i;
						y += j;
					}
					if (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE && board[x][y] == player)
					{
						while (0 <= x && x < GRID_SIZE && 0 <= y && y < GRID_SIZE && board[x][y] == 3 - player)
						{
							counter++;
							x += i;
							y += j;
						}
					}
				}
			}
		}
	}
	return counter;
}

//naor
int hasMoves(int board[][GRID_SIZE], int player)
{
	int i, j, k, counter = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (board[i][j] == EMPTY) 
			{
				if (i - 1 >= EMPTY)
				{
					if (board[i - 1][j] != EMPTY && board[i - 1][j] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i - k < EMPTY)
								break;
							if (board[i - k][j] != EMPTY && board[i - k][j] != player)
								continue;
							if (board[i - k][j] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
				if (i + 1 >= GRID_SIZE-1)
				{
					if (board[i + 1][j] != EMPTY && board[i + 1][j] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i + k >= GRID_SIZE-1)
								break;
							if (board[i + k][j] != EMPTY && board[i + k][j] != player)
								continue;
							if (board[i + k][j] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
				if (j - 1 >= EMPTY)
				{
					if (board[i][j - 1] != EMPTY && board[i][j - 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (j - k < EMPTY)
								break;
							if (board[i][j - k] != EMPTY && board[i][j - k] != player)
								continue;
							if (board[i - k][j] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}

				if (j + 1 <= GRID_SIZE-1)
				{
					if (board[i][j + 1] != EMPTY && board[i][j + 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (j + k <= GRID_SIZE-1)
								break;
							if (board[i][j + k] != EMPTY && board[i][j + k] != player)
								continue;
							if (board[i][j + k] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
				if (j- 1 >=EMPTY&&i-1>=EMPTY)
				{
					if (board[i - 1][j - 1] != EMPTY && board[i - 1][j - 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i - k <= EMPTY || j - k <= EMPTY)
								break;
							if (board[i - k][j - k] != EMPTY && board[i - k][j - k] != player)
								continue;
							if (board[i - k][j - k] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}

				if (j - 1 >= EMPTY&&i + 1 <= GRID_SIZE-1)
				{
					if (board[i + 1][j - 1] != EMPTY && board[i + 1][j - 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i + k >= GRID_SIZE-1 || j - k <= EMPTY)
								break;
							if (board[i + k][j - k] != EMPTY && board[i + k][j - k] != player)
								continue;
							if (board[i + k][j - k] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
				if (i - 1 >= EMPTY&&j + 1 <= GRID_SIZE - 1)
				{
					if (board[i - 1][j + 1] != EMPTY && board[i - 1][j + 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i - k <= EMPTY || j + k >= GRID_SIZE-1)
								break;
							if (board[i - k][j + k] != EMPTY && board[i - k][j + k] != player)
								continue;
							if (board[i - k][j - k] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
				if (i + 1 <= GRID_SIZE - 1 &&j + 1 <= GRID_SIZE - 1)
				{
					if (board[i + 1][j + 1] != EMPTY && board[i + 1][j + 1] != player)
					{
						for (k = 2; k < GRID_SIZE; k++)
						{
							if (i + k >= GRID_SIZE-1 || j+k >= GRID_SIZE-1)
								break;
							if (board[i + k][j + k] != EMPTY && board[i + k][j + k] != player)
								continue;
							if (board[i + k][j + k] == EMPTY)
							{
								counter++;
								break;
							}
						}
					}
				}
				
			}
		}
	}
	if (!counter)
		return FALSE;
	else
		return TRUE;
}
