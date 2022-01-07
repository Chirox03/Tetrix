const int nBoardWidth = 22;
const int nBoardHeight = 21;
Frame(pBuffer, L"[ SCORE ]", 17, 3, nBoardWidth, 1);
Frame(pBuffer, L"[ LINE ]", 17, 3, nBoardWidth, 4);
Frame(pBuffer, L"[ NEXT ]", 17, 6, nBoardWidth, 7);
// Next tetromino
Block(pBuffer, pColor, nNextPiece, 26, 8);

// Score
if (nScore >= nScoreComp)
{
    nScorePosX--;
    nScoreComp *= 10;
}
Text(pBuffer, pColor, to_wstring(nScore), 8 * 16 + 9, nScorePosX, 2);

// Line
if (nLine >= nLineComp)
{
    nLinePosX--;
    nLineComp *= 10;
}
Text(pBuffer, pColor, to_wstring(nLine), 8 * 16 + 9, nLinePosX, 5);

