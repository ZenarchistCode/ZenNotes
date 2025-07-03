modded class PlayerBase
{
	override void OnUnconsciousStart()
	{
		super.OnUnconsciousStart();

        #ifndef SERVER
		//! NOTES
        UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
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