modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		Print("[ZenNotes] OnInit");

		// Load notes config
		GetZenNotesConfig();
	}
};