#include "sierrachart.h"

enum ATRDisplayValues
{
    DisplayPoints,
    DisplayTicks,
    DisplayPointsAndTicks,
};

SCSFExport scsf_ATRDisplay(SCStudyInterfaceRef sc)
{
    SCSubgraphRef Subgraph_ATR = sc.Subgraph[0];

    SCInputRef Input_HorizontalPositionFromLeft = sc.Input[0];
    SCInputRef Input_VerticalPositionFromBottom = sc.Input[1];
    SCInputRef Input_ATR_Length = sc.Input[2];
    SCInputRef Input_ReferenceBarsBack = sc.Input[3];
    SCInputRef Input_DisplayValues = sc.Input[4];
    SCInputRef Input_UseBoldFont = sc.Input[5];
    SCInputRef Input_TransparentLabelBackground = sc.Input[6];
    SCInputRef Input_DrawAboveMainPriceGraph = sc.Input[7];

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
        Subgraph_ATR.LineWidth = 20;

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

        return;
    }

    // Implementation

    // Calculate the ATR across all bars
    for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
    {
        sc.ATR(sc.BaseDataIn, Subgraph_ATR, i, Input_ATR_Length.GetInt(), MOVAVGTYPE_SIMPLE);
    }

    // Get the requested ATR value
    int index = Subgraph_ATR.Data.GetArraySize() - 1 - Input_ReferenceBarsBack.GetInt();
    float valuePoints = Subgraph_ATR[index];

    // Display text label
    ATRDisplayValues displayValues = (ATRDisplayValues) Input_DisplayValues.GetIndex();
    SCString content;
    switch (displayValues)
    {
    case DisplayPoints:
        content.Format("ATR: %.2fP", valuePoints);
        break;
    
    case DisplayTicks:
        content.Format("ATR: %dT", sc.PriceValueToTicks(valuePoints));
        break;
    
    case DisplayPointsAndTicks:
    default:
        content.Format("ATR: %.2fP, %dT", valuePoints, sc.PriceValueToTicks(valuePoints));
        break;
    }
    sc.AddAndManageSingleTextDrawingForStudy(sc, false, Input_HorizontalPositionFromLeft.GetInt(), Input_VerticalPositionFromBottom.GetInt(), Subgraph_ATR, Input_TransparentLabelBackground.GetYesNo(), content, Input_DrawAboveMainPriceGraph.GetYesNo(), Input_UseBoldFont.GetYesNo());
}
