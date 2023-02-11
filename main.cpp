#include <windows.h>

CHAR szClassName[]="window";
HWND hEdit;

VOID AddLine(LPSTR str)
{
	DWORD len=SendMessage(hEdit,WM_GETTEXTLENGTH,0,0);
	SendMessage(hEdit,EM_SETSEL,(WPARAM)len,(LPARAM)len);
	SendMessage(hEdit,EM_REPLACESEL,(WPARAM)false,(LPARAM)str);
}

void GetDPI()
{
	TCHAR szText[1024];
	HDC screen = GetDC(0);
	int scaleX = GetDeviceCaps(screen, LOGPIXELSX);
	int scaleY = GetDeviceCaps(screen, LOGPIXELSY);
	ReleaseDC(0, screen);
	
	wsprintf(szText,"scaleX = %d\r\nscaleY = %d\r\n",scaleX,scaleY);
	AddLine(szText);
	
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg){
	case WM_CREATE:
		hEdit=CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|ES_MULTILINE,0,0,9999,9999,hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
		GetDPI();
		break;
	case WM_SIZE:
		MoveWindow(hEdit,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"DPI‚ðŽæ“¾",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}