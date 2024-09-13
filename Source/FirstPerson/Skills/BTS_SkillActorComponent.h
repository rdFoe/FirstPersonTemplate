// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTS_SkillActorComponent.generated.h"


class UInputMappingContext;
class UBTS_SkillDataAsset;
class UBTS_SkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSON_API UBTS_SkillActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBTS_SkillActorComponent();

	UFUNCTION(BlueprintCallable)
	TArray<UBTS_SkillBase*> GetCreatedSkills() { return CreatedSkills; }

	void InitializeSkills();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Skills", meta=(AllowPrivateAccess=true))
	TArray<UBTS_SkillDataAsset*> SkillsToRegister;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Skills", meta=(AllowPrivateAccess=true))
	UInputMappingContext* SkillInputMappingContext;	

private:
	UPROPERTY()
	TArray<UBTS_SkillBase*> CreatedSkills;
};
