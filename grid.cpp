#include"grid.h"
#include"iostream"
#include<vector>
#include"colors.h"
using namespace std;
Grid::Grid()	/// ���캯��
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();// �ڹ��캯���е��ú���
	Colors = GetCellColor();
}

//��������
void Grid::Initialize()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int colum = 0; colum < numCols;colum++)
		{
			grid[row][colum] = 0;
		}
	}
}

void Grid::print()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int colum = 0; colum < numCols; colum++)
		{
			std::cout << grid[row][colum] << " ";
		}
		std::cout << std::endl;
	}
}

/*
vector<Color>Grid::GetCellColor()
{
	Color darkGrey = {26,31,40,255};
	Color green = {47,230,23,255};
	Color red = {232,18,18,255};
	Color orange = {226,116,17,255};
	Color yellow = {237,234,4,255};
	Color purple = {166,0,247,255};
	Color cyan = {21,204,209,255};
	Color blue = {13,64,216,255};

	return { darkGrey ,green ,red ,orange ,yellow ,purple ,cyan ,blue };
}

*/

void Grid::Draw()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int colum = 0; colum < numCols; colum++)
		{
			int cellValue = grid[row][colum];
			/// +1 ��Ϊ������λ�ã������ߣ��� - 1 ��Ϊ����С�ߴ磨�����ߣ�����������ã��ﵽ������з�϶����ʾ��������Ŀ�ġ�
			DrawRectangle(colum * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1,Colors[cellValue]);
		}
	}


}

bool Grid::IsCellOutside(int row, int colum)
{
	if(row>=0 && row < numRows && colum>=0 && colum < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int colum)
{
	if (grid[row][colum] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row,completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int colum = 0; colum < numCols; colum++)
	{
		if (grid[row][colum] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int colum = 0; colum < numCols; colum++)
	{
		//grid[row][colum] = grid[0][colum];
		grid[row][colum] = 0;
	}
}
//��ԭʼ�е�ֵ���Ƶ����У������ԭʼ�У��������е�һ�������ƶ�numRows��
void Grid::MoveRowDown(int row, int numRows)
{
	for (int colum = 0; colum < numCols; colum++)
	{
		grid[row + numRows][colum] = grid[row][colum];
		grid[row][colum] = 0;
	}
}

