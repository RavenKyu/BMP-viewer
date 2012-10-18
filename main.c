 #include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); /* 메세지 처리함수 */

HWND hWndMain;
HINSTANCE g_hInst;              /* instance의 전역변수 선언 */
LPCTSTR lpszClass = TEXT("Class"); /* 윈도우 클래스의 이름 정의 */



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    /* 윈도우 클래스 정의 */
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	/*창의 배경색 설정*/
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	/*창에서 사용할 커서 지정*/	
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	/*아이콘 지정*/
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc; /* 메세지 처리 함수를 지정 */
    WndClass.lpszClassName = lpszClass; /* 윈도우 클래스 이름이 들어감 */
    WndClass.lpszMenuName = NULL;       /* 여기선 메뉴 사용 안함 */
    WndClass.style =  CS_HREDRAW | CS_VREDRAW;
    
    RegisterClass(&WndClass);	/* 윈도우 클래스 등록 */

	/* 메모리상에 윈도우 생성 */
	hWnd = CreateWindow(
		lpszClass,					/*생성하고자 하는 윈도우 클래스 지정*/
		TEXT("My first Windows API Program. Hello World"),	/*윈도우의 타이틀 바에 나타날 문자열*/
		WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,	/*만들고자 하는 윈도우의 형태를 지정*/
		0,	/*생성 위치 X*/
		0,	/*생성 위치 Y*/
		640,	/*생성 윈도우의 폭*/
		480,	/*생성 윈도우의 높이*/
		NULL,
		(HMENU)NULL, 
		hInstance, 
		NULL);

    /* 화면에 윈도우 표시 */
    ShowWindow(hWnd, nCmdShow); /* CreateWindow 함수가 리턴한 핸들을 이용하여 출력 */

    /* 사용자로부터의 메시지 처리  */
    while(GetMessage(&Message, NULL, 0, 0)) /* 메시지 큐에서 메시지 읽어옴. WM_QUIT면 False 리턴 */
    {
        TranslateMessage(&Message); /* 키보드 입력 처리 */
        DispatchMessage(&Message);  /* 큐에서 꺼낸 메시지를 WndProc함수의 iMessage로 전달하는 것이지 직접호출하지 않는다. */
    }
    return (int)Message.wParam; /* 메세지 루프 종료 후 이 프로그램을 실행시킨 OS로 리턴 */
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	/*운영체제가 호출하는 CALL BACK 함수*/
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	HANDLE hFile;
	DWORD dwRead;
	
	static TCHAR c_image[1024 * 1024];
	static char str[125] = {0, };
	
	static BITMAPFILEHEADER *bfp;	
	
	static char *image_p;
	
	int i_cnt_x = 10;
	int i_cnt_y = 10;
		
    switch(iMessage)
    {
		case WM_CREATE:
			hWndMain = hWnd;
			
			/*비트맵 파일을 불러온다.*/
			hFile = CreateFile(TEXT("1.bmp"), GENERIC_READ, 0, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if(hFile == INVALID_HANDLE_VALUE)	/*실패하면 프로그램 종료*/
			{
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				
				return 0;
			}
			else
			{
				/*메모리에 이미지를 적재한다.*/
				ReadFile(hFile, c_image, 1024 * 1024, &dwRead, NULL);	
				CloseHandle(hFile);
				
				bfp = (BITMAPFILEHEADER *)c_image;
				wsprintf(str, TEXT("%d"), bfp -> bfSize);	/*파일 크기 정보*/
												
			}
			InvalidateRect(hWnd, NULL, TRUE);
							
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			
			//TextOut(hdc, 10, 10, str, lstrlen(str)); 	/*파일의 총 크기를 출력*/
									
			/*for(i_cnt_x = 10; 40 >= i_cnt_x; ++i_cnt_x)
			{
				SetPixel(hdc, i_cnt_x, i_cnt_y, RGB(255, 0, 0));
			}*/
			
			image_p = c_image + (bfp -> bfOffBits);	/*image_p 는 image의 처음을 가리키게 된다.*/
			
			/*화면에 사진을 출력*/
			for(i_cnt_y = 0; 710 > i_cnt_y; ++i_cnt_y)
			{		
				for(i_cnt_x = 0; 361 > i_cnt_x; ++i_cnt_x)
				{
					SetPixel(hdc, i_cnt_x, 710 - i_cnt_y, RGB(*(image_p + 2), *(image_p + 1), *(image_p + 0)));	/*이미지의 한 줄만 출력해 본다. BGR 순으로 나온다.*/
					image_p = image_p + 3;	/*3바이트가 한 픽셀의 정보이기 때문에 이동 시켜준다.*/
				}										
			}
			
			EndPaint(hWnd, &ps);
			return 0;
	
		case WM_LBUTTONDOWN:
						
			return 0;
		
		case WM_KEYDOWN:		/*키 입력이 들어왔을 때 여기로 들어 온다.*/
			
			return 0;

		case WM_COMMAND:
			
			return 0;
			
		case WM_DESTROY:
			PostQuitMessage(0);	/*종료 메세지인 WM_DESTROY를 만든다.*/
			return 0;
	}
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

