// Copyright by Stiner. All Rights Reserved.

#include "PugaCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySet.h"


APugaCharacter::APugaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

UAbilitySystemComponent* APugaCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APugaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APugaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APugaCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APugaCharacter::Look);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APugaCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APugaCharacter::StopJump);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APugaCharacter::StartAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &APugaCharacter::StopAttack);

		//Guard
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &APugaCharacter::StartGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &APugaCharacter::StopGuard);

		//Spell
		EnhancedInputComponent->BindAction(SpellAction, ETriggerEvent::Triggered, this, &APugaCharacter::StartSpell);
		EnhancedInputComponent->BindAction(SpellAction, ETriggerEvent::Completed, this, &APugaCharacter::StopSpell);
	}

	SetupInputForAbilitySystem(PlayerInputComponent);
}

void APugaCharacter::SetupInputForAbilitySystem(UInputComponent* PlayerInputComponent)
{
	AbilitySystemComponent->BindToInputComponent(PlayerInputComponent);

	if (!GameplayAbilitySet)
	{
		UE_LOG(LogTemp, Log, TEXT("[APugaCharacter] AbilitSet is null."));
		return;
	}

	for (const FGameplayAbilityBindInfo& BindInfo : GameplayAbilitySet->Abilities)
	{
		FGameplayAbilitySpec Spec
		(
			/*Ability*/ BindInfo.GameplayAbilityClass->GetDefaultObject<UGameplayAbility>(),
			/*Level  */ 1,
			/*InputID*/ static_cast<int32>(BindInfo.Command)
		);

		FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GiveAbility(Spec);

		int32 AbilityID = static_cast<int32>(BindInfo.Command);

		UClass::TryFindTypeSlowSafe<UEnum>("EGameplayAbilityInputBinds");

		FGameplayAbilityInputBinds InputBinds
		(
			/*ConfirmTargetCommand*/ FString::Printf(TEXT("ConfirmTargetting_%s_%s"), *GetName(), *(BindInfo.GameplayAbilityClass->GetName())),
			/*CancelTargetCommand */ FString::Printf(TEXT("CancelTargetting_%s_%s"), *GetName(), *(BindInfo.GameplayAbilityClass->GetName())),
			/*EnumPathName        */ FTopLevelAssetPath(FString(TEXT("/Script/GameplayAbilities.EGameplayAbilityInputBinds"))),
			/*ConfirmTargetInputID*/ AbilityID,
			/*CancelTargetInputID */ AbilityID
		);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, InputBinds);

		AbilitySystemComponent->TryActivateAbility(AbilityHandle, 1);
	}
}

void APugaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APugaCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APugaCharacter::StartJump(const FInputActionValue& Value)
{
	Super::Jump();
}

void APugaCharacter::StopJump(const FInputActionValue& Value)
{
	Super::StopJumping();
}

void APugaCharacter::StartAttack(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StartAttack"));
}

void APugaCharacter::StopAttack(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StopAttack"));
}

void APugaCharacter::StartGuard(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StartGuard"));
}

void APugaCharacter::StopGuard(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StopGuard"));
}

void APugaCharacter::StartSpell(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StartSpell"));
}

void APugaCharacter::StopSpell(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("StopSpell"));
}




