class ActionZenReadNoteHandsCB : ActionContinuousBaseCB {}

class ActionZenReadNoteHands : ActionContinuousBase
{
	void ActionZenReadNoteHands()
	{
		m_CallbackClass = ActionZenReadNoteHandsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_PRONE;
		m_Text = "#read";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	// Action condition
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Return true on server
		if (GetGame().IsServer())
			return true;

		// If the player is currently looking at a note, disable the read note action on the note in their hands (to avoid confusion)
		if (target && target.GetObject() && target.GetObject().IsInherited(ZenNote))
			return false;

		// Otherwise return true if the item in the player's hand is a note and they are not placing it as a hologram
		return item && item.IsInherited(ZenNote) && !player.IsPlacingLocal();
	}

	// Called server-side - when the action begins, send the note data to the client and display the note GUI
	override void OnStartServer(ActionData action_data)
	{
		ZenNote note = ZenNote.Cast(action_data.m_MainItem);

		if (note)
		{
			auto data = new Param1<ref ZenNoteData>(note.GetNoteData());
			note.RPCSingleParam(ZENNOTERPCs.RECEIVE_WRITTEN_NOTE, data, true, action_data.m_Player.GetIdentity());
		}
	}
};