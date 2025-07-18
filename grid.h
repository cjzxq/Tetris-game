#pragma once	/// 确保头文件在编译单元中仅包含一次 避免重复定义
#include<vector>
#include"raylib.h"

class Grid {
public:
	Grid();
	void Initialize();
	void print();
	int grid[20][10];
	void Draw();
	bool IsCellOutside(int row, int colum);
	bool IsCellEmpty(int row, int colum);
	int ClearFullRows();

private:
	//std::vector<Color>GetCellColor();
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;/// 单元格大小
	std::vector<Color>Colors;
};