class CfgPatches
{
	class ZenNotesDefine
	{
		units[] = {};
		requiredVersion = 1.0;
		requiredAddons[] = 
		{ 
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenNotesDefine
	{
		dir = "ZenNotesDefine";
		name = "ZenNotesDefine";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] =
		{
			"World"
		};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenNotesDefine/scripts/3_game" };
			};
		};
	};
};
