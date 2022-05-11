// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UParticleSystem;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USoundBase;
class UCameraShakeBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(VisibleAnywhere,  Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere,  Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent * TrailParticles = nullptr;

	UPROPERTY(EditDefaultsOnly,  Category = "movement", meta = (AllowPrivateAccess = "true"))
	float InitialSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly,  Category = "movement", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly,  Category = "movement", meta = (AllowPrivateAccess = "true"))
	float Damage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticles = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USoundBase* LaunchSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass = nullptr;
};
