#include <raylib.h>
//#include "grid.h"
#include"iostream"
//#include"blocks.cpp"
#include"game.h"/// game.h中包含了include"blocks.cpp" include "grid.h"
#include <filesystem>

double lastUpdateTime = 0;
//方块下落速度慢一点
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
	/// 创建屏幕 显示的屏幕大小宽300像素，高600像素 如果想改屏幕大小还需改动	numRows = 20;	numCols = 10; 	InitWindow(300, 600, "realib tetris");
	///创建游戏窗口  让网格向左、向上、向下偏移10像素，向右偏移190像素偏移量  	InitWindow(500, 620, "realib tetris");游戏窗口在左上角绘制，还没有任何偏移 
	/// 为了偏移 然后grid.draw中的+1改为+11  	block.graw中得DrawRectangle中的+1也是变为+11 使得正在绘制得单元格x和y增加10像素
	InitWindow(500, 620, "realib tetris");
	Color DarkBlue = { 44,44,127,255 };
	/// 创建游戏帧率 
	SetTargetFPS(60);// 每秒执行60次 循环被调用了60次 		game.MoveBlockDown(); 一开始会下落的很快
	Font font = LoadFontEx("font/SourceHanSansSC-VF.ttf",64,0,0);
	//Grid grid = Grid();
	//grid.grid[0][0] = 1;
	//grid.grid[3][5] = 4;
	//grid.grid[17][8] = 7;
	//grid.print();
	//IBlock block = IBlock();
	Game game = Game();// Game()  表示调用 Game 类的构造函数来创建对象并初始化
	while (WindowShouldClose() == false)//每帧执行一次 每一帧，Raylib 都会重新“清空屏幕 -> 重新绘制所有元素 -> 显示出来”
	{
		UpdateMusicStream(game.music);
		game.HandleInput();
		if (EventTriggered (0.2))
		{
			game.MoveBlockDown();
		}
		//game.MoveBlockDown();
		/// 开始绘制
		BeginDrawing();
		ClearBackground(DarkBlue);
		///{365,15}显示分数位置
		DrawTextEx(font, "score", {365,15},38,2,WHITE);
		DrawTextEx(font, "next", { 370,175 }, 38, 2, WHITE);
		if (game.gameOver)
		{
			DrawTextEx(font, "Game Over", { 320,450 }, 38, 2, WHITE);
		}

		///画圆形矩形
		DrawRectangleRounded({320,55,170,60},0.3,6,lightblue);

		///让得到的分数居中显示
		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText,38,2);


		DrawTextEx(font, scoreText, { 320+(170- textSize.x)/2, 65 }, 38, 2, WHITE);
		///DrawTextEx(font, "score", { 365,15 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320,215,170,180 }, 0.3, 6, lightblue);
		/// 画网格
		//grid.Draw();
		//block.Draw();
		game.Draw();


		/// 结束绘制
		EndDrawing();
	}
	CloseWindow();
}