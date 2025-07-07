modded class Hologram
{
    override void EvaluateCollision(ItemBase action_item = null)
	{
        //! NOTES
		if (action_item && action_item.IsInherited(ZenNote))
		{
			SetIsColliding(false);
			return;
		}

		super.EvaluateCollision(action_item);
	}
}
