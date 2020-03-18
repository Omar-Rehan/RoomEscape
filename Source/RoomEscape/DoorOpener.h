#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "DoorOpener.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UDoorOpener : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float m_minimumMass = 20.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* m_triggerVolume = nullptr;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent m_openDoorEvent;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent m_closeDoorEvent;


	// Gets the total mass at the trigger
	float GetMassAtTrigger() const;
};
