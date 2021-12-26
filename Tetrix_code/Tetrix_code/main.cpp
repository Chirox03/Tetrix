#include "gamecheck.h"
#include "gamecontrol.h"
#include <iostream>
#include <windows.h>
#include "setup.h"

int main()
{
    Configure();
    WORD* pColor = new WORD[nScreenWidth * nScreenHeight];
    wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight];

    // Create screen buffer
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    DWORD dwBytesWritten = 0;
    while (1) // Loop
    {
        SetConsoleActiveScreenBuffer(hConsole);
        for (int i = 0; i < nScreenWidth; i++)
        {
            for (int j = 0; j < nScreenHeight; j++)
            {
                pBuffer[j * nScreenWidth + i] = L' ';
                pColor[j * nScreenWidth + i] = 8 * 16 + 9;
            }
        }
        //Countdown and gamescreen
         #include "countdown_gamescreen.h"
        //main game loop
        Frame(pBuffer, L"[ SCORE ]", 17, 3, nBoardWidth, 1);
        Frame(pBuffer, L"[ LINE ]", 17, 3, nBoardWidth, 4);
        Frame(pBuffer, L"[ NEXT ]", 17, 6, nBoardWidth, 7);
        //Game data Team 2
        while (1)
        {
            //Game timing (Team 2)
            //GAME LOGIC 
            // Game over limit (Team 2)
            //Handling input (Team 2)
            //Pause (Team 2)
            //MOVE DOWN
            if (bForceDown)
            {
                // Team 3 
            }

        }
        // DISPLAY Team 2
        //Frame
        //Current tetromino Team 2
        // Next tetromino(2)
        // Score(3)
        // Line(3)
        //Destroy the line Team 3
        //Game over Team 3

    }
	return 0;
}