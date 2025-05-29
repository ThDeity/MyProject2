// Включает заголовочный файл GraphWidget.h, содержащий определение класса UGraphWidget и его свойства.
#include "GraphWidget.h"
// Включает SlateBasics.h, который предоставляет базовые функции и классы Slate для отрисовки пользовательского интерфейса.
#include "SlateBasics.h"

// Реализация функции SetDataPoints для обновления массива точек графика.
// Принимает новый массив NewDataPoints и обновляет внутренние данные виджета.
void UGraphWidget::SetDataPoints(const TArray<float>& NewDataPoints)
{
    // Копирует входной массив NewDataPoints в свойство DataPoints класса.
    DataPoints = NewDataPoints;

    // Вычисляем минимальное и максимальное значения для масштабирования графика.
    if (DataPoints.Num() == 0)
    {
        // Если массив пуст, устанавливаем минимальное и максимальное значения в 0,
        // чтобы избежать деления на ноль при отрисовке.
        VMin = 0.0f;
        VMax = 0.0f;
    }
    else
    {
        // Инициализируем VMin и VMax первым элементом массива.
        VMin = DataPoints[0];
        VMax = DataPoints[0];
        // Проходим по всем значениям в DataPoints, чтобы найти минимум и максимум.
        for (float Value : DataPoints)
        {
            // Обновляем VMin, если текущее значение меньше текущего минимума.
            VMin = FMath::Min(VMin, Value);
            // Обновляем VMax, если текущее значение больше текущего максимума.
            VMax = FMath::Max(VMax, Value);
        }
    }
}

// Переопределение метода NativePaint для кастомной отрисовки графика.
// Вызывается Unreal Engine каждый кадр для рендеринга виджета.
int32 UGraphWidget::NativePaint(const FPaintArgs& Args, // Контекст рисования (например, время кадра)
    const FGeometry& AllottedGeometry, // Геометрия виджета (размер и положение)
    const FSlateRect& MyCullingRect, // Область отсечения для оптимизации рендеринга
    FSlateWindowElementList& OutDrawElements, // Список элементов для отрисовки
    int32 LayerId, // Слой рендеринга (порядок отрисовки)
    const FWidgetStyle& InWidgetStyle, // Стиль виджета (например, прозрачность)
    bool bParentEnabled) const // Указывает, активен ли родительский виджет
{
    // Сохраняем текущий слой рендеринга и возвращаем его в конце.
    int32 RetLayerId = LayerId;

    // Получаем размеры виджета (ширина и высота) из геометрии.
    FVector2D WidgetSize = AllottedGeometry.GetLocalSize();
    float Width = WidgetSize.X; // Ширина виджета в пикселях.
    float Height = WidgetSize.Y; // Высота виджета в пикселях.

    // Проверяем, достаточно ли точек для рисования линий (нужно минимум 2 точки).
    int32 NumPoints = DataPoints.Num();
    if (NumPoints >= 2)
    {
        // Цикл по всем парам последовательных точек для рисования линий.
        for (int32 i = 0; i < NumPoints - 1; ++i)
        {
            // Вычисляем координаты X для текущей и следующей точек.
            // X распределяется равномерно по ширине виджета.
            float x1 = (static_cast<float>(i) / (NumPoints - 1)) * Width;
            float x2 = (static_cast<float>(i + 1) / (NumPoints - 1)) * Width;

            // Вычисляем координаты Y с учётом масштабирования.
            float y1, y2;
            if (VMax > VMin)
            {
                // Нормализуем значения DataPoints в диапазон [0, Height].
                // Формула: y = Height - ((DataPoints[i] - VMin) / (VMax - VMin)) * Height
                // Это отображает VMin внизу виджета (y = Height) и VMax вверху (y = 0).
                y1 = Height - ((DataPoints[i] - VMin) / (VMax - VMin)) * Height;
                y2 = Height - ((DataPoints[i + 1] - VMin) / (VMax - VMin)) * Height;
            }
            else
            {
                // Если VMax == VMin (например, массив содержит одинаковые значения),
                // рисуем линию в середине виджета по высоте.
                y1 = Height / 2.0f;
                y2 = Height / 2.0f;
            }

            // Рисуем линию между точками (x1, y1) и (x2, y2).
            // FPaintGeometry не используется напрямую, но требуется для совместимости с Slate.
            FPaintGeometry LineGeometry;
            FSlateDrawElement::MakeLines(
                OutDrawElements, // Список элементов для рендеринга
                RetLayerId, // Текущий слой рендеринга
                AllottedGeometry.ToPaintGeometry(), // Геометрия преобразования для виджета
                TArray<FVector2D>{FVector2D(x1, y1), FVector2D(x2, y2)}, // Координаты линии
                ESlateDrawEffect::None, // Без дополнительных эффектов рендеринга
                LineColor, // Цвет линии (задаётся свойством класса)
                true, // Включить сглаживание (anti-aliasing)
                LineThickness // Толщина линии (задаётся свойством класса)
            );
        }
    }

    // Отрисовка осей (опционально).
    // Ось X: горизонтальная линия внизу виджета (y = Height).
    FSlateDrawElement::MakeLines(
        OutDrawElements,
        RetLayerId,
        AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{FVector2D(0, Height), FVector2D(Width, Height)}, // От (0, Height) до (Width, Height)
        ESlateDrawEffect::None,
        FLinearColor::Gray, // Серый цвет для оси
        true, // Включить сглаживание
        1.0f // Толщина линии оси
    );

    // Ось Y: вертикальная линия слева виджета (x = 0).
    FSlateDrawElement::MakeLines(
        OutDrawElements,
        RetLayerId,
        AllottedGeometry.ToPaintGeometry(),
        TArray<FVector2D>{FVector2D(0, 0), FVector2D(0, Height)}, // От (0, 0) до (0, Height)
        ESlateDrawEffect::None,
        FLinearColor::Gray, // Серый цвет для оси
        true, // Включить сглаживание
        1.0f // Толщина линии оси
    );

    // Возвращаем текущий слой рендеринга.
    return RetLayerId;
}