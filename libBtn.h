/*


	Copyright (c) 2024
	Sqrt404


	Permission to use, copy, modify, distribute and sell this software
	and its documentation for any purpose is hereby granted without fee,
    provided that the above copyright notice appear in all copies and
    that both that copyright notice and this permission notice appear in supporting documentation.  
    Every changes of this code should write a document for it.
    
    
*/



#include <windows.h>
#define KeyDown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
#include <bits/stdc++.h>
using namespace std;
namespace Ccs
{
    HANDLE consoleMutex;
    struct button
    {
        HANDLE Bthread;
        bool stat = false;
        int nx, ny, stats = -1, r, g, b;
        string text;
        HWND hwndbaba;
        void (*func)();
        void Goto(int x, int y)
        {
            COORD coord;
            coord.X = x;
            coord.Y = y;
            HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(a, coord);
        }

        void rgbb(int br, int bg, int bb)
        {
            printf("\033[48;2;%d;%d;%dm", br, bg, bb);
        }

        void rgbw(int wr, int wg, int wb)
        {
            printf("\033[38;2;%d;%d;%dm", wr, wg, wb);
        }

        void HideCursor()
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO CursorInfo;
            GetConsoleCursorInfo(handle, &CursorInfo);
            CursorInfo.bVisible = false;
            SetConsoleCursorInfo(handle, &CursorInfo);
        }

        static DWORD WINAPI ButtonThread(LPVOID lpParam)
        {
            button* self = static_cast<button*>(lpParam);
            self->HideCursor();
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
            DWORD mode;
            GetConsoleMode(hStdin, &mode);
            mode &= ~ENABLE_QUICK_EDIT_MODE;
            mode &= ~ENABLE_INSERT_MODE;
            mode &= ~ENABLE_MOUSE_INPUT;
            SetConsoleMode(hStdin, mode);
            self->HideCursor();
            CONSOLE_FONT_INFO k;
            POINT p;
            while (self->stat == true)
            {
            	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), false, &k);
                GetCursorPos(&p);
                ScreenToClient(GetConsoleWindow(), &p);
                WaitForSingleObject(consoleMutex, INFINITE);
                self->Goto(self->nx, self->ny);
                if (p.x / k.dwFontSize.X >= self->nx && p.y / k.dwFontSize.Y >= self->ny && p.x / k.dwFontSize.X <= self->nx + self->text.size() + 1 && p.y / k.dwFontSize.Y <= self->ny)
                {
                    if (self->hwndbaba == GetForegroundWindow() && KeyDown(VK_LBUTTON))
                    {
                        self->stats = 2;
                        self->rgbw(12, 12, 12);
                        self->rgbb(self->r, self->g, self->b);
                        cout << "-" << self->text << "-";
                        while (KeyDown(VK_LBUTTON));
                        self->Goto(self->nx, self->ny);
                        self->rgbw(self->r, self->g, self->b);
                        self->rgbb(12, 12, 12);
                        cout << "<" << self->text << ">";
                        self->Goto(self->nx, self->ny);
                        self->rgbw(255, 255, 255);
                        self->rgbb(12, 12, 12);
                        if(self->func != NULL) self->func();
                    }
                    else
                    {
                        self->stats = 1;
                        self->rgbw(self->r, self->g, self->b);
                        self->rgbb(12, 12, 12);
                        cout << "<" << self->text << ">";
                        self->rgbw(self->r, self->g, self->b);
	                    self->rgbw(255, 255, 255);
	                    self->rgbb(12, 12, 12);
                    }
                }
                else
                {
                    self->rgbw(self->r / 2, self->g / 2, self->b / 2);
                    self->rgbb(12, 12, 12);
                    self->stats = 0;
                    cout << "<" << self->text << ">";
                    self->rgbw(255, 255, 255);
                    self->rgbb(12, 12, 12);
                }
                ReleaseMutex(consoleMutex);
                Sleep(50);
            }
            WaitForSingleObject(consoleMutex, INFINITE);
            self->Goto(self->nx, self->ny);
            self->stats = -1;
            cout << "  ";
            for(int i = 0; i < self->text.size(); i++) cout << " ";
            ReleaseMutex(consoleMutex);
            return 0;
        }
        void startb(void (*f)(), int x, int y, string text1, int a1 = 255, int b1 = 255, int c1 = 255)
        {
            func = f;
            hwndbaba = GetConsoleWindow();
            nx = x;
            ny = y;
            r = a1;
            g = b1;
            b = c1;
            text = text1;
            stat = true;
            Bthread = CreateThread(NULL, 0, ButtonThread, this, 0, NULL);
        }
        void stopb()
        {
            stat = false;
            WaitForSingleObject(Bthread, INFINITE);
            CloseHandle(Bthread);
        }
        void ChangeColor(int ar = 255, int ag = 255, int ab = 255)
        {
        	r = ar;
        	g = ag;
        	b = ab;
		}
		void ChangeText(string text1)
		{
			text = text1;
		}
    };
    void Goto_OutOfStruct(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(a, coord);
    }
    void rgbw_OutOfStruct(int wr, int wg, int wb)
    {
        printf("\033[38;2;%d;%d;%dm", wr, wg, wb);
    }
    void StartSet()
    {
        rgbw_OutOfStruct(255, 255, 255);
        consoleMutex = CreateMutex(NULL, FALSE, NULL);
        srand(time(0));
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwInMode, dwOutMode;
        GetConsoleMode(hOut, &dwOutMode);
        dwOutMode |= 0x0004;
        SetConsoleMode(hOut, dwOutMode);
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO CursorInfo;
        GetConsoleCursorInfo(handle, &CursorInfo);
        CursorInfo.bVisible = false;
        SetConsoleCursorInfo(handle, &CursorInfo);
    }
    void StartMutex()
    {
        consoleMutex = CreateMutex(NULL, FALSE, NULL);
    }

    void mlock()
    {
        WaitForSingleObject(consoleMutex, INFINITE);
    }
    void munlock()
    {
        ReleaseMutex(consoleMutex);
    }
}
