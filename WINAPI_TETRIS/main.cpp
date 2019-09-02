#include "헤더.h"
#include "GameScene.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
const char* lpszClass = "TETRIS 2018";

enum GameState { Menu, Game };

GameState state;


GameScene gameScene;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 646,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// 랜덤 초기화
	srand(time(NULL));

	state = Menu;
	gameScene.hWnd = hWnd;

	while (true)
	{
		if(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT || Message.message == WM_DESTROY)
			{
				break;
			}
				
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		// GameLoop
		else if (state == Game)
		{
			gameScene.Input();
			gameScene.Update();
			// Render
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}
	}

	return Message.wParam;
}

void DrawBG(HINSTANCE hInst, HDC hdc, int id)
{
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	MemDC = CreateCompatibleDC(hdc);
	MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(id));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
	BitBlt(hdc, 0, 0, 800, 600, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	gameScene.hInst = g_hInst;
	switch (iMessage) {
	case WM_CREATE:
		return 0;

	case WM_KEYDOWN:
		switch (state)
		{
		case Menu:
			switch (wParam)
			{
			// 게임으로 들어가기
			case VK_RETURN:
				gameScene.Init();
				state = Game;
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
				break;

			default:
				break;
			}
			break;

		case Game:
			switch (wParam)
			{
			case VK_ESCAPE:
				gameScene.Exit();
				state = Menu;
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
				break;
			}
			break;
		}
		return 0;

	case WM_PAINT:
		gameScene.hdc = hdc = BeginPaint(hWnd, &ps);
		switch (state)
		{
		case Menu:
			DrawBG(g_hInst, hdc, IDB_MENUBG);
			break;
		case Game:
			gameScene.Render();
			break;
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}