#include <stdio.h>
#include <locale.h>

int main()
{
	// �ƽ�Ű �ڵ�
	// ���ĺ�, ����, Ư����ȣ, ���鹮��, ����ڸ� 
	// ��ǻ�Ϳ��� ���� �����ͷ� �˷��ֱ� ���ؼ� ���ܳ� �ڵ��Դϴ�.
	char A = 'A';

	printf("%c \n", A);
	printf("%d \n", A);
	printf("%c \n", 'A');
	printf("%d \n", 'A');

	"ABC";
	// '��';
	// '��';
	// '��';
	// '��������'

	3.14;
	3.14f;

	setlocale(LC_ALL, "KOREAN");

	// ���̵� ĳ����
	wchar_t Korea = L'��';
	printf("wchar_t Size : %zi \n", sizeof(wchar_t));	// 32,768 ������ ���ڸ� ǥ���� �� ����
	char myChar = 'A';
	wprintf(L"%c \n", Korea);
	wprintf(L"%c \n", myChar);

	const char* str = "�����ٶ�";	// ��Ƽ����Ʈ ���� ���� ��� �ɼ� �� �ѱ� �� ���ڴ� 2byte��
	printf("%s \n", str);

	return 0;
}