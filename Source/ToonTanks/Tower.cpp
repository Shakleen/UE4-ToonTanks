// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle, 
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true
    );
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsWithInRange())
        RotateTurret(Tank->GetActorLocation());
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition()
{
    if (IsWithInRange())
        Fire();
}

inline bool ATower::IsWithInRange() const
{
    if (!Tank) 
        return false;

    return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}
