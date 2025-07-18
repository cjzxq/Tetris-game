#include <raylib.h>
//#include "grid.h"
#include"iostream"
//#include"blocks.cpp"
#include"game.h"/// game.h�а�����include"blocks.cpp" include "grid.h"
#include <filesystem>

double lastUpdateTime = 0;
//���������ٶ���һ��
bool EventTriggered(double interval)
{
	double currenTime = GetTime();
	if (currenTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currenTime;
		return true;
	}
	return false;
}

//using namespace std;
int main()
{
	/// ������Ļ ��ʾ����Ļ��С��300���أ���600���� ��������Ļ��С����Ķ�	numRows = 20;	numCols = 10; 	InitWindow(300, 600, "realib tetris");
	///������Ϸ����  �������������ϡ�����ƫ��10���أ�����ƫ��190����ƫ����  	InitWindow(500, 620, "realib tetris");��Ϸ���������Ͻǻ��ƣ���û���κ�ƫ�� 
	/// Ϊ��ƫ�� Ȼ��grid.draw�е�+1��Ϊ+11  	block.graw�е�DrawRectangle�е�+1Ҳ�Ǳ�Ϊ+11 ʹ�����ڻ��Ƶõ�Ԫ��x��y����10����
	InitWindow(500, 620, "realib tetris");
	Color DarkBlue = { 44,44,127,255 };
	/// ������Ϸ֡�� 
	SetTargetFPS(60);// ÿ��ִ��60�� ѭ����������60�� 		game.MoveBlockDown(); һ��ʼ������ĺܿ�
	Font font = LoadFontEx("font/SourceHanSansSC-VF.ttf",64,0,0);
	//Grid grid = Grid();
	//grid.grid[0][0] = 1;
	//grid.grid[3][5] = 4;
	//grid.grid[17][8] = 7;
	//grid.print();
	//IBlock block = IBlock();
	Game game = Game();// Game()  ��ʾ���� Game ��Ĺ��캯�����������󲢳�ʼ��
	while (WindowShouldClose() == false)//ÿִ֡��һ�� ÿһ֡��Raylib �������¡������Ļ -> ���»�������Ԫ�� -> ��ʾ������
	{
		UpdateMusicStream(game.music);
		game.HandleInput();
		if (EventTriggered (0.2))
		{
			game.MoveBlockDown();
		}
		//game.MoveBlockDown();
		/// ��ʼ����
		BeginDrawing();
		ClearBackground(DarkBlue);
		///{365,15}��ʾ����λ��
		DrawTextEx(font, "score", {365,15},38,2,WHITE);
		DrawTextEx(font, "next", { 370,175 }, 38, 2, WHITE);
		if (game.gameOver)
		{
			DrawTextEx(font, "Game Over", { 320,450 }, 38, 2, WHITE);
		}

		///��Բ�ξ���
		DrawRectangleRounded({320,55,170,60},0.3,6,lightblue);

		///�õõ��ķ���������ʾ
		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText,38,2);


		DrawTextEx(font, scoreText, { 320+(170- textSize.x)/2, 65 }, 38, 2, WHITE);
		///DrawTextEx(font, "score", { 365,15 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320,215,170,180 }, 0.3, 6, lightblue);
		/// ������
		//grid.Draw();
		//block.Draw();
		game.Draw();


		/// ��������
		EndDrawing();
	}
	CloseWindow();
}