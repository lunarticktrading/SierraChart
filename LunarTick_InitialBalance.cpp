#include "sierrachart.h"

SCSFExport scsf_LunarTick_InitialBalance(SCStudyInterfaceRef sc)
{
	SCSubgraphRef Subgraph_IBHExt6  = sc.Subgraph[0];
	SCSubgraphRef Subgraph_IBHExt5  = sc.Subgraph[1];
	SCSubgraphRef Subgraph_IBHExt4  = sc.Subgraph[2];
	SCSubgraphRef Subgraph_IBHExt3  = sc.Subgraph[3];
	SCSubgraphRef Subgraph_IBHExt2  = sc.Subgraph[4];
	SCSubgraphRef Subgraph_IBHExt1  = sc.Subgraph[5];
	SCSubgraphRef Subgraph_IBHigh   = sc.Subgraph[6];
	SCSubgraphRef Subgraph_IBMid    = sc.Subgraph[7];
	SCSubgraphRef Subgraph_IBLow    = sc.Subgraph[8];
	SCSubgraphRef Subgraph_IBLExt1  = sc.Subgraph[9];
	SCSubgraphRef Subgraph_IBLExt2  = sc.Subgraph[10];
	SCSubgraphRef Subgraph_IBLExt3  = sc.Subgraph[11];
	SCSubgraphRef Subgraph_IBLExt4  = sc.Subgraph[12];
	SCSubgraphRef Subgraph_IBLExt5  = sc.Subgraph[13];
	SCSubgraphRef Subgraph_IBLExt6  = sc.Subgraph[14];
	SCSubgraphRef Subgraph_IBRegionTop		= sc.Subgraph[15];
	SCSubgraphRef Subgraph_IBRegionBottom	= sc.Subgraph[16];

	SCInputRef Input_IBType      = sc.Input[0];
	SCInputRef Input_StartTime   = sc.Input[1];
	SCInputRef Input_EndTime     = sc.Input[2];
	SCInputRef Input_NumDays     = sc.Input[3];
	SCInputRef Input_RoundExt    = sc.Input[4];
	SCInputRef Input_NumberDaysToCalculate = sc.Input[5];
	SCInputRef Input_NumberOfMinutes      = sc.Input[6];
	SCInputRef Input_StartEndTimeMethod = sc.Input[7];
	SCInputRef Input_PeriodEndAsMinutesFromSessionStart = sc.Input[8];

	SCInputRef Input_Multiplier1 = sc.Input[10];
	SCInputRef Input_Multiplier2 = sc.Input[11];
	SCInputRef Input_Multiplier3 = sc.Input[12];
	SCInputRef Input_Multiplier4 = sc.Input[13];
	SCInputRef Input_Multiplier5 = sc.Input[14];
	SCInputRef Input_Multiplier6 = sc.Input[15];

	if (sc.SetDefaults)
	{
		sc.GraphName		= "Initial Balance";
		sc.DrawZeros		= 0;
		sc.GraphRegion		= 0;
		sc.AutoLoop			= 1;

		sc.ScaleRangeType = SCALE_SAMEASREGION;
		sc.DrawStudyUnderneathMainPriceGraph = 1;

		Subgraph_IBHExt6.Name = "IB High Ext 3";
		Subgraph_IBHExt6.PrimaryColor = RGB(0, 255, 0);
		Subgraph_IBHExt6.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBHExt6.DrawZeros = false;

		Subgraph_IBHExt5.Name = "IB High 50%";
		Subgraph_IBHExt5.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBHExt5.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBHExt5.LineStyle = LINESTYLE_DASH;
		Subgraph_IBHExt5.DrawZeros = false;

		Subgraph_IBHExt4.Name = "IB High Ext 2";
		Subgraph_IBHExt4.PrimaryColor = RGB(0, 255, 0);
		Subgraph_IBHExt4.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBHExt4.DrawZeros = false;

		Subgraph_IBHExt3.Name = "IB High 50%";
		Subgraph_IBHExt3.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBHExt3.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBHExt3.LineStyle = LINESTYLE_DASH;
		Subgraph_IBHExt3.DrawZeros = false;

		Subgraph_IBHExt2.Name = "IB High Ext 1";
		Subgraph_IBHExt2.PrimaryColor = RGB(0, 255, 0);
		Subgraph_IBHExt2.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBHExt2.DrawZeros = false;

		Subgraph_IBHExt1.Name = "IB High 50%";
		Subgraph_IBHExt1.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBHExt1.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBHExt1.LineStyle = LINESTYLE_DASH;
		Subgraph_IBHExt1.DrawZeros = false;

		Subgraph_IBHigh.Name = "IB High";
		Subgraph_IBHigh.PrimaryColor = RGB(0, 255, 0);
		Subgraph_IBHigh.DrawStyle = DRAWSTYLE_DASH;
		Subgraph_IBHigh.DrawZeros = false;

		Subgraph_IBMid.Name = "IB 50%";
		Subgraph_IBMid.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBMid.DrawStyle = DRAWSTYLE_DASH;
        Subgraph_IBMid.LineStyle = LINESTYLE_DASH;
		Subgraph_IBMid.DrawZeros = false;

		Subgraph_IBLow.Name = "IB Low";
		Subgraph_IBLow.PrimaryColor = RGB(255, 0, 0);
		Subgraph_IBLow.DrawStyle = DRAWSTYLE_DASH;
		Subgraph_IBLow.DrawZeros = false;

		Subgraph_IBLExt1.Name = "IB Low 50%";
		Subgraph_IBLExt1.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBLExt1.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBLExt1.LineStyle = LINESTYLE_DASH;
		Subgraph_IBLExt1.DrawZeros = false;

		Subgraph_IBLExt2.Name = "IB Low Ext 1";
		Subgraph_IBLExt2.PrimaryColor = RGB(255, 0, 0);
		Subgraph_IBLExt2.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBLExt2.DrawZeros = false;

		Subgraph_IBLExt3.Name = "IB Low 50%";
		Subgraph_IBLExt3.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBLExt3.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBLExt3.LineStyle = LINESTYLE_DASH;
		Subgraph_IBLExt3.DrawZeros = false;

		Subgraph_IBLExt4.Name = "IB Low Ext 2";
		Subgraph_IBLExt4.PrimaryColor = RGB(255, 0, 0);
		Subgraph_IBLExt4.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBLExt4.DrawZeros = false;

		Subgraph_IBLExt5.Name = "IB Low 50%";
		Subgraph_IBLExt5.PrimaryColor = RGB(255, 128, 0);
		Subgraph_IBLExt5.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_IBLExt5.LineStyle = LINESTYLE_DASH;
		Subgraph_IBLExt5.DrawZeros = false;

		Subgraph_IBLExt6.Name = "IB Low Ext 3";
		Subgraph_IBLExt6.PrimaryColor = RGB(255, 0, 0);
		Subgraph_IBLExt6.DrawStyle = DRAWSTYLE_IGNORE;
		Subgraph_IBLExt6.DrawZeros = false;

		Subgraph_IBRegionTop.Name = "IB Region Top";
		Subgraph_IBRegionTop.PrimaryColor = COLOR_YELLOW;
		Subgraph_IBRegionTop.DrawStyle = DRAWSTYLE_TRANSPARENT_FILL_RECTANGLE_TOP;
		Subgraph_IBRegionTop.DrawZeros = false;

		Subgraph_IBRegionBottom.Name = "IB Region Bottom";
		Subgraph_IBRegionBottom.PrimaryColor = COLOR_YELLOW;
		Subgraph_IBRegionBottom.DrawStyle = DRAWSTYLE_TRANSPARENT_FILL_RECTANGLE_BOTTOM;
		Subgraph_IBRegionBottom.DrawZeros = false;

		// Inputs
		Input_IBType.Name = "Initial Balance Type";
		Input_IBType.SetCustomInputStrings("Daily;Weekly;Weekly Include Sunday;Intraday");
		Input_IBType.SetCustomInputIndex(0);

		Input_StartTime.Name = "Start Time";
		Input_StartTime.SetTime(HMS_TIME(9, 30, 0));
		
		Input_EndTime.Name = "End Time";
		Input_EndTime.SetTime(HMS_TIME(10, 29, 59));

		Input_NumDays.Name = "Weekly: Number of Days";
		Input_NumDays.SetInt(2);
		Input_NumDays.SetIntLimits(1, 5);

		Input_NumberOfMinutes.Name = "Intraday: Number of Minutes";
		Input_NumberOfMinutes.SetInt(15);

		Input_RoundExt.Name = "Round Extensions to TickSize";
		Input_RoundExt.SetYesNo(1);

		Input_NumberDaysToCalculate.Name = "Number of Days to Calculate";
		Input_NumberDaysToCalculate.SetInt(5);
		Input_NumberDaysToCalculate.SetIntLimits(1,INT_MAX);

		Input_StartEndTimeMethod.Name = "Start End Time Method";
		Input_StartEndTimeMethod.SetCustomInputStrings("Use Start/End Time;Use Session Start Time and Minutes From Start");
		Input_StartEndTimeMethod.SetCustomInputIndex(0);

		Input_PeriodEndAsMinutesFromSessionStart.Name = "Period End As Minutes from Session Start";
		Input_PeriodEndAsMinutesFromSessionStart.SetInt(30);

		Input_Multiplier1.Name = "Extension Multiplier 1";
		Input_Multiplier1.SetFloat(.5f);
		Input_Multiplier2.Name = "Extension Multiplier 2";
		Input_Multiplier2.SetFloat(1.0f);
		Input_Multiplier3.Name = "Extension Multiplier 3";
		Input_Multiplier3.SetFloat(1.5f);
		Input_Multiplier4.Name = "Extension Multiplier 4";
		Input_Multiplier4.SetFloat(2.0f);
		Input_Multiplier5.Name = "Extension Multiplier 5";
		Input_Multiplier5.SetFloat(2.5f);
		Input_Multiplier6.Name = "Extension Multiplier 6";
		Input_Multiplier6.SetFloat(3.0f);

		sc.SetChartStudyTransparencyLevel(sc.ChartNumber, sc.StudyGraphInstanceID, 85);

		return;
	}

	// Persistent variables
	auto& r_PeriodFirstIndex = sc.GetPersistentInt(1);
	auto& r_PeriodConfirmed = sc.GetPersistentInt(2);
	
	auto& r_PeriodStartDateTime = sc.GetPersistentSCDateTime(1);
	auto& r_PeriodEndDateTime   = sc.GetPersistentSCDateTime(2);

	auto& r_PeriodHigh       = sc.GetPersistentFloat(1);
	auto& r_PeriodLow        = sc.GetPersistentFloat(2);
	auto& r_PeriodMid        = sc.GetPersistentFloat(3);
	auto& r_PeriodHighExt1   = sc.GetPersistentFloat(4);
	auto& r_PeriodHighExt2   = sc.GetPersistentFloat(5);
	auto& r_PeriodHighExt3   = sc.GetPersistentFloat(6);
	auto& r_PeriodHighExt4   = sc.GetPersistentFloat(7);
	auto& r_PeriodHighExt5   = sc.GetPersistentFloat(8);
	auto& r_PeriodHighExt6   = sc.GetPersistentFloat(9);
	auto& r_PeriodLowExt1    = sc.GetPersistentFloat(10);
	auto& r_PeriodLowExt2    = sc.GetPersistentFloat(11);
	auto& r_PeriodLowExt3    = sc.GetPersistentFloat(12);
	auto& r_PeriodLowExt4    = sc.GetPersistentFloat(13);
	auto& r_PeriodLowExt5    = sc.GetPersistentFloat(14);
	auto& r_PeriodLowExt6    = sc.GetPersistentFloat(15);

	// Reset persistent variables upon full calculation
	if (sc.IsFullRecalculation && sc.Index == 0)
	{
		r_PeriodFirstIndex = -1;
		r_PeriodStartDateTime = 0;
		r_PeriodEndDateTime   = 0;
		r_PeriodHigh = -FLT_MAX;
		r_PeriodLow  =  FLT_MAX;
	}

	SCDateTimeMS LastBarDateTime = sc.BaseDateTimeIn[sc.ArraySize-1];
	SCDateTimeMS FirstCalculationDate = LastBarDateTime.GetDate() - SCDateTime::DAYS(Input_NumberDaysToCalculate.GetInt() - 1);

	SCDateTimeMS CurrentBarDateTime = sc.BaseDateTimeIn[sc.Index];
	
	SCDateTimeMS PrevBarDateTime;

	if (sc.Index > 0)
		PrevBarDateTime = sc.BaseDateTimeIn[sc.Index-1];

	if (CurrentBarDateTime.GetDate() < FirstCalculationDate) // Limit calculation to specified number of days back
		return;

	bool Daily  = Input_IBType.GetIndex() == 0;
	bool Weekly = Input_IBType.GetIndex() == 1 || Input_IBType.GetIndex() == 2;
	bool Intraday = Input_IBType.GetIndex() == 3;
	bool IncludeSunday = Input_IBType.GetIndex() == 2;


	SCDateTimeMS StartDateTime = CurrentBarDateTime;

	if (Input_StartEndTimeMethod.GetIndex() == 0)
		StartDateTime.SetTime(Input_StartTime.GetTime());
	else
		StartDateTime.SetTime(sc.StartTimeOfDay);

	if (Weekly)
	{
		int PeriodStartDayOfWeek = IncludeSunday ? SUNDAY : MONDAY;

		int DayOfWeek = StartDateTime.GetDayOfWeek();

		if (DayOfWeek != PeriodStartDayOfWeek)
			StartDateTime.AddDays(7 - DayOfWeek + PeriodStartDayOfWeek);
	}
		
	if (PrevBarDateTime < StartDateTime && CurrentBarDateTime >= StartDateTime)
	{
		r_PeriodFirstIndex = sc.Index;
		r_PeriodConfirmed = 0;
		r_PeriodHigh = -FLT_MAX;
		r_PeriodLow  = FLT_MAX;

		r_PeriodStartDateTime = StartDateTime;

		r_PeriodEndDateTime = r_PeriodStartDateTime;

		if (Input_StartEndTimeMethod.GetIndex() == 0)
			r_PeriodEndDateTime.SetTime(Input_EndTime.GetTime());
		else
		{
			r_PeriodEndDateTime.SetTime(static_cast<int>(sc.StartTimeOfDay + Input_PeriodEndAsMinutesFromSessionStart.GetInt() * SECONDS_PER_MINUTE - 1));
		}

		if (Daily || Intraday)
		{
			if (SCDateTimeMS(r_PeriodEndDateTime) <= r_PeriodStartDateTime)
				r_PeriodEndDateTime.AddDays(1);
		}
		else if (Weekly)
		{
			int PeriodEndDayOfWeek = IncludeSunday ? Input_NumDays.GetInt() - 1 : Input_NumDays.GetInt();

			int DayOfWeek = r_PeriodEndDateTime.GetDayOfWeek();

			if (DayOfWeek != PeriodEndDayOfWeek)
				r_PeriodEndDateTime.AddDays(PeriodEndDayOfWeek - DayOfWeek);
		}
	}

	// Check end of period
	if (r_PeriodFirstIndex >= 0)
	{
		// Check start of new intraday period
		if (Intraday)
		{
			SCDateTimeMS IntradayEndDateTime = r_PeriodStartDateTime + SCDateTime::MINUTES(Input_NumberOfMinutes.GetInt()) - SCDateTime::MICROSECONDS(1);

			if (PrevBarDateTime < IntradayEndDateTime && CurrentBarDateTime > IntradayEndDateTime)
			{
				r_PeriodFirstIndex = sc.Index;
				r_PeriodConfirmed = 0;
				r_PeriodStartDateTime.AddMinutes(Input_NumberOfMinutes.GetInt());
				r_PeriodHigh = -FLT_MAX;
				r_PeriodLow  = FLT_MAX;
			}
		}

		if (CurrentBarDateTime > r_PeriodEndDateTime)
		{
			r_PeriodFirstIndex = -1;

			if (Intraday)
			{
				r_PeriodHigh = -FLT_MAX;
				r_PeriodLow  = FLT_MAX;
			}
		}
	}

	// Collecting data, back propagate if changed
	bool IsDeveloping = false;
	if (r_PeriodFirstIndex >= 0)
	{
		IsDeveloping = true;
		bool Changed = false;

		if (sc.High[sc.Index] > r_PeriodHigh)
		{
			r_PeriodHigh = sc.High[sc.Index];
			Changed = true;
		}

		if (sc.Low[sc.Index] < r_PeriodLow)
		{
			r_PeriodLow = sc.Low[sc.Index];
			Changed = true;
		}

		if (Changed)
		{
			r_PeriodMid = (r_PeriodHigh + r_PeriodLow) / 2.0f;

			float Range = r_PeriodHigh - r_PeriodLow;

			r_PeriodHighExt1 = r_PeriodHigh + Input_Multiplier1.GetFloat() * Range; 
			r_PeriodHighExt2 = r_PeriodHigh + Input_Multiplier2.GetFloat() * Range; 
			r_PeriodHighExt3 = r_PeriodHigh + Input_Multiplier3.GetFloat() * Range; 
			r_PeriodHighExt4 = r_PeriodHigh + Input_Multiplier4.GetFloat() * Range; 
			r_PeriodHighExt5 = r_PeriodHigh + Input_Multiplier5.GetFloat() * Range; 
			r_PeriodHighExt6 = r_PeriodHigh + Input_Multiplier6.GetFloat() * Range; 

			r_PeriodLowExt1 = r_PeriodLow - Input_Multiplier1.GetFloat() * Range; 
			r_PeriodLowExt2 = r_PeriodLow - Input_Multiplier2.GetFloat() * Range; 
			r_PeriodLowExt3 = r_PeriodLow - Input_Multiplier3.GetFloat() * Range; 
			r_PeriodLowExt4 = r_PeriodLow - Input_Multiplier4.GetFloat() * Range; 
			r_PeriodLowExt5 = r_PeriodLow - Input_Multiplier5.GetFloat() * Range; 
			r_PeriodLowExt6 = r_PeriodLow - Input_Multiplier6.GetFloat() * Range; 

			if (Input_RoundExt.GetYesNo())
			{
				r_PeriodHighExt1 = sc.RoundToTickSize(r_PeriodHighExt1, sc.TickSize); 
				r_PeriodHighExt2 = sc.RoundToTickSize(r_PeriodHighExt2, sc.TickSize); 
				r_PeriodHighExt3 = sc.RoundToTickSize(r_PeriodHighExt3, sc.TickSize); 
				r_PeriodHighExt4 = sc.RoundToTickSize(r_PeriodHighExt4, sc.TickSize); 
				r_PeriodHighExt5 = sc.RoundToTickSize(r_PeriodHighExt5, sc.TickSize); 
				r_PeriodHighExt6 = sc.RoundToTickSize(r_PeriodHighExt6, sc.TickSize); 

				r_PeriodLowExt1 = sc.RoundToTickSize(r_PeriodLowExt1, sc.TickSize); 
				r_PeriodLowExt2 = sc.RoundToTickSize(r_PeriodLowExt2, sc.TickSize); 
				r_PeriodLowExt3 = sc.RoundToTickSize(r_PeriodLowExt3, sc.TickSize); 
				r_PeriodLowExt4 = sc.RoundToTickSize(r_PeriodLowExt4, sc.TickSize); 
				r_PeriodLowExt5 = sc.RoundToTickSize(r_PeriodLowExt5, sc.TickSize); 
				r_PeriodLowExt6 = sc.RoundToTickSize(r_PeriodLowExt6, sc.TickSize); 
			}

			// Backfill any changes to IB region
			for (int Index = r_PeriodFirstIndex; Index < sc.Index; Index++)
			{
				Subgraph_IBRegionTop[Index] = r_PeriodHigh;
				Subgraph_IBRegionBottom[Index] = r_PeriodLow;
			}

			sc.EarliestUpdateSubgraphDataArrayIndex = r_PeriodFirstIndex;
		}
	}

	// Plot current values
	if (r_PeriodLow != FLT_MAX)
	{
		if (IsDeveloping)
		{
			// Only draw IB region during developing period
			Subgraph_IBRegionTop[sc.Index] = r_PeriodHigh;
			Subgraph_IBRegionBottom[sc.Index] = r_PeriodLow;
		}
		else
		{
			if (!r_PeriodConfirmed)
			{
				// First call after IB region has confirmed, backfill IB levels
				for (int Index = sc.EarliestUpdateSubgraphDataArrayIndex; Index < sc.Index; Index++)
				{
					Subgraph_IBHigh[Index]  = r_PeriodHigh;
					Subgraph_IBLow[Index]   = r_PeriodLow;
					Subgraph_IBMid[Index]   = r_PeriodMid;
					Subgraph_IBHExt1[Index] = r_PeriodHighExt1;
					Subgraph_IBHExt2[Index] = r_PeriodHighExt2;
					Subgraph_IBHExt3[Index] = r_PeriodHighExt3;
					Subgraph_IBHExt4[Index] = r_PeriodHighExt4;
					Subgraph_IBHExt5[Index] = r_PeriodHighExt5;
					Subgraph_IBHExt6[Index] = r_PeriodHighExt6;
					Subgraph_IBLExt1[Index] = r_PeriodLowExt1;
					Subgraph_IBLExt2[Index] = r_PeriodLowExt2;
					Subgraph_IBLExt3[Index] = r_PeriodLowExt3;
					Subgraph_IBLExt4[Index] = r_PeriodLowExt4;
					Subgraph_IBLExt5[Index] = r_PeriodLowExt5;
					Subgraph_IBLExt6[Index] = r_PeriodLowExt6;
				}
				r_PeriodConfirmed = 1;
			}

			Subgraph_IBHigh[sc.Index]  = r_PeriodHigh;
			Subgraph_IBLow[sc.Index]   = r_PeriodLow;
			Subgraph_IBMid[sc.Index]   = r_PeriodMid;
			Subgraph_IBHExt1[sc.Index] = r_PeriodHighExt1;
			Subgraph_IBHExt2[sc.Index] = r_PeriodHighExt2;
			Subgraph_IBHExt3[sc.Index] = r_PeriodHighExt3;
			Subgraph_IBHExt4[sc.Index] = r_PeriodHighExt4;
			Subgraph_IBHExt5[sc.Index] = r_PeriodHighExt5;
			Subgraph_IBHExt6[sc.Index] = r_PeriodHighExt6;
			Subgraph_IBLExt1[sc.Index] = r_PeriodLowExt1;
			Subgraph_IBLExt2[sc.Index] = r_PeriodLowExt2;
			Subgraph_IBLExt3[sc.Index] = r_PeriodLowExt3;
			Subgraph_IBLExt4[sc.Index] = r_PeriodLowExt4;
			Subgraph_IBLExt5[sc.Index] = r_PeriodLowExt5;
			Subgraph_IBLExt6[sc.Index] = r_PeriodLowExt6;
		}
	}
}
