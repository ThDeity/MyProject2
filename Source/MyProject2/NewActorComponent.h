#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pendulum.h"
#include "NewActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UNewActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNewActorComponent();

	// Параметры маятника
	UPROPERTY(EditAnywhere)
	float length = 200.f; // Длина нити (в см)

	UPROPERTY(EditAnywhere)
	APendulum* sphere;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
