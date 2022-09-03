modded class ActionDeployObject
{
    override void SetupAnimation(ItemBase item)
    {
        if (item.IsKindOf("Paper"))
        {
            m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
            return;
        }

        super.SetupAnimation(item);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!GetGame().IsMultiplayer() || GetGame().IsClient())
        {
            if (player.IsPlacingLocal() && (item.IsInherited(ZenNote)))
                return true;
        }

        return super.ActionCondition(player, target, item);
    }
}