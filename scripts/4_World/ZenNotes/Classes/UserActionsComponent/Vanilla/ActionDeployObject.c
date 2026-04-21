modded class ActionDeployObject
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!item)
		{
			return super.ActionCondition(player, target, item);
		}

		#ifndef SERVER
		if (player.IsPlacingLocal() && item.IsKindOf("Paper"))
			return true;
		#endif

		return super.ActionCondition(player, target, item);
	}

	override void SetupAnimation(ItemBase item)
    {
        if (item.IsKindOf("Paper"))
        {
            m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
            return;
        }

        super.SetupAnimation(item);
    }
}
