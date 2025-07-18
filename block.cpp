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
	/// ������� tiles �е�ÿ�� Position��tiles = { {0,1}, {1,1}, {2,1}, {2,2} };
	for (Position item : tiles)
	{
		//Ϊ�����ұ���ʾ��һ�����飬ԭ����		DrawRectangle(item.colum * cellSize+11, item.row * cellSize+11, cellSize - 1, cellSize - 1, colors[id]);
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
	/// �����������������ƶ���ͼ��
	std::vector<Position>movedTiles;
	/// ѭ����������ͼ�飬����ƫ������ӵ��µ�λ��
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
