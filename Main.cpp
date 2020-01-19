#include "stdafx.h"

int generatePole();

void renderPole(poleData, objectLoader);
void renderBird(pos, objectLoader);


pos updateBird(pos, int);
poleData updatePole(poleData, int);

// Globals
int HIGHT = 0;

bool FLAP = false;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// File names
	LPCWSTR poleTopBMP = L"bottompole.bmp";
	LPCWSTR poleBottomBMP = L"bottompole.bmp";

	LPCWSTR birdNotBMP = L"Sample bird.bmp";
	LPCWSTR birdIsBMP = L"Sample bird.bmp";

	LPCWSTR backgroundBMP = L"background.bmp";
	LPCWSTR GetreadyBMP = L"Getready.bmp";


	
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
		0, 0,
		WINDX, WINDY,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	/*SetWindowPos(hwnd, HWND_TOPMOST, 0, 0,
		WINDX, WINDY;*/

	HIGHT = WINDY;
	// Show the window
	ShowWindow(hwnd, nCmdShow);

	// Textures
	objectLoader BKG(backgroundBMP, GetDC(hwnd));
	BKG.bitMapLoader();
	objectLoader GetReady(GetreadyBMP, GetDC(hwnd));
	GetReady.bitMapLoader();

	objectLoader poleTop(poleTopBMP, GetDC(hwnd));
	poleTop.bitMapLoader();
	objectLoader poleBottom(poleBottomBMP, GetDC(hwnd));
	poleBottom.bitMapLoader();
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

	// Bird
	pos bird;
	int score = 0;
	int speed;
	clock_t endWait;
	// Initialize the first position
	/*turns.push_back(position());*/

	// Get ready
	Sleep(10000);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (!start)
		{
			// Initialize all game data
			Poles.clear();
			poleCtr = 0;
			score = 0;
			speed = INITSPEED;

			bird.x = BIRDX;
			bird.y = 100;
			bird.ySpeed = -1;
			bird.xSpeed = INITSPEED;

			alive = true;
			start = true;
			GetReady.bitMapRender(0, 0);
			Sleep(1000);
			renderBird(bird, birdDown);
			
		}

		
		/*TranslateMessage(&msg);
		DispatchMessage(&msg);*/
		

		// Keep the pole array small
		for (int i = 0; i < poleCtr; i++)
		{
			if (Poles[i].xEnd < 0)
			{
				Poles.erase(Poles.begin()+i);
				poleCtr--;
			}
		}

		// Move stuff
		bird = updateBird(bird, score);
		speed = bird.xSpeed;

		for (int i = 0; i < poleCtr; i++)
		{
			Poles[i] = updatePole(Poles[i], speed);
		}

		// Get keystroke
		endWait = clock() + WAITTIME;
		while (clock() <= endWait)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				FLAP = true;
			}
		}



		BKG.bitMapRender(0, 0);
		// Render poles
		for (int i = 0; i < poleCtr; i++)
		{
			if (Poles[i].side)
			{
				renderPole(Poles[i], poleTop);
			}
			else
			{
				renderPole(Poles[i], poleBottom);
			}
		}
		
		// render bird
		if (FLAP)
		{
			renderBird(bird, birdUp);
			if (bird.ySpeed < 0)
			{
				bird.ySpeed = bird.ySpeed - FLAPPWR;
			}
			else
			{
				bird.ySpeed = 0 - FLAPPWR;
			}
		}
		else
		{
			renderBird(bird, birdDown);
		}
		FLAP = false;





		// Death checker
		for (int i = 0; i < poleCtr; i++)
		{
			if (bird.x + BIRDWIDTH >= Poles[i].xStart && bird.x <= Poles[i].xEnd)
			{
				if (Poles[i].side && bird.y <= Poles[i].y)
				{
					alive = false;
				}

				if (!Poles[i].side && bird.y + BIRDHIGHT >= Poles[i].y)
				{
					alive = false;
				}
			}
		}

		if (bird.y <= 0 || bird.y >= 600)
		{
			alive = false;
		}
			
		
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

poleData updatePole(poleData old, int speed)
{
	poleData updated;
	updated = old;

	updated.xEnd = old.xEnd - speed;
	updated.xStart = old.xStart - speed;

	return updated;
}


pos updateBird(pos old, int score)
{
	pos updated;

	updated.x = BIRDX;
	updated.y = old.y + old.ySpeed;
	updated.ySpeed = old.ySpeed + GRAVITY;
	updated.xSpeed = INITSPEED + 5*score;

	return updated;
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