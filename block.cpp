#include"block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColor();
	rowOffset = 0;
	columOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
	//std::vector<Position>tiles = cells[rotationState];
	std::vector<Position>tiles = GetCellPosition();
	/// 逐个遍历 tiles 中的每个 Position。tiles = { {0,1}, {1,1}, {2,1}, {2,2} };
	for (Position item : tiles)
	{
		//为了在右边显示下一个方块，原来是		DrawRectangle(item.colum * cellSize+11, item.row * cellSize+11, cellSize - 1, cellSize - 1, colors[id]);
		DrawRectangle(item.colum * cellSize+ offsetX, item.row * cellSize+ offsetY, cellSize - 1, cellSize - 1, colors[id]);

	}
}

void Block::Move(int rows,int colums)
{
	rowOffset += rows;
	columOffset += colums;
}

std::vector<Position> Block::GetCellPosition()
{

	std::vector<Position>tiles = cells[rotationState];
	/// 创建空向量来保存移动的图块
	std::vector<Position>movedTiles;
	/// 循环遍历所有图块，并将偏移量添加到新的位置
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset,item.colum + columOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::Rotate()
{
	rotationState++;
	if (rotationState == (int)cells.size())//cells.size() = 4
	{
		rotationState = 0;
	}
}

void Block::UndoRotation()
{
	rotationState--;
	if (rotationState == -1)
	{
		rotationState = (int)cells.size() - 1;
	}
}
