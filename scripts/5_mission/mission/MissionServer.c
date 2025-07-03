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
}