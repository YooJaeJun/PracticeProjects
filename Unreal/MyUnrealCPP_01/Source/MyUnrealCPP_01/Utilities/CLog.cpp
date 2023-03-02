#include "Utilities/CLog.h"

DEFINE_LOG_CATEGORY_STATIC(GP, Display, All)


void CLog::Log(int32 InValue)
{
	//GLog->Log("GP", ELogVerbosity::Display, FString::FromInt(InValue));
	UE_LOG(GP, Display, TEXT("%d"), InValue);
}

void CLog::Log(float InValue)
{
	UE_LOG(GP, Display, TEXT("%f"), InValue);
}

void CLog::Log(const FString& InValue)
{
	UE_LOG(GP, Display, TEXT("%s"), *InValue);
}

void CLog::Log(const FVector& InValue)
{
	UE_LOG(GP, Display, TEXT("%s"), *InValue.ToString());
}

void CLog::Log(const FRotator& InValue)
{
	UE_LOG(GP, Display, TEXT("%s"), *InValue.ToString());
}

void CLog::Log(const UObject* InValue)
{
	FString str;

	if (!!InValue)
		str.Append(InValue->GetName());

	str.Append(!!InValue ? " Not Null" : "Null");

	UE_LOG(GP, Display, TEXT("%s"), *str);
}
