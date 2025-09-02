modded class Pen_ColorBase : Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		//RemoveAction(ActionWritePaper);
		AddAction(ActionZenWritePaper);
	}
}