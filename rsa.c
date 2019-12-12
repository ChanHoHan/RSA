//2015270209 한찬호 rsa
#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<math.h>
#include <string.h>
#define MAX 2000


unsigned long long ll = 9943237852845877651;

char arr[60] = { 0 };


unsigned long long MSB_64 = 1;
unsigned long long p = 0;
unsigned long long q = 0;
unsigned long long Euler_n = 0;
unsigned long long d = 0;
unsigned long long M = 0;
unsigned long long C;

unsigned long long binary[64] = { 0, };
unsigned long long Calculate_Mod[64] = { 0, };

unsigned long long e = 13;
unsigned long long pre_Extended_A[3] = { 0, };
long long Extended_A[3] = { 0, };
long long Extended_B[3] = { 0, };
long long Extended_A_cache[3] = { 0, };

int binary_index = 0;

char save_mul_value[MAX] = "";

int ccnt = 0;


unsigned long long final_mod() {
	unsigned long long x = 0;    // mod 계산
	unsigned long long save = 0;
	int i = 0;
	while (save_mul_value[i] != NULL) {
		i++;
	}
	
	for (int j = 0; j < i; j++) {  // mod 계산

		x *= 10;
		x += (save_mul_value[i] - '0');
		if (x > ll) {
			save = x % ll;
			x = save;
			//sprintf(ttmp, "%d", save);
			//strcat(new_mul, ttmp);
		}
	}

	return x;
}



void multiply(unsigned long long b) {
	char num[2][MAX + 1], *ptr;
	unsigned char mul[MAX + MAX + 2];
	int len[2], mul_len, i, j, k;
	sprintf(num[1], "%llu", b);

	
	if (ccnt == 0) {
		strcpy_s(save_mul_value, sizeof(save_mul_value), num[1]);
		ccnt++;
		return;
	}


	strcpy_s(num[0], sizeof(save_mul_value), save_mul_value);
	len[0] = strlen(num[0]);
	len[1] = strlen(num[1]);


	


	mul_len = len[0] + len[1]; /*  마지막 자릿값 */

	memset(mul, 0x00, mul_len + 2); /* mul 배열 초기화.. */
	for (i = 0; i < len[0]; i++)
		for (j = 0; j < len[1]; j++)
		{
			k = mul_len - i - j; /* 뒷자리부터 연산.올림값 처리를 위해 */
			mul[k] += (num[0][len[0] - i - 1] - '0') * (num[1][len[1] - j - 1] - '0'); /* 곱 */
			if (mul[k] > 9) { 
				mul[k - 1] += (mul[k] / 10); 
				mul[k] %= 10; } /* 올림값 처리 */
		}
	for (i = 0; i <= mul_len; i++) mul[i] += '0';  /* mul 배열을 문자화 */
	for (i = 0; mul[i] == '0'; ) i++; /* 앞자리가 0 이면 출력에서 제외하기 위해서 */



	char kk[MAX] = "";
	int cnt = 0;
	for (int j = i; j <= mul_len; j++) {
		kk[cnt] = mul[j];
		cnt++;
	}

	strcpy_s(save_mul_value, sizeof(save_mul_value),kk);

}



unsigned long long multiply_and_mod(unsigned long long a) {
	char num[2][MAX + 1], *ptr;
	unsigned char mul[MAX + MAX + 2];
	int len[2], mul_len, i, j, k;


	sprintf(num[0], "%llu", a);
	sprintf(num[1], "%llu", a);
	len[0] = strlen(num[0]);
	len[1] = strlen(num[1]);

	mul_len = len[0] + len[1]; 

	memset(mul, 0x00, mul_len + 2); /* mul 배열 초기화.. */
	for (i = 0; i < len[0]; i++)
		for (j = 0; j < len[1]; j++) 
		{
			k = mul_len - i - j; /* 뒷자리부터 연산 */
			mul[k] += (num[0][len[0] - i - 1] - '0') * (num[1][len[1] - j - 1] - '0'); /* 곱 */
			if (mul[k] > 9) { mul[k - 1] += (mul[k] / 10); mul[k] %= 10; } /* 올림값 처리 */
		}

	// mul은 문자열을 표현하는 변수. 총 결과
	// num[0]는 앞 num[1]은 뒤 숫자 

	//len[0]은 num[0]의 길이, len[1]은 num[2]의 길이

	for (i = 0; i <= mul_len; i++) mul[i] += '0';  /* mul 배열을 문자화 */
	for (i = 0; mul[i] == '0'; ) i++; /* 앞자리가 0 이면 출력에서 제외하기 위해서 */


	unsigned long long x = 0;    // mod 계산
	unsigned long long save = 0;

	unsigned char new_mul[MAX + MAX + 2] = { 0, };
	for (j = i; j <= mul_len; j++) {  // mod 계산

		x *= 10;
		x += (mul[j] - '0');
		if (x > ll) {
			x = x % ll;
			//sprintf(ttmp, "%d", save);
			//strcat(new_mul, ttmp);
		}
	}

	return x;
}




