#include "PendulumGraphWidget.h"
#include "Slate.h"
#include "Framework/Application/SlateApplication.h"

void UPendulumGraphWidget::SetAngleData(const float& val)
{
    AnglePoints.Add(val);
    UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), val); // Логирование
    if (AnglePoints.Num() > 500)
        AnglePoints.RemoveAt(0);
}

void UPendulumGraphWidget::SetVelocityData(const float& val)
{
    VelocityPoints.Add(val);
    if (VelocityPoints.Num() > 100)
        VelocityPoints.RemoveAt(0); // Исправлено: удаление из VelocityPoints
}

int32 UPendulumGraphWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
    int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    /*FVector2D WidgetSize = AllottedGeometry.GetLocalSize();
    float Width = WidgetSize.X;
    float Height = WidgetSize.Y;

    // Разделение виджета на две области
    float GraphHeight = Height * 0.4f;
    float GraphPadding = Height * 0.05f;

    // График амплитуды (верхний)
    float AmplitudeTop = GraphPadding;
    float AmplitudeBottom = AmplitudeTop + GraphHeight;

    // График скорости (нижний)
    float VelocityTop = AmplitudeBottom + GraphPadding;
    float VelocityBottom = VelocityTop + GraphHeight;

    // Отрисовка графика смещения (амплитуды)
    if (AnglePoints.Num() >= 2)
    {
        // 1. Защита от деления на ноль
        float MaxValue = 1.0f;
        bool bFoundValues = false;

        // 2. Находим реальный максимум
        for (const float& val : AnglePoints)
        {
            if (!FMath::IsNaN(val))
            {
                float absVal = FMath::Abs(val);
                if (absVal > MaxValue || !bFoundValues)
                {
                    MaxValue = absVal;
                    bFoundValues = true;
                }
            }
        }

        // 3. Гарантируем минимальный масштаб
        MaxValue = FMath::Max(MaxValue * 1.2f, 10.0f); // Минимум 10 единиц

        TArray<FVector2D> LinePoints;
        LinePoints.Reserve(AnglePoints.Num());

        // 4. Защита от некорректных значений
        const int32 NumPoints = AnglePoints.Num();
        for (int32 i = 0; i < NumPoints; ++i)
        {
            if (FMath::IsNaN(AnglePoints[i])) continue;

            float X = static_cast<float>(i) / FMath::Max(1, NumPoints - 1) * Width;

            // 5. Безопасная нормализация
            float NormalizedY = (AnglePoints[i] + MaxValue) / (2 * MaxValue);
            NormalizedY = FMath::Clamp(NormalizedY, 0.0f, 1.0f);

            float Y = AmplitudeBottom - NormalizedY * GraphHeight;
            LinePoints.Add(FVector2D(X, Y));
        }

        // 6. Рисуем только если есть валидные точки
        if (LinePoints.Num() >= 2)
        {
            FSlateDrawElement::MakeLines(
                OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
                LinePoints, ESlateDrawEffect::None, AngleColor, true, LineThickness
            );
        }
    }

    // Отрисовка графика скорости (оставляем без изменений)
    if (VelocityPoints.Num() >= 2)
    {
        const float MinVelocity = -3.0f;
        const float MaxVelocity = 3.0f;

        for (int32 i = 0; i < VelocityPoints.Num() - 1; ++i)
        {
            float x1 = static_cast<float>(i) / (VelocityPoints.Num() - 1) * Width;
            float x2 = static_cast<float>(i + 1) / (VelocityPoints.Num() - 1) * Width;

            // Нормализация скорости
            float normalizedY1 = (VelocityPoints[i] - MinVelocity) / (MaxVelocity - MinVelocity);
            normalizedY1 = FMath::Clamp(normalizedY1, 0.0f, 1.0f);
            float y1 = VelocityBottom - normalizedY1 * GraphHeight;

            float normalizedY2 = (VelocityPoints[i + 1] - MinVelocity) / (MaxVelocity - MinVelocity);
            normalizedY2 = FMath::Clamp(normalizedY2, 0.0f, 1.0f);
            float y2 = VelocityBottom - normalizedY2 * GraphHeight;

            FSlateDrawElement::MakeLines(
                OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
                TArray<FVector2D>{FVector2D(x1, y1), FVector2D(x2, y2)},
                ESlateDrawEffect::None, VelocityColor, true, LineThickness
            );
        }
    }

    // Отрисовка разделительной линии
    FSlateDrawElement::MakeLines(
        OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{ FVector2D(0, AmplitudeBottom + GraphPadding / 2), FVector2D(Width, AmplitudeBottom + GraphPadding / 2) },
        ESlateDrawEffect::None, FLinearColor::Gray, true, 1.0f
    );*/

    return LayerId + 1;
}