// Fill out your copyright notice in the Description page of Project Settings.

// Предотвращает множественное включение заголовочного файла, чтобы избежать ошибок компиляции.
#pragma once

// Включает минимальный набор базовых определений Unreal Engine, необходимых для большинства классов (например, FString, TArray).
#include "CoreMinimal.h"

// Включает класс UUserWidget, который является базовым для создания пользовательских интерфейсов в UMG (Unreal Motion Graphics).
#include "Blueprint/UserWidget.h"

// Автоматически генерируемый макрос Unreal Engine для включения необходимых метаданных и функций для класса.
#include "GraphWidget.generated.h"

// Определяет класс UGraphWidget, который наследуется от UUserWidget и используется для кастомного виджета UMG.
UCLASS()
class MYPROJECT2_API UGraphWidget : public UUserWidget
{
    // Макрос, необходимый для всех классов Unreal Engine, генерирует код для поддержки рефлексии (например, сериализация, Blueprint-совместимость).
    GENERATED_BODY()

public:
    // Объявляет функцию SetDataPoints, доступную из Blueprints, для установки массива точек данных графика.
    // UFUNCTION(BlueprintCallable) делает функцию вызываемой из Blueprints.
    // Category = "Graph" группирует функцию в категории "Graph" в редакторе Blueprint.
    UFUNCTION(BlueprintCallable, Category = "Graph")
    void SetDataPoints(const TArray<float>& NewDataPoints);

protected:
    // Переопределяет виртуальный метод NativePaint, который вызывается для кастомной отрисовки виджета в Slate.
    // Используется для рисования линий графика на основе массива DataPoints.
    // Параметры:
    // - Args: Информация о контексте рисования (например, время кадра).
    // - AllottedGeometry: Геометрия виджета (размер и положение).
    // - MyCullingRect: Область отсечения для оптимизации рендеринга.
    // - OutDrawElements: Список элементов для отрисовки.
    // - LayerId: Слой рендеринга (порядок отрисовки).
    // - InWidgetStyle: Стиль виджета (например, прозрачность).
    // - bParentEnabled: Указывает, включён ли родительский виджет.
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
        FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
        bool bParentEnabled) const override;

private:
    // Массив точек данных для графика (значения Y для каждой точки).
    // UPROPERTY делает переменную видимой в редакторе Unreal и Blueprint.
    // VisibleAnywhere: Переменная видна в редакторе, но не редактируема.
    // BlueprintReadOnly: Доступна для чтения в Blueprints.
    // Category = "Graph": Группирует переменную в категории "Graph".
    // meta = (AllowPrivateAccess = "true"): Позволяет доступ из Blueprints, несмотря на private секцию.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    TArray<float> DataPoints;

    // Минимальное значение в массиве DataPoints, используется для масштабирования графика.
    // Хранит нижнюю границу значений Y для нормализации.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float VMin;

    // Максимальное значение в массиве DataPoints, используется для масштабирования графика.
    // Хранит верхнюю границу значений Y для нормализации.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float VMax;

    // Цвет линий графика.
    // EditAnywhere: Можно редактировать в редакторе и Blueprints.
    // BlueprintReadWrite: Доступна для чтения и записи в Blueprints.
    // По умолчанию белый цвет (FLinearColor::White).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    FLinearColor LineColor = FLinearColor::White;

    // Толщина линий графика (в пикселях).
    // EditAnywhere: Можно редактировать в редакторе и Blueprints.
    // BlueprintReadWrite: Доступна для чтения и записи в Blueprints.
    // По умолчанию 1.0 пиксель.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float LineThickness = 1.0f;
};