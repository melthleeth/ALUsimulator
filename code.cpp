/*
만들어야 할 기능:
이진수 변환(O)
2의 보수 변환(O)
덧셈/뺄셈: 병렬 가감산기
곱셈은 Booth alg로
*/

#include <iostream>
#define SIZE 32 // 레지스터 최대길이: 32비트
using namespace std;

int *convert_binary(int num, int *arr) {
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

int *convert_complement(int *arr) {
	/* 2의 보수 변환 */

	/* STEP 1: 비트반전(1의 보수) */
	for (int i = 0; i < SIZE; i++) {
		if (arr[i] == 0)
			arr[i] = 1;
		else if (arr[i] == 1)
			arr[i] = 0;
		//cout << arr[i];
	}

	/* STEP 2: +1해서 2의 보수로 만듦 */
	arr[SIZE - 1]++;

	for (int i = SIZE - 1; i >= 0; i--) {
		if (arr[i] == 1)
			break;
		else if (arr[i] == 2) {
			arr[i] = 0;
			arr[i - 1]++;
		}
		else if (arr[i] == 3) {
			arr[i] = 1;
			arr[i - 1]++;
		}
	}

	return arr;
}

void main() {
	int a; 
	int b;
	int A[SIZE];
	int B[SIZE];

	cout << "두 수를 입력하세요: ";
	cin >> a >> b;
	
	int *x	 = convert_binary(a, A);
	int *y = convert_binary(b, B);


	cout << "[" << a << "]의 2진수 변환" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << x[i];
	cout << endl;

	cout << "[" << b << "]의 2진수 변환" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << y[i];
	cout << endl;

	cout << endl;

	convert_complement(x);
	cout << "[" << a <<  "]의 2의 보수: " << endl;
	for (int i = 0; i < SIZE; i++)
		cout << x[i];
	cout << endl;

	convert_complement(y);
	cout << "[" << b << "]의 2의 보수: " << endl;
	for (int i = 0; i < SIZE; i++)
		cout << y[i];
	cout << endl;
	
	return;
}
