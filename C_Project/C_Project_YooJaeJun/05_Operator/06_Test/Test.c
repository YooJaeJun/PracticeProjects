#include <stdio.h>
#include <Windows.h>

int main()
{
	srand(GetTickCount64());
	int Random = (rand() % 10) + 1;		// random 1 ~ 10 사이의 랜덤값
	// rand() % n : 0 ~ (n - 1) 까지의 랜덤한 수를 뽑을 수 있는 기능입니다.

	// printf("Random : %i \n", Random);

	// 기회가 5번 주어지고 
	// 남은 기회 안에 컴퓨터가 뽑은 랜덤한 숫자를 맞추는 프로그램을 만들어주세요.
	// 남은 기회를 모두 소진한다면 정답을 알려주고, 프로그램을 종료해주세요.
	// 남은 기회를 모두 소진하기 전에 맞췄다면 프로그램이 종료가 되지 않아도 상관 없습니다.

	printf("컴퓨터가 1~10 사이의 랜덤한 정수를 뽑았습니다. \n\n");
	int chance = 5;
	int num;

	printf("숫자 입력: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "맞췄습니다!" : "틀렸습니다!");
	printf("남은 기회: %i \n\n", --chance);

	printf("숫자 입력: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "맞췄습니다!" : "틀렸습니다!");
	printf("남은 기회: %i \n\n", --chance);

	printf("숫자 입력: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "맞췄습니다!" : "틀렸습니다!");
	printf("남은 기회: %i \n\n", --chance);

	printf("숫자 입력: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "맞췄습니다!" : "틀렸습니다!");
	printf("남은 기회: %i \n\n", --chance);

	printf("숫자 입력: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "맞췄습니다!" : "틀렸습니다!");
	printf("남은 기회: %i \n\n", --chance);

	printf("남은 기회가 소진되었습니다. 프로그램 종료");


	int life = 5;
	
	int input;

	printf("1 ~ 10까지의 랜덤한 값을 맞춰주세요 ! \n");

	printf("남은 기회 : %i \n", life);
	printf("숫자를 입력해주세요: ");
	scanf_s("%d", &input);
	printf("%s \n", (input == Random) ? "정답입니다 !" : "오답입니다...");
	-life;
	// 반복...

	// Sleep(500) : 다음 명령까지 1초 정도 대기합니다.
	Sleep(500);
	// system("cls") : 콘솔 창을 지웁니다.
	system("cls");	

	printf("정답은 %i 였습니다. \n", Random);

	return 0;
}