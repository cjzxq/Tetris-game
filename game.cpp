#include"game.h"
#include<random>
#include"iostream"
Game::Game()
{
	/// �����������
	grid = Grid();
	//blocks = {IBlock(),JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	blocks = GetAllBlocks();
	currenBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();//׼����Ч
	if (!IsAudioDeviceReady()) {
		std::cout << "��Ƶ�豸��ʼ��ʧ�ܣ�" << std::endl;
	}
	music = LoadMusicStream("sounds/music.ogg");//׼����Ч����һ�Ρ���ʽ���֡������ڳ�ʱ�䲥�ŵĴ��ļ����֣����米�����֣���
	//music = LoadMusicStream("sounds/whoosh1.wav");
	PlayMusicStream(music);
	//rotateSound = LoadSound("Sounds/rotate.mp3");//����һ�ζ���Ч�����ڶ̴ٵ�Ч������������ת������ʱ����������mp3��ʽ����
	rotateSound = LoadSound("sounds/rotate.wav");
	clearSound = LoadSound("sounds/clear.wav");

	//SetSoundVolume(rotateSound, 1.0f); // �������
	//SetSoundVolume(clearSound, 1.0f);
	//SetMusicVolume(music, 1.0f);
}

Game::~Game()
{
	//ж�������ļ�
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::GetRandomBlock()/// ���ڲ��ĳ�Ա����GetRandomBlock���Է���˽�г�Աblocks
{
	/// ��������Ƿ�Ϊ��
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	/// ���������Ƴ����´ε��õ�ʱ�򣬸÷��鲻���� �����ĳ��ʱ�̣���������Ϊ�գ�����ζ�Ž������п��õķ��� ������Ҫ�÷��������������
	blocks.erase(blocks.begin() + randomIndex);
	return block;

}
/// ����һ�����ذ������з���������ĺ���  ����һ������������ÿ��Ԫ�ض���Block��һ������
std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(),JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() 
{
	grid.Draw();// ���õ��� Grid ���ͳ�Ա�� Draw ����
	currenBlock.Draw(11,11); //ԭ���ǵ��õ��� Block ���ͳ�Ա�� Draw ����,currenBlock������Block
	//nextBlock.Draw(270, 270);�ұ����еķ��鶼��ʾ�����λ��
	//ʹ���ұ���ʾ��Iblock��Oblock����
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

//�� ��
//��
//Rotate() �� rotationState++
//��
//��һ֡���� Draw()
//��
//Draw() �� GetCellPosition()
//��
//�� cells[rotationState] ȡ����״
//��
//DrawRectangle(...) ������ͼ��


void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	//��Ϸ������������Ϸ
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
		//currenBlock.Move(0, -1);ԭ��д����һ�У�û����һ��MoveBlockLeft();�ͳ����˷��������ƶ�����߽�������ͬʱ������ײҲ�Ḳ��
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

//�Ƿ���Ƴ�����
bool Game::IsBlockOutside()
{
	//��ȡ�������ͼ��
	std::vector<Position>tiles = currenBlock.GetCellPosition();
	//�������ͼ���Ƿ�������֮��
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
		//�赱ǰrotationState = 0��ִ�� Rotate() �� rotationState = 1 ���ֳ��� �� ���� UndoRotation() �� rotationState = 0
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
//��������ȷ������λ��
void Game::LockBlock()
{
	//��ȡ��ǰ���������С��λ�ã�������ƫ���������ʵλ�ã�
	std::vector<Position>tiles = currenBlock.GetCellPosition();
	for (Position item : tiles)
	{
		//�ѵ�ǰ�����ÿ��С���ӵ�λ�ã������� id д������������ grid.grid[row][col]����ʾ�����Ѿ��̶�����Щλ�á���
		grid.grid[item.row][item.colum] = currenBlock.id;
	}
	currenBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	//grid.ClearFullRows(); ������в�ȥ�������������䣬��ΪrowsCleared=0��
	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}

}
//������Ϸ
void Game::Reset()
{
	grid.Initialize();
	//����һ���������п��������
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
//���������ж��Ƿ����ײ
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
