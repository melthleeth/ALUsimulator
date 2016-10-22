#include <stdio.h>
#include <iostream>
using namespace std;

void main() {
	int a,b=0, count=31;
	int	bin[32] = {0, };
	int bin2[32] = {0, };

	int c[32] = {0, };
	int math[32] = {0, };

	cin >> a >> b;

	while(true)	{
		int mogc = a/2;		// ¸ò
		int nmg = a%2;		// ³ª¸ÓÁö
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


//	È®ÀÎ====================================
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

	cout << "=======================================" << endl;

	cout << "µ¡¼À" << endl;

	for(int i=31; i>=0; i--){
		math[i] = bin[i]+bin2[i]+c[i];
		if(math[i]==2){
			math[i]=0;
			++c[i-1];
		}
		if(math[i]==3){
			math[i]=1;
			++c[i-1];
		}
	}

	for(int i=0; i<32; i++){
		cout << math[i];
		if(i==31){
			cout<<endl;
		}
	}
	
	cout << "======================================"<<endl;


}