#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

// Khai báo các hằng số
const vector<vector<wstring>> tetromino = {
	// I
	{
		L"....XX......XX......XX......XX..", //   0 deg
		L"................XXXXXXXX........", //  90 deg
		L"..XX......XX......XX......XX....", // 180 deg
		L"........XXXXXXXX................"  // 270 deg
	},

	// J
	{
		L"....XX......XX....XXXX..........",
		L"..........XX......XXXXXX........",
		L"..........XXXX....XX......XX....",
		L"........XXXXXX......XX.........."
	},

	// L
	{
		L"..XX......XX......XXXX..........",
		L"..........XXXXXX..XX............",
		L"..........XXXX......XX......XX..",
		L"............XX..XXXXXX.........."
	},

	// O
	{
		L"..........XXXX....XXXX..........",
		L"..........XXXX....XXXX..........",
		L"..........XXXX....XXXX..........",
		L"..........XXXX....XXXX.........."
	},

	// S
	{
		L"..XX......XXXX......XX..........",
		L"............XXXX..XXXX..........",
		L"..........XX......XXXX......XX..",
		L"..........XXXX..XXXX............"
	},

	// T
	{
		L"..XX......XXXX....XX............",
		L"..........XXXXXX....XX..........",
		L"............XX....XXXX......XX..",
		L"..........XX....XXXXXX.........."
	},

	// Z
	{
		L"....XX....XXXX....XX............",
		L"..........XXXX......XXXX........",
		L"............XX....XXXX....XX....",
		L"........XXXX......XXXX.........."
	}
};
const int nScreenWidth = 22;
const int nScreenHeight = 21;

const int nBoardWidth = 22;
const int nBoardHeight = 21;

const wstring detail = L" █▓░╚╝║═";
void configure()
{
	// Set kích thước cửa sổ console
	system("MODE 22, 22");

	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
}

// Vẽ khung cho score, line, next


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