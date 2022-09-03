modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionZenWritePaper);
        actions.Insert(ActionZenReadNoteHands);
        actions.Insert(ActionZenReadNoteTarget);
    }
}