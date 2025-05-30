#include "Pendulum.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

APendulum::APendulum()
{
    PrimaryActorTick.bCanEverTick = true;

    // ������� ����� �������
    PivotPoint = CreateDefaultSubobject<USceneComponent>("PivotPoint");
    RootComponent = PivotPoint;

    // ������� ��� ����
    StringMesh = CreateDefaultSubobject<UStaticMeshComponent>("StringMesh");
    StringMesh->SetupAttachment(PivotPoint);

    // ��������� ��� ��� ����
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        StringMesh->SetStaticMesh(CubeMesh.Object);
    }

    // ������� ��� ������
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
    BallMesh->SetupAttachment(PivotPoint);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
    if (SphereMesh.Succeeded())
    {
        BallMesh->SetStaticMesh(SphereMesh.Object);
    }

    if (GraphWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("HEHEHEHEHEHE"));
        // Очищаем массив CubeOffsets перед началом, чтобы начать с пустого графика.
        PendulumSpeeds.Empty();
        // Передаём пустой массив в GraphWidget для инициализации.
        GraphWidget->SetDataPoints(PendulumSpeeds);
    }
}

void APendulum::ResetSimulation()
{
    CurrentAngle = InitialAngle;
    AngularVelocity = 0.0f;
}

void APendulum::SetPendulumLength(float NewLength)
{
    PendulumLength = FMath::Max(50.f, NewLength); // Ограничение минимум 50 единиц

    // Обновляем визуальные компоненты
    if (BallMesh && StringMesh)
    {
        BallMesh->SetRelativeLocation(FVector(0, 0, -PendulumLength));
        StringMesh->SetRelativeScale3D(FVector(
            StringThickness / 50.f,
            StringThickness / 50.f,
            PendulumLength / 100.f  // Масштабируем по Z
        ));
        StringMesh->SetRelativeLocation(FVector(0, 0, -PendulumLength / 2));
    }

    ResetSimulation(); // Перезапускаем симуляцию
}

void APendulum::BeginPlay()
{
    Super::BeginPlay();

    CurrentAngle = InitialAngle;

    // ��������� ����
    StringMesh->SetRelativeScale3D(FVector(StringThickness / 50.f, StringThickness / 50.f, PendulumLength / 100.f));
    StringMesh->SetRelativeLocation(FVector(0, 0, -PendulumLength / 2));

    // ��������� ������
    BallMesh->SetRelativeScale3D(FVector(0.5f));
    BallMesh->SetRelativeLocation(FVector(0, 0, -PendulumLength));
}

void APendulum::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Физика маятника с "умным" затуханием
    float AngularAcceleration = -(Gravity / PendulumLength) * FMath::Sin(CurrentAngle);

    // Добавляем затухание, пропорциональное скорости
    AngularVelocity += AngularAcceleration * DeltaTime;
    AngularVelocity *= (1.0f - DampingFactor * FMath::Abs(FMath::Sin(CurrentAngle)));

    // Коррекция для остановки в нулевой точке
    if (FMath::Abs(AngularVelocity) < 0.001f && FMath::Abs(CurrentAngle) < 0.05f)
    {
        AngularVelocity = 0.f;
        //CurrentAngle = 0.f;
        CurrentAngle = FMath::FInterpTo(CurrentAngle, 0.f, DeltaTime, 2.0f);
    }
    else
    {
        CurrentAngle += AngularVelocity * DeltaTime;
    }

    if (GraphWidget)
    {
        PendulumSpeeds.Add(AngularVelocity);
        if (PendulumSpeeds.Num() > MaxPoints)
            PendulumSpeeds.RemoveAt(0);

        if (GraphWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("AngularVelocity: %f"), AngularVelocity);
            GraphWidget->SetDataPoints(PendulumSpeeds);
        }
    }

    PivotPoint->SetRelativeRotation(FRotator(0, 0, FMath::RadiansToDegrees(CurrentAngle)));
}