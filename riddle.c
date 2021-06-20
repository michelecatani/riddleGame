#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This program was created by Michele Catani and submitted before a June 16, 2021 due date for Comp1400 at the 
University of Windsor.  The object of this game is to move the tiles until the gameboard is in order with the empty square 
occupying the bottom right space of the table. */

int main(void){

    // Welcome the player to the game.
    puts("Welcome to the game!");

    // This playAgain variable will be initalized as 1 and will only be changed at the end of the loop when the player decides if he wants to play again.
    int playAgain = 1;

    // Commence the main loop.

    while (playAgain == 1) {

        // flush scanf

        fflush(stdin);

        // set a new seed for random.

        srand(time(NULL));

        // Create a variable to start a new game if the user presses 0.  Will be used when we get the input for which square player wants to move.

        int startFresh = 0;
        
        // checkWin will be assigned the value 1 when the board is set up in such a way so as to satisfy the win condition.  For now, it is 0. This will be the condition of the while loop to continuously get player inputs.
        
        int checkWin = 0;
        
        // Initialize columns and rows variables.
        int columns = 0;
        int rows = 0;
        
        // Ask user for input to determine the number of rows and columns and check whether it is a valid input type.  Also ensure that the values for both are between 3 and 8.

        puts("How many columns do you want? Between 3 and 8.");
        
        while (scanf("%d", &columns) != 1){
            fflush(stdin);
            puts("The input must be an integer between 3 and 8!");
        }
        
        while (columns > 8 || columns < 3){
            puts("There can only be between 3 and 8 columns!!! Pick again.");
            while (scanf("%d", &columns) != 1){
                fflush(stdin);
                puts("The input must be an integer between 3 and 8!");
            }
        }
        
        puts("How many rows do you want? Between 3 and 8.");
        
        while (scanf("%d", &rows) != 1){
            fflush(stdin);
            puts("The input must be an integer between 3 and 8!");
        }
        
        while (rows > 8 || rows < 3){
            puts("There can only be between 3 and 8 rows!!! Pick again.");
            while (scanf("%d", &rows) != 1){
                fflush(stdin);
                puts("The input must be an integer between 3 and 8!");
            }
        }

        // Remind the player of their choice.

        printf("You have chosen to have a game with %d columns and %d rows!\n\n", columns, rows);

        // Create a variable arraySize that will be used throughout the program.

        int arraySize = columns * rows;

        // Initialize the gameBoard by using an array with size arraySize

        int gameBoard[arraySize];

        // Initialize a counter variable.  The same counter variable will be used throughout the program; its value will be changed as needed.
        int i = 0;

        // Fill the array with numbers from 0 to arraySize - 1 (0 will not be shown on the board).

        while (i < arraySize){
            gameBoard[i] = i;
            i++;
        }

        // Create two variables that will be used for the swapping when we shuffle the array.

        int forShuffle1 = 0;
        int forShuffle2 = 0;
        
        // Set counter to 0.

        i = 0;
        
        // Create a while loop that shuffles the array.  We will do 100 shuffles... this assures a certain level of randomness of the gameBoard.

        while (i < 100){
            forShuffle1 = (rand() % (rows * columns));
            forShuffle2 = (rand() % (rows * columns));
            int new1 = gameBoard[forShuffle1];
            int new2 = gameBoard[forShuffle2];
            gameBoard[forShuffle1] = new2;
            gameBoard[forShuffle2] = new1;
            i++;
        }

        /*  These can be used as test cases.  Comment out the code from 79 to 110 to use these.

        // int gameBoard[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 ,12 ,13 ,14 ,0 ,15};

        int gameBoard[] = {1, 2, 3, 4 , 5 , 6, 7, 8, 9 , 10 , 11, 12, 13, 14, 15, 16, 0, 17};

        // int gameBoard[] = {1,2,3,4,5,6,7,8,9, 10, 0, 11};

        */ 

        // The next little bit of code will be to show the gameBoard 

        printf("Here is the game board:\n\n");

        // Initialize rowNumber to be used in iteration to create the game.

        int rowNumber = 0;
        
        // Set counter to 0. (IF testing, must declare it with int.)

        i = 0;
        
        // This loop draws the table.

        while (rowNumber < rows) {

            // Initialize columnNumber to be used in iteration to create the gameBoard.

            int columnNumber = 0;

            //  While loop to print horizontally and then newline once we reach the end of a row.

            while (columnNumber < columns){
                if ((gameBoard[i] / 10) > 0){
                    printf("|%d ", gameBoard[i]);
                }
                else if (gameBoard[i] == 0){
                    printf("%s", "|   ");
                }
                else {
                    printf("| %d ", gameBoard[i]);
                } 
                // Update count and columnNumber.
                columnNumber++;
                i++;
            }
            
            // Update rowNumber and print the last vertical line to complete the row.
            
            printf("|\n");
            rowNumber++;
        }

        // Space for aesthetic purposes.

        printf("\n");

        // Initialize a variable moveNumber to 1.  This is to track how many moves.

        int moveNumber = 1;

        // Create a loop that will run unless the game has been won, using the checkWin variable.

        while (checkWin == 0){
            
            // Initialize numberToMove.  The number the player selects to move will be stored here later.

            int numberToMove;
            
            // Initialize a variable that will store the value of the emptySquareIndex.

            int emptySquareIndex;
            
            // Reset counter.

            i = 0;

            // Use a loop to find the emptySquareIndex.  We will need to use this to check and then to move the number selected.

            while (i < arraySize){
                if (gameBoard[i] == 0){
                    emptySquareIndex = i;
                    break;
                }
                i++;
            }

            //  Create a variable to figure out which index the user moved.  Initialized to -1.

            int movedSquareIndex = -1;

            // Create boolean variable that will store whether or not an adjacent square in that direction exists.  Initialize to true.

            int adjSquareUp = 1;
            int adjSquareDown = 1;
            int adjSquareLeft = 1;
            int adjSquareRight = 1;

            // Check the corresponding index values to see if we need to change the above variables to false.
            // The values will be set to false if the empty square doesn't have an adjacent square in that direction.

            if (emptySquareIndex == 0){
                adjSquareLeft = 0;
                adjSquareUp = 0;
            }
            else if (emptySquareIndex == columns - 1){
                adjSquareRight = 0;
                adjSquareUp = 0;
            }
            else if (emptySquareIndex == arraySize - columns){
                adjSquareLeft = 0;
                adjSquareDown = 0;
            }
            else if (emptySquareIndex == arraySize - 1){
                adjSquareDown = 0;
                adjSquareRight = 0;
            }
            else if (emptySquareIndex + columns >= arraySize){
                adjSquareDown = 0;
            }
            else if (emptySquareIndex - columns < 0){
                adjSquareUp = 0;
            }
            else if ((emptySquareIndex + 1) % columns == 0){
                adjSquareRight = 0;
            }
            else if ((emptySquareIndex) % columns == 0){
                adjSquareLeft = 0;
            }
            
            // Initialize an array to store the valid indices that can be moved.  Initialize values to negative numbers, as these will never be able to be moved.  
            
            int validIndices[4] = {-5, -5, -5, -5};

            // Check the boolean variables created and if they are true, we add the corresponding index to validIndices.

            if (adjSquareLeft == 1){
                validIndices[0] = emptySquareIndex - 1;
            }

            if (adjSquareRight == 1){
                validIndices[1] = emptySquareIndex + 1;
            }

            if (adjSquareUp == 1){
                validIndices[2] = emptySquareIndex - columns;
            }

            if (adjSquareDown == 1){
                validIndices[3] = emptySquareIndex + columns;
            }

            // Create a variable that will be used to determine whether or not the square the user selected can be moved.

            int canIMoveIt = 0;

            // Create a variable that will determine if the rest of the loop should be skipped.  This will be used in cases of invalid input.

            int skipRestOfLoop = 0;

            // This is the loop that gets player input and determines if it is valid.

            while (canIMoveIt == 0){
                
                // clear input for scanf.

                fflush(stdin);
                
                // Reset value of skipRestOfLoop so it functions properly.

                int skipRestOfLoop = 0;

                // Tell user what moveNumber it is and get input.  Check for type, and also if the user entered 0, we end the program.

                printf("It is move number %d. Which number would you like to move? (0 for exit)\n", moveNumber);
                    while (scanf("%d", &numberToMove) != 1){
                        fflush(stdin);
                        puts("You have to select an integer visible on the table!!!");
                    }
                if (numberToMove == 0){
                    puts("You have chosen to quit this game");
                    startFresh = 1;
                }

                // Break this loop if user entered 0.

                if (startFresh == 1){
                    break;
                }

                // Reset counter.

                i = 0;

                // Check if the number is on the board.  If it isn't, inform the user and we move back to the top of the loop with continue, using the boolean variable skipRestOfLoop.
                // If it is, we update the value of movedSquareIndex and break the loop.

                while (i < arraySize){
                    if (gameBoard[i] == numberToMove){
                        movedSquareIndex = i;
                        break;
                    }
                    else if (i == arraySize - 1){
                        puts("This number is not on the board.");
                        skipRestOfLoop = 1;
                    }
                    i++;
                }

                // Check skipRestOfLoop

                if (skipRestOfLoop == 1){
                    continue;
                }

                // Reset counter.

                i = 0;

                // Check to see if the index selected can be moved.  If it can, update canIMoveIt.  Else, inform the user and skip the rest of loop.

                while (i < 4){
                    if (movedSquareIndex == validIndices[i]){
                        canIMoveIt = 1;
                        break;
                    }
                    else if (i == 3){
                        puts("This cell cannot be moved as it is not adjacent to the empty square.");
                        skipRestOfLoop = 1;
                    }
                    i++;
                }

                // continue if skipRestOfLoop is 1.

                if (skipRestOfLoop == 1){
                    continue;
                }

                //Update moveNumber if the user has made it this far in the loop.

                moveNumber = moveNumber + 1;
            }

            // Break this loop if user entered 0.

            if (startFresh == 1){
                break;
            }

            // Create a variable newFullSquare and assign in the value stored in the movedSquareIndex.

            int newFullSquare = gameBoard[movedSquareIndex];

            // Assign gameBoard[movedSquareIndex] the value 0, making it the new empty square for the next iteration.

            gameBoard[movedSquareIndex] = 0;

            // Assign gameBoard[emptySquareIndex] the value of newFullSquare, making it filled with the value stored in the index that the player decided to move.

            gameBoard[emptySquareIndex] = newFullSquare;

            // Reset count.

            i = 0;

            // This loop draws the table again.  So, reset rowNumber and do it again.

            rowNumber = 0;

            while (rowNumber < rows) {

                // Initialize columnNumber to be used in iteration to draw the table.

                int columnNumber = 0;

                //  While loop to print horizontally and then newline once we reach the end of a row.

                while (columnNumber < columns){
                    if ((gameBoard[i] / 10) > 0){
                        printf("|%d ", gameBoard[i]);
                    }
                    else if (gameBoard[i] == 0){
                        printf("%s", "|   ");
                    }
                    else {
                        printf("| %d ", gameBoard[i]);
                    } 
                    // Update count and columnNumber.
                    columnNumber++;
                    i++;
                }
                
                // Update rowNumber and print the last vertical line to complete the row.
                
                printf("|\n");
                rowNumber++;
            }

            // Create an array of size arraySize and call it winningArray.
            
            int winningArray[arraySize];

            // Set count to 1, as we want 1 to be the first value in this array.

            i = 1;

            // Create an array that will push the values to the left, with the last value being 0 (the win condition). 

            while (i < arraySize){
                winningArray[i-1] = i;
                i++;
            }

            // Set last value of the array to 0.

            winningArray[i - 1] = 0;

            // Reset counter.

            i = 0;

            // If any of the values of the two arrays aren't the same, we set checkWin to 0 and break the loop.

            while (i < arraySize){
                if (gameBoard[i] != winningArray[i]){
                    checkWin = 0;
                    break;
                }
                else{
                    checkWin = 1;
                }
                i++;
            }
        }

        // If user entered 0, we ask if the player wants to play again without a win message.

        if (startFresh == 1){
            puts("Press 1 if you want to play again, if not, put another integer.");
            while ((scanf("%d", &playAgain)) != 1){
                fflush(stdin);
                puts("Please enter 1 to play again or any other integer to quit.");
            }
            continue;
        }
    
        // Inform player that they won and in how many moves. (Use moveNumber - 1 because it will have updated to the next value at the end of the player selection loop).

        printf("%s", "You win!!!\n");
        
        printf("It took you %d moves to win!\n\n", moveNumber - 1);

        // Check if user wants to play again using the playAgain variable, and check the input.
        puts("Press 1 if you want to play again, if not, put another integer.");
        while ((scanf("%d", &playAgain)) != 1){
            fflush(stdin);
            puts("Please enter 1 to play again or any other integer to quit.");
        }
    }
    
    // Thank the player for playing and then end the program.
    
    puts("Thanks for playing!!!");
    return 0;
    
}

