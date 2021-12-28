#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;
#include "setting.h"
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
			pColor[j * nScreenWidth + i] = 8 * 16 + 9;

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
	while (1)
	{
		//Game timing
		//Input
		// Game logic
		//Display
		DWORD dwBytesWritten = 0;
		int nCurrentPiece = 4;
		int nCurrentRotation = 0;
		int nCurrentX = nBoardWidth / 2 - 4;
		int nCurrentY = 0;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (tetromino.at(nCurrentPiece).at(nCurrentRotation).at(j * 8 + i) != L'.' && nCurrentY + j >= 0)
				{
					pBuffer[(nCurrentY + j) * nScreenWidth + (nCurrentX + i)] = L'▓';
				}
			}
		}
		for (int i = 0; i < nScreenWidth; i++)
		{
			for (int j = 0; j < nScreenHeight; j++)
			{
				COORD cPos;
				cPos.X = i;
				cPos.Y = j;
				WriteConsoleOutputAttribute(hConsole, &pColor[j * nScreenWidth + i], 1, cPos, &dwBytesWritten);
			}
		}

		WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	_getch();
	return 0;
}