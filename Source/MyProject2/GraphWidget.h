// Fill out your copyright notice in the Description page of Project Settings.

// ������������� ������������� ��������� ������������� �����, ����� �������� ������ ����������.
#pragma once

// �������� ����������� ����� ������� ����������� Unreal Engine, ����������� ��� ����������� ������� (��������, FString, TArray).
#include "CoreMinimal.h"

// �������� ����� UUserWidget, ������� �������� ������� ��� �������� ���������������� ����������� � UMG (Unreal Motion Graphics).
#include "Blueprint/UserWidget.h"

// ������������� ������������ ������ Unreal Engine ��� ��������� ����������� ���������� � ������� ��� ������.
#include "GraphWidget.generated.h"

// ���������� ����� UGraphWidget, ������� ����������� �� UUserWidget � ������������ ��� ���������� ������� UMG.
UCLASS()
class MYPROJECT2_API UGraphWidget : public UUserWidget
{
    // ������, ����������� ��� ���� ������� Unreal Engine, ���������� ��� ��� ��������� ��������� (��������, ������������, Blueprint-�������������).
    GENERATED_BODY()

public:
    // ��������� ������� SetDataPoints, ��������� �� Blueprints, ��� ��������� ������� ����� ������ �������.
    // UFUNCTION(BlueprintCallable) ������ ������� ���������� �� Blueprints.
    // Category = "Graph" ���������� ������� � ��������� "Graph" � ��������� Blueprint.
    UFUNCTION(BlueprintCallable, Category = "Graph")
    void SetDataPoints(const TArray<float>& NewDataPoints);

protected:
    // �������������� ����������� ����� NativePaint, ������� ���������� ��� ��������� ��������� ������� � Slate.
    // ������������ ��� ��������� ����� ������� �� ������ ������� DataPoints.
    // ���������:
    // - Args: ���������� � ��������� ��������� (��������, ����� �����).
    // - AllottedGeometry: ��������� ������� (������ � ���������).
    // - MyCullingRect: ������� ��������� ��� ����������� ����������.
    // - OutDrawElements: ������ ��������� ��� ���������.
    // - LayerId: ���� ���������� (������� ���������).
    // - InWidgetStyle: ����� ������� (��������, ������������).
    // - bParentEnabled: ���������, ������� �� ������������ ������.
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
        FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
        bool bParentEnabled) const override;

private:
    // ������ ����� ������ ��� ������� (�������� Y ��� ������ �����).
    // UPROPERTY ������ ���������� ������� � ��������� Unreal � Blueprint.
    // VisibleAnywhere: ���������� ����� � ���������, �� �� ������������.
    // BlueprintReadOnly: �������� ��� ������ � Blueprints.
    // Category = "Graph": ���������� ���������� � ��������� "Graph".
    // meta = (AllowPrivateAccess = "true"): ��������� ������ �� Blueprints, �������� �� private ������.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    TArray<float> DataPoints;

    // ����������� �������� � ������� DataPoints, ������������ ��� ��������������� �������.
    // ������ ������ ������� �������� Y ��� ������������.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float VMin;

    // ������������ �������� � ������� DataPoints, ������������ ��� ��������������� �������.
    // ������ ������� ������� �������� Y ��� ������������.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float VMax;

    // ���� ����� �������.
    // EditAnywhere: ����� ������������� � ��������� � Blueprints.
    // BlueprintReadWrite: �������� ��� ������ � ������ � Blueprints.
    // �� ��������� ����� ���� (FLinearColor::White).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    FLinearColor LineColor = FLinearColor::White;

    // ������� ����� ������� (� ��������).
    // EditAnywhere: ����� ������������� � ��������� � Blueprints.
    // BlueprintReadWrite: �������� ��� ������ � ������ � Blueprints.
    // �� ��������� 1.0 �������.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph", meta = (AllowPrivateAccess = "true"))
    float LineThickness = 1.0f;
};