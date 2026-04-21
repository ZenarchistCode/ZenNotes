modded class FireplaceBase
{
	typename ATTACHMENT_ZENNOTE = ZenNote;

	void FireplaceBase()
	{
		m_FireConsumableTypes.Insert(ATTACHMENT_ZENNOTE, new FireConsumableType(ATTACHMENT_ZENNOTE, 10, true, "ZenNote"));
	}
}