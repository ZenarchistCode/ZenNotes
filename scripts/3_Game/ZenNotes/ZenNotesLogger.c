class ZenNotesLogger
{
	const static string LOG_FILE = "ZenNotes.log";
	const static string BLACKLIST_LOG_FILE = "ZenNotes_Blacklist.log";
	static string LOG_FOLDER = "$profile:\\Zenarchist\\Logs\\";
	static string DATE_FORMAT = "";

	static void Log(string txt, bool blacklist = false)
	{
		if (!FileExist(LOG_FOLDER))
		{
			MakeDirectory(LOG_FOLDER);
		}

		string file_path = LOG_FOLDER + LOG_FILE;
		if (blacklist)
		{
			file_path = LOG_FOLDER + BLACKLIST_LOG_FILE;
		}

		FileHandle logFile = OpenFile(file_path, FileMode.APPEND);
		if (logFile != 0)
		{
			FPrintln(logFile, ZenNotesGetDate() + " | " + txt);
			Print(ZenNotesGetDate() + " | " + txt);
			CloseFile(logFile);
		}
		else 
		{
			Error("Failed to open log file: " + file_path);
		}
	}
}

static string ZenNotesGetDate(bool fileFriendly = false)
{
	int year, month, day, hour, minute, second;

	GetYearMonthDay(year, month, day);
	GetHourMinuteSecond(hour, minute, second);

	string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
	if (fileFriendly)
	{
		date.Replace(" ", "_");
		date.Replace(".", "-");
		date.Replace(":", "-");
	}

	return date;
}