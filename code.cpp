/*
만들어야 할 기능:
이진수 변환(O)
2의 보수 변환(O)
덧셈/뺄셈(O)
곱셈
나눗셈
*/

#include <iostream>
#include <cmath>
#define SIZE 32 // 레지스터 최대길이: 32비트
using namespace std;

int *convert_complement(int *arr, int size) { /* 2의 보수 변환 - 값을 담을 배열 */
	/* STEP 1: 비트반전(1의 보수) */
	for (int i = 0; i < size; i++) {
		if (arr[i] == 0)
			arr[i] = 1;
		else if (arr[i] == 1)
			arr[i] = 0;
		//cout << arr[i];
	}

	/* STEP 2: +1해서 2의 보수로 만듦 */
	arr[size - 1]++;

	for (int i = size - 1; i >= 0; i--) {
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


int *convert_binary(int num, int *arr, int size) { /* 이진수 변환 - 변환할 수, 저장할 배열, 레지스터 크기 */ 
	int k = size - 1; // 카운팅용 변수
	bool minus = false;

	if (num < 0) { // 음수판별 --> 추후 2의 보수로 바꿀지 결정하는데 사용됨
		num = num * (-1);
		minus = true;
	}

	for (int i = 0; i < size; i++) // 배열 모두 0으로 채움 - 초기화
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
		convert_complement(arr, size);
	}
	/*
	// 출력 잘되는지 확인
	for (int i = 0; i < size; i++) {
		cout << arr[i];
		if (i % 4 == 3) cout << "|";
	}
	*/

	return arr;
}

int convert_decimal(int *arr, int size) { /* 십진수 변환 - 계산할 때 사용될 배열 */
	int result = 0; // 결과값 저장
	bool negative = false; // 양수 음수 판단 변수

	/* STEP 1: 십진수 변환을 위해 양수로 바꿔줌 */
	if (arr[0] == 1) { // 먼저 보수로 바꿔줌
		negative = true;
		arr = convert_complement(arr, size);
	}

	/* STEP 2: 십진수 변환 */
	int k = 0; // 지수 카운팅용 변수
	for (int i = size - 1; i >= 0; i--) {
		if (arr[i] == 1)
			result = result + pow(2, k);
		k++;
	}

	//cout << "result = " << result << endl;

	if (negative) result = result * (-1); // 부호비트가 1(음수)였다면 음수로 취해줌

	return result;
}

int *sum(int *arr1, int *arr2, int *result, int size) { /* 덧셈연산 - 계산할 이진수 배열 2개, 결과값을 담을 배열 */
	//int result[SIZE]; // 결과 저장용 배열
	
	// 결과값 담을 배열 초기화
	for (int i = 0; i < size; i++)
		result[i] = 0;

	cout << "원래 값: ";
	for (int i = 0; i < size; i++) cout << arr1[i];
	cout << "\n더할 애: ";
	for (int i = 0; i < size; i++) cout << arr2[i];
	cout << endl;

	for (int i = size - 1; i >= 0; i--) {
		int sum = arr1[i] + arr2[i]; // 자릿수 합 저장
		int temp = sum + result[i]; // 자리올림 발생할 수 있으므로 변수 하나 더 정의
		

		if (temp == 1 || temp == 0)
			result[i] = temp;
		else if (temp == 2) {
			result[i] = 0;
			if (i != 0) result[i - 1] = 1; // array index 가 -1 이 되는 것을 방지
			else break;
		}
		else if (temp == 3) {
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

void copy(int *original, int *object, int size) {
	for (int i = 0; i < size; i++)
		original[i] = object[i];
}

void print(int *A, int *Q, int prev) { // 매번 쓰기 번거로우므로 출력하는 함수 따로 선언
	//cout << "수행 결과: ";
	for (int i = 0; i < SIZE / 2; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < SIZE / 2; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

void sprint(int *A, int *Q, int prev) { // A ± M 수행 결과 출력
	char sign;
	if (prev == 0) sign = '-';
	else if (prev == 1) sign = '+';
	cout << "A" << sign << "M 수행 결과: ";
	for (int i = 0; i < SIZE / 2; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < SIZE / 2; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

void ASR(int *A, int *Q, int &prev, int size) { /* Arithmatic Shift-Right - 적용될 배열, Q_-1 값, 배열 크기 */
	/*함수를 빠져나가니까 값 저장이 안됨. 값을 저장해서 밖으로 빼야됨*/
	
	cout << "전prev값: " << prev << endl;
	prev = Q[size - 1]; //  Q_-1에 배열 끝값 저장
	cout << "후prev값: " << prev << endl;
	
	cout << "Q 전출력 확인: ";
	for (int i = 0; i < size; i++)
		cout << Q[i];
	cout << endl;

	for (int i = size - 1; i > 0; i--)
		Q[i] = Q[i - 1];
	Q[0] = A[size - 1];

	cout << "Q 후출력 확인: ";
	for (int i = 0; i < size; i++)
		cout << Q[i];
	cout << endl;

	cout << "A 전출력 확인: ";
	for (int i = 0; i < size; i++)
		cout << A[i];
	cout << endl;

	for (int i = size - 1; i > 0; i--)
		A[i] = A[i - 1];
	//A[0] = A[1];

	cout << "A 후출력 확인: ";
	for (int i = 0; i < size; i++)
		cout << A[i];
	cout << endl;

	cout << "ASR 수행 결과: ";
	for (int i = 0; i < size; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < size; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

int *mul(int *Q, int *M, int *A, int *result, int size) { /* 곱셈 by BOOTH Alg. - 계산할 이진수 배열 2개, A레지스터, Q레지스터 */
	int prev = 0; // Q_-1 값 저장할 변수
	int init_M = M[0]; // M의 처음 부호비트
	
	/* STEP 1: A레지스터 값 설정, M레지스터 보수값 미리 구해놓기 */
	for (int i = 0; i < size; i++)
		A[i] = Q[0]; 
	
	int *M_cpl = convert_complement(M, size); // M의 2의 보수
	int init_Mcpl = M_cpl[0]; // M'의 처음 부호비트

	cout << "\n\n[곱셈]M의 2의 보수: ";
	for (int i = 0; i < size; i++)
		cout << M_cpl[i];

	cout << endl;

	cout << "\t\t A \t\t    Q \t    Q_-1" << endl;
	cout << "초기상태: ";
	print(A, Q, prev);
	
	/* STEP 2: Q레지스터 비트 크기(SIZE/2 = 16)만큼 cycle 반복 */

	int A_result[SIZE / 2] = { 0 }; // A레지스터 연산 결과 저장할 임시 변수
	int *R = { 0 };

	for (int i = 0; i < size; i++) {

		//cout << "\n\nA레지스터값: ";
		//for (int k = 0; k < size; k++)
		//	cout << A[k];

		//cout << "\n\nM레지스터값: ";
		//for (int k = 0; k < size; k++)
		//	cout << M[k];

		cout << "\ncycle " << i+1 << endl;
		if (Q[size - 1] == 0 && prev == 0) { // 00일 경우 - just ASR(Arithmatic Shift - Right)
			cout << "<00일 경우>\n";
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 1 && prev == 1) { // 11일 경우 - just ASR
			cout << "<11일 경우>\n";
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 0 && prev == 1) { // 01일 경우 - A + M & ASR
			cout << "<01일 경우>\n";
			if (M[0] != init_M) M = convert_complement(M, size);
			R = sum(A, M, A_result, size);
			copy(A, R, size); // A에 A_result값 덮어 씌움
			sprint(A, Q, prev);
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 1 && prev == 0) { // 10일 경우 - A + M'(M의 보수) & ASR
			cout << "<10일 경우>\n";
			if (M_cpl[0] != init_Mcpl) M_cpl = convert_complement(M_cpl, size);
			R = sum(A, M_cpl, A_result, size);
			copy(A, R, size); // A에 A_result값 덮어 씌움
			sprint(A, Q, prev);
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
	}

	/* STEP 3: A와 Q레지스터 합쳐서 결과레지스터에 저장 */
	for (int i = 0; i < size; i++) {
		result[i] = A[i];
		//cout << result[i];
		//if (i % 4 == 3) cout << "_";
	}
	for (int j = 0; j < size; j++) {
		result[j + size] = Q[j];
		//cout << result[j + size];
		//if (j % 4 == 3) cout << "_";
	}

	////출력 확인용
	//cout << endl << "결과 레지스터: ";
	//for (int i = 0; i < SIZE; i++)
	//	cout << result[i];

	return result;
}

void main() {
	int a; 
	int b;
	int A[SIZE] = { 0 };
	int B[SIZE] = { 0 };
	int sumarr[SIZE] = { 0 }; // 덧셈결과 저장 배열
	/* 곱셈연산용 변수 */
	int a_register[SIZE / 2] = { 0 };
	int q_register[SIZE / 2] = { 0 };
	int m_register[SIZE / 2] = { 0 };
	int result_mul[SIZE] = { 0 };

	cout << "두 수를 입력하세요: ";
	cin >> a >> b;
	
	int *x = convert_binary(a, A, SIZE);
	int *y = convert_binary(b, B, SIZE);


	cout << "[" << a << "]의 2진수 변환: ";
	if (a < 0) cout << "(2의보수로 변환됨)" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << x[i];
	cout << endl;

	cout << "[" << b << "]의 2진수 변환: ";
	if (b < 0) cout << "(2의보수로 변환됨)" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << y[i];
	cout << endl;

	int *result = sum(x, y, sumarr, SIZE);
	cout << "덧셈 후:\t  ";
	for (int i = 0; i < SIZE; i++)
		cout << result[i];
	cout << endl;

	int test = convert_decimal(result, SIZE); // 32비트의 십진수 변환
	cout << "덧셈 결과값 십진수 변환 결과: " << test << endl;

	cout << "\n*\t*\t*\t*\t*\t*\t*";

	if (abs(a) >= pow(2, SIZE / 2) || abs(b) >= pow(2, SIZE / 2))
		cout << "수의 범위를 초과하여 곱셈 연산이 불가능합니다." << endl;
	else { // p, q는 16비트로 변환한 이진수
		int *p = convert_binary(a, q_register, SIZE / 2);
		int *q = convert_binary(b, m_register, SIZE / 2);

		int *result2 = mul(p, q, a_register, result_mul, SIZE / 2); // Q, M, A, A와 Q 합쳐서 출력하는 결과 레지스터
		
		cout << "\n곱셈 후: ";
		for (int i = 0; i < SIZE; i++)
			cout << result2[i];
		cout << endl;

		int test2 = convert_decimal(result2, SIZE); // 32비트의 십진수 변환
		cout << "\n십진수 변환 결과: " << test2 << endl;
	}

	return;
}
