// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
    TowerCount = GetTowerCount();
}

int AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> TowerList;

    UGameplayStatics::GetAllActorsOfClass(
        this,
        ATower::StaticClass(),
        TowerList
    );

    return TowerList.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (!PlayerController)
    {
        PlayerController->SetPlayerEnabled(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &AToonTanksPlayerController::SetPlayerEnabled,
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );
    }
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank) 
    {
        Tank->HandleDestruction();
        GameOver(false);

        if (PlayerController)
            PlayerController->SetPlayerEnabled(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TowerCount--;

        if (!TowerCount) 
            GameOver(true);
    }
}