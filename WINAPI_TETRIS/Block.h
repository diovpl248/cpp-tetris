#pragma once
#include "���.h"
#define COLOR_COUNT 6

struct Point
{
	int x;
	int y;

	Point operator += (Point another)
	{
		x += another.x;
		y += another.y;
		return *this;
	}

	Point operator + (Point another)
	{
		return Point{ x + another.x,y += another.y };
	}
};

enum eTileInfo { EMPTY = 0, RED = 101, ORANGE, YELLOW, GREEN, BLUE, PURPLE, GRAY = 198, GUIDE = 199 };


class Block
{
private:
	eTileInfo mTileData[4][4];// ������� ����
	Point mPosition;//��ġ����
	eTileInfo mColor; //�÷�����
	int mType;  //����� Ÿ��

public:
	void Init();
	void CreateBlock();
	void CopyBlock(Block& block);

	void GetEachTilePosition(Point nextPosition,Point* outPoint);	// �ʻ��� Ÿ�� ������ ��ġ�� �����ش�.
	void GetEachTileVecPosition(Point* outPoint);	// Ÿ�� ������ �����ġ�� �����ش�.
	void SetEachTilePosition(Point inPosition[4]);

	Point GetPosition();
	void SetPosition(Point position);

	void GetBlockData(eTileInfo outData[4][4]);
	void SetBlockData(eTileInfo data[4][4]);

	int GetBlockType();
	void SetBlockType(int type);

	eTileInfo GetBlockColor();


public:
	Block();
	~Block();
};

