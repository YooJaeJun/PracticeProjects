#include "02_Profiler/C01_Log.h"
#include "Global.h"

AC01_Log::AC01_Log()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC01_Log::BeginPlay()
{
	Super::BeginPlay();

	CLog::Log(10);
	CLog::Log(PI);
	CLog::Log("C01_Log");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);

	CLog::Log(__FILE__);
	CLog::Log(__FUNCTION__);
	CLog::Log(__LINE__);
}

void AC01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

