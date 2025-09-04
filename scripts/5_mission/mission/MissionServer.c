modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenNotes"))
			return;
		#endif

		GetZenNotesConfig();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenNotes"))
			return;
		#endif

		if (GetZenNotesConfig().DeleteAllNotes)
		{
			GetZenNotesConfig().DeleteAllNotes = false;
			GetZenNotesConfig().Save();
		}
	}
}