 #include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); /* �޼��� ó���Լ� */

HWND hWndMain;
HINSTANCE g_hInst;              /* instance�� �������� ���� */
LPCTSTR lpszClass = TEXT("Class"); /* ������ Ŭ������ �̸� ���� */



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    /* ������ Ŭ���� ���� */
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	/*â�� ���� ����*/
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	/*â���� ����� Ŀ�� ����*/	
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	/*������ ����*/
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc; /* �޼��� ó�� �Լ��� ���� */
    WndClass.lpszClassName = lpszClass; /* ������ Ŭ���� �̸��� �� */
    WndClass.lpszMenuName = NULL;       /* ���⼱ �޴� ��� ���� */
    WndClass.style =  CS_HREDRAW | CS_VREDRAW;
    
    RegisterClass(&WndClass);	/* ������ Ŭ���� ��� */

	/* �޸𸮻� ������ ���� */
	hWnd = CreateWindow(
		lpszClass,					/*�����ϰ��� �ϴ� ������ Ŭ���� ����*/
		TEXT("My first Windows API Program. Hello World"),	/*�������� Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�*/
		WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,	/*������� �ϴ� �������� ���¸� ����*/
		0,	/*���� ��ġ X*/
		0,	/*���� ��ġ Y*/
		640,	/*���� �������� ��*/
		480,	/*���� �������� ����*/
		NULL,
		(HMENU)NULL, 
		hInstance, 
		NULL);

    /* ȭ�鿡 ������ ǥ�� */
    ShowWindow(hWnd, nCmdShow); /* CreateWindow �Լ��� ������ �ڵ��� �̿��Ͽ� ��� */

    /* ����ڷκ����� �޽��� ó��  */
    while(GetMessage(&Message, NULL, 0, 0)) /* �޽��� ť���� �޽��� �о��. WM_QUIT�� False ���� */
    {
        TranslateMessage(&Message); /* Ű���� �Է� ó�� */
        DispatchMessage(&Message);  /* ť���� ���� �޽����� WndProc�Լ��� iMessage�� �����ϴ� ������ ����ȣ������ �ʴ´�. */
    }
    return (int)Message.wParam; /* �޼��� ���� ���� �� �� ���α׷��� �����Ų OS�� ���� */
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	/*�ü���� ȣ���ϴ� CALL BACK �Լ�*/
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	int i_cnt_x = 10;
	int i_cnt_y = 10;
		
    switch(iMessage)
    {
		case WM_CREATE:
			hWndMain = hWnd;
									
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
									
			for(i_cnt_x = 10; 40 >= i_cnt_x; ++i_cnt_x)
			{
				SetPixel(hdc, i_cnt_x, i_cnt_y, RGB(255, 0, 0));
			} 	
							
			EndPaint(hWnd, &ps);
			return 0;
	
		case WM_LBUTTONDOWN:
						
			return 0;
		
		case WM_KEYDOWN:		/*Ű �Է��� ������ �� ����� ��� �´�.*/
			
			return 0;

		case WM_COMMAND:
			
			return 0;
			
		case WM_DESTROY:
			PostQuitMessage(0);	/*���� �޼����� WM_DESTROY�� �����.*/
			return 0;
	}
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

