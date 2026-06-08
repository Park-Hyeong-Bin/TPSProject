// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnim.h"

#include "TPSPlayer.h"
#include "Chaos/Utilities.h"
#include "GameFramework/CharacterMovementComponent.h"

//매 프레임 자동 호출 - Tick 직접안해도 UE 자체가 호출
void UTPSPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	//애니메이션 인스턴스를 수용한 폰(TPS플레이어) 가져오기
	APawn* pawn = TryGetPawnOwner();
	if (pawn == nullptr) return;
	
	//ATPSPlayer 폰의 상태 추출을 하기 위한 캐스팅 (속도, 점프 중인지)
	ATPSPlayer* player = Cast<ATPSPlayer>(pawn);
	if (player)
	{
		//속도, 전후, 좌우 벡터 가져오기
		FVector velocity = player->GetVelocity();
		FVector forward = player->GetActorForwardVector();
		FVector right = player->GetActorRightVector();
		
		//DotProduct() 로 전후 성분과 좌우 성분을 분리 -> BlendSpace 8방향 보간을 위함
		speed = FVector::DotProduct(velocity, forward); // 앞 = 양수, 뒤 = 음수
		direction = FVector::DotProduct(velocity, right); // 오른쪽 = 양수, 왼쪽 = 음수
		
		// 공중에 떠 있는 상태인지
		UCharacterMovementComponent* movement = player->GetCharacterMovement();
		if (movement)
		{
			isInair = movement->IsFalling();
		}
	}
	
	
	
	//디버그
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0.f,FColor::Cyan,
			FString::Printf(TEXT("Speed : %.1f, direction : %.1f, isInair : = %s"),speed, direction, isInair ? TEXT("true") : TEXT("false")));
	}
}
