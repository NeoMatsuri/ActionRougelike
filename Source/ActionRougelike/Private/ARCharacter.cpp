// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "ARAttributeComponent.h"





// Sets default values
AARCharacter::AARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp ->SetupAttachment(RootComponent);

	MuzzleFlash = CreateDefaultSubobject<UParticleSystem>("MuzzleFlash");

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp ->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UARInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");
	this->AddInstanceComponent(AttributeComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	
}

void AARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AARCharacter::OnHealthChanged);
}




// Called when the game starts or when spawned
void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AARCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;



	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}


// Called every frame
void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AARCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AARCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &AARCharacter::BlackHole);
	PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &AARCharacter::Teleport);

}

void AARCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	
}


void AARCharacter::PrimaryAttack_TimeElapsed()
{
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;


	FHitResult Hit;
	FVector TraceStart = CameraComp->GetComponentLocation();
	// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
	FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

	FCollisionShape Shape;
	Shape.SetSphere(20.0f);

	// Ignore Player
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FRotator ProjRotation;
	// true if we got to a blocking hit (Alternative: SweepSingleByChannel with ECC_WorldDynamic)
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
	{
		// Adjust location to end up at crosshair look-at
		ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
	}
	else
	{
		// Fall-back since we failed to find any blocking hit
		ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
	}


	FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetMesh(), TEXT("Muzzle_01"));
	


	/*FHitResult Hit;
	

	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * 2000.f;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, HandLocation, End, ObjectQueryParams);
	
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;	


	FRotator HitRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.Location);
	FRotator TraceEnd = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	if (bBlockingHit)
	{
		FTransform SpawnTM = FTransform(HitRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

	else
	{
		FTransform SpawnTM = FTransform(TraceEnd, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
	

	//DrawDebugLine(GetWorld(), HandLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	//FString CombinedString = FString::Printf(TEXT("Hit at Location: %s"), *Hit.ImpactPoint.ToString());
	//DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);*/
}

void AARCharacter::BlackHole()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::BlackHole_TimeElapsed, 0.2f);
	
}

void AARCharacter::BlackHole_TimeElapsed()
{
	FHitResult Hit;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);


	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * 5000.f;

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, HandLocation, End, ObjectQueryParams);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;


	FRotator HitRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.Location);
	FRotator TraceEnd = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	if (bBlockingHit)
	{
		FTransform SpawnTM = FTransform(HitRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(SkillClass, SpawnTM, SpawnParams);
	}

	else
	{
		FTransform SpawnTM = FTransform(TraceEnd, HandLocation);
		GetWorld()->SpawnActor<AActor>(SkillClass, SpawnTM, SpawnParams);
	}


	//DrawDebugLine(GetWorld(), HandLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	//FString CombinedString = FString::Printf(TEXT("Hit at Location: %s"), *Hit.ImpactPoint.ToString());
	//DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

void AARCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::Teleport_TimeElapsed, 0.2f);
}

void AARCharacter::Teleport_TimeElapsed()
{

	
	FHitResult Hit;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);


	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * 2000.f;

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, HandLocation, End, ObjectQueryParams);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;


	FRotator HitRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.Location);
	FRotator TraceEnd = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	if (bBlockingHit)
	{
		FTransform SpawnTM = FTransform(HitRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(SkillClass2, SpawnTM, SpawnParams);
	}

	else
	{
		FTransform SpawnTM = FTransform(TraceEnd, HandLocation);
		GetWorld()->SpawnActor<AActor>(SkillClass2, SpawnTM, SpawnParams);
	}


	//DrawDebugLine(GetWorld(), HandLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	//FString CombinedString = FString::Printf(TEXT("Hit at Location: %s"), *Hit.ImpactPoint.ToString());
	//DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

}

void AARCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void AARCharacter::OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (NewHealth <= -0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}

}




