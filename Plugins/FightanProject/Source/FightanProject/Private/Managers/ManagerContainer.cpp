// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ManagerContainer.h"

// Sets default values
AManagerContainer::AManagerContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VFXManager = CreateDefaultSubobject<UVFXManager>(TEXT("VFXManager"));
	SFXManager = CreateDefaultSubobject<USFXManager>(TEXT("VSXManager"));
}

// Called when the game starts or when spawned
void AManagerContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManagerContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}