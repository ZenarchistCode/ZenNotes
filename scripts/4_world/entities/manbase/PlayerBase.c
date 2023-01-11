// Handle uncon/death while writing notes (TODO: Figure out how the fuck to drop the written note upon death, not as easy as it sounds)
modded class PlayerBase
{
	override void OnUnconsciousStart()
	{
		super.OnUnconsciousStart();

        #ifndef SERVER
        // Check if note UI is open, if so, close it
        if (GetGame() && GetGame().GetUIManager())
        {
            UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
            if (menu)
            {
                ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
                if (noteMenu)
                {
                    noteMenu.OnExitBtnClick();
                }
            }
        }
        #endif
	};
};
