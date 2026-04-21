modded class PlayerBase
{
	override void OnUnconsciousStart()
	{
		super.OnUnconsciousStart();

        #ifndef SERVER
		//! NOTES
        UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
        if (!menu)
			return;

        ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
        if (noteMenu)
        {
            noteMenu.OnExitBtnClick();
        }
        #endif
	}
}