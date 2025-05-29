// �������� ������������ ���� GraphWidget.h, ���������� ����������� ������ UGraphWidget � ��� ��������.
#include "GraphWidget.h"
// �������� SlateBasics.h, ������� ������������� ������� ������� � ������ Slate ��� ��������� ����������������� ����������.
#include "SlateBasics.h"

// ���������� ������� SetDataPoints ��� ���������� ������� ����� �������.
// ��������� ����� ������ NewDataPoints � ��������� ���������� ������ �������.
void UGraphWidget::SetDataPoints(const TArray<float>& NewDataPoints)
{
    // �������� ������� ������ NewDataPoints � �������� DataPoints ������.
    DataPoints = NewDataPoints;

    // ��������� ����������� � ������������ �������� ��� ��������������� �������.
    if (DataPoints.Num() == 0)
    {
        // ���� ������ ����, ������������� ����������� � ������������ �������� � 0,
        // ����� �������� ������� �� ���� ��� ���������.
        VMin = 0.0f;
        VMax = 0.0f;
    }
    else
    {
        // �������������� VMin � VMax ������ ��������� �������.
        VMin = DataPoints[0];
        VMax = DataPoints[0];
        // �������� �� ���� ��������� � DataPoints, ����� ����� ������� � ��������.
        for (float Value : DataPoints)
        {
            // ��������� VMin, ���� ������� �������� ������ �������� ��������.
            VMin = FMath::Min(VMin, Value);
            // ��������� VMax, ���� ������� �������� ������ �������� ���������.
            VMax = FMath::Max(VMax, Value);
        }
    }
}

// ��������������� ������ NativePaint ��� ��������� ��������� �������.
// ���������� Unreal Engine ������ ���� ��� ���������� �������.
int32 UGraphWidget::NativePaint(const FPaintArgs& Args, // �������� ��������� (��������, ����� �����)
    const FGeometry& AllottedGeometry, // ��������� ������� (������ � ���������)
    const FSlateRect& MyCullingRect, // ������� ��������� ��� ����������� ����������
    FSlateWindowElementList& OutDrawElements, // ������ ��������� ��� ���������
    int32 LayerId, // ���� ���������� (������� ���������)
    const FWidgetStyle& InWidgetStyle, // ����� ������� (��������, ������������)
    bool bParentEnabled) const // ���������, ������� �� ������������ ������
{
    // ��������� ������� ���� ���������� � ���������� ��� � �����.
    int32 RetLayerId = LayerId;

    // �������� ������� ������� (������ � ������) �� ���������.
    FVector2D WidgetSize = AllottedGeometry.GetLocalSize();
    float Width = WidgetSize.X; // ������ ������� � ��������.
    float Height = WidgetSize.Y; // ������ ������� � ��������.

    // ���������, ���������� �� ����� ��� ��������� ����� (����� ������� 2 �����).
    int32 NumPoints = DataPoints.Num();
    if (NumPoints >= 2)
    {
        // ���� �� ���� ����� ���������������� ����� ��� ��������� �����.
        for (int32 i = 0; i < NumPoints - 1; ++i)
        {
            // ��������� ���������� X ��� ������� � ��������� �����.
            // X �������������� ���������� �� ������ �������.
            float x1 = (static_cast<float>(i) / (NumPoints - 1)) * Width;
            float x2 = (static_cast<float>(i + 1) / (NumPoints - 1)) * Width;

            // ��������� ���������� Y � ������ ���������������.
            float y1, y2;
            if (VMax > VMin)
            {
                // ����������� �������� DataPoints � �������� [0, Height].
                // �������: y = Height - ((DataPoints[i] - VMin) / (VMax - VMin)) * Height
                // ��� ���������� VMin ����� ������� (y = Height) � VMax ������ (y = 0).
                y1 = Height - ((DataPoints[i] - VMin) / (VMax - VMin)) * Height;
                y2 = Height - ((DataPoints[i + 1] - VMin) / (VMax - VMin)) * Height;
            }
            else
            {
                // ���� VMax == VMin (��������, ������ �������� ���������� ��������),
                // ������ ����� � �������� ������� �� ������.
                y1 = Height / 2.0f;
                y2 = Height / 2.0f;
            }

            // ������ ����� ����� ������� (x1, y1) � (x2, y2).
            // FPaintGeometry �� ������������ ��������, �� ��������� ��� ������������� � Slate.
            FPaintGeometry LineGeometry;
            FSlateDrawElement::MakeLines(
                OutDrawElements, // ������ ��������� ��� ����������
                RetLayerId, // ������� ���� ����������
                AllottedGeometry.ToPaintGeometry(), // ��������� �������������� ��� �������
                TArray<FVector2D>{FVector2D(x1, y1), FVector2D(x2, y2)}, // ���������� �����
                ESlateDrawEffect::None, // ��� �������������� �������� ����������
                LineColor, // ���� ����� (������� ��������� ������)
                true, // �������� ����������� (anti-aliasing)
                LineThickness // ������� ����� (������� ��������� ������)
            );
        }
    }

    // ��������� ���� (�����������).
    // ��� X: �������������� ����� ����� ������� (y = Height).
    FSlateDrawElement::MakeLines(
        OutDrawElements,
        RetLayerId,
        AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{FVector2D(0, Height), FVector2D(Width, Height)}, // �� (0, Height) �� (Width, Height)
        ESlateDrawEffect::None,
        FLinearColor::Gray, // ����� ���� ��� ���
        true, // �������� �����������
        1.0f // ������� ����� ���
    );

    // ��� Y: ������������ ����� ����� ������� (x = 0).
    FSlateDrawElement::MakeLines(
        OutDrawElements,
        RetLayerId,
        AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{FVector2D(0, 0), FVector2D(0, Height)}, // �� (0, 0) �� (0, Height)
        ESlateDrawEffect::None,
        FLinearColor::Gray, // ����� ���� ��� ���
        true, // �������� �����������
        1.0f // ������� ����� ���
    );

    // ���������� ������� ���� ����������.
    return RetLayerId;
}