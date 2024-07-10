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

5.
```cpp
Ccs::button btn;
btn.startb(NULL, 1, 1, "hi");
while(1)
{
    system("pause");
    Ccs::mlock();
    cout << btn.stats;
    Ccs::munlock();
}
```
按钮状态，0为未触摸也未按下，1为触摸但是未按下，2为已按下

---
### 贡献者：
- [Sqrt404](https://github.com/Sqrt404)
---
### 注意事项：
- 使用了这个头文件后在正常的输出前需要使用`Ccs::mlock()`，输出后需要使用`Ccs::munlock()`。例如：
  ```cpp
  Ccs::button btn;
  btn.startb(NULL, 1, 1, "hi");
  Ccs::mlock();
  cout << "Hallo World!" << endl;
  Ccs::munlock();
  ```

- 在主函数开头需要使用`Ccs::ColorSet()`和`Ccs::StartSet()`以初始化按钮所需的函数。
