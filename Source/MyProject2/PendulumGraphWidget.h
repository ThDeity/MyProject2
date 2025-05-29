#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PendulumGraphWidget.generated.h"

UCLASS()
class   MYPROJECT2_API UPendulumGraphWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // ������������� ������ ��� ������� ��������� (����)
    UFUNCTION(BlueprintCallable, Category = "Pendulum Graph")
    void SetAngleData(const float& val);

    // ������������� ������ ��� ������� ��������
    UFUNCTION(BlueprintCallable, Category = "Pendulum Graph")
    void SetVelocityData(const float& val);

protected:
    // �������������� ���������
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
        int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
    // ������ ��� ��������
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pendulum Graph", meta = (AllowPrivateAccess = "true"))
    TArray<float> AnglePoints;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pendulum Graph", meta = (AllowPrivateAccess = "true"))
    TArray<float> VelocityPoints;

    // ��������� ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Graph", meta = (AllowPrivateAccess = "true"))
    FLinearColor AngleColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Graph", meta = (AllowPrivateAccess = "true"))
    FLinearColor VelocityColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pendulum Graph", meta = (AllowPrivateAccess = "true"))
    float LineThickness = 2.0f;
};