// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IBuffReceiver.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeedChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyInitialized);

USTRUCT(BlueprintType)
struct FEnemyCharacteristics
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Characteristics")
	float BaseMovementSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Characteristics")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Characteristics")
	FLinearColor Color = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Characteristics")
	float ScaleMultiplier = 1.f;
};

UCLASS(config=Game)
class UEBUFFSYSTEMDEMO_API AEnemy : public ACharacter, public IBuffReceiver
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	virtual void Init(FEnemyCharacteristics InCharacteristics);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** IBuffReceiver interface start*/
	virtual void BuffImpact_Implementation(UClass* InEffectClass) override;
	/** IBuffReceiver interface end*/
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for take damage */
	void TakeDamage(float DamageValue);

	/** Called for healing */
	void TakeHeal(float HealValue);

	/** Called for change speed */
	void AddSpeed(float InAddingValue);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetBaseSpeed() const;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeColor(FLinearColor InColor);
	
	UPROPERTY(BlueprintAssignable, Category = "Enemy Characteristics")
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Enemy Characteristics")
	FOnSpeedChanged OnSpeedChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Enemy Characteristics")
	FOnEnemyInitialized OnEnemyInitialized;
	
private:
	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category="Enemy Characteristics")
	FEnemyCharacteristics CurrentCharacteristics;

	UPROPERTY(meta=(AllowPrivateAccess="true"), VisibleAnywhere, BlueprintReadOnly, Category="Enemy Characteristics")
	float CurrentHealth = 100.f;
	
	UPROPERTY(meta=(AllowPrivateAccess="true"), VisibleAnywhere, BlueprintReadOnly, Category="Enemy Characteristics")
	bool bIsRandomCharacteristics = false;
};
