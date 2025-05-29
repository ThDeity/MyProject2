// Предотвращает множественное включение заголовочного файла, чтобы избежать ошибок компиляции.
#pragma once

// Включает минимальный набор базовых определений Unreal Engine, необходимых для большинства классов (например, FString, TArray, FVector).
#include "CoreMinimal.h"
#include "Pendulum.h"

// Включает класс PlayerController, который является базовым для управления игроком в игре.
#include "GameFramework/PlayerController.h"

// Включает заголовочный файл GraphWidget.h, содержащий определение кастомного виджета UMG для отображения графика.
#include "GraphWidget.h"

// Автоматически генерируемый макрос Unreal Engine для включения необходимых метаданных и функций для класса.
#include "MyPlayerController.generated.h"

// Определяет класс AMyPlayerController, который наследуется от APlayerController.
// Этот класс управляет логикой игрока, включая отслеживание движения куба и обновление графика на HUD.
UCLASS()
class MYPROJECT2_API AMyPlayerController : public APlayerController
{
    // Макрос, необходимый для всех классов Unreal Engine, генерирует код для поддержки рефлексии (например, сериализация, Blueprint-совместимость).
    GENERATED_BODY()

protected:
    // Переопределяет метод BeginPlay, который вызывается при старте игры для инициализации.
    // Используется для настройки HUD и поиска куба в уровне.
    virtual void BeginPlay() override;

    // Переопределяет метод Tick, который вызывается каждый кадр.
    // Используется для обновления позиции куба и передачи данных смещения в GraphWidget.
    virtual void Tick(float DeltaTime) override;

public:
    // Ссылка на класс Blueprint-виджета HUD (например, HUDWidget).
    // EditAnywhere: Можно редактировать в редакторе и Blueprints.
    // BlueprintReadWrite: Доступна для чтения и записи в Blueprints.
    // Category = "HUD": Группирует переменную в категории "HUD" в редакторе.
    // Используется для создания экземпляра HUDWidget в BeginPlay.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // Указатель на экземпляр GraphWidget, который будет найден в HUDWidget.
    // Не редактируется в редакторе (без UPROPERTY-атрибутов), так как инициализируется в коде.
    // Хранит ссылку на виджет графика для обновления данных.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    UGraphWidget* GraphWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    UGraphWidget* SpeedWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    APendulum* PendulumComponent;

    // Ссылка на куб (AActor), который будет отслеживаться для построения графика.
    // EditAnywhere: Можно задать в редакторе или Blueprints (например, указать актор с тегом MovingCube).
    // BlueprintReadWrite: Доступна для чтения и записи в Blueprints.
    // Category = "Graph": Группирует переменную в категории "Graph".
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    AActor* MovingCube;

    // Начальная позиция куба (FVector), сохраняется при старте для вычисления смещений.
    // VisibleAnywhere: Видна в редакторе, но не редактируема.
    // BlueprintReadOnly: Доступна только для чтения в Blueprints.
    // Category = "Graph": Группирует переменную в категории "Graph".
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    FVector InitialCubePosition;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    FRotator InitialAngle;

    // Массив смещений куба (например, по оси Y) относительно начальной позиции.
    // Используется для хранения данных, которые передаются в GraphWidget для отрисовки.
    // VisibleAnywhere: Видна в редакторе, но не редактируема.
    // BlueprintReadOnly: Доступна только для чтения в Blueprints.
    // Category = "Graph": Группирует переменную в категории "Graph".
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    TArray<float> CubeOffsets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph")
    TArray<float> PendulumSpeed;

    // Максимальное количество точек в массиве CubeOffsets, чтобы ограничить размер графика.
    // EditAnywhere: Можно редактировать в редакторе и Blueprints.
    // BlueprintReadWrite: Доступна для чтения и записи в Blueprints.
    // Category = "Graph": Группирует переменную в категории "Graph".
    // По умолчанию равно 50, чтобы график не перегружал систему.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph")
    int32 MaxPoints = 50;
};