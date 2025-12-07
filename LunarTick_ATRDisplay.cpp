#include "sierrachart.h"

enum ATRDisplayValues
{
    DisplayPoints,
    DisplayTicks,
    DisplayPointsAndTicks,
};

enum ATRDisplaySubgraphs
{
    ATRSubgraphDefault,
    ATRSubgraphLowVolatility,
    ATRSubgraphHighVolatility,
    ATRSubgraphExtremeVolatility
};

SCSFExport scsf_ATRDisplay(SCStudyInterfaceRef sc)
{
    SCSubgraphRef Subgraph_ATR = sc.Subgraph[0];
    SCSubgraphRef Subgraph_LowVolatility = sc.Subgraph[1];
    SCSubgraphRef Subgraph_HighVolatility = sc.Subgraph[2];
    SCSubgraphRef Subgraph_ExtremeVolatility = sc.Subgraph[3];

    SCInputRef Input_HorizontalPositionFromLeft = sc.Input[0];
    SCInputRef Input_VerticalPositionFromBottom = sc.Input[1];
    SCInputRef Input_ATR_Length = sc.Input[2];
    SCInputRef Input_ReferenceBarsBack = sc.Input[3];
    SCInputRef Input_DisplayValues = sc.Input[4];
    SCInputRef Input_UseBoldFont = sc.Input[5];
    SCInputRef Input_TransparentLabelBackground = sc.Input[6];
    SCInputRef Input_DrawAboveMainPriceGraph = sc.Input[7];
    SCInputRef Input_ShowVolatilityWarnings = sc.Input[8];
    SCInputRef Input_LowVolatilityThreshold = sc.Input[9];
    SCInputRef Input_HighVolatilityThreshold = sc.Input[10];
    SCInputRef Input_ExtremeVolatilityThreshold = sc.Input[11];

    if (sc.SetDefaults)
    {
        sc.GraphName = "ATR Display";
        sc.StudyDescription = "Displays the ATR value on the chart as a text label.";
        sc.GraphRegion = 0;
        sc.AutoLoop = 0;

        // Configure subgraphs

        Subgraph_ATR.Name = "ATR Display";
        Subgraph_ATR.PrimaryColor = COLOR_WHITE;
        Subgraph_ATR.SecondaryColor = COLOR_BLACK;
        Subgraph_ATR.SecondaryColorUsed = 1;
        Subgraph_ATR.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_ATR.LineWidth = 14;

        Subgraph_LowVolatility.Name = "Low Volatility";
        Subgraph_LowVolatility.PrimaryColor = COLOR_GRAY;
        Subgraph_LowVolatility.SecondaryColor = COLOR_BLACK;
        Subgraph_LowVolatility.SecondaryColorUsed = 1;
        Subgraph_LowVolatility.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_LowVolatility.LineWidth = 14;

        Subgraph_HighVolatility.Name = "High Volatility";
        Subgraph_HighVolatility.PrimaryColor = COLOR_RED;
        Subgraph_HighVolatility.SecondaryColor = COLOR_YELLOW;
        Subgraph_HighVolatility.SecondaryColorUsed = 1;
        Subgraph_HighVolatility.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_HighVolatility.LineWidth = 14;

        Subgraph_ExtremeVolatility.Name = "Extreme Volatility";
        Subgraph_ExtremeVolatility.PrimaryColor = COLOR_YELLOW;
        Subgraph_ExtremeVolatility.SecondaryColor = COLOR_RED;
        Subgraph_ExtremeVolatility.SecondaryColorUsed = 1;
        Subgraph_ExtremeVolatility.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_ExtremeVolatility.LineWidth = 14;

        // Configure inputs

        Input_HorizontalPositionFromLeft.Name = "Horizontal Position From Left (1-150)";
        Input_HorizontalPositionFromLeft.SetInt(50);
        Input_HorizontalPositionFromLeft.SetIntLimits(1, 150);

        Input_VerticalPositionFromBottom.Name = "Vertical Position From Bottom (1-100)";
        Input_VerticalPositionFromBottom.SetInt(50);
        Input_VerticalPositionFromBottom.SetIntLimits(1, 100);

        Input_ATR_Length.Name = "ATR Length";
        Input_ATR_Length.SetInt(14);
        Input_ATR_Length.SetIntLimits(1, MAX_STUDY_LENGTH);

        Input_ReferenceBarsBack.Name = "Reference Bars Back";
        Input_ReferenceBarsBack.SetInt(1);
        Input_ReferenceBarsBack.SetIntLimits(0, MAX_STUDY_LENGTH);

        Input_DisplayValues.Name = "Display Values";
        Input_DisplayValues.SetCustomInputStrings("Points;Ticks;Points & Ticks");
        Input_DisplayValues.SetCustomInputIndex(2);

        Input_UseBoldFont.Name = "Use Bold Font";
        Input_UseBoldFont.SetYesNo(1);

        Input_TransparentLabelBackground.Name = "Transparent Label Background";
        Input_TransparentLabelBackground.SetYesNo(0);

        Input_DrawAboveMainPriceGraph.Name = "Draw Above Main Price Graph";
        Input_DrawAboveMainPriceGraph.SetYesNo(1);

        Input_ShowVolatilityWarnings.Name = "Show Volatility Warnings";
        Input_ShowVolatilityWarnings.SetYesNo(0);

        Input_LowVolatilityThreshold.Name = "Low Volatility Threshold";
        Input_LowVolatilityThreshold.SetFloat(10);
        Input_LowVolatilityThreshold.SetFloatLimits(0, FLT_MAX);

        Input_HighVolatilityThreshold.Name = "High Volatility Threshold";
        Input_HighVolatilityThreshold.SetFloat(30);
        Input_HighVolatilityThreshold.SetFloatLimits(0, FLT_MAX);

        Input_ExtremeVolatilityThreshold.Name = "Extreme Volatility Threshold";
        Input_ExtremeVolatilityThreshold.SetFloat(50);
        Input_ExtremeVolatilityThreshold.SetFloatLimits(0, FLT_MAX);

        return;
    }

    // Implementation

    SCString& lastChartSymbol = sc.GetPersistentSCString(0);
    int& symbolDecimalPlaces = sc.GetPersistentIntFast(0);
    if (lastChartSymbol.IsEmpty() || lastChartSymbol.Compare(sc.Symbol) != 0)
    {
        lastChartSymbol = sc.Symbol;
        symbolDecimalPlaces = 0;

        float tickSize = sc.TickSize;

        // Check if we have any decimal places
        if (tickSize > floor(tickSize))
        {
            SCString tickSizeString;
            tickSizeString.Format("%g", tickSize);
            auto dotIndex = tickSizeString.IndexOf('.', 0);
            symbolDecimalPlaces = (dotIndex >= 0) ? (tickSizeString.GetLength() - dotIndex - 1) : 0;
        }

        SCString message;
        message.Format("Symbol [%s], tickSize [%g], decimal places [%d]", sc.Symbol.GetChars(), tickSize, symbolDecimalPlaces);
        sc.AddMessageToLog(message, 0);
    }

    // Calculate the ATR across all bars
    for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
    {
        sc.ATR(sc.BaseDataIn, Subgraph_ATR, i, Input_ATR_Length.GetInt(), MOVAVGTYPE_SIMPLE);
    }

    // Get the requested ATR value
    int index = Subgraph_ATR.Data.GetArraySize() - 1 - Input_ReferenceBarsBack.GetInt();
    float valuePoints = Subgraph_ATR[index];

    // Format text label
    ATRDisplayValues displayValues = (ATRDisplayValues) Input_DisplayValues.GetIndex();
    SCString content;
    switch (displayValues)
    {
    case DisplayPoints:
        content.Format("ATR: %.*fP", symbolDecimalPlaces, valuePoints);
        break;
    
    case DisplayTicks:
        content.Format("ATR: %dT", sc.PriceValueToTicks(valuePoints));
        break;
    
    case DisplayPointsAndTicks:
    default:
        content.Format("ATR: %.*fP, %dT", symbolDecimalPlaces, valuePoints, sc.PriceValueToTicks(valuePoints));
        break;
    }

    // Volatility warnings
    int subgraphIndex = ATRSubgraphDefault;
    if (Input_ShowVolatilityWarnings.GetYesNo())
    {
        if (valuePoints > Input_ExtremeVolatilityThreshold.GetFloat())
            subgraphIndex = ATRSubgraphExtremeVolatility;
        else if (valuePoints > Input_HighVolatilityThreshold.GetFloat())
            subgraphIndex = ATRSubgraphHighVolatility;
        else if (valuePoints < Input_LowVolatilityThreshold.GetFloat())
            subgraphIndex = ATRSubgraphLowVolatility;
    }

    // Display text label
    sc.AddAndManageSingleTextDrawingForStudy(sc, false, Input_HorizontalPositionFromLeft.GetInt(), Input_VerticalPositionFromBottom.GetInt(), sc.Subgraph[subgraphIndex], Input_TransparentLabelBackground.GetYesNo(), content, Input_DrawAboveMainPriceGraph.GetYesNo(), Input_UseBoldFont.GetYesNo());
}
