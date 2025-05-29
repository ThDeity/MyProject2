#include "PendulumGraphWidget.h"
#include "Slate.h"
#include "Framework/Application/SlateApplication.h"

void UPendulumGraphWidget::SetAngleData(const float& val)
{
    AnglePoints.Add(val);
    UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), val); // �����������
    if (AnglePoints.Num() > 200)
        AnglePoints.RemoveAt(0);
}

void UPendulumGraphWidget::SetVelocityData(const float& val)
{
    VelocityPoints.Add(val);
    if (VelocityPoints.Num() > 100)
        VelocityPoints.RemoveAt(0); // ����������: �������� �� VelocityPoints
}

int32 UPendulumGraphWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
    int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    FVector2D WidgetSize = AllottedGeometry.GetLocalSize();
    float Width = WidgetSize.X;
    float Height = WidgetSize.Y;

    // ��������������� ���������� Padding � GraphPadding
    float GraphHeight = Height * 0.4f;
    float GraphPadding = Height * 0.05f;

    // ������ ��������� (�������)
    float AmplitudeTop = GraphPadding;
    float AmplitudeBottom = AmplitudeTop + GraphHeight;

    // ������ �������� (������)
    float VelocityTop = AmplitudeBottom + GraphPadding;
    float VelocityBottom = VelocityTop + GraphHeight;

    // ��������� ������� ���������
    /*if (AnglePoints.Num() >= 2)
    {
        TArray<FVector2D> AmplitudeLinePoints;
        for (int32 i = 0; i < AnglePoints.Num(); ++i)
        {
            float X = static_cast<float>(i) / (AnglePoints.Num() - 1) * Width;
            float Y = AmplitudeBottom - (AnglePoints[i] + 1.0f) * GraphHeight / 2.0f;
            AmplitudeLinePoints.Add(FVector2D(X, Y));
        }
        FSlateDrawElement::MakeLines(
            OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
            AmplitudeLinePoints, ESlateDrawEffect::None, AngleColor, true, LineThickness
        );
    }*/
    if (AnglePoints.Num() >= 2)
    {
        for (int32 i = 0; i < AnglePoints.Num() - 1; ++i)
        {
            float x1 = (float)i / (AnglePoints.Num() - 1) * Width;
            float x2 = (float)(i + 1) / (AnglePoints.Num() - 1) * Width;
            float y1 = Height - (AnglePoints[i] + 1.0f) * Height / 2.0f; // ������������ [-1, 1] -> [0, Height]
            float y2 = Height - (AnglePoints[i + 1] + 1.0f) * Height / 2.0f;

            FSlateDrawElement::MakeLines(
                OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
                TArray<FVector2D>{FVector2D(x1, y1), FVector2D(x2, y2)},
                ESlateDrawEffect::None, AngleColor, true, LineThickness
            );
        }
    }

    // ��������� ������� ��������
    if (VelocityPoints.Num() >= 2)
    {
        TArray<FVector2D> VelocityLinePoints;
        for (int32 i = 0; i < VelocityPoints.Num(); ++i)
        {
            float X = static_cast<float>(i) / (VelocityPoints.Num() - 1) * Width;
            float Y = VelocityBottom - (VelocityPoints[i] + 1.0f) * GraphHeight / 2.0f;
            VelocityLinePoints.Add(FVector2D(X, Y));
        }
        FSlateDrawElement::MakeLines(
            OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
            VelocityLinePoints, ESlateDrawEffect::None, VelocityColor, true, LineThickness
        );
    }

    // ��������� �������������� �����
    FSlateDrawElement::MakeLines(
        OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{ FVector2D(0, AmplitudeBottom + GraphPadding / 2), FVector2D(Width, AmplitudeBottom + GraphPadding / 2) },
        ESlateDrawEffect::None, FLinearColor::Gray, true, 1.0f
    );

    return LayerId + 1;
}