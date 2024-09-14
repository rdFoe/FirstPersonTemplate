// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SkillActorComponent.h"

#include "BTS_SkillBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPerson/FirstPersonPlayerController.h"
#include "FirstPerson/DataAssets/BTS_SkillDataAsset.h"

// Sets default values for this component's properties
UBTS_SkillActorComponent::UBTS_SkillActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBTS_SkillActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if(SkillInputMappingContext)
	{
		if(const AFirstPersonPlayerController* pc = GetOwner<AFirstPersonPlayerController>())
		{
			// get the enhanced input subsystem
			if (UEnhancedInputLocalPlayerSubsystem* enhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
			{
				// add skill input context
				enhancedInputSubsystem->AddMappingContext(SkillInputMappingContext, 0);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not add Skill Input Context because Input System NULL"))
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not add Skill Input Context because player controller NULL"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add Skill Input Context because SkillInputMappingContext NULL"))
	}

	InitializeSkills();
}

void UBTS_SkillActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CreatedSkills.Empty();
}

void UBTS_SkillActorComponent::InitializeSkills()
{

	if(const AFirstPersonPlayerController* pc = GetOwner<AFirstPersonPlayerController>())
	{
		// get the enhanced input subsystem
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(pc->InputComponent))
		{
			for (auto Element : SkillsToRegister)
			{
				if(!Element->ClassToGenerate)
				{
					continue;
				}
				if(!Element->ClassToGenerate->IsChildOf(UBTS_SkillBase::StaticClass()))
				{
					continue;
				}
				
				UBTS_SkillBase* generatedSkill = NewObject<UBTS_SkillBase>(this, Element->ClassToGenerate);
				if(!generatedSkill)
				{
					continue;
				}
				generatedSkill->RegisterSkill(Element, this);
				CreatedSkills.Add(generatedSkill);

				EnhancedInputComponent->BindAction(Element->InputAction, ETriggerEvent::Triggered, generatedSkill, &UBTS_SkillBase::TryExecuteSkill);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not add Skill Input Context because Input System NULL"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add Skill Input Context because player controller NULL"))
	}
}

