
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
        csbiex.ColorTable[8] = RGB(204, 255, 255);
        csbiex.ColorTable[7] = RGB(255, 255, 255);
        csbiex.ColorTable[9] = RGB(20, 20, 20);
		SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);

		CONSOLE_FONT_INFOEX cfiex;
		cfiex.cbSize = sizeof(CONSOLE_FONT_INFOEX);

		GetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
		cfiex.dwFontSize.Y = 36;

		SetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
}

// Vẽ khung cho score, line, next

