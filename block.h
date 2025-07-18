#pragma once
#include"vector"
#include"map"
#include"position.h"
#include"colors.h" 

class Block{
public:
	Block();
	//为了在右边显示下一个方块，原来是	void Draw();现在多加了两个偏移量
	void Draw(int offsetX,int offsetY);
	void Move(int rows, int colums);
	std::vector<Position> GetCellPosition();
	void Rotate();
	void UndoRotation();
	int id; 
	/// cells成员变量  它将一个 整数 key（如 0, 1, 2, 3），映射到一个 Position 向量	也就是每一个 cells[i] 都是一个 std::vector<Position>
		///这是从 cells 这个 map 中取出当前旋转状态下的格子（小方块）坐标。
	std::map<int, std::vector<Position>>cells;
private:
	int cellSize;
	int rotationState;
	std::vector<Color>colors;
	int rowOffset;
	int columOffset;

};