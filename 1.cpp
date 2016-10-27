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
void Signbit(int num);
void Carrybit(int num);
void Zerobit(int *num);
void Overbit(int carry1, int carry2);

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

int *sum(int *arr1, int *arr2, bool status) { /* �������� */
   int result[SIZE] = { 0 }; // ��� ����� �迭
   int carry1 = 0;
   int carry2 = 0;

   for (int i = SIZE - 1; i >= 0; i--) {
      int sum = arr1[i] + arr2[i]; // �ڸ��� �� ����
      int temp = sum + result[i]; // �ڸ��ø� �߻��� �� �����Ƿ� ���� �ϳ� �� ����

	  if(i==2)
		  carry1 = temp;
	  if(i==1)
		  carry2 = temp;

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

   //����� ���
   if(status) { //������ ��
   cout << "���� ��� : ";
    for (int i = 0; i < SIZE; i++)
	  cout << result[i];
	cout << endl;

	//��Ʈ�� ���
	Carrybit(carry2);
    Signbit(result[0]);
	Zerobit(result);
	Overbit(carry1, carry1); //carry1�� ����ĳ��, carry2�� �ܺ�ĳ��
   }
//	cout << carry1 << endl;
//	cout << carry2 << endl;

	return result;
}

int convert_decimal(int *arr, int size) { /* ������ ��ȯ - ����� �� ���� �迭 */
	int result = 0; // ����� ����
	bool negative = false; // ��� ���� �Ǵ� ����

	/* STEP 1: ������ ��ȯ�� ���� ����� �ٲ��� */
	if (arr[0] == 1) { // ���� ������ �ٲ���
		negative = true;
		arr = convert_complement(arr, size);
	}

	/* STEP 2: ������ ��ȯ */
	int k = 0; // ���� ī���ÿ� ����
	for (int i = size - 1; i >= 0; i--) {
		if (arr[i] == 1)
			result = result + pow((double)2, k);
		k++;
	}

	//cout << "result = " << result << endl;

	if (negative) result = result * (-1); // ��ȣ��Ʈ�� 1(����)���ٸ� ������ ������

	return result;
}

void copy(int *original, int *object, int size) {
	for (int i = 0; i < size; i++)
		original[i] = object[i];
}

void print(int *A, int *Q, int prev) { // �Ź� ���� ���ŷο�Ƿ� ����ϴ� �Լ� ���� ����
	//cout << "���� ���: ";
	for (int i = 0; i < SIZE / 2; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < SIZE / 2; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

void sprint(int *A, int *Q, int prev) { // A �� M ���� ��� ���
	char sign;
	if (prev == 0) sign = '-';
	else if (prev == 1) sign = '+';
	cout << "A" << sign << "M ���� ���: ";
	for (int i = 0; i < SIZE / 2; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < SIZE / 2; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

void ASR(int *A, int *Q, int &prev, int size) { /* Arithmatic Shift-Right - ����� �迭, Q_-1 ��, �迭 ũ�� */
	/*�Լ��� ���������ϱ� �� ������ �ȵ�. ���� �����ؼ� ������ ���ߵ�*/
	
	cout << "��prev��: " << prev << endl;
	prev = Q[size - 1]; //  Q_-1�� �迭 ���� ����
	cout << "��prev��: " << prev << endl;
	
	cout << "Q ����� Ȯ��: ";
	for (int i = 0; i < size; i++)
		cout << Q[i];
	cout << endl;

	for (int i = size - 1; i > 0; i--)
		Q[i] = Q[i - 1];
	Q[0] = A[size - 1];

	cout << "Q ����� Ȯ��: ";
	for (int i = 0; i < size; i++)
		cout << Q[i];
	cout << endl;

	cout << "A ����� Ȯ��: ";
	for (int i = 0; i < size; i++)
		cout << A[i];
	cout << endl;

	for (int i = size - 1; i > 0; i--)
		A[i] = A[i - 1];
	//A[0] = A[1];

	cout << "A ����� Ȯ��: ";
	for (int i = 0; i < size; i++)
		cout << A[i];
	cout << endl;

	cout << "ASR ���� ���: ";
	for (int i = 0; i < size; i++) cout << A[i];
	cout << " ";
	for (int i = 0; i < size; i++) cout << Q[i];
	cout << " ";
	cout << prev << endl;
}

int *mul(int *Q, int *M, int *A, int *result, int size) { /* ���� by BOOTH Alg. - ����� ������ �迭 2��, A��������, Q�������� */
	int prev = 0; // Q_-1 �� ������ ����
	int init_M = M[0]; // M�� ó�� ��ȣ��Ʈ
	
	/* STEP 1: A�������� �� ����, M�������� ������ �̸� ���س��� */
	for (int i = 0; i < size; i++)
		A[i] = Q[0]; 
	
	int *M_cpl = convert_complement(M, size); // M�� 2�� ����
	int init_Mcpl = M_cpl[0]; // M'�� ó�� ��ȣ��Ʈ

	cout << "\n\n[����]M�� 2�� ����: ";
	for (int i = 0; i < size; i++)
		cout << M_cpl[i];

	cout << endl;

	cout << "\t\t A \t\t    Q \t    Q_-1" << endl;
	cout << "�ʱ����: ";
	print(A, Q, prev);
	
	/* STEP 2: Q�������� ��Ʈ ũ��(SIZE/2 = 16)��ŭ cycle �ݺ� */

	int A_result[SIZE / 2] = { 0 }; // A�������� ���� ��� ������ �ӽ� ����
	int *R = { 0 };

	for (int i = 0; i < size; i++) {

		//cout << "\n\nA�������Ͱ�: ";
		//for (int k = 0; k < size; k++)
		//	cout << A[k];

		//cout << "\n\nM�������Ͱ�: ";
		//for (int k = 0; k < size; k++)
		//	cout << M[k];

		cout << "\ncycle " << i+1 << endl;
		if (Q[size - 1] == 0 && prev == 0) { // 00�� ��� - just ASR(Arithmatic Shift - Right)
			cout << "<00�� ���>\n";
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 1 && prev == 1) { // 11�� ��� - just ASR
			cout << "<11�� ���>\n";
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 0 && prev == 1) { // 01�� ��� - A + M & ASR
			cout << "<01�� ���>\n";
			if (M[0] != init_M) M = convert_complement(M, size);
			R = sum(A, M, A_result, size);
			copy(A, R, size); // A�� A_result�� ���� ����
			sprint(A, Q, prev);
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
		else if (Q[size - 1] == 1 && prev == 0) { // 10�� ��� - A + M'(M�� ����) & ASR
			cout << "<10�� ���>\n";
			if (M_cpl[0] != init_Mcpl) M_cpl = convert_complement(M_cpl, size);
			R = sum(A, M_cpl, A_result, size);
			copy(A, R, size); // A�� A_result�� ���� ����
			sprint(A, Q, prev);
			ASR(A, Q, prev, size);
			//print(A, Q, prev);
		}
	}

	/* STEP 3: A�� Q�������� ���ļ� ����������Ϳ� ���� */
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

	////��� Ȯ�ο�
	//cout << endl << "��� ��������: ";
	//for (int i = 0; i < SIZE; i++)
	//	cout << result[i];

	return result;
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

void ieee_multipler(int* arr1, int* arr2) { //���⼭ �� ����ϰ� ���� ����...

	int result[SIZE] = { 0 };
	int arr11[24] = {0};
	int arr22[24] = {0}; // ���� ���� ������ �����θ� ������ �迭��
	int count1=0;
	int	count2=0; //������
	int k1=0;
	int k2=0; // ������ �ڸ���
	int m=0; //�� ������ �ڸ���
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

void ieee_divider(int* arr1, int* arr2) {
	
	int result[SIZE] = { 0 };
	int num = 0; // ������ ��



//	int *ieee =	convert_ieee(result,m,num,minus);

	cout << "���� ������ ���� ��� : " ;
//	for(int i=0; i<SIZE-1; i++)
//		cout << ieee[i]; // ��� ���
//	cout << endl;

	return;
}

void main() {
   double a;
   double b;
   int A[SIZE];
   int B[SIZE];
	int sumarr[SIZE] = { 0 }; // ������� ���� �迭
	/* ��������� ���� */
	int a_register[SIZE / 2] = { 0 };
	int q_register[SIZE / 2] = { 0 };
	int m_register[SIZE / 2] = { 0 };
	int result_mul[SIZE] = { 0 };
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

   if(!ieeea) {
	int *result = sum(x, y, true);
	   cout << "�� ���� ����: " << endl;
	for (int i = 0; i < SIZE; i++)
	   cout << result[i];
	  cout << endl; 
   

	int test = convert_decimal(result, SIZE); // 32��Ʈ�� ������ ��ȯ
	cout << "���� ����� ������ ��ȯ ���: " << test << endl;

	cout << "\n*\t*\t*\t*\t*\t*\t*";

	if (abs(a) >= pow((double)2, SIZE / 2) || abs(b) >= pow((double)2, SIZE / 2))
		cout << "���� ������ �ʰ��Ͽ� ���� ������ �Ұ����մϴ�." << endl;
	else { // p, q�� 16��Ʈ�� ��ȯ�� ������
		int *p = convert_binary(a, q_register, SIZE / 2);
		int *q = convert_binary(b, m_register, SIZE / 2);

		int *result2 = mul(p, q, a_register, result_mul, SIZE / 2); // Q, M, A, A�� Q ���ļ� ����ϴ� ��� ��������
		
		cout << "\n���� ��: ";
		for (int i = 0; i < SIZE; i++)
			cout << result2[i];
		cout << endl;

		int test2 = convert_decimal(result2, SIZE); // 32��Ʈ�� ������ ��ȯ
		cout << "\n������ ��ȯ ���: " << test2 << endl;
	}
   }

	if(ieeea)
	   ieee_multipler(x,y);
   if(ieeea)
	   ieee_divider(x,y);

   return;
}

void Signbit(int num) { // ����� ���� ����

	if(num<0)
		cout << "S bit : 1" << endl;
	else
		cout << "S bit : 0" << endl;

	return;

}


void Carrybit(int num) { //�� ���� �� ���ڸ� �� �ϳ��� �޴´�.

	if(num > 1)
		cout << "C bit : 1" << endl;
	else
		cout << "C bit : 0" << endl;

	return;

}


void Zerobit(int* num) { // ��� �Ϸ�� �� �ޱ�

	for(int i=0; i<SIZE-1; i++) {
		if(num[i] == 0)
			continue;
		else {
			cout << "Z bit : 0" << endl;
			return;
		}
	}

	cout << "Z bit : 1" << endl;

	return;
}


void Overbit(int carry1, int carry2) { // ������ �� ��°�Ǹ�� C��Ʈ �ޱ�

	if(carry1+carry2>3) // ĳ������ �ִٸ� 2 �̻��� ����... �ϳ����� �������Ƿ� 3���� Ŭ ��쿣 ����+�ܺ� �� �Ͼ ���� ģ��
		cout << "V bit : 1" << endl;
	else
		cout << "V bit : 0" << endl;

	return;

}