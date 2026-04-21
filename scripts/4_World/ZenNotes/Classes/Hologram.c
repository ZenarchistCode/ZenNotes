modded class Hologram
{
    override void EvaluateCollision(ItemBase action_item = null)
	{
        //! NOTES - override vanilla collisions check for holograms to make placing notes easier.
		if (action_item && action_item.IsInherited(ZenNote))
		{
			SetIsColliding(false);
			return;
		}

		super.EvaluateCollision(action_item);
	}
}