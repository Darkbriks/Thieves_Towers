#include "TD_Player.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GA_ThievesTowers.h"
#include "InputActionValue.h"
#include "Card.h"

//////////////////////////////////////////////////////////////////////////
/// ATD_Player - Constructor
//////////////////////////////////////////////////////////////////////////
ATD_Player::ATD_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Movable);
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);

	CardHandSpline = CreateDefaultSubobject<USplineComponent>(TEXT("CardHand"));
	CardHandSpline->SetupAttachment(Root);

	CardHandSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CardHandSceneComponent"));
	CardHandSceneComponent->SetupAttachment(Root);
}

//////////////////////////////////////////////////////////////////////////
/// ATD_Player - Protected Overrides Methods
//////////////////////////////////////////////////////////////////////////
void ATD_Player::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TT_GameInstance = Cast<UGA_ThievesTowers>(GetGameInstance());
	
	if (TT_GameInstance)
	{
		// Assigner le Delegate a la game instance
		TT_GameInstance->CreateHandDelegate.BindUObject(this, &ATD_Player::CreateHand);

		CardHandPositions.Empty(); CardHandRotations.Empty();
		// Initialiser les positions et rotations des cartes dans la main
		const float SplineLength = CardHandSpline->GetSplineLength();
		const int NumberOfSlots = TT_GameInstance->GetMaxHandSize() * 2 - 1;
		for (int i = 0; i < NumberOfSlots; i++)
		{
			float Distance = SplineLength * i / (NumberOfSlots - 1);
			CardHandPositions.Add(CardHandSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local));
			CardHandRotations.Add(CardHandSpline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local));
		}
	}

	// Activer le cursor
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) { PlayerController->bShowMouseCursor = true; }
}

//////////////////////////////////////////////////////////////////////////
/// ATD_Player - Protected Methods
//////////////////////////////////////////////////////////////////////////
void ATD_Player::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	FVector NewLocation = this->GetActorLocation();
	NewLocation += this->GetActorForwardVector() * MovementVector.Y * MoveSpeed;
	NewLocation += this->GetActorRightVector() * MovementVector.X * MoveSpeed;
	NewLocation.Z = this->GetActorLocation().Z;

	this->SetActorLocation(NewLocation);
}

void ATD_Player::UpDown(const FInputActionValue& Value)
{
	float UpDownVector = Value.Get<float>();

	FVector NewLocation = this->GetActorLocation();
	NewLocation.Z += UpDownVector * UpDownSpeed;

	this->SetActorLocation(NewLocation);

	if (TT_GameInstance)
	{
		TT_GameInstance->AddCardToHand(ACard::StaticClass());
	}
}

void ATD_Player::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	FRotator NewRotation = this->GetActorRotation();
	NewRotation.Yaw += FMath::Clamp(LookVector.X * LookSpeed, -70, 70);
	NewRotation.Pitch += LookVector.Y * LookSpeed;
	NewRotation.Roll = 0;

	this->SetActorRotation(NewRotation);
}

void ATD_Player::CreateHand(TArray<TSubclassOf<ACard>> NewHand)
{
	if (!TT_GameInstance) { return; }
	
	for (ACard* Card : CardsInHand) { Card->Destroy(); } CardsInHand.Empty();
	
	int StartIndex = ((TT_GameInstance->GetMaxHandSize() * 2 - 1) - (2 * NewHand.Num()) + 1) / 2;
	for (int i = 0; i < NewHand.Num(); i++)
	{
		ACard* NewCard = GetWorld()->SpawnActor<ACard>(NewHand[i], FVector::ZeroVector, FRotator::ZeroRotator);
		NewCard->AttachToComponent(CardHandSceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		NewCard->SetActorRelativeLocation(CardHandPositions[StartIndex + 2 * i]);
		NewCard->SetActorRelativeRotation(CardHandRotations[StartIndex + 2 * i]);
		NewCard->SetActorScale3D(CardScale);
		
		CardsInHand.Add(NewCard);
	}
}

//////////////////////////////////////////////////////////////////////////
/// ATD_Player - Public Overrides Methods
//////////////////////////////////////////////////////////////////////////
void ATD_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATD_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATD_Player::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATD_Player::Look);
		EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Triggered, this, &ATD_Player::UpDown);
	}
}