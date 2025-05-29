// ������������� ������������� ��������� ������������� �����, ����� �������� ������ ����������.
#pragma once

// �������� ����������� ����� ������� ����������� Unreal Engine, ����������� ��� ����������� ������� (��������, FString, TArray, FVector).
#include "CoreMinimal.h"
#include "Pendulum.h"

// �������� ����� PlayerController, ������� �������� ������� ��� ���������� ������� � ����.
#include "GameFramework/PlayerController.h"

// �������� ������������ ���� GraphWidget.h, ���������� ����������� ���������� ������� UMG ��� ����������� �������.
#include "GraphWidget.h"

// ������������� ������������ ������ Unreal Engine ��� ��������� ����������� ���������� � ������� ��� ������.
#include "MyPlayerController.generated.h"

// ���������� ����� AMyPlayerController, ������� ����������� �� APlayerController.
// ���� ����� ��������� ������� ������, ������� ������������ �������� ���� � ���������� ������� �� HUD.
UCLASS()
class MYPROJECT2_API AMyPlayerController : public APlayerController
{
    // ������, ����������� ��� ���� ������� Unreal Engine, ���������� ��� ��� ��������� ��������� (��������, ������������, Blueprint-�������������).
    GENERATED_BODY()

protected:
    // �������������� ����� BeginPlay, ������� ���������� ��� ������ ���� ��� �������������.
    // ������������ ��� ��������� HUD � ������ ���� � ������.
    virtual void BeginPlay() override;

    // �������������� ����� Tick, ������� ���������� ������ ����.
    // ������������ ��� ���������� ������� ���� � �������� ������ �������� � GraphWidget.
    virtual void Tick(float DeltaTime) override;

public:
    // ������ �� ����� Blueprint-������� HUD (��������, HUDWidget).
    // EditAnywhere: ����� ������������� � ��������� � Blueprints.
    // BlueprintReadWrite: �������� ��� ������ � ������ � Blueprints.
    // Category = "HUD": ���������� ���������� � ��������� "HUD" � ���������.
    // ������������ ��� �������� ���������� HUDWidget � BeginPlay.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // ��������� �� ��������� GraphWidget, ������� ����� ������ � HUDWidget.
    // �� ������������� � ��������� (��� UPROPERTY-���������), ��� ��� ���������������� � ����.
    // ������ ������ �� ������ ������� ��� ���������� ������.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    UGraphWidget* GraphWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    UGraphWidget* SpeedWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    APendulum* PendulumComponent;

    // ������ �� ��� (AActor), ������� ����� ������������� ��� ���������� �������.
    // EditAnywhere: ����� ������ � ��������� ��� Blueprints (��������, ������� ����� � ����� MovingCube).
    // BlueprintReadWrite: �������� ��� ������ � ������ � Blueprints.
    // Category = "Graph": ���������� ���������� � ��������� "Graph".
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    AActor* MovingCube;

    // ��������� ������� ���� (FVector), ����������� ��� ������ ��� ���������� ��������.
    // VisibleAnywhere: ����� � ���������, �� �� ������������.
    // BlueprintReadOnly: �������� ������ ��� ������ � Blueprints.
    // Category = "Graph": ���������� ���������� � ��������� "Graph".
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    FVector InitialCubePosition;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    FRotator InitialAngle;

    // ������ �������� ���� (��������, �� ��� Y) ������������ ��������� �������.
    // ������������ ��� �������� ������, ������� ���������� � GraphWidget ��� ���������.
    // VisibleAnywhere: ����� � ���������, �� �� ������������.
    // BlueprintReadOnly: �������� ������ ��� ������ � Blueprints.
    // Category = "Graph": ���������� ���������� � ��������� "Graph".
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    TArray<float> CubeOffsets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    TArray<float> PendulumSpeed;

    // ������������ ���������� ����� � ������� CubeOffsets, ����� ���������� ������ �������.
    // EditAnywhere: ����� ������������� � ��������� � Blueprints.
    // BlueprintReadWrite: �������� ��� ������ � ������ � Blueprints.
    // Category = "Graph": ���������� ���������� � ��������� "Graph".
    // �� ��������� ����� 50, ����� ������ �� ���������� �������.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    int32 MaxPoints = 50;
};