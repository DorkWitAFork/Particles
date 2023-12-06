#include "Matrices.h"
#include <iostream>

using namespace std;
using namespace Matrices;

Matrix::Matrix(int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;
	a.resize(rows);

	for (int i = 0; i < rows; i++)
	{
		a.at(i).resize(cols, 0);
	}
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix c(a.getRows(), a.getCols());
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		throw std::runtime_error("Error: dimensions must agree");
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getCols(); j++)
		{
			c(i, j) = a(i, j) + b(i, j);
		}
	}
	return c;
}
Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.getCols() != b.getRows())
	{
		throw runtime_error("Error: dimensions must agree");
	}
	Matrix c(a.getRows(), b.getCols());

	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < b.getCols(); j++)
		{
			for (int k = 0; k < a.getCols(); k++)
			{
				c(i, j) += a(i, k) * b(k, j);
			}
		}
	}

	return c;

}

bool operator==(const Matrix& a, const Matrix& b)
{

	if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
	{
		return false;
	}


	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getCols(); j++)
		{
			if (abs(a(i, j) - b(i, j)) > 0.001)
			{
				return false;
			}
		}
	}

	return true;
}


bool operator!=(const Matrix& a, const Matrix& b)
{
	return !(a == b);

}


ostream& operator<<(ostream& os, const Matrix& a)
{
	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getCols(); j++)
		{
			os << setw(10) << right << a(i, j);
		}
		os << endl;
	}
	return os;
}


RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
{
	a.at(0).at(0) = cos(theta);
	a.at(0).at(1) = -sin(theta);
	a.at(1).at(0) = sin(theta);
	a.at(1).at(1) = cos(theta);


}

ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
{
	a.at(0).at(0) = scale;
	a.at(1).at(1) = scale;
	a.at(0).at(1) = 0;
	a.at(1).at(0) = 0;

}




TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
{
	for (int i = 0; i < nCols; i++)
	{
		a.at(0).at(i) = xShift;
		a.at(1).at(i) = yShift;
	}
}
