/*
만들어야 할 기능:
이진수 변환(O)
2의 보수 변환
덧셈/뺄셈: 병렬 가감산기
곱셈은 Booth alg로
*/

#include <iostream>
#include <math.h>
#define SIZE 32 // 레지스터 최대길이: 32비트
using namespace std;

int *convert_ieee(int *arr, int count1, int count2, bool minus);

int *convert_complement(int *arr, int size) { /* 2의 보수 변환 */

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


int *convert_binary(double num, int *arr, int size) {
   int k = size - 1; // 카운팅용 변수
   bool minus = false;
   bool ieee = false;
   double R = 0;
   int count1 = 0; // 전체 개수
   int count2 = 0; // 정수 개수

   if (num < 0) { // 음수판별 --> 추후 2의 보수로 바꿀지 결정하는데 사용됨
      num = num * (-1);
      minus = true;
   }

   if ((int)num != num) { // 실수판별 --> 추후 IEEE754 표준형으로 바꿀지 결정하는 데 사용됨
      ieee = true;
      R = num - (int)num;
   }

   for (int i = 0; i < size; i++) // 배열 모두 0으로 채움
      arr[i] = 0;

   if (ieee) { //실수일 때는 실수부 먼저 계산한다
      do {

         R = R * 2;

         if (R >= 1) {
            R = R - 1;
            arr[k] = 1;
         }

         count1++;
         k--;

         cout << "R값 : " << R << endl;

      } while (R != 0);

      if (count1) { //자리 바꾸기

         int swap = count1-1;
         int i = 1;
         int temp = 0;

         while (1) {
            cout << swap << endl;
            temp = arr[k+i];

            if (swap <= 0)
               break;

     //       cout << arr[k] << "arr[" << i + 1 << "]랑 arr[" << k + swap << "]" << arr[k + swap] << " 바꾸는 중ㅎㅎ" << endl;
       //     Sleep(60);

            arr[k + i] = arr[k + swap+i];
            arr[k + swap + i] = temp;
            swap=swap-2;
            i++;

         }
      }
   }

   while (1) {
      arr[k] = (int)num % 2;
      //cout << arr[k];
      num = (int)num / 2;
      count1++;
     count2++; // 정수부분
      if (num == 1) {
         arr[k - 1] = 1;
         break;
      }
      else k--;
   }

   if (ieee) { // 위에서 실수라는 게 확인되었다면 ieee 표준으로 변환됨
      convert_ieee(arr, count1, count2, minus);
     minus = false; // 실수는 보수로 바꿀 필요x
   }

   if (minus) { // 위에서 음수라는게 확인되었다면 2의 보수로 변환됨
      convert_complement(arr, size);
   }

   return arr;
}


int *convert_ieee(int *arr, int count1, int count2, bool minus) {

   int exp1[8] = { 0 };
   int ieee1[SIZE] = { 0 };
   int k = 8;
   int j = 31;   

   ieee1[0] = minus; // 부호비트

   for(j;j-count1<32;j++) {
   
      ieee1[k] = arr[j-count1];
      
      cout << k << "가수부 넣는 중" << endl;
   cout << ieee1[k] << endl;

   k++;

   }

   count2 = count2 + 127; // 바이어스 값 더해주기

   int *exp = convert_binary((double)count2, exp1, 8);

   k = 8;
   j = 7;

   while (1) { // 지수부 집어넣기

      ieee1[k] = exp[j];

     j--;
     k--;

      if (k == 0)
         break;
   }
	cout << endl;
   cout << "지수부 다 넣음" << endl;
 
   for (int i = 0; i < SIZE; i++)
      cout << ieee1[i];
   cout << endl;

   for(int i=0; i<SIZE; i++) {
	   arr[i] = ieee1[i];
   }

   for (int i = 0; i < SIZE; i++)
      cout << arr[i];
   cout << endl;

   return arr;

}

int *sum(int *arr1, int *arr2) { /* 덧셈연산 */
   int result[SIZE] = { 0 }; // 결과 저장용 배열

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

   /* for (int i = 0; i < SIZE; i++)
   cout << result[i]; */

   return result;
}

void multipler(int* arr1, int* arr2) { //여기서 값 출력하고 끝낼 것임...

	int result[SIZE] = { 0 };
	int arr11[24] = {0};
	int arr22[24] = {0}; // 연산 위해 기존의 가수부를 저장할 배열들
	int count1=0;
	int	count2=0;
	int k1=0;
	int k2=0;
	int m=0;
	int n=1;
	int num=0; //총 지수승 값
	bool minus = false; // 총 연산 결과의 부호

	if(arr1[0]!=arr2[0])
		minus = true;
	else
		minus = false;
	//이 연산의 부호 구하기

	for(int i=8; i>0; i--) {
		count1 += arr1[i]* n;
		n *= 2;
	}

	count1 = count1 -127;

	n=1;

	for(int i=8; i>0; i--) {
		count2 += arr2[i]* n;
		n *= 2;
	}

	count2 = count2 -127;
	// 지수승 10진수 변환
	///////////////////////////////////// 클리어

	for(int i=SIZE-1; i>9; i--) {
		k1=i;
		if(arr1[i] == 0)
			continue;
		else
			break;
	}

	k1 = k1-8;
//	cout << "arr1의 가수 자리: " <<k1<< endl;

	for(int i=SIZE-1; i>9; i--) {
		k2=i;
		if(arr2[i] == 0)
			continue;
		else
			break;
	}

	k2 = k2-8;
	//소수점 몇 자리인지 구하기

//	cout << "arr2의 가수 자리: " <<k2<< endl;

	for(int i=0; i<=k1; i++) { // 연산 위해 다른 배열에 집어넣기
		arr11[24-1-i] = arr1[8+k1-i];
		if(i == k1)
			arr11[24-1-i] = 1;
	}

	for(int i=0; i<=k2; i++) { // 연산 위해 다른 배열에 집어넣기
		arr22[24-1-i] = arr2[8+k2-i];
		if(i == k2)
			arr22[24-1-i] = 1;
	}

	cout << "arr11 : " ;
	for(int i=0; i<24; i++)
		cout << arr11[i]; // 결과 출력
	cout << endl;

	cout << "arr22 : " ;
	for(int i=0; i<24; i++)
		cout << arr22[i]; // 결과 출력
	cout << endl;

	for(int j=0; j<k1+1; j++)	 { //가수부 곱셈 수행
		for(int i=0; i<k2+1; i++) {
			result[SIZE-1-j-i] += arr11[24-1-i] * arr22[24-1-j];
			
			cout << result[SIZE-1-j-i] << " += " << arr11[24-1-i] << " * " << arr22[24-1-j] << endl;
			cout << "result는 " << SIZE-1-j-i <<"번째, arr11은 " << 24-1-i <<"번째, arr2는 " << 24-1-j << "번째" << endl;

			if(result[SIZE-1-j-i]>1) { // 2나 3 같이 이진수로 표현할 수 있는 수가 초과되었을 때 바꿔주기
				result[SIZE-2-j-i] += result[SIZE-1-j-i]/2;
				result[SIZE-1-j-i] = result[SIZE-1-j-i]%2;
			}
			else
				continue;
		}
	}

	cout << "곱셈 수행 결과 : " ;
	for(int i=0; i<SIZE; i++)
		cout << result[i]; // 결과 출력
	cout << endl;

	for(int i=0; i<SIZE; i++) { //구한 곱셈이 몇 자리인지 구하기
		m++;
		cout << m << endl;
		if(result[i]==0)
			continue;
		else
			break;
	}


	m = 32-m;
	cout << "m값 : " << m << endl;
	num = count1+count2;
//	cout << count1 << " + " << count2 << endl;

	if(k1+k2 != m) {
		num += m - k1 - k2;
	cout << "num값 : " << num << endl;
	}

	int *ieee =	convert_ieee(result,m,num,minus);

	cout << "최종 곱셈 수행 결과 : " ;
	for(int i=0; i<SIZE-1; i++)
		cout << ieee[i]; // 결과 출력
	cout << endl;

	return;
}

void main() {
   double a;
   double b;
   int A[SIZE];
   int B[SIZE];
   bool ieeea = false;

   cout << "두 수를 입력하세요: ";
   cin >> a >> b;

   int *x = convert_binary(a, A, SIZE);
   int *y = convert_binary(b, B, SIZE);

   if((int)a != a)
	   ieeea = true;

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

/*   int *result = sum(x, y);
   cout << "두 수의 덧셈: " << endl;
   for (int i = 0; i < SIZE; i++)
   cout << result[i];
   cout << endl;
*/
   if(ieeea)
	   multipler(x,y);

   return;
}