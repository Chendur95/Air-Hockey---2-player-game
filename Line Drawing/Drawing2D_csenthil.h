#pragma once
class Drawing2D : public Line2D
{
protected:
	int numoflines;
public:
	Line2D *line2D_ptr;
	void Draw(int movex, int movey);
	char filename[256];
	Drawing2D();
	~Drawing2D();
	void cleanup();
	void ReadFile(char filename[256]);
	Drawing2D(const Drawing2D &Source)
	{
		numoflines = Source.numoflines;
		line2D_ptr = Source.line2D_ptr;
	}
	Drawing2D& operator= (const Drawing2D &Source);
};