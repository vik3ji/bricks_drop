/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Viktoria Petrova
* @idnumber 2MI0600374
* @compiler <използван компилатор - GCC или VC>
*
* <предназначение на файла>
*
*/

#include <iostream>
using namespace std;

double startNum = 1; //създавам глобална помощна променлива, 
                     //която да използвам за генериране на случайно число

unsigned randomNumberGenerator() {
    unsigned numberGenerator = 977;
    double generateNum = startNum / numberGenerator;
    startNum++;
    int endNum = generateNum * 10000000;
    endNum %= 10;
    if (endNum == 8 || endNum == 9)
        randomNumberGenerator();
    else
        return endNum;
}

/*
-блокче с дължина 1 ще отбелязваме със син цвят - b
-блокче с дължина 2 ще отбелязваме с розов цвят - p
-блокче с дължина 3 ще отбелязваме с зелен цвят - g
-блокче с дължина 4 ще отбелязваме с жълт цвят - y
*/

char randomColorGenerator(){
    int random = randomNumberGenerator();
    switch (random%4)
    {
    case 0: return 'b';
    case 1: return 'p';
    case 2: return 'g';
    case 3: return 'y';
        break;
    }
}

void swapPosition(char& x, char& y) {
    char temp = x;
    x = y;
    y = temp;
}

int strCompare(const char* first, const char* second)
{
    if (!first || !second)
        return 0;
    while ((*first) && (*second) && ((*first) == (*second))) {
        first++;
        second++;
    }
    return (*first - *second);
}

int surchBrickLen(const char bricksMatrix[], size_t size, char color) {
    for (int i = 0; i < size; i++){
        if (bricksMatrix[i]==color){
            return bricksMatrix[i - 1];
        }
    }
    return -1;
}

bool isEmptryToGenerate(const char field[][8], int position, const int brickLen) {
    for (int i = 0; i < brickLen; i++){
        if (field[9][position] != '0') {
            return 0;
        }
         position++;
    }
    return 1;
}

bool isGenerationValid(const char field[][8], const char bricksMatrix[], const int position, const char color, unsigned brickLen) {
    bool isEmptry = isEmptryToGenerate(field, position, brickLen);
    return ((brickLen + position <= 8) && isEmptry);
}

bool isLineFull(const char field[][8], unsigned line) {
    for (int i = 0; i < 8; i++){
        if (field[line][i] == '0') {
            return 0;
        }
    }
    return 1;
}

void fillMatrix(char field[][8]) {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
             field[i][j] = '0';
        }
    }
}

