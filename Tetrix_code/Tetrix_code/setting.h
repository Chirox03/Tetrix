
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

// countdown
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
const vector<vector<wstring>> wsCountDown = { wsThree, wsTwo, wsOne, wsReady };

