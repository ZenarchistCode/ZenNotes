// Registers item animations
modded class JMAnimRegister
{
	override void OnRegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.OnRegisterOneHanded(pType, pBehavior);

		// Set note hand-held animation
		pType.AddItemInHandsProfileIK("ZenNote", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/paper.anm");
	}
};