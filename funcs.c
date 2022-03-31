void interactivePlay();
void randomPlayer(int board[][GRID_SIZE], int player);
void createBoard(int[][GRID_SIZE]);/* Task 1 */
void displayBoard(int board[][GRID_SIZE]);                                 
int isLegal(int board[][GRID_SIZE], int player, int row, int column);/* Task 2 */
int play(int board[][GRID_SIZE], int player, int row, int column);/* Task 3 */
void HelpPlay(int board[][GRID_SIZE], int player, int row, int column);/* Task 3 */
int benefit(int[][GRID_SIZE], int, int, int);/* Task 4 */
int HelpBenfit(int board[][GRID_SIZE], int player, int row, int column);/* Task 4 */
int validMoves(int board[][GRID_SIZE], int player, int movesArr[][2]);/* Task 5 */
int hasMoves(int[][GRID_SIZE], int);/* Task 6 */
int findTheWinner(int board[][GRID_SIZE]);/* Task 7 */
int gameOver(int board[][GRID_SIZE]);/* Task 8 */
