modded class MissionGameplay
{
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);

		if (key == KeyCode.KC_ESCAPE)
		{
			UIScriptedMenu menu = m_UIManager.GetMenu();
			if (menu)
			{
				//! NOTES
				ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
				if (noteMenu)
				{
					noteMenu.OnExitBtnClick();
				}
			}
		}
	}
}