// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//충돌체 등록
	collisonComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collison Component"));
	//충돌 프로필 설정
	collisonComp -> SetCollisionProfileName(TEXT("BlockAll"));
	//충돌체 크기 설정
	collisonComp -> SetSphereRadius(13.f);
	//루트 컴포넌트로 등록
	RootComponent = collisonComp;
	
	//외관 컴포넌트 등록
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh Component"));
	//계층화
	bodyMeshComp -> SetupAttachment(collisonComp);
	//외관 컴포넌트 충돌은 off
	bodyMeshComp -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//외관 크기 설정
	bodyMeshComp -> SetRelativeScale3D(FVector(0.25f));
	
	//발사체 컴포넌트 등록
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	//movement 컴포넌트가 갱신시킬 컴포넌트 지정
	movementComp -> SetUpdatedComponent(collisonComp);
	//초기 속도
	movementComp -> InitialSpeed = 5000.f;
	//최대 속도
	movementComp -> MaxSpeed = 5000.f;
	// 반동 여부
	movementComp -> bShouldBounce = true;
	//반동 값(탄성)
	movementComp -> Bounciness = 0.3f;	
	
	/*
	//객체 생명 시간 스스로 destroy
	InitialLifeSpan = 2.f;
	*/
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle deathTimer;
	//SetTimer(핸들러, 대상 객체, 호출함수, 시간, 반복여부)
	GetWorldTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.f, false);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::Die()
{
	Destroy();
}


