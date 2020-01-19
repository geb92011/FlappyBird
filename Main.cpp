#include "stdafx.h"

int generatePole();

void renderPole(poleData, objectLoader);
void renderBird(pos, objectLoader);



// Globals
int HIGHT = 0;



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// File names
	LPCWSTR poleBMP = L"";

	LPCWSTR birdNotBMP = L"";
	LPCWSTR birdIsBMP = L"";
	LPCWSTR backgroundBMP = L"";


	
	//HACCEL hAccelTable;
	HRESULT hr = S_OK;

	// Register the windows class
	LPCWSTR g_szClassName = L"Vikings";
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 5);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, NULL);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed", L"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Initialize window and style
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		g_szClassName,                  // Window class
		L"Vikings",					    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0L);
	HIGHT = GetSystemMetrics(SM_CXSCREEN);
	// Show the window
	ShowWindow(hwnd, nCmdShow);

	// Textures
	objectLoader BKG(backgroundBMP, GetDC(hwnd));
	BKG.bitMapLoader();

	objectLoader pole(poleBMP, GetDC(hwnd));
	pole.bitMapLoader();
	objectLoader birdUp(birdIsBMP, GetDC(hwnd));
	birdUp.bitMapLoader();
	objectLoader birdDown(birdNotBMP, GetDC(hwnd));
	birdDown.bitMapLoader();

	// play variables
	bool alive = true;
	bool start = false;
	
	// Data
	std::vector<poleData> Poles;
	int poleCtr = 0;
	// Initialize the first position
	/*turns.push_back(position());*/


	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (!start)
		{
			// Initialize all game data
			Poles.clear();
			poleCtr = 0;



			alive = true;
			start = true;
		}

		BKG.bitMapRender(0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
			
		
		// When dies
		if (!alive)
		{



			start = false;
		}
	}


	//HWND hwndButton = CreateWindow(
	//	TEXT("button"),             // The class name required is button
	//	TEXT("Push Button"),                  // the caption of the button
	//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	//	0, 0,                                  // the left and top co-ordinates
	//	100, 300,                              // width and height
	//	hwnd,                                 // parent window handle
	//	(HMENU)ID,                   // the ID of your button
	//	hInstance,                            // the instance of your application
	//	NULL);

	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	// choose which Windows messages you want to use
	switch (message)
	{
		/*case WM_CLOSE:
			DestroyWindow(hwnd);
			break;*/

			// the window is being destroyed, so terminate the application
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:// let Windows process any messages not specified in the switch statement
		return DefWindowProc(hwnd, message, wParam, lParam);
	}



}



// Randomly generats a pole
int generatePole()
{
	double random;
	bool rational = false;
	while (!rational)
	{
		
		random = std::rand() / RAND_MAX;

		random = random * HIGHT;

		if (random-50 <= HIGHT)
		{
			rational = true;
		}

	}
	return (int)random;
}

// Renders the pole
void renderPole(poleData position, objectLoader pole)
{
	int yPos;
	if (position.side)
	{
		yPos = position.y - POLEHIGHT;
	}
	else
	{
		yPos = position.y;
	}


	pole.bitMapRender(position.xStart, yPos);
}

// Renders the bird
void renderBird(pos position, objectLoader bird)
{
	bird.bitMapRender(position.x, position.y);
}