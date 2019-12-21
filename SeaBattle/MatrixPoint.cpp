#include "stdafx.h"
#include "MatrixPoint.h"

MatrixPoint::MatrixPoint()
{
	_i = 0;
	_j = 0;
}

MatrixPoint::MatrixPoint(int i, int j)
{
	_i = i;
	_j = j;
}

int MatrixPoint::GetI() const
{
	return _i;
}

int MatrixPoint::GetJ() const
{
	return _j;
}

void MatrixPoint::SetI(int i)
{
	_i = i;
}

void MatrixPoint::SetJ(int j)
{
	_j = j;
}

bool MatrixPoint::operator==(const MatrixPoint& p1) const
{
	if (p1.GetI() == this->GetI() && p1.GetJ() == this->GetJ())
		return true;
	return false;
}
bool MatrixPoint::operator!=(const MatrixPoint& p1) const
{
	if (p1 == *this)
		return false;
	return true;
}

MatrixPoint MatrixPoint::GetNotexistPoint()
{
	return MatrixPoint(-1,-1);
}

bool MatrixPoint::IsNotexist() const
{
	return *this == GetNotexistPoint();
}


