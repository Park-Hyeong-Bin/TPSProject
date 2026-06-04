// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// 스프링 암 컴포넌트 선언
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	
	// 카메라 컴포넌트 선언
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* cameraComp;
	
	// 총 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class USkeletalMeshComponent* gunMeshComp;
	
	// 스나이퍼 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;
	
	//IMC 선택 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* imc_TPS;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_LookUp;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Turn;
	
	//전후좌우 키보드 이동 IA 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Move;
	
	// 키보드 점프 IA 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Jump;
	
	//마우스 발사 IA 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Fire;
	
	//총 스왑 IA 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_GrenadeGun;
	
	//총 스왑 IA 필드 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_SniperGun;
	
	// 현재 유탄총을 사용중인지 여부(true = 유탄총, false = 스나이퍼)
	bool bUsingGrenadeGun = true;
	
	// 조준상태 여부
	bool bSniperZoom = false;
	
	//런타임에 생성될 UI 인스턴스
	UPROPERTY()
	class UUserWidget* sniperUI;
	
	//스나이퍼 줌 IA 선언
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_SniperZoom;
	
	//이동속도
	UPROPERTY(EditDefaultsOnly, Category = Input)
	float walkSpeed = 600.f;
	
	//총알 스폰 팩토리
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;
	
	//스나이퍼 줌 UI 위젯 (WBP_SniperUI를 에디터에서 할당 필요)
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;
	
	//런타임에 생성될 UI 인스턴스
	UPROPERTY()
	class UUserWidget* CrosshairUI;
	
	//일반 조준 그로스헤어 UI 위젯 팩토리
	//스나이퍼 줌 UI 위젯 (WBP_SniperUI를 에디터에서 할당 필요)
	UPROPERTY(EditDefaultsOnly, Category = CrosshairUI)
	TSubclassOf<class UUserWidget> CrosshairUIFactory;
	
	//이동방향
	FVector direction;
	
	//상하 회전 입력 함수 선언
	void LookUp(const struct FInputActionValue& inputValue);
	
	void Turn(const struct FInputActionValue& inputValue);
	
	//이동 함수 선언
	void Move(const struct FInputActionValue& inputValue);
	
	//점프 함수 선언
	void InputJump(const FInputActionValue& inputValue);
	
	//총알 발사 함수 선언
	void InputFire(const FInputActionValue& inputValue);
	
	//총 교체 입력 함수 선언
	void ChangeToGrenadeGun(const struct FInputActionValue& inputValue);
	void ChangeToSniperGun(const struct FInputActionValue& inputValue);
	
	//스나이퍼 줌 함수 선언
	void SniperZoom();
	
	// 스나이퍼 사격 명중 시 표시할 총알 파편 효과 선언
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* bulletEffectFactory;
};
