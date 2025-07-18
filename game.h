#pragma once
#include"grid.h"
#include"blocks.cpp"

class Game {
public:
/// ���캯��
	Game();
	~Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
/// ��Ϸ����봴��������һ������

	bool gameOver;
	int score;
	Music music;




private:
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	void Reset();
	void UpdateScore(int LinesCleared,int moveDownPoint);
	void MoveBlockLeft();
	void MoveBlockRight();
	Grid grid;

	/// ����һ�����Բ����浱ǰ�飬����������Ļ�Ͽɼ� ���ȴ���һ���������з��������
	std::vector<Block>blocks;
	bool BlockFits();
	Block currenBlock;
	Block nextBlock;

	Sound rotateSound;
	Sound clearSound;

};
