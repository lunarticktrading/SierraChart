#include "sierrachart.h"

SCSFExport scsf_LunarTick_SwingLevels(SCStudyInterfaceRef sc)
{
    SCString message;

    SCSubgraphRef Subgraph_SwingHigh = sc.Subgraph[0];
    SCSubgraphRef Subgraph_SwingLow = sc.Subgraph[1];

    SCInputRef Input_Length = sc.Input[0];

    if (sc.SetDefaults)
    {
        sc.GraphName = "Swing Levels";
        sc.StudyDescription = "Displays high/low swing levels.";
        sc.GraphRegion = 0;
        sc.AutoLoop = 1;

        // Configure subgraphs

        Subgraph_SwingHigh.Name = "Swing High";
        Subgraph_SwingHigh.PrimaryColor = COLOR_CYAN;
        Subgraph_SwingHigh.DrawStyle = DRAWSTYLE_POINT;
        Subgraph_SwingHigh.LineWidth = 5;

        Subgraph_SwingLow.Name = "Swing Low";
        Subgraph_SwingLow.PrimaryColor = COLOR_YELLOW;
        Subgraph_SwingLow.DrawStyle = DRAWSTYLE_POINT;
        Subgraph_SwingLow.LineWidth = 5;


        // Configure inputs

        Input_Length.Name = "Swing Length";
        Input_Length.SetInt(5);
        Input_Length.SetIntLimits(1, MAX_STUDY_LENGTH);

        return;
    }

    // Implementation

    const auto SwingLength = Input_Length.GetInt();

    // Persistent variables
    auto& r_prev_bar_index = sc.GetPersistentIntFast(0);     // Last seen bar index

    auto& r_pending_sh_index = sc.GetPersistentIntFast(1);   // Index of the pending SwingHigh (not confirmed yet)
    auto& r_sh_index = sc.GetPersistentIntFast(2);           // Index of the confirmed SwingHigh
    auto& r_sh_active = sc.GetPersistentIntFast(3);          // Is the SwingHigh still active? (false if breached)

    auto& r_pending_sl_index = sc.GetPersistentIntFast(4);   // Index of the pending SwingLow (not confirmed yet)
    auto& r_sl_index = sc.GetPersistentIntFast(5);           // Index of the confirmed SwingLow
    auto& r_sl_active = sc.GetPersistentIntFast(6);          // Is the SwingLow still active? (false if breached)

    auto& r_pending_sh_value = sc.GetPersistentFloatFast(0); // Value of the pending SwingHigh (not confirmed yet)
    auto& r_sh_value = sc.GetPersistentFloatFast(1);         // Value of the confirmed SwingHigh

    auto& r_pending_sl_value = sc.GetPersistentFloatFast(2); // Value of the pending SwingLow (not confirmed yet)
    auto& r_sl_value = sc.GetPersistentFloatFast(3);         // Value of the confirmed SwingLow

	// Reset persistent variables upon full calculation
    if (sc.IsFullRecalculation && sc.Index == 0)
    {
        r_prev_bar_index = 0;

        r_pending_sh_index = 0;
        r_sh_index = 0;
        r_sh_active = 0;

        r_pending_sl_index = 0;
        r_sl_index = 0;
        r_sl_active = 0;

        r_pending_sh_value = 0;
        r_sh_value = 0;

        r_pending_sl_value = 0;
        r_sl_value = 0;
    }

    // Wait for start of new bar
    if (sc.Index > SwingLength && sc.Index != r_prev_bar_index)
    {
        // Check for new pending SwingHigh
        auto prevHigh = sc.BaseDataIn[SC_HIGH][sc.Index - 1];
        auto preceedingHighest = sc.GetHighest(sc.BaseDataIn[SC_HIGH], sc.Index - 2, SwingLength);
        //message.Format("Current Index [%d]: Checking for new pending SwingHigh: prevHigh=%f, preceedingHighest=%f", sc.Index, prevHigh, preceedingHighest);
        //sc.AddMessageToLog(message, 0);
        if (prevHigh > preceedingHighest)
        {
            // Found new pending SwingHigh
            r_pending_sh_index = sc.Index - 1;
            r_pending_sh_value = prevHigh;
            //message.Format("Current Index [%d]: Found new pending SwingHigh: r_pending_sh_index=%d, r_pending_sh_value=%f", sc.Index, r_pending_sh_index, r_pending_sh_value);
            //sc.AddMessageToLog(message, 0);
        }

        // Check for new pending SwingLow
        auto prevLow = sc.BaseDataIn[SC_LOW][sc.Index - 1];
        auto preceedingLowest = sc.GetLowest(sc.BaseDataIn[SC_LOW], sc.Index - 2, SwingLength);
        //message.Format("Current Index [%d]: Checking for new pending SwingLow: prevLow=%f, preceedingLowest=%f", sc.Index, prevLow, preceedingLowest);
        //sc.AddMessageToLog(message, 0);
        if (prevLow < preceedingLowest)
        {
            // Found new pending SwingLow
            r_pending_sl_index = sc.Index - 1;
            r_pending_sl_value = prevLow;
            //message.Format("Current Index [%d]: Found new pending SwingLow: r_pending_sl_index=%d, r_pending_sl_value=%f", sc.Index, r_pending_sl_index, r_pending_sl_value);
            //sc.AddMessageToLog(message, 0);
        }


        // Check if pending SwingHigh is confirmed
        //message.Format("Current Index [%d]: Check if pending SwingHigh is confirmed: r_pending_sh_index=%d, SwingLength=%d, index_diff=%d", sc.Index, r_pending_sh_index, SwingLength, sc.Index - r_pending_sh_index);
        //sc.AddMessageToLog(message, 0);
        if ((r_pending_sh_index >= SwingLength) && (sc.Index - r_pending_sh_index) == (SwingLength + 1))
        {
            // Pending SwingHigh is now confirmed
            r_sh_index = r_pending_sh_index;
            r_sh_value = r_pending_sh_value;
            r_sh_active = 1;
            //message.Format("Current Index [%d]: Pending SwingHigh confirmed: index=%d, value=%f", sc.Index, r_sh_index, r_sh_value);
            //sc.AddMessageToLog(message, 1);

            // Backfill swing level from the swing point
            for (int i = r_sh_index; i < sc.Index; i++)
            {
                Subgraph_SwingHigh[i] = r_sh_value;
            }
        }

        // Check if pending SwingLow is confirmed
        //message.Format("Current Index [%d]: Check if pending SwingLow is confirmed: r_pending_sl_index=%d, SwingLength=%d, index_diff=%d", sc.Index, r_pending_sl_index, SwingLength, sc.Index - r_pending_sl_index);
        //sc.AddMessageToLog(message, 0);
        if ((r_pending_sl_index >= SwingLength) && (sc.Index - r_pending_sl_index) == (SwingLength + 1))
        {
            // Pending SwingLow is now confirmed
            r_sl_index = r_pending_sl_index;
            r_sl_value = r_pending_sl_value;
            r_sl_active = 1;
            //message.Format("Current Index [%d]: Pending SwingLow confirmed: index=%d, value=%f", sc.Index, r_sl_index, r_sl_value);
            //sc.AddMessageToLog(message, 1);

            // Backfill swing level from the swing point
            for (int i = r_sl_index; i < sc.Index; i++)
            {
                Subgraph_SwingLow[i] = r_sl_value;
            }
        }
    }

    if (r_sh_index >= SwingLength)
    {
        if (r_sh_active)
        {
            if (sc.BaseDataIn[SC_HIGH][sc.Index] > r_sh_value)
            {
                // Current SwingHigh breached
                r_sh_active = 0;
                Subgraph_SwingHigh[sc.Index] = 0;
            }
            else
            {
                Subgraph_SwingHigh[sc.Index] = r_sh_value;
            }
        }

        if (r_sl_active)
        {
            if (sc.BaseDataIn[SC_LOW][sc.Index] < r_sl_value)
            {
                // Current SwingLow breached
                r_sl_active = 0;
                Subgraph_SwingLow[sc.Index] = 0;
            }
            else
            {
                Subgraph_SwingLow[sc.Index] = r_sl_value;
            }
        }
    }

    r_prev_bar_index = sc.Index;
}
