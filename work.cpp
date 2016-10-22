#include <stdio.h>
#include <iostream>
using namespace std;

void main() {
	int a,b=0, count=31;
	int	bin[32] = {0, };
	int bin2[32] = {0, };

	cin >> a >> b;

	while(true)	{
		int mogc = a/2;		// 몫
		int nmg = a%2;		// 나머지
		bin[count] = nmg;
		count--;

		if(mogc==0){
			break;
		}
		a = mogc;			
	}
	count=31;
	while(true)	{
		int mogc = b/2;
		int nmg = b%2;
		bin2[count] = nmg;
		count--;

		if(mogc==0){
			break;
		}
		b = mogc;			
	}


//	확인====================================
	for(int i=0; i<32; i++){
		cout << bin[i];
		if(i==31){
			cout<<endl;
		}
	}
	for(int i=0; i<32; i++){
		cout << bin2[i];
		if(i==31){
			cout<<endl;
		}
	}
//==========================================



}