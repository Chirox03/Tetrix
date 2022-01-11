
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
	},
	//+
	{
		L"....XX....XXXXXX....XX..........",
		L"....XX....XXXXXX....XX..........",
		L"....XX....XXXXXX....XX..........",
		L"....XX....XXXXXX....XX..........",
    },
	//U
	{
		L"..XX..XX..XX..XX..XXXXXX........",
		L"..XXXXXX..XX......XXXXXX........",
		L"..XXXXXX..XX..XX..XX..XX........",
		L"..XXXXXX......XX..XXXXXX........"
	}


};
const int nScreenWidth = 52;
const int nScreenHeight = 21;

const int nBoardWidth = 30;
const int nBoardHeight = 21;

const wstring detail = L" █▓░╚╝║═";
void configure()
{
	// Set kích thước cửa sổ console
	system("MODE 52, 22");
	system("color 89");

	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);
	csbiex.ColorTable[0] = RGB(255, 0, 24);
	csbiex.ColorTable[1] = RGB(255, 165, 44);
	csbiex.ColorTable[2] = RGB(255, 255, 65);
	csbiex.ColorTable[3] = RGB(0, 128, 24);
	csbiex.ColorTable[4] = RGB(0, 0, 249);
	csbiex.ColorTable[5] = RGB(134, 0, 125);
	csbiex.ColorTable[6] = RGB(248, 139, 194);
	csbiex.ColorTable[7] = RGB(255, 153, 51);
	csbiex.ColorTable[8] = RGB(51, 153, 255);
	csbiex.ColorTable[9] = RGB(255, 51, 153);
	csbiex.ColorTable[10] = RGB(255, 255, 51);
	csbiex.ColorTable[12] = RGB(204, 255, 255);
	csbiex.ColorTable[11] = RGB(255, 255, 255);
	csbiex.ColorTable[13] = RGB(20, 20, 20);
	SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);

	CONSOLE_FONT_INFOEX cfiex;
	cfiex.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
	cfiex.dwFontSize.Y = 36;

	SetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
}
const vector<wstring> wsThree = {
			L"──▄",
			L" ─█",
			L"──▀"
};

const vector<wstring> wsTwo = {
	L"──▄",
	L"▄─▀",
	L"▀──"
};

const vector<wstring> wsOne = {
	L"─▄ ",
	L" █ ",
	L" ▀ "
};

const vector<wstring> wsReady = {
	L"▄──┐ ▄── ┌──▄ ▄──┐ ▄ ┬",
	L"█─┬┘ █─  ├──█ █ ┌┘ ▀▄┘",
	L"▀ └─ ▀── ┴  ▀ ▀─┘   ▀ "
};
const vector<wstring> wsGo = {
	L"   ▄──┐ ▄──▄  ▄ ▄ ▄   ",
	L"   █ -▄ █  █  █ █ █   ",
	L"   ▀--▀ ▀──▀  ▄ ▄ ▄   "
};
const vector<vector<wstring>> wsCountDown = { wsThree, wsTwo, wsOne, wsReady, wsGo};
const vector<wstring> wsGameOver = {
			L"▄──┐┌──▄ ┌─▄─▄ ▄──",
			L"█ ─┐├──█ │ ▀ █ █─ ",
			L"▀──┘┴  ▀ ┴   ▀ ▀──",
			L"▄──┐ ▄  ┬ ▄── ▄──┐",
			L"█  │ █ ┌┘ █─  █─┬┘",
			L"▀──┘ ▀─┘  ▀── ▀ └─"
};
void Block(wchar_t*& pBuffer, WORD*& pColor, int nTetromino, int nNextPiece_color, int nPosX, int nPosY)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (tetromino.at(nTetromino).at(0).at(j * 8 + i) != L'.')
			{
				pBuffer[(nPosY + j) * nScreenWidth + (nPosX + i)] = detail[1];
			}
			else
			{
				pBuffer[(nPosY + j) * nScreenWidth + (nPosX + i)] = L' ';
			}
			pColor[(nPosY + j) * nScreenWidth + (nPosX + i)] = 12 * 16 + nNextPiece_color;
		}
	}
}
void Text(wchar_t*& pBuffer, WORD*& pColor, wstring wsContent, WORD wColor, int nPosX, int nPosY)
{
	for (int i = 0; i < wsContent.length(); i++, nPosX++)
	{
		pBuffer[nPosY * nScreenWidth + nPosX] = wsContent.at(i);
		pColor[nPosY * nScreenWidth + nPosX] = wColor;
	}
}
void Frame(wchar_t*& pBuffer, wstring wsCaption, int nWidth, int nHeight, int nPosX, int nPosY)
{

	pBuffer[nPosY * nScreenWidth + nPosX] = L'╔';
	pBuffer[(nHeight + nPosY - 1) * nScreenWidth + nPosX] = L'╚';
	pBuffer[nPosY * nScreenWidth + nWidth + nPosX - 1] = L'╗';
	pBuffer[(nHeight + nPosY - 1) * nScreenWidth + nWidth + nPosX - 1] = L'╝';
	for (int j = nPosY + 1; j < nHeight + nPosY - 1; j++)
	{
		pBuffer[j * nScreenWidth + nPosX] = L'║';
		pBuffer[j * nScreenWidth + nWidth + nPosX - 1] = L'║';
	}
	for (int i = nPosX + 1; i < nWidth + nPosX - 1; i++)
	{
		pBuffer[nPosY * nScreenWidth + i] = L'═';
		pBuffer[(nPosY + nHeight - 1) * nScreenWidth + i] = L'═';
	}
	int CapIndex = nPosY * nScreenWidth + (nPosX + (nWidth - wsCaption.length()) / 2);
	for (int i = 0; i < wsCaption.length(); i++, CapIndex++)
	{
		pBuffer[CapIndex] = wsCaption.at(i);
	}
}
//SFX


