class ActionZenWritePaperCB : ActionContinuousBaseCB {}

class ActionZenWritePaper : ActionContinuousBase
{
	void ActionZenWritePaper()
	{
		m_CallbackClass = ActionZenWritePaperCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_PRONE;
		m_Text = "#write_note";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(1.2); // 1.2 meters
	}

	// Check to make sure that we're using a pen on paper
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Return true on server
		if (GetGame().IsServer())
			return true;

		// If item or target doesn't exist, stop
		if (!item || !target.GetObject())
			return false;

		// Make sure this item is not an already-written note
		if (item.IsInherited(ZenNote) || target.GetObject().IsInherited(ZenNote))
			return false;

		// Is main item or target paper, and is main item or target a color-based item (ie. pen)
		if ((item.ConfigIsExisting("penColor") && Paper.Cast(target.GetObject())) || (target.GetObject().ConfigIsExisting("penColor") && Paper.Cast(item)))
		{
			return true;
		}

		return false;
	}

	// Called when action begins on client-side
	override void OnStartClient(ActionData action_data)
	{
		ZenNoteGUI gui = ZenNoteGUI.Cast(GetGame().GetUIManager().EnterScriptedMenu(MENU_ZEN_NOTE_GUI, NULL));

		if (gui)
		{
			// Check if paper is main item or target
			Paper paper = Paper.Cast(action_data.m_MainItem);
			if (!paper)
				paper = Paper.Cast(action_data.m_Target.GetObject());

			// Check if pen is main item or target
			Pen_ColorBase pen = Pen_ColorBase.Cast(action_data.m_MainItem);
			if (!pen)
				pen = Pen_ColorBase.Cast(action_data.m_Target.GetObject());

			// Prepare note GUI for writing
			gui.SetPaper(paper);
			gui.SetReadOnly(false);
			gui.SetPenColour(GetPenColour(pen));
		}
	}

	// Called when action begins on server-side
	override void OnStartServer(ActionData action_data)
	{
		if (GetZenNotesConfig().NoteDateFormat.Format == 0)
		{
			// 0 = no date on notes
			return;
		}

		// Check if paper is main item or target
		Paper paper = Paper.Cast(action_data.m_MainItem);
		if (!paper)
			paper = Paper.Cast(action_data.m_Target.GetObject());

		if (!paper)
			return;

		// Send server-side date formatted to client
		Param1<string> data = new Param1<string>(GetZenNotesConfig().GetDate());
		paper.RPCSingleParam(ZENNOTERPCs.RECEIVE_NOTE_DATE, data, true, action_data.m_Player.GetIdentity());
	}

	// Called when action ends
	void End(ActionData action_data)
	{
		// Reduce pen quantity
		if (GetGame().IsServer())
		{
			// Check if pen is main item or target
			Pen_ColorBase pen;
			
			if (action_data.m_MainItem)
				pen = Pen_ColorBase.Cast(action_data.m_MainItem);
			if (!pen && action_data.m_Target)
				pen = Pen_ColorBase.Cast(action_data.m_Target.GetObject());

			if (pen)
			{
				pen.SetQuantity(pen.GetQuantity() - GetZenNotesConfig().PenConsumeQuantity);
			}
		}

		super.End(action_data);
	}

	// Get the ARGB colour integer for the given pen
	static int GetPenColour(Pen_ColorBase pen)
	{
		if (!pen)
			return 0;

		// Get RGB pen color from config.cpp
		TIntArray rgbArray = new TIntArray();
		pen.ConfigGetIntArray("penColor", rgbArray);

		// Return RGB converted to ARGB with 100% opacity (255 alpha)
		return ARGB(255, rgbArray[0], rgbArray[1], rgbArray[2]);
	}
};