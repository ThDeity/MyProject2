// Включает заголовочный файл MyPlayerController.h, содержащий определение класса AMyPlayerController и его свойства.
#include "MyPlayerController.h"

// Включает класс UUserWidget для работы с виджетами пользовательского интерфейса (UMG) в Unreal Engine.
#include "Blueprint/UserWidget.h"

// Включает класс UWorld для доступа к игровому миру (например, для получения времени или поиска акторов).
#include "Engine/World.h"

// Включает класс AActor, который является базовым классом для всех акторов в игре, включая MovingCube.
#include "GameFramework/Actor.h"

// Включает GameplayStatics для использования утилит, таких как поиск акторов по тегу или классу.
#include <Kismet/GameplayStatics.h>

// Реализация метода BeginPlay, вызываемого при старте игры для инициализации логики контроллера игрока.
void AMyPlayerController::BeginPlay()
{
    // Вызывает родительскую реализацию BeginPlay для выполнения стандартной инициализации PlayerController.
    Super::BeginPlay();

    // Пытаемся найти куб по классу AActor (начальная попытка, которая здесь не используется корректно).
    // Примечание: Эта строка избыточна, так как далее используется поиск по тегу.
    //MovingCube = UGameplayStatics::GetActorOfClass(GetWorld(), AActor::StaticClass());

    // Создаём массив для хранения акторов, найденных по тегу.
    TArray<AActor*> FoundActors;
    // Ищем все акторы в мире с тегом "MovingCube".
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Pendulum"), FoundActors);

    // Проверяем, найден ли хотя бы один актор с тегом "MovingCube".
    if (FoundActors.Num() > 0)
    {
        // Устанавливаем MovingCube как первый найденный актор.
        MovingCube = FoundActors[0];
        // Сохраняем начальную позицию куба для последующего вычисления смещений.
        InitialCubePosition = MovingCube->GetActorLocation();
        InitialAngle = MovingCube->GetActorRotation();
    }

    if (GraphWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("HEHEHEHEHEHE"));
        // Очищаем массив CubeOffsets перед началом, чтобы начать с пустого графика.
        CubeOffsets.Empty();
        // Передаём пустой массив в GraphWidget для инициализации.
        GraphWidget->SetDataPoints(CubeOffsets);
    }
}

// Реализация метода Tick, выз—weемого каждый кадр для обновления логики.
void AMyPlayerController::Tick(float DeltaTime)
{
    // Вызывает родительскую реализацию Tick для выполнения стандартной логики PlayerController.
    Super::Tick(DeltaTime);

    // Проверяем, существует ли куб (MovingCube) для отслеживания.
    if (MovingCube)
    {
        // Получаем текущее игровое время (в секундах) для синусоидального движения.
        float Time = GetWorld()->GetTimeSeconds();
        // Копируем начальную позицию куба, чтобы вычислить новую позицию.
        FVector NewLocation = InitialCubePosition;
        // Добавляем синусоидальное смещение по оси Y (±100 единиц) на основе времени.
        //NewLocation.Y += FMath::Sin(Time) * 100.0f;
        
        // Устанавливаем новую позицию куба в мире.
        //MovingCube->SetActorLocation(NewLocation);

        // Вычисляем смещение по оси Y относительно начальной позиции.
        float Offset = NewLocation.Y - InitialCubePosition.Y;

        // Получаем текущий Pitch (ось X)
        float CurrentPitch = MovingCube->GetActorRotation().Roll;
        // Вычисляем разницу с учётом кругового характера углов
        float Difference = FMath::FindDeltaAngleDegrees(InitialAngle.Roll, CurrentPitch);

        // Добавляем смещение в массив CubeOffsets для построения графика.
        CubeOffsets.Add(Difference);
        /*UE_LOG(LogTemp, Warning, TEXT("X: %f"), CurrentPitch);
        UE_LOG(LogTemp, Warning, TEXT("Y: %f"), MovingCube->GetActorRotation().Yaw);
        UE_LOG(LogTemp, Warning, TEXT("Z: %f"), MovingCube->GetActorRotation().Roll);
        UE_LOG(LogTemp, Warning, TEXT("DifferInitialAngle.Pitch: %f"), InitialAngle.Roll)*/

        // Ограничиваем размер массива CubeOffsets, чтобы избежать переполнения.
        // Если количество точек превышает MaxPoints, удаляем самую старую точку.
        if (CubeOffsets.Num() > MaxPoints)
        {
            CubeOffsets.RemoveAt(0);
        }

        // Проверяем, существует ли GraphWidget для обновления графика.
        if (GraphWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Difference.Pitch: %f"), Difference);
            // Передаём текущий массив CubeOffsets в GraphWidget для отрисовки графика.
            GraphWidget->SetDataPoints(CubeOffsets);
        }
    }
}