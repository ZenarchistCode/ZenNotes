ref ZenNotesClientConfig g_ZenNotesClientConfig;

static ZenNotesClientConfig GetZenNotesClientConfig()
{
	if (!g_ZenNotesClientConfig) GetZenConfigRegister().RegisterConfig(ZenNotesClientConfig);
	return g_ZenNotesClientConfig;
}

modded class ZenConfigRegister
{
	override void RegisterPreload()
	{
		super.RegisterPreload(); 
		RegisterType(ZenNotesClientConfig);
	}
}

class ZenNotesClientConfig: ZenConfigBase
{
	// -------------------------
	// CONFIG SETTINGS
	// -------------------------
	override void OnRegistered()
	{
		g_ZenNotesClientConfig = this;
	}
	
	override string    	GetCurrentVersion()   		{ return "1.29.1"; }
	override bool		ShouldLoadOnClient() 		{ return true; }
	override bool 		IsClientOnlyConfig()		{ return true; }
	
	override bool ReadJson(string path, out string err)
	{
		return JsonFileLoader<ZenNotesClientConfig>.LoadFile(path, this, err);
	}

	override bool WriteJson(string path, out string err)
	{
		return JsonFileLoader<ZenNotesClientConfig>.SaveFile(path, this, err);
	}

	// Main config data
	int LastUsedFontStyle;
}