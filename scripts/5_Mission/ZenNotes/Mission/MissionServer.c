modded class MissionServer
{
	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		if (GetZenNotesConfig().DeleteAllNotes)
		{
			GetZenNotesConfig().DeleteAllNotes = false;
			GetZenNotesConfig().Save();
		}
	}
}