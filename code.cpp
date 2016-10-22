/*
만들어야 할 기능:
이진수 변환
보수 변환
덧셈/뺄셈: 병렬 가감산기
곱셈은 Booth alg로
*/

#include <iostream>
#define SIZE 32 // 레지스터 최대길이: 32비트
using namespace std;

int *convert_binary(int num, int *arr) {
	//int arr[SIZE];
	int k = SIZE - 1; // 카운팅용 변수

	for (int i = 0; i < SIZE; i++) // 배열 모두 0으로 채움
		arr[i] = 0;

	while (1) {
		arr[k] = num % 2;
		//cout << arr[k];
		num = num / 2;
		if (num == 1) {
			arr[k - 1] = 1;
			break;
		}
		else k--;
	}
	//// ****출력 잘되는지 확인용****
	//for (int i = 0; i < SIZE; i++) {
	//	cout << arr[i];
	//	if (i % 4 == 3) cout << "|";
	//}
	//// ****************************
	return arr;
}


void main() {
	int a; 
	int b;
	int arr[SIZE];

	cout << "두 수를 입력하세요: ";
	cin >> a >> b;
	
	int *x = convert_binary(a, arr);
	int *y = convert_binary(b, arr);
	
	//cout << endl;

	//// 출력확인용
	//for (int i = 0; i < SIZE; i++)
	//	cout << k[i];
	//cout << endl;
	//// ****

	return;
}