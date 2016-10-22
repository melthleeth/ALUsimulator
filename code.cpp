/*
만들어야 할 기능:
이진수 변환(O)
십진수 변환(O)
2의 보수 변환(O)
덧셈/뺄셈(O)
곱셈/나눗셈
*/

#include <iostream>
#define SIZE 32 // 레지스터 최대길이: 32비트
using namespace std;

int *convert_complement(int *arr) { /* 2의 보수 변환 */

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


int *convert_binary(int num, int *arr) {
	int k = SIZE - 1; // 카운팅용 변수
	bool minus = false;

	if (num < 0) { // 음수판별 --> 추후 2의 보수로 바꿀지 결정하는데 사용됨
		num = num * (-1);
		minus = true;
	}

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

	if (minus) { // 위에서 음수라는게 확인되었다면 2의 보수로 변환됨
		convert_complement(arr);
	}
	//// ****출력 잘되는지 확인용****
	//for (int i = 0; i < SIZE; i++) {
	//	cout << arr[i];
	//	if (i % 4 == 3) cout << "|";
	//}
	//// ****************************

	return arr;
}

int *sum(int *arr1, int *arr2, int *result) { /* 덧셈연산 */
	//int result[SIZE]; // 결과 저장용 배열
	
	for (int i = 0; i < SIZE; i++) // 배열 초기화
		result[i] = 0;

	for (int i = SIZE - 1; i >= 0; i--) {
		int sum = arr1[i] + arr2[i]; // 자릿수 합 저장
		int temp = sum + result[i]; // 자리올림 발생할 수 있으므로 변수 하나 더 정의
		

		if (temp == 1 || temp == 0)
			result[i] = temp;
		if (temp == 2) {
			result[i] = 0;
			if (i != 0) result[i - 1] = 1; // array index 가 -1 이 되는 것을 방지
			else break;
		}
		if (temp == 3) {
			result[i] = 1;
			if (i != 0) result[i - 1] = 1;
			else break;
		}
		//cout << sum << " " << temp << " " << result[i] << endl;
	}

	//cout << "함수 안에서 덧셈 후" << endl;
	// for (int i = 0; i < SIZE; i++)
	//	cout << result[i];

	// cout << endl;

	return result;
}

void main() {
	int a; 
	int b;
	int A[SIZE];
	int B[SIZE];
	int sumarr[SIZE]; // 덧셈결과 저장 배열

	cout << "두 수를 입력하세요: ";
	cin >> a >> b;
	
	int *x = convert_binary(a, A);
	int *y = convert_binary(b, B);


	cout << "[" << a << "]의 2진수 변환" << endl;
	if (a < 0) cout << "(2의보수로 변환됨)" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << x[i];
	cout << endl;

	cout << "[" << b << "]의 2진수 변환" << endl;
	if (b < 0) cout << "(2의보수로 변환됨)" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << y[i];
	cout << endl;

	int *result = sum(x, y, sumarr);
	cout << "함수 밖에서 덧셈 후" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << result[i];
	cout << endl;

	
	return;
}
