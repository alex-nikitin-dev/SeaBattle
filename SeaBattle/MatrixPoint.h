#pragma once
class MatrixPoint
{
public:
	MatrixPoint();
	MatrixPoint(int i, int j);
	int GetI() const;
	int GetJ() const;
	void SetI(int i);
	void SetJ(int j);
	bool operator == (const MatrixPoint &p1) const;
	bool operator!=(const MatrixPoint& p1) const;

	static MatrixPoint GetNotexistPoint();
	bool IsNotexist() const;
private:
	int _i;
	int _j;
};

