#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void find(int n);
bool judge(int n);

int main4() {

	int input;
	while (scanf("%d", &input)) {
		printf("%d = ", input);
		find(input);
	}
	return 0;
}

void find(int n) {
	if (n == 1) {
		printf("%d", n);
		return;
	}
	else if (n == 2) {
		printf("%d", n);
		return;
	}
	if (judge(n)) {
		printf(" %d\n", n);
		return;
	}
	int i = 2;
	for (i = 2; i <= n; i++) {
		if (judge(i) && n % i == 0) {
			printf("%d * ", i);
			break;
		}
	}
	int nxtN = n / i;
	if (judge(nxtN)) {
		printf("%d \n", nxtN);
		return;

	}
	else {
		find(nxtN);
	}
}

bool judge(int n) {
	int temp = sqrt(n);
	if (n == 1 || n == 2) {
		return true;
	}
	for (int i = 2; i <= temp; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

