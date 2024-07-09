#include "libBtn.h"

void halloworld()
{
	cout << "Hallo World!\n";
}

int main()
{
	Css::Button btn;
	btn.startb(halloworld, 1, 1, "hi");
	while(btn.stats != 2);
	btn.stopb();
	system("pause");
	return 0;
}
