#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "setting.h"
#include "Random.h"
void Block(wchar_t*& pBuffer, WORD*& pColor, int nTetromino, int nPosX, int nPosY)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (tetromino.at(nTetromino).at(0).at(j * 8 + i) != L'.')
			{
				pBuffer[(nPosY + j) * nScreenWidth + (nPosX + i)] = L'▓';
			}
			else
			{
				pBuffer[(nPosY + j) * nScreenWidth + (nPosX + i)] = L' ';
			}

			pColor[(nPosY + j) * nScreenWidth + (nPosX + i)] = 8 * 16 + nTetromino;
		}
	}
}

void Text(wchar_t*& pBuffer, wstring content, int nPosX, int nPosY)
{
	for (int i = 0; i < content.length(); i++, nPosX++)
	{
		pBuffer[nPosY * nScreenWidth + nPosX] = content.at(i);
	}
}
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
int main()
{
	// Set kích thước cửa sổ console
	configure();

	// Tạo Console Screen Buffer
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	// Tạo mảng lưu thuộc tính màu sắc và mảng lưu ký tự
	WORD* pColor = new WORD[nScreenWidth * nScreenHeight];
	wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth; i++)
	{
		for (int j = 0; j < nScreenHeight; j++)
		{
			pBuffer[j * nScreenWidth + i] = L' ';
            //vẽ caro cho nền
            if ((i / 2 + i % 2 + j) % 2 == 0)
			pColor[j * nScreenWidth + i] = 8 * 16 + 9;
            else pColor[j * nScreenWidth + i] = 7 * 16 + 9;

		}
	}

	// Tạo mảng đánh dấu Game Board
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

	// Chuyển mảng đánh dấu Game Board lên mảng lưu ký tự để hiển thị
	for (int i = 0; i < nBoardWidth; i++)
	{
		for (int j = 0; j < nBoardHeight; j++)
		{
			pBuffer[j * nScreenWidth + i] = detail[pMatrix[j * nBoardWidth + i]];
		}
	}

	// Vẽ các ô Score, Line, Next
	 DWORD dwBytesWritten = 0;
	//Khai báo các biến điều khiển
	const vector<char> key = { 'W', 'A', 'S', 'D' };
	int MoveX[] = {0,-2,0,2};
	int MoveY[] = {0,0,-5,0};
	bool bKey[5];
	bool bForceDown = 0;
	int nCurrentPiece = random(0, 6);
	int nNextPiece = random(0, 6);
	int nCurrentRotation = 0;
	int nCurrentX = nBoardWidth / 2 - 4;
	int nCurrentY = 0;
	int nFrame = 10;
	int nFrameCount = 0;
	int nLimit = 0;
	int mColorX[] = { 7,8,8,7 };
	int mColorY[] = { 8,7,7,8 };
	bool bgameover = 0;

    bool bRotateHold = 1;
	int nLine = 0;
    bool bGameOver = 0;
	vector<int> vLines;
    while (bGameOver != 1)
    {
        // GAME TIMING
        Sleep(75);
        nFrameCount++;
        if (nFrameCount == nFrame)
        {
            bForceDown = 1;
        }
        else
        {
            bForceDown = 0;
        }

