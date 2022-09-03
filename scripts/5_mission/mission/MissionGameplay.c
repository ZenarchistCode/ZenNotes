modded class MissionGameplay
{
	// Close menu if escape key is pressed
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);

		if (key == KeyCode.KC_ESCAPE) // Escape key
		{
			UIScriptedMenu menu = m_UIManager.GetMenu();
			if (menu)
			{
				ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
				if (noteMenu)
				{
					noteMenu.OnExitBtnClick(); // Enables user control & HUD etc. Call this instead of HideScriptedMenu()
				}
			}
		}
	}
}