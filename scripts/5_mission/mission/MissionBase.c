modded class MissionBase
{
    // Create user interface
    override UIScriptedMenu CreateScriptedMenu(int id)
    {
        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        if (!menu)
        {
            switch (id)
            {
                case MENU_ZEN_NOTE_GUI:
                {
                    menu = new ZenNoteGUI;
                    break;
                }
            }
        }

        return menu;
    }
}