#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();
	
	/// Initialize the physics handle component
	{
		m_physicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		if (m_physicsHandleComponent == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("%s does not have a physics handle component"), *(GetOwner()->GetName()))
		}
	}

	/// Initialize the input component
	{
		m_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
		if (m_inputComponent == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("%s does not have an input component"), *(GetOwner()->GetName()))
		} else {
			m_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
			m_inputComponent->BindAction("Release", IE_Released, this, &UGrabber::Release);
		}
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_physicsHandleComponent != nullptr) {
		FVector startPosition, endPosition;
		GetRayEnds(OUT startPosition, OUT endPosition);

		/// Update the grabbed actor's position
		if (m_physicsHandleComponent->GetGrabbedComponent() != nullptr) {
			m_physicsHandleComponent->SetTargetLocation(endPosition);
		}
	}
}

void UGrabber::GetRayEnds(FVector& startPosition, FVector& endPosition) {
	/// Get start position
	FRotator playerRotation;
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	playerController->GetPlayerViewPoint(OUT startPosition, OUT playerRotation);
	
	/// Get end position
	endPosition = startPosition + m_reach * playerRotation.Vector();
}
FHitResult UGrabber::Raycast(const FVector& startPosition, const FVector& endPosition) const {
	FHitResult hitResult;
	
	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		startPosition,
		endPosition,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return hitResult;
}

void UGrabber::Grab() {
	/// Sanity check
	if (m_physicsHandleComponent == nullptr) return;
	
	/// Check if an actor is already grabbed
	if (m_physicsHandleComponent->GetGrabbedComponent() != nullptr) return;

	/// Perform Raycasting
	FHitResult hitResult;
	{
		FVector startPosition, endPosition;
		GetRayEnds(OUT startPosition, OUT endPosition);
		hitResult = Raycast(startPosition, endPosition);
	}

	/// Grab actor in reach
	if (hitResult.GetActor() != nullptr) {
		UPrimitiveComponent* overlappingPrimitiveComponent = hitResult.GetComponent();
		if (overlappingPrimitiveComponent != nullptr) {
			m_physicsHandleComponent->GrabComponent(
				overlappingPrimitiveComponent,
				NAME_None,
				overlappingPrimitiveComponent->GetOwner()->GetActorLocation(),
				true
			);
		}
	}
}
void UGrabber::Release() {
	/// Sanity check
	if (m_physicsHandleComponent == nullptr) return;
	
	/// Release grabbed actor
	if (m_physicsHandleComponent->GetGrabbedComponent() != nullptr) {
		m_physicsHandleComponent->ReleaseComponent();
	}
}