#include"position.h"

Position::Position(int row, int colum)
{
	/// this关键字用于引用当前对象，this->用于访问对象内的变量，this->row=row;表示将row参数的值赋给当前对象的row属性
	this->row=row;
	this->colum = colum;
}