#include "DoorOpener.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpener::BeginPlay() {
	Super::BeginPlay();
	
	if (m_triggerVolume == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("NO trigger volume attached to %s"), *(GetOwner()->GetName()))
		return;
	}
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassAtTrigger() > m_minimumMass) {
		m_openDoorEvent.Broadcast();
	} 
	else {
		m_closeDoorEvent.Broadcast();
	}
}

// Gets the total mass at the trigger
float UDoorOpener::GetMassAtTrigger() const {
	float totalMass = 0;

	TArray<AActor*> overlappingActors;
	m_triggerVolume->GetOverlappingActors(overlappingActors);

	for (const auto& actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return totalMass;
}

