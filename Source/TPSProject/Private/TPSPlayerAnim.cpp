// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnim.h"

#include "TPSPlayer.h"

//매 프레임 자동 호출 - Tick 직접안해도 UE 자체가 호출
void UTPSPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	//애니메이션 인스턴스를 수용한 폰(TPS플레이어) 가져오기
	APawn* pawn = TryGetPawnOwner();
	if (pawn == nullptr) return;
	
	//ATPSPlayer 폰의 속도 측정
	ATPSPlayer* player = Cast<ATPSPlayer>(pawn);
	if (player)
	{
		speed = player->GetVelocity().Size();
	}
	
	//디버그
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0.f,FColor::Cyan,FString::Printf(TEXT("AnimeSpeed : %f"),speed));
	}
}
