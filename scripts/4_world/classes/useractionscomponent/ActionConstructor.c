modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        //! NOTES 
        actions.Insert(ActionZenWritePaper);
        actions.Insert(ActionZenReadNoteHands);
        actions.Insert(ActionZenReadNoteTarget);
    }
}