void printMatrix(const char field[][8]) {
    cout << endl << "   ";         
    for (size_t z = 0; z < 8; z++){
        cout << z << ". ";
    }
    cout << endl;
    for (size_t i = 0; i < 10; i++){
        cout << i << ". ";
        for (size_t j = 0; j < 8; j++) {
            cout << field[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int generateFirstRow(char field[][8], const char bricksMatrix[], const int countOfBricksPerRow, int currentCountOfBricks) {
    if (isLineFull(field, 9) || (currentCountOfBricks == countOfBricksPerRow)) {
        return -1;
    }
    char color = randomColorGenerator();
    int position = randomNumberGenerator();
    int brickLen = surchBrickLen(bricksMatrix, 8, color);
    if (!isGenerationValid(field, bricksMatrix, position, color, brickLen)){
        return generateFirstRow(field, bricksMatrix, countOfBricksPerRow, currentCountOfBricks);
    }
    for (int i = 0; i < brickLen; i++){
        field[9][position] = color;
        position++;
    }
    currentCountOfBricks++;
    return generateFirstRow(field, bricksMatrix, countOfBricksPerRow, currentCountOfBricks);  
}

bool isRowEmpty(const char field[][8], const int row) {
    for (int i = 0; i < 8; i++) {
        if (field[row][i] != '0') {
            return 0;
        }
    }
    return 1;
}

void moveRowUp(char field[][8]) {
    for (size_t i = 0; i < 9; i++){
        for (size_t j = 0; j < 8; j++){
            field[i][j] = field[i + 1][j];
        }
    }
    for (size_t z = 0; z < 8; z++) {
        field[9][z] = '0';
    } 
}

void moveRowDown(char field[][8], const int rowToDisappear) {
    for (size_t i = rowToDisappear; i > 0; i--) {
        for (size_t j = 0; j < 8; j++) {
            field[i][j] = field[i - 1][j];
        }
    }
    for (size_t z = 0; z < 8; z++) {
        field[0][z] = '0';
    }
}

int isAnyLineFull(const char field[][8]) {
    for (size_t i = 9; i > 0; i--){
        if (isLineFull(field, i)){
            return i;
        }
    }
    return 0;
}

void moveTheBrick(unsigned rowToMove, unsigned positionOfBrick, unsigned movementOfBrick, char sideToMove,
                  char field[][8], const char bricksMatrix[], const int brickLen) {
    if (sideToMove == 'l') {
        int positionForMovement = positionOfBrick - movementOfBrick;
        for (size_t i = positionForMovement; i < positionForMovement + brickLen; i++){
            swapPosition(field[rowToMove][i], field[rowToMove][positionOfBrick]);
            positionOfBrick++;
        }
    }
    if (sideToMove == 'r') {
        int positionForMovement = positionOfBrick + movementOfBrick + brickLen - 1;
        for (size_t i = positionForMovement; i > positionForMovement - brickLen; i--){
            swapPosition(field[rowToMove][i], field[rowToMove][positionOfBrick + brickLen - 1]);
            positionOfBrick--;
        }
    }
}

bool isDataFromUserValid(unsigned rowToMove,const int positionOfBrick,unsigned movementOfBrick, const char sideToMove, 
                         const char field[][8], const char bricksMatrix[], const int brickLen) {
    if (rowToMove < 1 || rowToMove > 9)
        return 0;
    if (isRowEmpty(field, rowToMove))
        return 0;
    if (positionOfBrick < 0 || positionOfBrick > 9)
        return 0;
    if (field[rowToMove][positionOfBrick] == '0')
        return 0;
    if (sideToMove != 'l' && sideToMove != 'r')
        return 0;
    if (sideToMove == 'l'){
        for (size_t i = 1; i <= movementOfBrick; i++){
            if (field[rowToMove][positionOfBrick - i] != '0')
                return 0;
        } 
    }
    if (sideToMove == 'r') {
        for (size_t i = 0; i < movementOfBrick; i++) {
            if (field[rowToMove][positionOfBrick + brickLen + i] != '0')
                return 0;
        }
    }
}

void takeDataAndMove(unsigned& rowToMove, unsigned& positionOfBrick, unsigned& movementOfBrick, char& sideToMove,
                         char field[][8], const char bricksMatrix[]) {
    cin >> rowToMove >> positionOfBrick >> movementOfBrick >> sideToMove;
    while(!isDataFromUserValid(rowToMove, positionOfBrick, movementOfBrick, sideToMove, field, bricksMatrix,
        surchBrickLen(bricksMatrix, 8, field[rowToMove][positionOfBrick]))){
        cout << "Incorect Input" << endl;
        cin >> rowToMove >> positionOfBrick >> movementOfBrick >> sideToMove;
    }
    moveTheBrick(rowToMove, positionOfBrick, movementOfBrick, sideToMove, field, bricksMatrix, 
        surchBrickLen(bricksMatrix, 8, field[rowToMove][positionOfBrick]));
}

void brickFall(char field[][8], const int brickLen, int i, int j) {
    for (size_t z = 0; z < brickLen; z++) {
        field[i + 1][j-1] = field[i][j-1];
        field[i][j-1] = '0';
        j--;
    }
}

void checkbrickFall(char field[][8], const int brickLen, int& i, int& j, int& counterOfChanges) {
    unsigned counterOfFreeSpace = 0;
    for (size_t z = 0; z < brickLen; z++)
    {
        if (field[i + 1][j] == '0') {
            counterOfFreeSpace++;
        }
        j++;
    }
    if (counterOfFreeSpace == brickLen) {
        brickFall(field, brickLen, i, j);
        counterOfChanges++;
    }
    j--;
}

void surchBrickForFall(char field[][8], const char bricksMatrix[]) {
    int counterOfChanges = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 8; j++){
            if (field[i][j] != '0') {
                int brickLen = surchBrickLen(bricksMatrix, 8, field[i][j]);
                checkbrickFall(field, brickLen, i, j, counterOfChanges);
            }
        }
    }
    if (counterOfChanges > 0) {
        return surchBrickForFall(field, bricksMatrix);
    }
    
}

void firstMove(char field[][8], const char bricksMatrix[],  
               int currentCountOfBricks, int& counterOfPoints) {
    int countOfBricksPerRow = (randomNumberGenerator() % 4 + 1);
    generateFirstRow(field, bricksMatrix, countOfBricksPerRow, currentCountOfBricks);
    int fullRow = isAnyLineFull(field);
    if (fullRow) {
        moveRowDown(field, fullRow);
        counterOfPoints += 10;
    }
    
}

void playGame(char field[][8], const char bricksMatrix[]) {
    char player[20];
    cout << "Pleace enter your name.." << endl;
    cin >> player;
    
    fillMatrix(field);
    int counterOfPoints = 0;
    int currentCountOfBricks = 0;

    cout << " Please enter row of the brick you want to move,"
        << endl << " the first position of the brick,"
        << endl << " how many positions you want to move the brick,"
        << endl << " - l - if you want to move the brick to the left"
        << endl << " - r if you want to move the brick to the right" << endl;
    //искам на ? ред да преместя ? тухличка с ? стъпки на ляво/дяснo

    firstMove(field, bricksMatrix, currentCountOfBricks, counterOfPoints);
    printMatrix(field);
    while (isRowEmpty(field, 0)) {
        unsigned rowToMove, positionOfBrick, movementOfBrick;
        char sideToMove;
        takeDataAndMove(rowToMove, positionOfBrick, movementOfBrick, sideToMove, field, bricksMatrix);
        surchBrickForFall(field, bricksMatrix);
        moveRowUp(field);
        firstMove(field, bricksMatrix, currentCountOfBricks, counterOfPoints);
        surchBrickForFall(field, bricksMatrix);
        printMatrix(field);
        cout << "Your current points are: " << counterOfPoints << endl;
    }
    cout << "Game Over!" << endl;
    char answerPlayer[4];
    char answerYes[4] = "yes";
    cout << "Do you want to continue?" << endl;
    cin >> answerPlayer;
    if (!strCompare(answerPlayer, answerYes)) {
        return playGame(field, bricksMatrix);
    }

}

int main()
{
    char field[10][8];
    char bricksMatrix[] = { 1, 'b', 2, 'p', 3, 'g', 4, 'y' };
    playGame(field, bricksMatrix);
}
