class ZenNotesConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenNotesConfig.json";

	// Main config data
	string ConfigVersion = "";
	int PenConsumeQuantity;
	ref ZenNoteDateFormat NoteDateFormat;
	ref array<string> WordBlacklist = new array<string>;
	string SendPlayerWarning;

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (GetGame().IsServer())
		{
			if (FileExist(zenModFolder + zenConfigName))
			{ // If config exists, load file
				JsonFileLoader<ZenNotesConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

				// If version mismatch, backup old version of json before replacing it
				if (ConfigVersion != CONFIG_VERSION)
				{
					JsonFileLoader<ZenNotesConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
					ConfigVersion = CONFIG_VERSION;
				}
				else
				{
					// Config exists and version matches, stop here.
					return;
				}
			}

			// Clear old config
			WordBlacklist.Clear();

			// Set new config version
			ConfigVersion = CONFIG_VERSION;

			// Set default config
			SendPlayerWarning = "We don't tolerate that sort of language on our server. Your note has been logged and any repeat offenses may result in a permenent ban.";
			PenConsumeQuantity = 3;

			// Set default date format
			NoteDateFormat = new ZenNoteDateFormat;
			NoteDateFormat.Format = 1;
			NoteDateFormat.DaySuffix = new array<string>;
			NoteDateFormat.DaySuffix.Insert("st");
			NoteDateFormat.DaySuffix.Insert("nd");
			NoteDateFormat.DaySuffix.Insert("rd");
			NoteDateFormat.DaySuffix.Insert("th");
			NoteDateFormat.MonthName = new array<string>;
			NoteDateFormat.MonthName.Insert("January");
			NoteDateFormat.MonthName.Insert("February");
			NoteDateFormat.MonthName.Insert("March");
			NoteDateFormat.MonthName.Insert("April");
			NoteDateFormat.MonthName.Insert("May");
			NoteDateFormat.MonthName.Insert("June");
			NoteDateFormat.MonthName.Insert("July");
			NoteDateFormat.MonthName.Insert("August");
			NoteDateFormat.MonthName.Insert("September");
			NoteDateFormat.MonthName.Insert("October");
			NoteDateFormat.MonthName.Insert("November");
			NoteDateFormat.MonthName.Insert("December");

			// Set default blacklisted words
			WordBlacklist.Insert("REALLY_NASTY_WORDS_YOU_DONT_WANT_WRITTEN");

			// Save config
			Save();
		}
	}

	// Save config
	void Save()
	{
		if (!FileExist(zenModFolder))
		{ // If config folder doesn't exist, create it.
			MakeDirectory(zenModFolder);
		}

		// Save JSON config
		JsonFileLoader<ZenNotesConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	// Check if the given message contains a blacklisted word
	bool IsBlacklisted(string msg)
	{
		msg.ToLower();
		foreach (string s : WordBlacklist)
		{
			s.ToLower();
			if (msg.Contains(s))
				return true;
		}

		return false;
	}

	// Get readable date
	string GetDate()
	{
		if (NoteDateFormat.Format == 0)
		{
			return "";
		}

		// Get date as numbers
		int year, month, day;
		GetYearMonthDay(year, month, day);

		// Prepare date strings
		string date;
		string dayNumber;
		string monthNumber;

		// Get day number (eg. convert 07 -> 7)
		dayNumber = day.ToStringLen(2);
		if (day <= 9)
			dayNumber = day.ToStringLen(1);

		// Get month number (eg. convert 07 -> 7)
		monthNumber = month.ToStringLen(2);
		if (month <= 9)
			monthNumber = month.ToStringLen(1);

		if (NoteDateFormat.Format == 1) // eg. 23rd September, 2022
		{
			// Get formatted date 
			string dayStr;
			string monthStr;
			dayStr = GetNumberDateyThingy(day);
			monthStr = GetMonth(month);
			date = dayNumber + dayStr + " " + monthStr + ", " + year.ToStringLen(4);
		}
		else
		if (NoteDateFormat.Format == 2) // eg. 23/09/2022
		{
			date = day.ToStringLen(2) + "/" + month.ToStringLen(2) + "/" + year.ToStringLen(4);
		}
		else
		if (NoteDateFormat.Format == 3) // eg. 3/6/2022
		{
			date = dayNumber + "/" + monthNumber + "/" + year.ToStringLen(4);
		}
		else
		if (NoteDateFormat.Format == 4) // eg. 09/23/22
		{
			date = month.ToStringLen(2) + "/" + day.ToStringLen(2) + "/" + year.ToStringLen(4);
		}
		else
		if (NoteDateFormat.Format == 5) // eg. 12/9/22
		{
			date = monthNumber + "/" + dayNumber + "/" + year.ToStringLen(4);
		}

		return date;
	}

	// Returns the suffix of a date number (for lack of a more educated term)
	string GetNumberDateyThingy(int number)
	{
		switch (number % 10)
		{
			case 1:  return NoteDateFormat.DaySuffix.Get(0);
			case 2:  return NoteDateFormat.DaySuffix.Get(1);
			case 3:  return NoteDateFormat.DaySuffix.Get(2);
			default: return NoteDateFormat.DaySuffix.Get(3);
		}

		return "";
	}

	// Gets the month as a string
	string GetMonth(int month)
	{
		return NoteDateFormat.MonthName.Get(month - 1);
	}
}

// Define the date format
class ZenNoteDateFormat
{
	int Format;
	ref array<string> DaySuffix;
	ref array<string> MonthName;
};

// Save config data
ref ZenNotesConfig m_ZenNotesConfig;

// Helper function to return Config data storage object
static ZenNotesConfig GetZenNotesConfig()
{
	if (!m_ZenNotesConfig)
	{
		Print("[ZenNotesConfig] Init");
		m_ZenNotesConfig = new ZenNotesConfig;
		m_ZenNotesConfig.Load();
	}

	return m_ZenNotesConfig;
};