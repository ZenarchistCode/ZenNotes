class CfgPatches
{
	class ZenNotes
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Consumables"
		};
	};
};

class CfgMods
{
	class ZenNotes
	{
		dir = "ZenNotes";
		name = "Zen's Notes";
		author = "Zenarchist";
		credits = "";
		version = "1.0";
		type = "mod";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class engineScriptModule
			{
				files[]=
				{
					"ZenNotes/scripts/1_Core",
					"ZenNotes/scripts/Common"
				};
			};
			class gameLibScriptModule
			{
				files[]=
				{
					"ZenNotes/scripts/2_GameLib",
					"ZenNotes/scripts/Common"
				};
			};
			class gameScriptModule
			{
				files[] = 
				{ 
					"ZenNotes/scripts/Common",
					"ZenNotes/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[] = 
				{ 
					"ZenNotes/scripts/Common",
					"ZenNotes/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{ 
					"ZenNotes/scripts/Common",
					"ZenNotes/scripts/5_mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;

	//! NOTES 
	// Make paper stackable up to 5
	class Paper : Inventory_Base
	{
		canBeSplit = 1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 5;
		varStackMax = 5;
		varQuantityDestroyOnMin = 1;
	};

	// Make punched card non-stackable as it inherits from Paper
	class PunchedCard : Paper
	{
		canBeSplit = 0;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 1;
		varStackMax = 1;
		varQuantityDestroyOnMin = 1;
	};

	// Define a written note (non-stackable)
	class ZenNote : Paper
	{
		scope = 2;
		displayName = "$STR_ZenNoteTxt";
		descriptionShort = "$STR_ZenNoteDesc";
		canBeSplit = 0;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 1;
		varStackMax = 1;
	};

	// Define colored pens
	class Pen_ColorBase : Inventory_Base
	{
		scope = 0;
		quantityBar = 1;
		varQuantityInit = 100;
		varQuantityMin = 0;
		varQuantityMax = 100;
		//varQuantityDestroyOnMin = 0;
		stackedUnit = "percentage";
	};
	class Pen_Black : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Black";
		penColor[] = { 10,10,10 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_black_co.paa" };
	};
	class Pen_Red : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Red";
		penColor[] = { 200,20,20 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_red_co.paa" };
	};
	class Pen_Green : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Green";
		penColor[] = { 24,150,24 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_green_co.paa" };
	};
	class Pen_Blue : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Blue";
		penColor[] = { 0,65,200 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_blue_co.paa" };
	};
	class Pen_Pink : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Pink";
		penColor[] = { 255,0,162 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_pink_co.paa" };
	};
	class Pen_Purple : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Purple";
		penColor[] = { 144,0,255 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_purple_co.paa" };
	};
	class Pen_Orange : Pen_ColorBase
	{
		scope = 2;
		displayName = "$STR_ZenPen_Orange";
		penColor[] = { 255,150,0 };
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenNotes\data\textures\notes\loot_pen_orange_co.paa" };
	};
};