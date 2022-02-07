// Amos Bocelli Copyrights


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw; //TargetYaw = TargetYaw + InitialYaw;

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("The %s has the open door component on it but no pressureplate set!!!"), *GetOwner()->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
/* 	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("The Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
 */
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, .5f * DeltaTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}