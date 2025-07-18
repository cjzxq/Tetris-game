#pragma once
#include"vector"
#include"map"
#include"position.h"
#include"colors.h" 

class Block{
public:
	Block();
	//Ϊ�����ұ���ʾ��һ�����飬ԭ����	void Draw();���ڶ��������ƫ����
	void Draw(int offsetX,int offsetY);
	void Move(int rows, int colums);
	std::vector<Position> GetCellPosition();
	void Rotate();
	void UndoRotation();
	int id; 
	/// cells��Ա����  ����һ�� ���� key���� 0, 1, 2, 3����ӳ�䵽һ�� Position ����	Ҳ����ÿһ�� cells[i] ����һ�� std::vector<Position>
		///���Ǵ� cells ��� map ��ȡ����ǰ��ת״̬�µĸ��ӣ�С���飩���ꡣ
	std::map<int, std::vector<Position>>cells;
private:
	int cellSize;
	int rotationState;
	std::vector<Color>colors;
	int rowOffset;
	int columOffset;

};