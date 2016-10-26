/*
������ �� ���:
������ ��ȯ(O)
2�� ���� ��ȯ
����/����: ���� �������
������ Booth alg��
*/

#include <iostream>
#include <math.h>
#define SIZE 32 // �������� �ִ����: 32��Ʈ
using namespace std;

int *convert_ieee(int *arr, int count1, int count2, bool minus);

int *convert_complement(int *arr, int size) { /* 2�� ���� ��ȯ */

                           /* STEP 1: ��Ʈ����(1�� ����) */
   for (int i = 0; i < size; i++) {
      if (arr[i] == 0)
         arr[i] = 1;
      else if (arr[i] == 1)
         arr[i] = 0;
      //cout << arr[i];
   }

   /* STEP 2: +1�ؼ� 2�� ������ ���� */
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
   int k = size - 1; // ī���ÿ� ����
   bool minus = false;
   bool ieee = false;
   double R = 0;
   int count1 = 0; // ��ü ����
   int count2 = 0; // ���� ����

   if (num < 0) { // �����Ǻ� --> ���� 2�� ������ �ٲ��� �����ϴµ� ����
      num = num * (-1);
      minus = true;
   }

   if ((int)num != num) { // �Ǽ��Ǻ� --> ���� IEEE754 ǥ�������� �ٲ��� �����ϴ� �� ����
      ieee = true;
      R = num - (int)num;
   }

   for (int i = 0; i < size; i++) // �迭 ��� 0���� ä��
      arr[i] = 0;

   if (ieee) { //�Ǽ��� ���� �Ǽ��� ���� ����Ѵ�
      do {

         R = R * 2;

         if (R >= 1) {
            R = R - 1;
            arr[k] = 1;
         }

         count1++;
         k--;

         cout << "R�� : " << R << endl;

      } while (R != 0);

      if (count1) { //�ڸ� �ٲٱ�

         int swap = count1-1;
         int i = 1;
         int temp = 0;

         while (1) {
            cout << swap << endl;
            temp = arr[k+i];

            if (swap <= 0)
               break;

     //       cout << arr[k] << "arr[" << i + 1 << "]�� arr[" << k + swap << "]" << arr[k + swap] << " �ٲٴ� �ߤ���" << endl;
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
     count2++; // �����κ�
      if (num == 1) {
         arr[k - 1] = 1;
         break;
      }
      else k--;
   }

   if (ieee) { // ������ �Ǽ���� �� Ȯ�εǾ��ٸ� ieee ǥ������ ��ȯ��
      convert_ieee(arr, count1, count2, minus);
     minus = false; // �Ǽ��� ������ �ٲ� �ʿ�x
   }

   if (minus) { // ������ ������°� Ȯ�εǾ��ٸ� 2�� ������ ��ȯ��
      convert_complement(arr, size);
   }

   return arr;
}


int *convert_ieee(int *arr, int count1, int count2, bool minus) {

   int exp1[8] = { 0 };
   int ieee1[SIZE] = { 0 };
   int k = 8;
   int j = 31;   

   ieee1[0] = minus; // ��ȣ��Ʈ

   for(j;j-count1<32;j++) {
   
      ieee1[k] = arr[j-count1];
      
      cout << k << "������ �ִ� ��" << endl;
   cout << ieee1[k] << endl;

   k++;

   }

   count2 = count2 + 127; // ���̾ �� �����ֱ�

   int *exp = convert_binary((double)count2, exp1, 8);

   k = 8;
   j = 7;

   while (1) { // ������ ����ֱ�

      ieee1[k] = exp[j];

     j--;
     k--;

      if (k == 0)
         break;
   }
	cout << endl;
   cout << "������ �� ����" << endl;
 
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

int *sum(int *arr1, int *arr2) { /* �������� */
   int result[SIZE] = { 0 }; // ��� ����� �迭

   for (int i = SIZE - 1; i >= 0; i--) {
      int sum = arr1[i] + arr2[i]; // �ڸ��� �� ����
      int temp = sum + result[i]; // �ڸ��ø� �߻��� �� �����Ƿ� ���� �ϳ� �� ����


      if (temp == 1 || temp == 0)
         result[i] = temp;
      if (temp == 2) {
         result[i] = 0;
         if (i != 0) result[i - 1] = 1; // array index �� -1 �� �Ǵ� ���� ����
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

void multipler(int* arr1, int* arr2) { //���⼭ �� ����ϰ� ���� ����...

	int result[SIZE] = { 0 };
	int arr11[24] = {0};
	int arr22[24] = {0}; // ���� ���� ������ �����θ� ������ �迭��
	int count1=0;
	int	count2=0;
	int k1=0;
	int k2=0;
	int m=0;
	int n=1;
	int num=0; //�� ������ ��
	bool minus = false; // �� ���� ����� ��ȣ

	if(arr1[0]!=arr2[0])
		minus = true;
	else
		minus = false;
	//�� ������ ��ȣ ���ϱ�

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
	// ������ 10���� ��ȯ
	///////////////////////////////////// Ŭ����

	for(int i=SIZE-1; i>9; i--) {
		k1=i;
		if(arr1[i] == 0)
			continue;
		else
			break;
	}

	k1 = k1-8;
//	cout << "arr1�� ���� �ڸ�: " <<k1<< endl;

	for(int i=SIZE-1; i>9; i--) {
		k2=i;
		if(arr2[i] == 0)
			continue;
		else
			break;
	}

	k2 = k2-8;
	//�Ҽ��� �� �ڸ����� ���ϱ�

//	cout << "arr2�� ���� �ڸ�: " <<k2<< endl;

	for(int i=0; i<=k1; i++) { // ���� ���� �ٸ� �迭�� ����ֱ�
		arr11[24-1-i] = arr1[8+k1-i];
		if(i == k1)
			arr11[24-1-i] = 1;
	}

	for(int i=0; i<=k2; i++) { // ���� ���� �ٸ� �迭�� ����ֱ�
		arr22[24-1-i] = arr2[8+k2-i];
		if(i == k2)
			arr22[24-1-i] = 1;
	}

	cout << "arr11 : " ;
	for(int i=0; i<24; i++)
		cout << arr11[i]; // ��� ���
	cout << endl;

	cout << "arr22 : " ;
	for(int i=0; i<24; i++)
		cout << arr22[i]; // ��� ���
	cout << endl;

	for(int j=0; j<k1+1; j++)	 { //������ ���� ����
		for(int i=0; i<k2+1; i++) {
			result[SIZE-1-j-i] += arr11[24-1-i] * arr22[24-1-j];
			
			cout << result[SIZE-1-j-i] << " += " << arr11[24-1-i] << " * " << arr22[24-1-j] << endl;
			cout << "result�� " << SIZE-1-j-i <<"��°, arr11�� " << 24-1-i <<"��°, arr2�� " << 24-1-j << "��°" << endl;

			if(result[SIZE-1-j-i]>1) { // 2�� 3 ���� �������� ǥ���� �� �ִ� ���� �ʰ��Ǿ��� �� �ٲ��ֱ�
				result[SIZE-2-j-i] += result[SIZE-1-j-i]/2;
				result[SIZE-1-j-i] = result[SIZE-1-j-i]%2;
			}
			else
				continue;
		}
	}

	cout << "���� ���� ��� : " ;
	for(int i=0; i<SIZE; i++)
		cout << result[i]; // ��� ���
	cout << endl;

	for(int i=0; i<SIZE; i++) { //���� ������ �� �ڸ����� ���ϱ�
		m++;
		cout << m << endl;
		if(result[i]==0)
			continue;
		else
			break;
	}


	m = 32-m;
	cout << "m�� : " << m << endl;
	num = count1+count2;
//	cout << count1 << " + " << count2 << endl;

	if(k1+k2 != m) {
		num += m - k1 - k2;
	cout << "num�� : " << num << endl;
	}

	int *ieee =	convert_ieee(result,m,num,minus);

	cout << "���� ���� ���� ��� : " ;
	for(int i=0; i<SIZE-1; i++)
		cout << ieee[i]; // ��� ���
	cout << endl;

	return;
}

void main() {
   double a;
   double b;
   int A[SIZE];
   int B[SIZE];
   bool ieeea = false;

   cout << "�� ���� �Է��ϼ���: ";
   cin >> a >> b;

   int *x = convert_binary(a, A, SIZE);
   int *y = convert_binary(b, B, SIZE);

   if((int)a != a)
	   ieeea = true;

   cout << "[" << a << "]�� 2���� ��ȯ" << endl;
   if (a < 0) cout << "(2�Ǻ����� ��ȯ��)" << endl;
   for (int i = 0; i < SIZE; i++)
      cout << x[i];
   cout << endl;

   cout << "[" << b << "]�� 2���� ��ȯ" << endl;
   if (b < 0) cout << "(2�Ǻ����� ��ȯ��)" << endl;
   for (int i = 0; i < SIZE; i++)
   cout << y[i];
   cout << endl;

/*   int *result = sum(x, y);
   cout << "�� ���� ����: " << endl;
   for (int i = 0; i < SIZE; i++)
   cout << result[i];
   cout << endl;
*/
   if(ieeea)
	   multipler(x,y);

   return;
}