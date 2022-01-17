#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Random.h"
#include "SFML/Audio.hpp"
#include "setting.h"
bool CheckPiece(int*& pMatrix, int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (nPosX + i >= 0 && nPosX + i < nBoardWidth)
            {
                if (nPosY + j >= 0 && nPosY + j < nBoardHeight)
                {
                    if (tetromino.at(nTetromino).at(nRotation).at(j * 8 + i) != L'.' && pMatrix[(nPosY + j) * nBoardWidth + (nPosX + i)] != 0)
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}
//check thử có bị lỗi ko 
int main()
{
    configure();

    // Buffer data
    WORD* pColor = new WORD[nScreenWidth * nScreenHeight];
    wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight];

    // Create screen buffer
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    DWORD dwBytesWritten = 0;
    // Load music and sound
    sf::Music countdown;
    if (!countdown.openFromFile("countdown.wav"))
        cout << "Error"; // error
    sf::Music themesong;
    if (!themesong.openFromFile("Tetris.wav"))
        cout << "Error"; // error
    sf::SoundBuffer buffer_1;
    if (!buffer_1.loadFromFile("rotate.wav"))
        cout << "Error";
    sf::SoundBuffer buffer_2;
    if (!buffer_2.loadFromFile("Gameover.wav"))
        cout << "Error";
    sf::SoundBuffer buffer_3;
    if (!buffer_3.loadFromFile("fall.wav"))
        cout << "Error";
    sf::SoundBuffer buffer_4;
    if (!buffer_4.loadFromFile("breaking.wav")) cout << "Error";
    sf::Sound rotateSFX;
    sf::Sound GameOverSFX;
    sf::Sound FallSFX;
    sf::Sound BreakSFX;
    rotateSFX.setBuffer(buffer_1);
    GameOverSFX.setBuffer(buffer_2);
    FallSFX.setBuffer(buffer_3);
    BreakSFX.setBuffer(buffer_4);
    countdown.play();

    while (1)
    {
        SetConsoleActiveScreenBuffer(hConsole);//active the screen buffer

        // GET STARTED
        // Clear screen
        for (int i = 0; i < nScreenWidth; i++)
        {
            for (int j = 0; j < nScreenHeight; j++)
            {
                pBuffer[j * nScreenWidth + i] = L' ';
                pColor[j * nScreenWidth + i] = 11 * 16 + 9;
            }
        }

        // Count down
        for (int i = 0; i < wsCountDown.size(); i++)
        {
            for (int j = 0; j < wsCountDown.at(i).size(); j++)
            {
                if (i >= 3)
                {
                    // Nếu là chữ ready và go thì lùi lại 1 tí cho nó cân 
                    Text(pBuffer, pColor, wsCountDown.at(i).at(j), 11 * 16 + 7, 15, 9 + j);
                }
                else
                {
                    Text(pBuffer, pColor, wsCountDown.at(i).at(j), 11 * 16 + 4, 25, 9 + j);
                }

            }
            // Xuất buffer ra console
            /*for (int j = 0; j < nScreenHeight; j++)
            {
                for (int i = 0; i < nScreenWidth; i++)
                {
                    COORD cPos;
                    cPos.X = i;
                    cPos.Y = j;
                }
            }*/
            WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, {0,0}, &dwBytesWritten);
            WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
            Sleep(1000);
        }
        countdown.stop();
        themesong.setLoop(true);
        themesong.play();
            // Create game screen
        // Tạo nền caro
        for (int i = 0; i < nScreenWidth; i++)
        {
            for (int j = 0; j < nScreenHeight; j++)
            {
                pBuffer[j * nScreenWidth + i] = L' ';
                if ((i / 2 + i % 2 + j) % 2 == 0)
                    pColor[j * nScreenWidth + i] = 11 * 16 + 9;
                else pColor[j * nScreenWidth + i] = 12 * 16 + 9;
            }
        }
        // Game data
        int* pMatrix = new int[nBoardWidth * nBoardHeight];
        for (int i = 0; i < nBoardWidth; i++)
        {
            for (int j = 0; j < nBoardHeight; j++)
            {
                if (j == nBoardHeight - 1)
                {
                    if (i == 0)
                    {
                        pMatrix[j * nBoardWidth + i] = 4;
                    }
                    else if (i == nBoardWidth - 1)
                    {
                        pMatrix[j * nBoardWidth + i] = 5;
                    }
                    else
                    {
                        pMatrix[j * nBoardWidth + i] = 7;
                    }
                }

                else
                {
                    if (i == 0 || i == nBoardWidth - 1)
                    {
                        pMatrix[j * nBoardWidth + i] = 6;
                    }
                    else
                    {
                        pMatrix[j * nBoardWidth + i] = 0;
                    }
                }
            }
        }
        // Khởi tạo các biến 
        //Mảng chứa các phím sử dụng trong game
        const vector<char> key = { 'W', 'A', 'S', 'D', 27 };
        bool bKey[5];
        // Các biến thể hiện trang thái của khối hiện tại
        int nCurrentPiece = random(0, 8);
        int nNextPiece = random(0, 8);
        int nNextPiece_color = random(0, 10);
        int nCurrentPiece_color = random(0, 10);
        int nCurrentRotation = 0;
        int nCurrentX = nBoardWidth / 2 - 4;
        int nCurrentY = 0;
        // Biến đếm frame, 1 game tick gồm nFrame ( sau này dùng để tăng độ khó)
        int nFrame = 20;
        int nFrameCount = 0;
        //Các biến bool 
        bool bForceDown = 0;
        bool bRotateHold = 1;
        //Các biến tăng độ khó
        int nLevelLimit = 2;
        int nPieceCount = 0;// Số mảnh đã đáp xuống
        // Các biến đếm điểm
        int nScore = 0;
        int nScorePosX = 40;
        int nScoreComp = 10;
        //Đếm số dòng
        int nLine = 0;
        int nLinePosX = 40;
        int nLineComp = 10;
        //Vector kiểm tra sự xóa dòng
        vector<int> vLines;
        
        // Game loop
        while (1)
        {
            Sleep(40);
            // GAME TIMING
            nFrameCount++;
            if (nFrameCount == nFrame)
                bForceDown = 1;
            else
                bForceDown = 0;

            // INPUT
            for (int i = 0; i < key.size(); i++)
            {
                bKey[i] = 0;
                if ((GetKeyState(key.at(i)) & 0x8000) != 0)
                    bKey[i] = 1;
            }

            // GAME LOGIC

            // Game over limit
            int nLimit = 0;
            if (nCurrentPiece == 3)
            {
                nLimit = -1;
            }
            //Tetromino
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (tetromino.at(nCurrentPiece).at(nCurrentRotation).at(j * 8 + i) != L'.' && nCurrentY + j >= 0)
                    {
                        if (((nCurrentX + i) / 2 + (nCurrentX + i) % 2 + (nCurrentY + j)) % 2 == 0)
                            pColor[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = 11 * 16 + nCurrentPiece_color;
                        else pColor[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = 12 * 16 + nCurrentPiece_color;
                        pBuffer[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = L'▓';
                    }
                }
            }
            // Handling input
            //Sang phải - D
            if (bKey[3] == 1 && nCurrentY >= nLimit)
            {
                rotateSFX.play();
                if (CheckPiece(pMatrix, nCurrentPiece, nCurrentRotation, nCurrentX + 2, nCurrentY) == 1)
                {
                    nCurrentX += 2;
                }
            }
            //Sang trái - A
            if (bKey[1] == 1 && nCurrentY >= nLimit && CheckPiece(pMatrix, nCurrentPiece, nCurrentRotation, nCurrentX - 2, nCurrentY) == 1)
            {
                rotateSFX.play();
                nCurrentX -= 2;

            }
            //Thả nhanh xuống - S
            if (bKey[2] == 1 && nCurrentY >= nLimit)
            {
                FallSFX.play();
                int i{};
                while (CheckPiece(pMatrix, nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + i) == 1)
                {
                    i++;
                }
                nCurrentY += i - 1;
            }
            //Xoay khối
            if (bKey[0] == 1 && nCurrentY >= nLimit && bRotateHold == 1 && CheckPiece(pMatrix, nCurrentPiece, (nCurrentRotation + 1) % 4, nCurrentX, nCurrentY) == 1)
            {
                rotateSFX.play();
                nCurrentRotation++;
                nCurrentRotation %= 4;
                bRotateHold = 0;
            }
            else
            {
                bRotateHold = 1;
            }
            // Pause
            if (bKey[4] == 1)
            {
                int nSelect = 0;
                WORD* pTmpColor = new WORD[nScreenWidth * nScreenHeight];

                for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
                {
                    pTmpColor[i] = pColor[i];
                }

                while (1)
                {
                    Text(pBuffer, pTmpColor, L" ═════ PAUSE ════ ", 13 * 16 + 11, 6, 8);
                    Text(pBuffer, pTmpColor, L"                  ", 13 * 16 + 11, 6, 9);
                    Text(pBuffer, pTmpColor, L" ════════════════ ", 13 * 16 + 11, 6, 12);


                    if (nSelect == 0)
                    {
                        //rotateSFX.play();
                        Text(pBuffer, pTmpColor, L" >>  Continue  << ", 10 * 16 + 7, 6, 10);
                        Text(pBuffer, pTmpColor, L"       Quit       ", 10 * 16 + 13, 6, 11);
                        if (GetKeyState('S') & 0x8000)
                        {
                            rotateSFX.play();
                            nSelect++;
                        }
                        else if (GetKeyState(13) & 0x8000)
                        {
                            rotateSFX.play();
                            break;
                        }
                    }
                    else
                    {
                        //rotateSFX.play();
                        Text(pBuffer, pTmpColor, L"     Continue     ", 10 * 16 + 13, 6, 10);
                        Text(pBuffer, pTmpColor, L" >>    Quit    << ", 10 * 16 + 7, 6, 11);

                        if (GetKeyState('W') & 0x8000)
                        {
                            rotateSFX.play();
                            nSelect--;
                        }
                        else if (GetKeyState(13) & 0x8000)
                        {
                            rotateSFX.play();
                            return 0;
                        }
                    }


                    WriteConsoleOutputAttribute(hConsole, pTmpColor, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
                    WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
                }
            }
            // Move down
            if (bForceDown)
            {
                // Update difficulty
                nFrameCount = 0;
                if (nPieceCount == nLevelLimit && nFrame >= 5)
                {
                    nFrame--;
                    nPieceCount = 0;
                    nLevelLimit *= 2;
                }

                // Check if piece can be moved down
                if (CheckPiece(pMatrix, nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
                {
                    nCurrentY++;
                }
                else
                {
                    // If the tetromino has not appeared completely, game over
                    if (nCurrentY < nLimit)
                    {
                        break;
                    }
                    else
                    {
                        nPieceCount++;

                        //Fix the tetromino
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                if (nCurrentY >= 0 && tetromino.at(nCurrentPiece).at(nCurrentRotation).at(j * 8 + i) != L'.')
                                {
                                    pMatrix[(nCurrentY + j) * nBoardWidth + (nCurrentX + i)] = 1;
                                    if (((nCurrentX + i) / 2 + (nCurrentX + i) % 2 + (nCurrentY + j)) % 2 == 0)
                                        pColor[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = 11 * 16 + nCurrentPiece_color;
                                    else pColor[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = 12 * 16 + nCurrentPiece_color;
                                }
                            }
                        }

                        // Check for lines
                        for (int j = 0; j < 4; j++)
                        {
                            if (nCurrentY + j < nBoardHeight - 1)
                            {
                                bool bLine = 1;
                                for (int i = 1; i < nBoardWidth - 1; i++)
                                {
                                    if (pMatrix[(nCurrentY + j) * nBoardWidth + i] == 0)
                                    {
                                        bLine = 0;
                                        break;
                                    }
                                }

                                if (bLine == 1)
                                {
                                    nLine++;

                                    // A little animation
                                    for (int i = 1; i < nBoardWidth - 1; i++)
                                    {
                                        pMatrix[(nCurrentY + j) * nBoardWidth + i] = 3;
                                    }
                                    vLines.push_back(nCurrentY + j);
                                }
                            }
                        }

                        // Increase score
                        nScore += 25;
                        if (!vLines.empty())
                        {
                            nScore += (1 << vLines.size()) * 100; 
                        }

                        // Pick new tetromino
                        nCurrentX = nBoardWidth / 2 - 4;
                        nCurrentY = -4;
                        nCurrentRotation = 0;
                        nCurrentPiece = nNextPiece;
                        nCurrentPiece_color = nNextPiece_color;
                        nNextPiece_color = random(0, 10);
                        nNextPiece = random(0, 8);
                    }
                }
            }

            // DISPLAY

            // Frame
            for (int i = 0; i < nBoardWidth; i++)
            {
                for (int j = 0; j < nBoardHeight; j++)
                {
                    pBuffer[j * nScreenWidth + i] = detail[pMatrix[j * nBoardWidth + i]];
                }
            }


            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (tetromino.at(nCurrentPiece).at(nCurrentRotation).at(j * 8 + i) != L'.' && nCurrentY + j >= 0)
                    {
                        pColor[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = 11 * 16 + nCurrentPiece_color;
                        pBuffer[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = L'▓';
                    }
                }
            }


            // Score
            if (nScore >= nScoreComp)
            {
                nScorePosX--;
                nScoreComp *= 10;
            }

            // Line
            if (nLine >= nLineComp)
            {
                nLinePosX--;
                nLineComp *= 10;
            }
            Frame(pBuffer, L"[ SCORE ]", 19, 3, nBoardWidth + 1, 1);
            Frame(pBuffer, L"[ LINE ]", 19, 3, nBoardWidth + 1, 4);
            Frame(pBuffer, L"[ NEXT ]", 19, 8, nBoardWidth + 1, 7);
            Block(pBuffer, pColor, nNextPiece, nNextPiece_color, nBoardWidth + 6, 9);
            Text(pBuffer, pColor, to_wstring(nScore), 11 * 16 + 9, nScorePosX, 2);
            Text(pBuffer, pColor, to_wstring(nLine), 11 * 16 + 9, nLinePosX, 5);
            // Destroy the lines
            if (!vLines.empty())
            {
                WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
                Sleep(400);

                for (int l = 0; l < vLines.size(); l++)
                {
                    for (int i = 1; i < nBoardWidth - 1; i++)
                    {
                        for (int j = vLines.at(l); j > 0; j--)
                        {
                            if ((i / 2 + i % 2 + j) % 2 == 0)
                                pColor[j * nScreenWidth + i] = pColor[(j - 1) * nScreenWidth + i] - 16;
                            else

                                pColor[j * nScreenWidth + i] = pColor[(j - 1) * nScreenWidth + i] + 16;

                            pMatrix[j * nBoardWidth + i] = pMatrix[(j - 1) * nBoardWidth + i];
                        }
                        pMatrix[i] = 0;
                    }
                }
                BreakSFX.play();
                vLines.clear();
            }

            WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
            WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
        }

        // Game over
        themesong.stop();
        GameOverSFX.play();
        for (int i = 0; i < nScreenWidth; i++)
        {
            for (int j = 0; j < nScreenHeight; j++)
            {
                pBuffer[j * nScreenWidth + i] = L' ';
                pColor[j * nScreenWidth + i] = 10 * 16 + 11;
            }
        }

        int nSelect = 0;
        while (1)
        {
            for (int i = 0; i < wsGameOver.size(); i++)
            {
                Text(pBuffer, pColor, wsGameOver.at(i), 10 * 16 + 1, 17, 3 + i);
            }

            Text(pBuffer, pColor, L"════ SCORE ════", 10 * 16 + 3, 18, 11);
            Text(pBuffer, pColor, L"═══════════════", 10 * 16 + 3, 18, 13);

            int nScorePosX = 17 + 8;
            int nScoreComp = 100;
            while (nScore >= nScoreComp)
            {
                nScorePosX--;
                nScoreComp *= 100;
            }

            Text(pBuffer, pColor, to_wstring(nScore), 10 * 16 + 3, nScorePosX, 12);

            if (nSelect == 0)
            {
                Text(pBuffer, pColor, L">> Play Again <<", 10 * 16 + 13, 17, 17);
                Text(pBuffer, pColor, L"      Quit      ", 10 * 16 + 7, 17, 18);

                if (GetKeyState('S') & 0x8000)
                {
                    rotateSFX.play();
                    nSelect++;
                }
                if (GetKeyState(13) & 0x8000)
                {
                    rotateSFX.play();
                    break;
                }
            }
            else
            {
                Text(pBuffer, pColor, L"   Play Again   ", 10 * 16 + 7, 17, 17);
                Text(pBuffer, pColor, L">>    Quit    <<", 10 * 16 + 13, 17, 18);

                if (GetKeyState('W') & 0x8000)
                {
                    rotateSFX.play();
                    nSelect--;
                }
                if (GetKeyState(13) & 0x8000)
                {
                    rotateSFX.play();
                    return 0;
                }
            }

            WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
            WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
        }
    }

    return 0;
}