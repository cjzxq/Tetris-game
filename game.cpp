#include"game.h"
#include<random>
#include"iostream"
Game::Game()
{
	/// 创建网格对象
	grid = Grid();
	//blocks = {IBlock(),JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	blocks = GetAllBlocks();
	currenBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();//准备音效
	if (!IsAudioDeviceReady()) {
		std::cout << "音频设备初始化失败！" << std::endl;
	}
	music = LoadMusicStream("sounds/music.ogg");//准备音效加载一段“流式音乐”，用于长时间播放的大文件音乐（例如背景音乐）。
	//music = LoadMusicStream("sounds/whoosh1.wav");
	PlayMusicStream(music);
	//rotateSound = LoadSound("Sounds/rotate.mp3");//加载一段短音效，用于短促的效果音（例如旋转、消除时的声音）。mp3格式不行
	rotateSound = LoadSound("sounds/rotate.wav");
	clearSound = LoadSound("sounds/clear.wav");

	//SetSoundVolume(rotateSound, 1.0f); // 最大音量
	//SetSoundVolume(clearSound, 1.0f);
	//SetMusicVolume(music, 1.0f);
}

Game::~Game()
{
	//卸载音乐文件
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::GetRandomBlock()/// 类内部的成员函数GetRandomBlock可以访问私有成员blocks
{
	/// 检查向量是否为空
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	/// 从向量中移除，下次调用的时候，该方块不可用 最后，在某个时刻，向量将变为空，这意味着将不在有可用的方块 所以需要用方块重新填充向量
	blocks.erase(blocks.begin() + randomIndex);
	return block;

}
/// 创建一个返回包含所有方块的向量的函数  返回一个向量，里面每个元素都是Block的一个对象
std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(),JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() 
{
	grid.Draw();// 调用的是 Grid 类型成员的 Draw 函数
	currenBlock.Draw(11,11); //原来是调用的是 Block 类型成员的 Draw 函数,currenBlock类型是Block
	//nextBlock.Draw(270, 270);右边所有的方块都显示在这个位置
	//使在右边显示的Iblock和Oblock居中
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 280);
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}
}

//按 ↑
//↓
//Rotate() → rotationState++
//↓
//下一帧调用 Draw()
//↓
//Draw() → GetCellPosition()
//↓
//从 cells[rotationState] 取出形状
//↓
//DrawRectangle(...) 绘制新图形


void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	//游戏结束，重启游戏
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}
	switch (keyPressed)
	{
	case KEY_UP:
		RotateBlock();
		break;
	case KEY_LEFT:
		MoveBlockLeft();
		//currenBlock.Move(0, -1);原来写的这一行，没有上一行MoveBlockLeft();就出现了方块左右移动会出边界的情况，同时方块碰撞也会覆盖
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		//currenBlock.Move(0, 1);
		break;
	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		//currenBlock.Move(1, 0);
		break;
	}
}

void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currenBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currenBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currenBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currenBlock.Move(0, -1);
		}
	}
}
void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currenBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currenBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

//是否会移出网格
bool Game::IsBlockOutside()
{
	//获取块的所有图块
	std::vector<Position>tiles = currenBlock.GetCellPosition();
	//检查所有图块是否在网格之外
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.colum))
		{
			return true;
		}
	}
	return false;
}

//rotationState = 0
void Game::RotateBlock()
{
	if (!gameOver)
	{
		currenBlock.Rotate();
		//设当前rotationState = 0，执行 Rotate() → rotationState = 1 发现出界 → 调用 UndoRotation() → rotationState = 0
		if (IsBlockOutside() || BlockFits() == false)
		{
			currenBlock.UndoRotation();
		}
		else
		{
			PlaySound(rotateSound);
		}
	}
}
//方块下落确定方块位置
void Game::LockBlock()
{
	//获取当前方块的所有小格位置（考虑了偏移量后的真实位置）
	std::vector<Position>tiles = currenBlock.GetCellPosition();
	for (Position item : tiles)
	{
		//把当前方块的每个小格子的位置，用它的 id 写入网格数组中 grid.grid[row][col]，表示方块已经固定在这些位置。”
		grid.grid[item.row][item.colum] = currenBlock.id;
	}
	currenBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	//grid.ClearFullRows(); 如果这行不去掉，则分数不会变，因为rowsCleared=0了
	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}

}
//重启游戏
void Game::Reset()
{
	grid.Initialize();
	//创建一个包含所有块的新向量
	blocks = GetAllBlocks();
	currenBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}
void Game::UpdateScore(int LinesCleared, int moveDownPoint)
{
	switch (LinesCleared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 200;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	score += moveDownPoint;
}
//方块下落判断是否会碰撞
bool Game::BlockFits()
{
	std::vector<Position>tiles = currenBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row,item.colum) == false)
		{
			return false;
		}
	}

	return true;
}
