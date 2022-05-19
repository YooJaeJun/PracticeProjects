// 전처리기 (PreProcessor)
// - 전처리 지시자라고도 불립니다.
// - 실제 컴파일이 시작되기 전에 컴파일러에게 특별한 명령을 미리 처리하도록
//	지시할 때 사용하는 구문
// - 전처리기는 '#' 으로 시작되며, 한 라인에 한 개의 전처리기 명령만을 사용할 수 있습니다.
// - 전처리기에는 끝에 세미콜론을 작성하지 않습니다.

#pragma once
// #pragma : 컴파일러의 기능을 확장시킬 수 있도록 하는 지시어입니다.
// #pragma once : 컴파일러에게 해당 헤더파일이 한 번만 포함되도록 지시합니다.
// - 헤더파일(.h / Header File) : 선언한 코드를 다른 파일에서 사용할 수 
//								있도록 포함시킬 수 있는 파일입니다.

#pragma warning(disable : 4996)
// #pragma warning(disable : 4996) : 지정한 code 의 경고메시지를 무시합니다.

#pragma region Region
// - # pragme region BlockName : 확장 / 축소 시킬 수 있는 블록을 생성합니다.
//								# pragma endregion 으로 끝나야 합니다.
#pragma endregion 
// # pragma endregion : # pragma region 에 대한 끝을 나타냅니다.

#include <stdio.h>
// #include
// 지정한 파일의 내용을 읽어와 지시자가 작성된 파일에 포함시킵니다.
// - 사용자 정의 헤더 파일 : 사용자가 직접 작성한 헤더 파일을 의미합니다.
//						큰 따옴표("")를 사용하여 추가시킬 수 있습니다.
//						ex) #include "01_PreProcessor.h"
// 
// - 기본 제공 헤더 파일 : Visual Studio 에서 기본적으로 제공하는 헤더파일입니다.
//						꺾쇠(<>) 를 사용하여 추가시킬 수 있습니다.
//						ex ) #include <stdio.h>

// - 심볼 DEBUG 를 정의합니다.
#define DEBUG
// #define : 심볼, 또는 매크로 상수 / 함수를 정의합니다.

// 매크로 상수 PI 를 정의합니다.
#define PI 3.14f
// - 3.14f 를 PI 키워드로 정의합니다.
// PI를 사용하게 된다면 3.14f 라는 코드로 치환됩니다.

// 매크로 함수 plus 를 정의합니다.
#define plus(x, y) (x + y)
// - 사용 시 plus(x, y) 코드가 (x + y)라는 코드로 치환됩니다.
// 매개변수의 타입을 지정할 수 없습니다.

#define INT 1
#if INT == 0
// #if : 조건에 따라 컴파일 여부를 검사합니다.
//		정수 형식만을 검사하실 수 있습니다.
#elif INT == 1
// #elif : 위 조건이 맞지 않을 시 검사하는 전처리 지시어입니다.
#else
// #else : 모든 조건이 맞지 않을 시 컴파일 하는 지시어입니다.
#endif
// #endif : 조건 여부 전처리 지시어를 사용한다면 반드시 #endif 로 끝내야 합니다.

#ifdef DEBUG
// #ifdef : 심볼, 매크로 상수, 함수가 정의되어 있는지 검사합니다.
#undef DEBUG
// #undef : 심볼, 매크로 상수, 함수의 정의를 해제합니다.
#endif

#ifndef DEBUG
// #ifndef : 심볼, 매크로 상수, 함수가 정의되어 있지 않은지를 검사합니다.
#define DOUBLE 1.234
#endif



#define Calculate

#ifdef Calculate
#define Addition(x, y) (x + y)
#define Subtraction(x, y) (x - y)
#define Multiplication(x, y) (x * y)
#define Division(x, y) (x / y)
#define Remained(x, y) (x % y)
#endif
