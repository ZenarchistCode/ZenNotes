class ZenNote extends Paper
{
	// Store a reference to this note's data
	protected ref ZenNoteData m_ZenNoteData;

	// Set note actions
	override void SetActions()
	{
		super.SetActions();

		// Remove actions that aren't related to notes (ie. attach to fireplace, take item by tapping F)
		RemoveAction(ActionTakeItem);
		RemoveAction(ActionAttach);

		// Add actions related to written notes
		AddAction(ActionZenReadNoteHands);
		AddAction(ActionZenReadNoteTarget);
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}

	// Receive note data from server
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		Param1<ref ZenNoteData> params = new Param1<ref ZenNoteData>(m_ZenNoteData);

		// Client-side receiver
		if (rpc_type == ZENNOTERPCs.RECEIVE_WRITTEN_NOTE)
		{
			if (ctx.Read(params))
			{
				if (params.param1)
				{
					m_ZenNoteData = params.param1;

					// Show note GUI as read-only
					ZenNoteGUI gui = ZenNoteGUI.Cast(GetGame().GetUIManager().EnterScriptedMenu(MENU_ZEN_NOTE_GUI, NULL));

					if (gui)
					{
						gui.SetNoteData(m_ZenNoteData);
						gui.SetReadOnly(true);
					}
				}
			}
		}
	}

	// Return this note's data
	ZenNoteData GetNoteData()
	{
		return m_ZenNoteData;
	}

	// Set this note's data
	void SetNoteData(ZenNoteData data)
	{
		m_ZenNoteData = data;
	}

	// Load note data
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		// Load the note's persistent data
		if (!ctx.Read(m_ZenNoteData))
		{
			return false;
		}

		return true;
	}

	// Save note data
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		// Save the note's persistent data
		ctx.Write(m_ZenNoteData);
	}
};