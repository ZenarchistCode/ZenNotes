class CfgPatches
{
	class ZenNotes
	{
		units[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = 
		{ 
			"DZ_Data",
			"DZ_Scripts",
			"ZenUtilities", // For debug & logging
		};
	};
};

class CfgMods
{
	class ZenNotes
	{
		dir = "ZenNotes";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenNotes";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.1";
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
				files[] = { "ZenNotes/scripts/3_game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenNotes/scripts/4_world" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenNotes/scripts/5_mission" };
			};
		};
	};
};

class CfgVehicles
{
	class Paper;
	class ZenNote : Paper
	{
		scope = 2;
		model = "\dz\gear\consumables\Paper.p3d";
		displayName = "Note";
		descriptionShort = "It's a written note left behind by a survivor...";
		inventorySlot[] = {}; // fireplace
		canBeSplit = 0;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 1;
		varStackMax = 1;
	};
	class Pen_ColorBase
	{
		quantityBar = 1;
		varQuantityInit = 30;
		varQuantityMin = 0;
		varQuantityMax = 30;
		stackedUnit = "percentage";
	};
	class Pen_Black : Pen_ColorBase
	{
		scope = 2;
		displayName = "Black Pen";
		rgbColor[] = { 0,0,0 };
	};
	class Pen_Red : Pen_ColorBase
	{
		scope = 2;
		displayName = "Red Pen";
		rgbColor[] = { 180,4,4 };
	};
	class Pen_Green : Pen_ColorBase
	{
		scope = 2;
		displayName = "Green Pen";
		rgbColor[] = { 8,138,8 };
	};
	class Pen_Blue : Pen_ColorBase
	{
		scope = 2;
		displayName = "Blue Pen";
		rgbColor[] = { 4,49,180 };
	};
};
