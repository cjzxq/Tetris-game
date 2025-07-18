#pragma once
#include"grid.h"
#include"blocks.cpp"

class Game {
public:
/// 构造函数
	Game();
	~Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
/// 游戏类必须创建并保存一个网格

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

	/// 创建一个属性并保存当前块，该属性在屏幕上可见 首先创建一个包含所有方块的向量
	std::vector<Block>blocks;
	bool BlockFits();
	Block currenBlock;
	Block nextBlock;

	Sound rotateSound;
	Sound clearSound;

};
