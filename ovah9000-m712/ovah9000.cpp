/*
TEH OVAH 9000 CALCULATOR - m712 edition
PLEASE BUILD UPON THIS CODE
*/
#include <iostream>

using namespace std;

int main(int argc, const char **argv)
{
	int value = 0;

	cout << "How old are you" << endl;
	cin >> value;

	if (value <= 16)
		cout << "epic fail" << endl;
    else if (value >= 16)
		cout << "ALMOST THERE" << endl;
    else if (value >= 42)
        cout << "You're the answer to life, universe, and everything. :3" << endl;
    else if (value >= 9001)
		cout << "ITS OVAH 9000" << endl;

	return 0;
}
