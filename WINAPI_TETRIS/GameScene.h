#pragma once
#include "���.h"
#include "resource.h"
#include "Block.h"
#include "SoundManager.h"

const int MOVE_DELAY = 150;
const int TURN_DELAY = 200;
const int SPACE_DELAY = 200;

enum eInputType {NONE, LEFT, RIGHT, UP, DOWN, SPACE, ESC};

class GameScene
{
private:
	SoundManager* theSoundManager;

	unsigned char mMap[HEIGHT][WIDTH];	// ��ü ���� �����ϴ� ����
	Block mNextBlock;
	Block mCurBlock;

	Point mGuidePosition;		// ����� ���� �������� �����ִ� ���̵���� ��ġ
	
	int mHighScore;			
	int mCurrentScore;
	
	int mLastTick;
	
	int mMoveTime;			// Ű�� ������ �󸶳� �������� ����
	int mTurnTime;
	int mSpaceTime;

	int mScore;

	bool mLose;		// ���ӿ� �������
	bool mbEscape;	// �޴�����

public:
	HWND hWnd;
	HINSTANCE hInst;
	HDC hdc;
	HDC hdc2;
	HBITMAP newBitmap, oldBitmap;

	HFONT newFont, oldFont;

	eInputType inputType;	// �������� �Էµ� ��� ����

private:
	void InputProcess();	// �ԷµȰ� ó��

	void ResetBlock();		// ���� ����� ����������� �ٲ��ְ�, ��������� ���� �����Ѵ�.
	bool CollisionCheck(Point nextPosition, Block& block);	// �ش���ġ�� ����� �����Ұ�� ���� ��ϰ� �浹�ϴ��� üũ
	void PutBlock();		// ����� ������ġ�� �д�.
	void LineClear();		// �ʿ� ���ٷ� ä���� ������ �����ش�.
	void TurnBlock();		// ���� ����� ȸ����Ŵ

	void DrawBG();		// ����� �׷��ش�.
	void DrawBlock(Block& block, Point position, eTileInfo color);		// ���� ��, ���� ��, ���̵���� �׷��ش�.
	void DrawBox(Point position, int type);		// ���κ���� ��ĭ��ĭ �׷��ش�.
	void DrawGameOver();	// ���ӿ��� �ǳ� ���
	void DrawLogo();	// �ΰ� ���

public:
	void Init();	// �ʱ�ȭ
	void Input();	// �Է�
	void Update();	// ������Ʈ
	void Render();	// ����

	void Exit(); //����

	GameScene();
	~GameScene();
};

