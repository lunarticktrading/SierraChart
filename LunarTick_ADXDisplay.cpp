#include "sierrachart.h"

enum ADXDisplaySubgraphs
{
    ADXSubgraphDefault,
    ADXSubgraphTrend,
    ADXSubgraphStrongTrend
};

SCSFExport scsf_LunarTick_ADXDisplay(SCStudyInterfaceRef sc)
{
    SCSubgraphRef Subgraph_ADX = sc.Subgraph[0];
    SCSubgraphRef Subgraph_Trend = sc.Subgraph[1];
    SCSubgraphRef Subgraph_StrongTrend = sc.Subgraph[2];

    SCInputRef Input_HorizontalPositionFromLeft = sc.Input[0];
    SCInputRef Input_VerticalPositionFromBottom = sc.Input[1];
    SCInputRef Input_ADX_Length = sc.Input[2];
    SCInputRef Input_ADX_Smoothing = sc.Input[3];
    SCInputRef Input_ReferenceBarsBack = sc.Input[4];
    SCInputRef Input_UseBoldFont = sc.Input[5];
    SCInputRef Input_TransparentLabelBackground = sc.Input[6];
    SCInputRef Input_DrawAboveMainPriceGraph = sc.Input[7];
    SCInputRef Input_ShowTrendWarnings = sc.Input[8];
    SCInputRef Input_TrendThreshold = sc.Input[9];
    SCInputRef Input_StrongTrendThreshold = sc.Input[10];

    if (sc.SetDefaults)
    {
        sc.GraphName = "ADX Display";
        sc.StudyDescription = "Displays the ADX value on the chart as a text label.";
        sc.GraphRegion = 0;
        sc.AutoLoop = 0;

        // Configure subgraphs

        Subgraph_ADX.Name = "ADX Display";
        Subgraph_ADX.PrimaryColor = COLOR_WHITE;
        Subgraph_ADX.SecondaryColor = COLOR_BLACK;
        Subgraph_ADX.SecondaryColorUsed = 1;
        Subgraph_ADX.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_ADX.LineWidth = 14;

        Subgraph_Trend.Name = "Trend";
        Subgraph_Trend.PrimaryColor = COLOR_WHITE;
        Subgraph_Trend.SecondaryColor = RGB(74, 20, 140);
        Subgraph_Trend.SecondaryColorUsed = 1;
        Subgraph_Trend.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_Trend.LineWidth = 14;

        Subgraph_StrongTrend.Name = "Strong Trend";
        Subgraph_StrongTrend.PrimaryColor = COLOR_WHITE;
        Subgraph_StrongTrend.SecondaryColor = RGB(156, 39, 176);
        Subgraph_StrongTrend.SecondaryColorUsed = 1;
        Subgraph_StrongTrend.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_StrongTrend.LineWidth = 14;

        // Configure inputs

        Input_HorizontalPositionFromLeft.Name = "Horizontal Position From Left (1-150)";
        Input_HorizontalPositionFromLeft.SetInt(50);
        Input_HorizontalPositionFromLeft.SetIntLimits(1, 150);

        Input_VerticalPositionFromBottom.Name = "Vertical Position From Bottom (1-100)";
        Input_VerticalPositionFromBottom.SetInt(40);
        Input_VerticalPositionFromBottom.SetIntLimits(1, 100);

        Input_ADX_Length.Name = "ADX Length";
        Input_ADX_Length.SetInt(14);
        Input_ADX_Length.SetIntLimits(1, MAX_STUDY_LENGTH);

        Input_ADX_Smoothing.Name = "ADX Smoothing";
        Input_ADX_Smoothing.SetInt(14);
        Input_ADX_Smoothing.SetIntLimits(1, MAX_STUDY_LENGTH);

        Input_ReferenceBarsBack.Name = "Reference Bars Back";
        Input_ReferenceBarsBack.SetInt(1);
        Input_ReferenceBarsBack.SetIntLimits(0, MAX_STUDY_LENGTH);

        Input_UseBoldFont.Name = "Use Bold Font";
        Input_UseBoldFont.SetYesNo(1);

        Input_TransparentLabelBackground.Name = "Transparent Label Background";
        Input_TransparentLabelBackground.SetYesNo(0);

        Input_DrawAboveMainPriceGraph.Name = "Draw Above Main Price Graph";
        Input_DrawAboveMainPriceGraph.SetYesNo(1);

        Input_ShowTrendWarnings.Name = "Show Trend Warnings";
        Input_ShowTrendWarnings.SetYesNo(0);

        Input_TrendThreshold.Name = "Trend Threshold";
        Input_TrendThreshold.SetFloat(25.0f);
        Input_TrendThreshold.SetFloatLimits(0.0f, FLT_MAX);

        Input_StrongTrendThreshold.Name = "Strong Trend Threshold";
        Input_StrongTrendThreshold.SetFloat(50.0f);
        Input_StrongTrendThreshold.SetFloatLimits(0.0f, FLT_MAX);

        return;
    }

    // Implementation

    // Calculate the ADX across all bars
    for (int i = sc.UpdateStartIndex; i < sc.ArraySize; i++)
    {
        sc.ADX(sc.BaseDataIn, Subgraph_ADX, i, Input_ADX_Length.GetInt(), Input_ADX_Smoothing.GetInt());
    }

    // Get the requested ADX value
    int index = Subgraph_ADX.Data.GetArraySize() - 1 - Input_ReferenceBarsBack.GetInt();
    float value = Subgraph_ADX[index];

    // Format text label
    SCString content;
    content.Format("ADX: %.3f", value);

    // Trend warnings
    int subgraphIndex = ADXSubgraphDefault;
    if (Input_ShowTrendWarnings.GetYesNo())
    {
        if (value > Input_StrongTrendThreshold.GetFloat())
            subgraphIndex = ADXSubgraphStrongTrend;
        else if (value > Input_TrendThreshold.GetFloat())
            subgraphIndex = ADXSubgraphTrend;
    }

    // Display text label
    sc.AddAndManageSingleTextDrawingForStudy(sc, false, Input_HorizontalPositionFromLeft.GetInt(), Input_VerticalPositionFromBottom.GetInt(), sc.Subgraph[subgraphIndex], Input_TransparentLabelBackground.GetYesNo(), content, Input_DrawAboveMainPriceGraph.GetYesNo(), Input_UseBoldFont.GetYesNo());
}
