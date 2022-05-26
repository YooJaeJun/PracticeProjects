// 제한 시간 : 50분
// 오픈북 형태이며 구글링을 하여도 무관합니다.
// ruri0324@naver.com

/*
  1. 서식 문자중 개행을 시켜주는 문자는 ? 
  1 ) '\a'
  2 ) '\"'
  3 ) '\n'
  4 ) '\t'
  5 ) '\''
    답 : 3

  2. 다음 중 4byte 의 크기를 가지고 있는 자료형은 ?
  1 ) char
  2 ) long long
  3 ) float     // float, long, int
  4 ) double
  5 ) short
    답 : 3

  3. 다음 중 메모리의 최소단위를 나타내는 것은 ?
  1 ) Byte
  2 ) Giga Byte
  3 ) Kilo byte
  4 ) Mega Byte
  5 ) Bit   // 0, 1을 저장할 수 있는 메모리의 최소 단위
    답 : 5

  4. C 언어 표준 라이브러리 파일은 ?
  1 ) stdio.h   // 입출력
  2 ) string.h
  3 ) stdlib.h  // 표준
  4 ) windows.h
  5 ) stdafx.h
    답 : 1 (3)

  5. 2Byte 의 메모리에 23이 저장되는 bit 중 옳은 것은 ?
  // 16bit 16자리
  // 10111. 나머지 0
  1 ) 0101 1101
  2 ) 0001 0111
  3 ) 0000 0000 0110 1100
  4 ) 0000 0000 0101 1101
  5 ) 0000 0000 0001 0111
    답 : 5 

  6. 다음 중 상수 형태가 아닌 것은 ?
  1 ) 'a'       // const char
  2 ) 3.14      // const double
  3 ) const int
  4 ) 3.14f     // const float
  5 ) float
    답 : 5

  7. A = 10 , B = 20 일 때 다음 보기의 결과값은 ?
     
        보기 )  !(((A + 10) == 10) || (B != 20)) && A
                    10 + 10 == 10       false       10
                        false                false
                    true
                                true
  1 ) 10
  2 ) 5
  3 ) 1
  4 ) 0 
  5 ) -1
    답 : 3

  8. 다음중 비교 연산자에 속하지 않는 것은 ?
  1 ) >
  2 ) ==
  3 ) !=
  4 ) !     // 관계 연산자
  5 ) <=
    답 : 4

  9. if 문의 구성 요소가 아닌 것은 ?
  1 ) 조건식
  2 ) if
  3 ) case
  4 ) else
  5 ) else if
    답 : 3

  10. 반복문을 빠져 나오지 못하여 다음 명령을 수행하지 못하는 것을 무엇이라 하는 가 ?
  1 ) 컴파일
  2 ) 무한루프
  3 ) 빌드
  4 ) 런타임
  5 ) 디버그
    답 : 2

  11. int count = 10 일 때 다음 보기의 반복문을 5번 반복하고 싶다
       가장 옳은 것은 ?
                  
                  보기 ) while (count != 0) { ? }
  1 ) ++count;
  2 ) count--;
  3 ) count - 2;
  4 ) count -= 2;
  5 ) ----count;
    답 : 4

  12. for 문의 구성 요소가 아닌 것은 ?
  1 ) 조건식
  2 ) 반복할 코드
  3 ) 초기식
  4 ) 증감식
  5 ) do
    답 : 5

  13. 다음 점프문중 반복중인 명령을 중단하고 조건식으로 다시 되돌아가는 명령어는 무엇입니까 ?
  1 ) continue;
  2 ) break;
  3 ) return;
  4 ) goto;
  5 ) do;
    답 : 1

  14. A 라는 구조체를 선언한 후 A 의 맴버로 int 자료형 2개와 char 하나를 선언하였다.
       sizeof(A) 의 결과값은 ?
       // 보통 4바이트씩 끊는다고 함
  1 ) 16
  2 ) 12
  3 ) 7
  4 ) 5
  5 ) 10
    답 : 2

  15. 자료형에 대한 별칭을 지정해주는 키워드는 무엇입니까 ?
  1 ) typedef
  2 ) const
  3 ) struct
  4 ) if
  5 ) unsigned
    답 : 1

  16. 배열의 요소에 접근하기위해서 [] 연산자를 사용한다.
       배열의 시작 인덱스와 끝 인덱스가 알맞게 짝지어진 것은 ?
       시작 인덱스            끝 인덱스
  1 )  배열의 길이 - 1        배열의 길이
  2 )  배열의 길이 - 1        0
  3 )  0                     배열의 길이 - 1        
  4 )  1                     배열의 길이
  5 )  1                     배열의 길이 - 1
    답 : 3

  17. 배열의 초기화 방법중 에러가 나타날 수 있는 것은 ?
  1 ) int Num[3];
      Num[0] = 1;
      Num[1] = 2;
      Num[2] = 3;
  2 ) int Num[3] = { 1, 2, 3 };
  3 ) int Num[3];
      Num = { 1, 2, 3 };    // 중괄호 초기화는 선언과 동시에.
  4 ) int Num[3] = { 1 };
  5 ) for (int i = 0; i < 3; ++i) Num[i] = i + 1;
    답 : 3

  18. 숫자나 영어 특수기호를 인코딩하기 위해여 7bit 로 이루어진 코드를 무엇이라 하는가 ?
  1 ) 소스코드
  2 ) 아스키코드
  3 ) 유니코드
  4 ) 그레이코드
  5 ) 바이트코드
    답 : 2

  19. 다음중 널 문자로 사용할 수 없는 것은 ?
  1 ) 0
  2 ) '\0'
  3 ) '0'
  4 ) NULL
  5 ) ('A' - 65)
    답 : 3

  20. int[4][3][2] 배열의 크기는 몇 Byte 입니까 ? 
  1 ) 12
  2 ) 36
  3 ) 96 
  4 ) 128
  5 ) 256
    답 : 3

  21 . 다음중 함수의 정의를 작성할 때 필수적으로 작성하지 않아도 되는 것은?
  1 ) 매개변수 목록
  2 ) 함수의 이름
  3 ) ( )
  4 ) 반환형
  5 ) { }
    답 : 1

  22. 다음중 매개변수를 통해 넘긴 공간의 값을 수정할 수 있는 것은?
  1 ) void Change(int num);
  2 ) void Change(const int num);
  3 ) void Change(const int* num);  // 주소값 변경 가능, 간접참조로 값 변경 불가능
  4 ) void Change(int* const num);  // 주소값 변경 불가능, 간접참조로 값 변경 가능
  5 ) void Change(const int * const num);
    답 : 4

  23. 64bit 체제의 프로그램에서 포인터의 크기는 ?
  1 ) 2Byte
  2 ) 4Btye // 32bit
  3 ) 6Byte
  4 ) 8Byte
  5 ) 16Byte
    답 : 4

  24. 보기와 같이 코드가 작성되어 있을 때 값이 다른 것은 ?
    보기 )
            int Num = 10;
            int * p = &Num;
            int * p2 = p;
    // &Num
   1 ) p;
   2 ) p2;
   3 ) &Num;
   4 ) &*p2;    // & 주소 연산자, * 간접 참조 연산자 붙어있으면 둘 다 떼면 됨
   5 ) *&*p;
     답 : 5

   25. 배열 int Array[5] 의 시작 주소가 80 일 때
       Array + 4 의 주소인 것은 ?
   1 ) 80
   2 ) 84
   3 ) 88
   4 ) 92
   5 ) 96
  답 : 5

   26. 배열 float Array[5] 의 시작 주소가 100 일때
       값이 다른 것은 ?
   1 ) &(Array[3])
   2 )   Array + 3
   3 ) 112
   4 ) &*(Array + 3)
   5 ) &(*Array + 3)
     답 : 5

   27. 다음 보기와 같이 코드가 작성이 되어있을 때 값이 다른 것은 ?
        보기 )
                int Num   = 10;
                int * p   = &Num;
                int ** pp = &p;
    1 ) &Num
    2 ) p
    3 ) &p
    4 ) &(**pp)
    5 ) *pp     // p == &Num
      답 : 3

    28. 다음중 컴파일러가 수행하는 일이 아닌 것은 ?
    1 ) 소스코드를 기계어로 변환
    2 ) 컴파일링 에러 확인
    3 ) 일으킨 문제의 소스코드 라인 지시
    4 ) 파일 참조 오류 반환
    5 ) 실행 도중 에러에 대한 반환     // 런타임. 컴파일러는 컴파일 타임에서 수행
      답 : 5

    29. 지역변수와 전역변수의 설명중 옳지 않은 것은 ?
    1 ) 지역변수는 특정 지역에서만 사용이 가능하다.
    2 ) 전역변수는 지역과 관계없이 어느곳에서나 가능하다.
    3 ) 전역변수는 프로그램의 시작부터 끝까지 남아있는 데이터다.
    4 ) 같은 이름의 지역변수와 전역변수가 있을 때 먼저 접근하는 것은
        무조건 지역변수가 먼저이다.
        int A;
        {
        {
        int A;
        }
        A;
        }
    5 ) 지역변수와 같은 경우 자기가 선언된 중괄호안에 있는 지역이라면
        어느곳이든 사용이 가능하다.
  답 : 4

    30. 정적 지역변수와 정적 전역변수의 설명중 옳지 않은 것은 ?
  
    1 ) 정적 지역변수와 같은 경우 딱 한번만의 선언이 이루어진다.
    2 ) 정적 전역변수와 같은 경우 파일에 상관없이 어느곳이든 이용이 가능하다.     // 정적 전역변수는 그 파일 안에서만 사용 가능
    3 ) 정적 지역변수와 전역 변수는 한번 할당이 이루어 진다면 프로그램이
        종료될 때까지 남아있는 데이터다.
    4 ) 정적 지역변수와 전역 변수는 static 키워드를 이용하여 선언이 가능하다.
    5 ) 정적 지역변수와 전역 변수는 매개변수의 타입으로 사용할 수 가 없다. -> 함수의 인자값으로 사용할 수 없다.
      답 : 5 ( 2 )

    31. 메모리 영역중 해당 되지 않는 것은 ?
    1 ) Code Area
    2 ) Stack Area
    3 ) Heap Area
    4 ) Read Area
    5 ) Data Area
      답 : 4

    32. Data Area 에 저장되지 않는 것은 ?        // 데이터 공간: 프로그램 종료할 때까지 남아있는 공간
    1 ) 정적 전역 변수
    2 ) 정적 지역 변수
    3 ) 전역 변수
    4 ) 지역 변수
    5 ) 해당 없음
      답 : 4

    33. Stack Area 에 저장되지 않는 것은 ?
    1 ) Local Variable
    2 ) Parmeter
    3 ) Return Value
    4 ) Macro Literal   // Code Area
    5 ) Return Address
      답 : 4

    34. 다음중 C 에서의 쓸 수 없는 동적할당 관련 메서드는 ?
    1 ) malloc
    2 ) calloc
    3 ) new
    4 ) realloc
    5 ) free
      답 : 3

    35. double Function (int a, int b); 로 선언되어 있는 함수를 함수포인터에 저장하고 싶을 때
        알맞은 것은 ?
    1 ) (*Func)(int , int) = Function();
    2 ) double (*Func)(int , int) = Function();
    3 ) double (*Func)() = Function;
    4 ) double (*Func)(int , int) = Function;
    5 ) (*Func)(int , int) double = Function;
      답 : 4

    36. Call By Value 에 대한 설명이 아닌 것은 ?
    1 ) 값에 의한 전달을 의미한다.
    2 ) 전달되는 값이 매개변수에 복사되어 들어간다.
    3 ) 원본에 값에 영향이 가지않는 방식이다.
    4 ) 매개변수의 값을 변경하면 외부의 변수의 값이 변경될 수 있다.  // Call By Address
    5 ) 해당 없음
      답 : 4

    37. 보기와 같이 작성한 코드가 에러가 발생하는 이유중 알맞은 것은 ?
        보기 )
                int Array1[5] = { 1, 2, 3, 4, 5 };
                int Array2[5] = { 10 , 20 , 30, 40, 50 };
                Array1 = Array2; - Error ! -

                int * const 
                // Constant pointer 포인터 상수
                // 주소값 변경 불가능
                // 간접 참조로 인한 값 변경 가능

                const int * 
                // Pointer to Contant 상수 포인터
                // 주소값 변경 가능
                // 간접 참조로 인한 값 변경 불가능


    1 ) 배열의 이름은 상수 이기 때문입니다.
    2 ) 배열의 이름은 상수 포인터이기 때문입니다.
    3 ) 배열의 이름은 포인터 상수이기 때문입니다.
    4 ) 배열의 길이가 같지 않아서 입니다. 
    5 ) 배열의 요소들의 값이 같지 않아서 입니다.
      답 : 3

    38. 다음 중 프로그램이 수행하고 있는 시간을 가리키는 것은 ?
    1 ) Compile Time
    2 ) RunTime
    3 ) Debugging Time
    4 ) Build Time
    5 ) Link Time
      답 : 2

    39. 전처리 지시어가 처리되는 때는 언제인가 ?
    1 ) 컴파일 직전
    2 ) 컴파일 도중
    3 ) 컴파일 이후
    3 ) 런타임
    4 ) 해당 없음
      답 : 1

    40. 전처리 지시어중 매크로나 심볼을 정의할 때 사용하는 것은 ?
    1 ) #elif
    2 ) #include
    3 ) #pragma region
    4 ) #define
    5 ) #undef
      답 : 4

    41. 보기와 같이 구조체를 동적할당할 때 맴버의 접근 방법중 옳은 것은 ?
        보기 )
                Struct* p = (Struct*)malloc(sizeof(Struct) * 5);

    1 ) p.member;
    2 ) p[0]->member;       // *(p + 0)
    3 ) (*p)->member;
    4 ) *(p + 1).member;
    5 ) *(p[1])->member;
      답 : 4

    42. const int * p 의 설명으로 옳지 않은 것은 ?
    1 ) p 가 가르키고 있는 변수의 값의 수정이 불가능하다.
    2 ) p 가 가르키고 있는 주소의 변경이 가능하다.
    3 ) p 가 가르키고 있는 변수의 값에 접근이 불가능하다.
    4 ) p 를 통하여 다른 변수를 가르킬 수 있게 수정이 가능하다. 
    5 ) p 는 자기 자신만의 주소를 가지고 있다.
      답 : 3

    43. 다음중 함수를 사용하기 위해서 진행해야 할 과정이 아닌 것은 ?
    1 ) 함수의 선언
    2 ) 함수의 정의
    3 ) 함수의 호출
    4 ) 함수의 해제
    5 ) 해당 없음
      답 : 4

    44. 동적할당한 메모리를 해제하고 NULL 로 초기화 해주는 이유중 알맞지 않은 것은 ?
    1 ) 댕글링 포인터가 발생하지 않기 위해서 입니다.
    2 ) 동적할당한 메모리가 해제되지 않아서 입니다.
    3 ) 해당 포인터가 다른 변수를 가르키는 일이 발생하지 않도록 하기 위해서 입니다.         // 이미 해제되었다.
    4 ) 0 을 가르키게 하여 아무것도 가르키지 않는다고 명시하기 위해서 입니다.
    5 ) 존재하지 않은 공간의 주소를 가르키지 않기 위해서 입니다.
      답 : 3 (2)

    45. 보기와 같이 작성된 코드에서 맴버 접근이 안되는 코드는 ?
        보기 ) Monster monster;
              Monster* pMonster = &monster;
              Monster** ppMonster = &pMonster;

              monster == *pMonster == **ppMonster
              &monster == pMonster == *ppMonster
              &pMonster == ppMonster

    1 ) monster.member;
    2 ) pMonster->member;
    3 ) (*pMonster).member;
    4 ) (ppMonster)->member;
    5 ) (*ppMonster)->member;
      답 : 4

    46. 단일 포인터에 관하여 옳지 않은 것은 ?
    1 ) 주소값을 저장할 수 있는 기능이다.
    2 ) 간접참조를 통하여 가리키고 있는 변수에 접근할 수 있다.
    3 ) 모든 주소값을 저장할 수 있다.
    4 ) 구조체 , 배열 , 변수등의 주소를 저장할 수 있다.
    5 ) const 키워드를 이용하여 변경하지 않을 값을 지정할 수 있다.
      답 : 3
 

    47. const 키워드에 대해 옳지 않은 것은 ?
    1 ) 기본 자료형에 사용할 수 있다.
    2 ) 매개변수에 사용할 수 있다.
    3 ) 구조체에 사용할 수 있다.
    4 ) 선언시 초기화가 이루어져야 한다.
    5 ) 함수의 반환형으로 사용할 수 없다.
      답 : 5

    48. 다음의 형식 문자중 정수형태를 출력해주는 것이 아닌 것은 ?
    1 ) %lld
    2 ) %f
    3 ) %d
    4 ) %i
    5 ) %u
      답 : 2
*/

