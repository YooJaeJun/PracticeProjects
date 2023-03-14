#include "03_Collision/C06_Explosion.h"
#include "Global.h"
#include "C06_EventTrigger.h"
#include "Particles/ParticleSystem.h"
#include "Components/TextRenderComponent.h"

AC06_Explosion::AC06_Explosion()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CreateTextRender();
	
	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit.P_ky_hit'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_dark.P_ky_hit_dark'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_fire.P_ky_hit_fire'");
}

void AC06_Explosion::BeginPlay()
{
	Super::BeginPlay();

	AC06_EventTrigger* trigger = CHelpers::FindActor<AC06_EventTrigger>(GetWorld());
	CheckNull(trigger);

	trigger->OnExplosionEvent.AddUFunction(this, "OnExplosion");
	trigger->OnExplosionEvent.Broadcast(0);
}

void AC06_Explosion::OnExplosion(int32 InIndex)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
}
