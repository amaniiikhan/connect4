#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Board {
//contains board dimensions
    int rows;
    int cols; };

char ** makeBoard(struct Board game, char **board){
//returns and prints an empty and labelled board
    for (int i = 0; i < game.rows; i++){
        for (int j = 0; j < game.cols; j++){
            if (j == game.cols - 2){
                board[i][j] = '\n';
            }     
            else if (j == game.cols - 1){
                board[i][j] = '\0';
            }
            else if (i == 0 && j == 0){
                board[i][j] = ' ';
            }
            else if (i == 0){
                board[i][j] = 'A' - 1 + j;
            }
            else if (j== 0){
                board[i][j] = '7' - i;
            }
            else{
                board[i][j] = '.';
            }
        }
        printf("%s",board[i]);}
    return board; }

_Bool isFull(char **board, struct Board game){
//checks if board is full
    for (int j = 0; j < game.cols; j++){
        if (board[1][j] == '.'){
            return false; } }
    printf("\nIt's a draw! End of game.\n");
    return true;}

struct node {
//struct for a node to be added to a linked list
    char data;
    struct node *next; };

void listAdd(char ch, struct node *head){
//creates and adds a node to the end of the
//linked list that head refers to
    struct node *new_node = NULL;
    new_node = malloc(sizeof(struct node));
    struct node *last = head;  
    new_node->data = ch;
    new_node->next = NULL;
    while (last->next != NULL){
        last = last->next;}
    last->next = new_node; }

void addChecker(char checker, char col, char **board, struct Board game){
//adds a checker to the board then prints the board with the added checker

    int colnum, rownum;
    colnum = col - 'A' + 1;
    for (int i = 1; i <  game.rows; i++){
        if (board[i][colnum] == '.'){
            rownum = i;
        }
    }
    board[rownum][colnum] = checker;
    for (int k = 0; k < game.rows; k++){
        printf("%s",board[k]); } }

_Bool horizWin(char checker, char **board, struct Board game){
//checks if there is a horizontal win for the checker
    for (int i = 1; i < game.rows; i++){
        for (int j = 1; j < game.cols - 3; j++){
            if (board[i][j] == checker
                && board[i][j+1] == checker
                && board[i][j+2] == checker
                && board[i][j+3] == checker){
                    return true;
                } } }
                return false; }

_Bool vertWin(char checker, char **board, struct Board game){
//checks if there is a vertical win for the checker 
   for (int i = 1; i < game.rows - 3; i++){
        for (int j = 1; j < game.cols; j++){
            if (board[i][j] == checker
                && board[i+1][j] == checker
                && board[i+2][j] == checker
                && board[i+3][j] == checker){
                    return true;
                } } }
                return false; }

_Bool uDiagWin(char checker, char **board, struct Board game){
//checks if there is an upwards diagonal win for the checker
    for (int i = 1; i < game.rows - 3; i++){
        for (int j = 1; j < game.cols - 3; j++){
            if (board[i][j] == checker
                && board[i+1 ][j-1] == checker
                && board[i+2][j-2] == checker
                && board[i+3][j-3] == checker){
                    return true;
                } } }
                return false; }

_Bool dDiagWin(char checker, char **board, struct Board game){
//checks if there is a downwards diagonal win for the checker
    for (int i = 1; i < game.rows - 3; i++){
        for (int j = 1; j < game.cols - 3; j++){
            if (board[i][j] == checker
                && board[i+1 ][j+1] == checker
                && board[i+2][j+2] == checker
                && board[i+3][j+3] == checker){
                    return true;
                } } }
                return false; }

_Bool isWin(char checker, char **board, struct Board game){
//checks if there is any win for the checker
    if (horizWin(checker, board, game) || vertWin(checker, board, game) 
        || uDiagWin(checker, board, game)  || dDiagWin(checker, board, game)){
            return true;
        }
    return false; }

int main(){
    struct Board game; //will contain dimensions for the board
    game.rows = 7;
    game.cols = 10;
    char **gboard; //pointer to a 2D array (the game board)
    gboard = malloc(sizeof(char *) * game.rows);
    for (int i = 0; i < game.rows; i++){
        gboard[i] = malloc(sizeof(char) * game.cols);
    }
    if (gboard == NULL){
        printf("ERROR: malloc failed!\n");
        exit(1);
    }
    if (gboard != NULL){
        makeBoard(game,gboard); //creates an empty and labelled board
    }
    struct node *head; //will refer to list of moves
    head = NULL;
    head = malloc(sizeof(struct node));
    int moves = 0; //counter variable of moves
    char column; //column player wants to add to
    printf("\nWelcome to Connect Four!\nPlayer X will start.\n");
    //conduct first move (Player X)
    printf("Player X:\nEnter column: ");
    scanf("%c",&column); //get user input to decide column
    head->data = column; //put information in head node
    head->next = NULL;
    printf("\n");
    addChecker('X',column,gboard,game); //add move to board
    moves ++; //update moves
    //conduct rest of the moves until win or draw
    while (isFull(gboard,game) != true){
        if (moves % 2 != 0){
	 //odd moves are Player O 
	    printf("Player O:\nEnter column: ");
            scanf(" %c",&column);
            listAdd(column, head); //add to list referred to by head
            printf("\n");
            addChecker('O',column, gboard, game);
            moves++;
            if (isWin('O',gboard,game) == true){
		//if there is a win, game is over so we break the loop
                printf("\nCongratulations! Player O has won!");
                break;
            }
        }
        else{
	//even moves are Player X
	    printf("Player X:\nEnter column: ");
            scanf(" %c",&column);
            listAdd(column, head);
            printf("\n");
            addChecker('X',column, gboard, game);
            moves++;
            if (isWin('X',gboard,game) == true){
                printf("\nCongratulations! Player X has won!");
                break;
        }
    } }
    //print moves
    printf("\nMoves: ");
    while (head != NULL){
        printf("%c ",head->data);
        head = head->next;}
    //free up allocated space
    free(gboard);
    return 0;

    }
