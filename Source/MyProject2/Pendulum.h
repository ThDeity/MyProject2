#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PendulumGraphWidget.h"
#include "Pendulum.generated.h"

UCLASS()
class MYPROJECT2_API APendulum : public AActor
{
    GENERATED_BODY()

public:
    APendulum();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
    UPendulumGraphWidget* GraphWidget;

    UFUNCTION(BlueprintCallable, Category = "Pendulum")
    void ResetSimulation();

    UFUNCTION(BlueprintCallable, Category = "Pendulum")
    void SetPendulumLength(float NewLength);

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float DampingFactor = 0.02f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* PivotPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StringMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float PendulumLength = 200;

    UPROPERTY(EditAnywhere, Category = "Pendulum Settings")
    float StringThickness = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float Gravity = 9.81f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float InitialAngle = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float AngularVelocity;
private:
<<<<<<< HEAD
    float CurrentAngle;
    //float AngularVelocity;
=======
    float CurrentAngle; // ������� ���� (�������)
    float AngularVelocity; // ������� ��������
    float CurrentDisplacement = 0;
>>>>>>> parent of d954649 (AmplitudeGraph)
};