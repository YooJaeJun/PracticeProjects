#include <stdio.h>
#include <Windows.h>

int main()
{
	srand(GetTickCount64());
	int Random = (rand() % 10) + 1;		// random 1 ~ 10 ������ ������
	// rand() % n : 0 ~ (n - 1) ������ ������ ���� ���� �� �ִ� ����Դϴ�.

	// printf("Random : %i \n", Random);

	// ��ȸ�� 5�� �־����� 
	// ���� ��ȸ �ȿ� ��ǻ�Ͱ� ���� ������ ���ڸ� ���ߴ� ���α׷��� ������ּ���.
	// ���� ��ȸ�� ��� �����Ѵٸ� ������ �˷��ְ�, ���α׷��� �������ּ���.
	// ���� ��ȸ�� ��� �����ϱ� ���� ����ٸ� ���α׷��� ���ᰡ ���� �ʾƵ� ��� �����ϴ�.

	printf("��ǻ�Ͱ� 1~10 ������ ������ ������ �̾ҽ��ϴ�. \n\n");
	int chance = 5;
	int num;

	printf("���� �Է�: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "������ϴ�!" : "Ʋ�Ƚ��ϴ�!");
	printf("���� ��ȸ: %i \n\n", --chance);

	printf("���� �Է�: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "������ϴ�!" : "Ʋ�Ƚ��ϴ�!");
	printf("���� ��ȸ: %i \n\n", --chance);

	printf("���� �Է�: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "������ϴ�!" : "Ʋ�Ƚ��ϴ�!");
	printf("���� ��ȸ: %i \n\n", --chance);

	printf("���� �Է�: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "������ϴ�!" : "Ʋ�Ƚ��ϴ�!");
	printf("���� ��ȸ: %i \n\n", --chance);

	printf("���� �Է�: ");
	scanf_s("%i", &num);
	printf("%s \n", Random == num ? "������ϴ�!" : "Ʋ�Ƚ��ϴ�!");
	printf("���� ��ȸ: %i \n\n", --chance);

	printf("���� ��ȸ�� �����Ǿ����ϴ�. ���α׷� ����");


	int life = 5;
	
	int input;

	printf("1 ~ 10������ ������ ���� �����ּ��� ! \n");

	printf("���� ��ȸ : %i \n", life);
	printf("���ڸ� �Է����ּ���: ");
	scanf_s("%d", &input);
	printf("%s \n", (input == Random) ? "�����Դϴ� !" : "�����Դϴ�...");
	-life;
	// �ݺ�...

	// Sleep(500) : ���� ��ɱ��� 1�� ���� ����մϴ�.
	Sleep(500);
	// system("cls") : �ܼ� â�� ����ϴ�.
	system("cls");	

	printf("������ %i �����ϴ�. \n", Random);

	return 0;
}