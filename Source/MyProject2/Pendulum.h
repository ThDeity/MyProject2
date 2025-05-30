#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphWidget.h"
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
    UFUNCTION(BlueprintCallable, Category = "Pendulum")
    void ResetSimulation();

    UFUNCTION(BlueprintCallable, Category = "Pendulum")
    void SetPendulumLength(float NewLength);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum")
    UGraphWidget* GraphWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    TArray<float> PendulumSpeeds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    int32 MaxPoints = 50;

    virtual void Tick(float DeltaTime) override;
    // � ����� APendulum ���������:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float DampingFactor = 0.02f; // ����������� ��������� (0 = ��� ���������, 1 = ���������� ���������)

    // ����������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* PivotPoint; // ����� �������

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* BallMesh; // �����

    // ��������� ��������� ��� ����
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StringMesh;

    // ��������� ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float PendulumLength = 200; // ����� ���� (� ��)

    UPROPERTY(EditAnywhere, Category = "Pendulum Settings")
    float StringThickness = 5.f; // ������� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float Gravity = 9.81f; // ��������� ���������� �������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Settings")
    float InitialAngle = 0.5f; // ��������� ���� (� ��������)

private:
    float CurrentAngle; // ������� ���� (�������)
    float AngularVelocity; // ������� ��������
};