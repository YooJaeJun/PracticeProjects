#include <stdio.h>

// switch case ��
// case �� ���� ������ �ڵ带 �з��մϴ�.
// case �� �ݵ�� ������� �մϴ�.

// switch(A)
// {
// case A : ���̽��� A �� �� ������ ����
//	break;
// case B :	���̽��� B �� �� ������ ����
//	break;
// case C : case D :	���̽��� C �ų� D �� �� ������ ����
// default : ���̽��� A �� B �� ��� �ƴ� �� ������ ����
//	break;
// }

int main()
{
	int input;
	printf("�Է� : ");
	scanf_s("%i", &input);
	
	switch (input) {
	case 1:
		printf("�Է��� ���� 1�Դϴ�. \n");
		break;
	case 2:
		printf("�Է��� ���� 2�Դϴ�. \n");
		break;
	case 3:
		printf("�Է��� ���� 3�Դϴ�. \n");
		break;
	case 4:
		printf("�Է��� ���� 4�Դϴ�. \n");
	case 5:
		printf("�Է��� ���� 5�Դϴ�. \n");
		break;
	default :
		printf("�Է��� ���� 1, 2, 3, 4, 5 �� �ƴմϴ�. \n");
		break;
	}

	
	if (input < 0) printf("�����Դϴ�. \n");
	else 
	{
		switch (input % 2)
		{
		case 0:
			if (input == 0) printf("0 �Դϴ�.");
			else printf("¦���Դϴ�. \n");
			break;
		case 1:	printf("Ȧ���Դϴ�. \n");
			break;
		}
	}

	// ���� ����� 2�� ���϶�� if ���� �ӵ��� �����ϴ�.
	// 3�� �̻��̶�� switch~case ���� �ӵ��� �� �����ϴ�.
	// ������ ������ �� ����̶�� if ���� 
	// ������ ���������� ���� ����� ���ϰ� �ʹٸ� switch~case ���� ����ϴ� ���� �����ϴ�.

	// ���1 hp < 0 : if
	// ���2 WASD �̵� : switch~case
}