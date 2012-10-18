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
			
			/*��Ʈ�� ������ �ҷ��´�.*/
			hFile = CreateFile(TEXT("1.bmp"), GENERIC_READ, 0, NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if(hFile == INVALID_HANDLE_VALUE)	/*�����ϸ� ���α׷� ����*/
			{
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				
				return 0;
			}
			else
			{
				/*�޸𸮿� �̹����� �����Ѵ�.*/
				ReadFile(hFile, c_image, 1024 * 1024, &dwRead, NULL);	
				CloseHandle(hFile);
				
				bfp = (BITMAPFILEHEADER *)c_image;
				wsprintf(str, TEXT("%d"), bfp -> bfSize);	/*���� ũ�� ����*/
												
			}
			InvalidateRect(hWnd, NULL, TRUE);
							
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			
			//TextOut(hdc, 10, 10, str, lstrlen(str)); 	/*������ �� ũ�⸦ ���*/
									
			/*for(i_cnt_x = 10; 40 >= i_cnt_x; ++i_cnt_x)
			{
				SetPixel(hdc, i_cnt_x, i_cnt_y, RGB(255, 0, 0));
			}*/
			
			image_p = c_image + (bfp -> bfOffBits);	/*image_p �� image�� ó���� ����Ű�� �ȴ�.*/
			
			/*ȭ�鿡 ������ ���*/
			for(i_cnt_y = 0; 710 > i_cnt_y; ++i_cnt_y)
			{		
				for(i_cnt_x = 0; 361 > i_cnt_x; ++i_cnt_x)
				{
					SetPixel(hdc, i_cnt_x, 710 - i_cnt_y, RGB(*(image_p + 2), *(image_p + 1), *(image_p + 0)));	/*�̹����� �� �ٸ� ����� ����. BGR ������ ���´�.*/
					image_p = image_p + 3;	/*3����Ʈ�� �� �ȼ��� �����̱� ������ �̵� �����ش�.*/
				}										
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