void MakeBinary() {
	int index = 0;
	for (int i = 0; i < 64; i++) {
		if (MSB_64&d) {
			break;
		}
		MSB_64 = MSB_64 >> 1;
		index++;
	}
	unsigned long long LSB = 1;
	index = 63 - index;
	for (int i = 0; i <= index ; i++) {
		if (LSB & d) {
			binary[i] = 1;
		}
		LSB = LSB << 1;
	}

	binary_index = index;
}





void Mod() {
	unsigned long long temp_c = 1;
	unsigned long long calc_2 = 1;
	Calculate_Mod[0] = C % ll;
	for (int i = 0; i < binary_index ; i++) {
		/*calc_2 = calc_2 << i;
		for (int j = 0; j < calc_2; j++) {
			temp_c *= C;
		}*/
		Calculate_Mod[i + 1] = multiply_and_mod(Calculate_Mod[i]);
	}
}

void Square_and_Multiply() {
	Mod();
	unsigned long long temp = 1;
	for (int i = 0; i <= binary_index; i++) {
		if (binary[i] == 1 ) {
			multiply(Calculate_Mod[i]);
		}
	}
	unsigned long long the_end;
	the_end = final_mod();
	M = the_end;
}

void Decrypt() {
	MSB_64 = MSB_64 << 63;
	C = 1220703125;
	MakeBinary();
	Square_and_Multiply();
}


void Find_d() {

	unsigned long long b = sqrt(ll);
	unsigned long long i = 0;
	for (i = b; i < ll; i++) {
		if (ll % i == 0) {
			p = ll / i;
			q = i;
			break;
		}
	}
	printf("p : %llu ", p);
	printf("q : %llu ", q);
}


void Extended_Euclidean_algorithm() {
	pre_Extended_A[0] = 1;
	pre_Extended_A[2] = Euler_n;
	Extended_B[0] = 0;
	Extended_B[1] = 1;
	Extended_B[2] = e;

	unsigned long long cacheA = 0;
	long long mul_max = 0; // 곱할거
	int cnt = 0;
	while (Extended_B[2] != 1) {
		if (cnt == 0) {
			mul_max = pre_Extended_A[2] / Extended_B[2];
		}
		else {
			mul_max = Extended_A[2] / Extended_B[2];
		}
		for (int i = 0; i < 3; i++) {
			if (cnt == 0) {
				cacheA = pre_Extended_A[i];
				Extended_A[i] = Extended_B[i];
				unsigned long long ks = (unsigned long long)mul_max * (unsigned long long)Extended_A[i];
				Extended_B[i] = cacheA - ks;
			}
			else {
				Extended_A_cache[i] = Extended_A[i];
				Extended_A[i] = Extended_B[i];
				Extended_B[i] = Extended_A_cache[i] - (mul_max * Extended_A[i]);
			}
		}
		
		cnt++;
	}
	d = (unsigned long long)(Extended_B[1]);
}

int main() {
	Find_d();
	Euler_n = (p - 1)*(q - 1);
	Extended_Euclidean_algorithm();
	Decrypt();
	printf("d : %lld \n", d);

	printf("plaintext : %lld", M);
	system("pause");
	return 0;
}