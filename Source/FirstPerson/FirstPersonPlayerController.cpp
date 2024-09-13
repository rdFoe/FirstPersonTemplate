// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstPersonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonCharacter.h"
#include "TP_WeaponComponent.h"
#include "Engine/LocalPlayer.h"
#include "Skills/BTS_SkillActorComponent.h"

UTP_WeaponComponent* AFirstPersonPlayerController::GetWeaponComponent()
{
	UTP_WeaponComponent* weaponComp = nullptr;
	if(AFirstPersonCharacter* character = Cast<AFirstPersonCharacter>(GetCharacter()))
	{
		// somehow I can not find the component via character->GetComponentbyClass. Have to figure this out later but should not block me now.
		for (auto Element : character->GetInstanceComponents())
		{
			if (Cast<UTP_WeaponComponent>(Element))
			{
				weaponComp = Cast<UTP_WeaponComponent>(Element);
			}
		}
	}
	
	return weaponComp;
}

AFirstPersonPlayerController::AFirstPersonPlayerController()
{
	SkillActorComponent = CreateDefaultSubobject<UBTS_SkillActorComponent>("SkillActorComponent");
}

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
