// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabled(bool bEnabled)
{
    bShowMouseCursor = bEnabled;
    
    if (bEnabled)
        GetPawn()->EnableInput(this);
    else
        GetPawn()->DisableInput(this);
}