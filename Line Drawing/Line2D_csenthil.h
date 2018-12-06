#pragma once
class Line2D
{
protected:
	int X1, X2, Y1, Y2, R, G, B;
public:
	void Draw(int movex, int movey) const;
	void MakeFromString(char str[256]);
	int Parse(int wordTop[], int wordLength[], int maxNumWord, char str[]);
	Line2D();
	~Line2D();
};
