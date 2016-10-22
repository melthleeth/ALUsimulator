#include <iostream>
#include <climits>

using namespace std;

void main() {
	int a; // length of stick
	int cnt = 0; // count #1

	while(1) {
		cout << "원하는 길이를 입력하세요(0<길이<65): ";
		cin >> a;

		if (a > 64 || a < 1)
			cout << "길이를 초과하였습니다." << endl;
		else if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "숫자만 입력가능합니다." << endl;
		}
			break;
	}
	//cout << a;

	while (1) {
		if (a == 1) break;

		//cout << a % 2;
		if (a % 2 == 1) {
			cnt++;
			a = a / 2;
			//cout << "[" << a << "]";
		}
		else if (a % 2 == 0) {
			a = a / 2;
			//cout << "[" << a << "]";
		}
	}
	cnt++;

	cout << "붙인 막대 수:" << cnt << endl;

	return;
}