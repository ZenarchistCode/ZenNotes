modded class MissionBase
{
	override UIScriptedMenu CreateScriptedMenu(int id)
    {
        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        if (!menu)
        {
            switch (id)
            {
				//! NOTES
                case ZenNotesMenu.NOTE_GUI:
                {
                    menu = new ZenNoteGUI;
                    break;
                }
            }
        }

        return menu;
    }
}