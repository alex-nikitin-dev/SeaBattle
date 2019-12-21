#pragma once
class GameColors
{
public:
	static const COLORREF _regular= RGB(216, 248, 255);
	static const COLORREF _killed= RGB(2, 129, 227);
	static const COLORREF _injured= RGB(66, 210, 255);
	static const COLORREF _missed= RGB(196, 196, 196);
	static const COLORREF _regularForPen= RGB(255, 255, 255);
	static const COLORREF _marksColor = RGB(0,0,0);
public:
	static COLORREF Regular();
	static  COLORREF Killed();
	static  COLORREF Injured();
	static  COLORREF Missed();
	static  COLORREF RegularForPen();
	static  COLORREF MarksColor();
};

