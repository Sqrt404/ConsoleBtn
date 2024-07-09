## 控制台按钮：

### 函数、变量定义：

```cpp
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
        void Goto(int x, int y);
        void rgbb(int br, int bg, int bb);
        void rgbw(int wr, int wg, int wb);
        void HideCursor();
        static DWORD WINAPI ButtonThread(LPVOID lpParam);
        void startb(void (*f)(), int x, int y, string text1, int a1 = 255, int b1 = 255, int c1 = 255);
        void stopb();
        void ChangeColor(int ar = 255, int ag = 255, int ab = 255);
		void ChangeText(string text1);
    };
    void Goto_OutOfStruct(int x, int y);
    void rgbw_OutOfStruct(int wr, int wg, int wb);
    void StartSet();
    void StartMutex();
    void mlock();
    void munlock();
};
```

---

### 函数、变量使用方法

1.

```cpp
void startb(void (*f)(), int x, int y, string text1, int a1 = 255, int b1 = 255, int c1 = 255);
```
第一个参数为按钮按下时执行的函数，可以为NULL。第二个和第三个参数为按钮位置。第四个是按钮中的文字。最后三个参数可以不填，表示按钮的RGB值，不填默认为白色。

2.

```cpp
void stopb();
```

关闭按钮显示。

3.

```cpp
void ChangeColor(int ar = 255, int ag = 255, int ab = 255);
```

修改按钮颜色，不写默认重置为白色。

4.

```cpp
void ChangeText(string text1);
```

修改按钮文字。

### 贡献者：

- [Sqrt404](https://github.com/Sqrt404)
