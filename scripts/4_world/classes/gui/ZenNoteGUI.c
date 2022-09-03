class ZenNoteGUI extends UIScriptedMenu
{
	// Layout constants
	static const string LAYOUT_FILE = "ZenNotes/data/gui/layouts/NoteGUI.layout";

	// Font variables
	private int m_FontIndex = 0;

	// Text widgets
	private ref array<ref MultilineEditBoxWidget> m_TextBoxes = {};
	private ref array<ref TextWidget> m_Dates = {};

	// Button widgets
	private ButtonWidget m_ExitBtn;
	private ButtonWidget m_SelectFontBtn;

	// Pen & paper variables
	private ItemBase m_Paper;
	private int m_PenColour;
	static string DATE_TEXT = "";

	void ~ZenNoteGUI()
	{
		// Cleanup - unlink widgets
		m_ExitBtn.Unlink();
		m_SelectFontBtn.Unlink();

		// Unlink arrays
		foreach (MultilineEditBoxWidget box : m_TextBoxes)
		{
			box.Unlink();
		}

		foreach (TextWidget date : m_Dates)
		{
			date.Unlink();
		}
	}

	// Init widgets
	override Widget Init()
	{
		// Load layout
		layoutRoot = GetGame().GetWorkspace().CreateWidgets(LAYOUT_FILE);

		// Load text widget arrays
		for (int i = 0; i < 100; i++)
		{
			MultilineEditBoxWidget box = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoteText" + i));
			TextWidget date = TextWidget.Cast(layoutRoot.FindAnyWidget("DateText" + i));

			if (box && date)
			{
				m_TextBoxes.Insert(box);
				m_Dates.Insert(date);
				date.SetText(DATE_TEXT);
			}
			else
			{
				break; // We've loaded all textboxes
			}
		}

		// Load required widgets
		m_ExitBtn		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseBtn"));
		m_SelectFontBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FontBtn"));

		if (!m_ExitBtn || !m_SelectFontBtn)
		{
			ErrorMsg("Failed to load widgets for ZenNotes!");
			return NULL;
		}

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetMission().GetHud().Show(false);

		return layoutRoot;
	}

	// Set the paper reference object
	void SetPaper(ItemBase item)
	{
		m_Paper = item;
	}

	// READ-ONLY NOTE DATA SENT - we're reading a note that's already written and saved.
	void SetNoteData(ZenNoteData data)
	{
		// Set font index first
		SetFontIndex(data.m_FontIndex);

		MultilineEditBoxWidget edit_box = m_TextBoxes.Get(m_FontIndex);
		TextWidget date = m_Dates.Get(m_FontIndex);

		if (!edit_box || !date)
		{
			OnExitBtnClick();
			return;
		}
			

		edit_box.Show(true);
		edit_box.SetText(data.m_NoteText);
		date.Show(true);
		date.SetText(data.m_DateText);

		// Hide all editboxes that are not equal to the specified font index editbox sent from the server
		for (int i = 0; i < m_TextBoxes.Count(); i++)
		{
			MultilineEditBoxWidget temp_box = m_TextBoxes.Get(i);
			TextWidget temp_date = m_Dates.Get(i);

			if (i != m_FontIndex)
			{
				temp_box.Enable(false);
				temp_date.Enable(false);
				temp_box.Show(false);
				temp_date.Show(false);
			}
		}

		// Hide font selection
		m_SelectFontBtn.Enable(false);
		m_SelectFontBtn.Show(false);

		// Set text colour
		SetPenColour(data.m_ARGBColour);
	}

	// Set note date (formatted by server)
	void SetDate(string date)
	{
		DATE_TEXT = date;
		TextWidget dateWidget = m_Dates.Get(m_FontIndex);
		if (dateWidget)
		{
			dateWidget.SetText(DATE_TEXT);
		}
	}

	// Set font index
	void SetFontIndex(int index)
	{
		m_FontIndex = index;
	}

	// Set pen text colour
	void SetPenColour(int colour)
	{
		// Set all edit box colours (for editing - if read only this doesn't matter)
		foreach (MultilineEditBoxWidget box : m_TextBoxes)
		{
			box.SetColor(colour);
		}

		// Set all date colours
		foreach(TextWidget date : m_Dates)
		{
			date.SetColor(colour);
		}

		m_ExitBtn.SetTextColor(colour);
		m_SelectFontBtn.SetTextColor(colour);
		m_PenColour = colour;
	}

	// Set read only
	void SetReadOnly(bool readOnly)
	{
		// Set all edit box read-only
		foreach (MultilineEditBoxWidget box : m_TextBoxes)
		{
			box.Enable(!readOnly);
		}
	}

	// Handles clicks on button widgets
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);

		if (w == m_ExitBtn)
		{
			return OnExitBtnClick();
		}

		if (w == m_SelectFontBtn)
		{
			return HandleFontClick();
		}

		return true;
	}

	// Handle font click
	bool HandleFontClick()
	{
		// Prepare txt string for swapping editbox contents
		string msgTxt;

		// Get old edit box
		MultilineEditBoxWidget edit_box_old = m_TextBoxes.Get(m_FontIndex);
		TextWidget date_old = m_Dates.Get(m_FontIndex);

		if (edit_box_old)
		{
			m_FontIndex++;
			if (m_FontIndex >= m_TextBoxes.Count())
				m_FontIndex = 0;

			MultilineEditBoxWidget edit_box_new = m_TextBoxes.Get(m_FontIndex);
			TextWidget date_new = m_Dates.Get(m_FontIndex);

			if (edit_box_new && date_new)
			{
				edit_box_old.GetText(msgTxt);
				edit_box_new.SetText(msgTxt);
				date_new.SetText(DATE_TEXT);

				edit_box_old.Show(false);
				edit_box_old.Enable(false);
				date_old.Show(false);

				edit_box_new.Show(true);
				edit_box_new.Enable(true);
				date_new.Show(true);
			}
			else
			{
				ErrorMsg("NEW EDIT BOX NOT FOUND!");
			}
		}
		else
		{
			ErrorMsg("OLD EDIT BOX NOT FOUND!");
		}

		return true;
	}

	// Close GUI
	bool OnExitBtnClick()
	{
		string msgTxt;

		MultilineEditBoxWidget box = m_TextBoxes.Get(m_FontIndex);

		if (box)
		{
			box.GetText(msgTxt);
		}
		else
		{
			ErrorMsg("EDIT BOX NOT FOUND FOR FONT INDEX " + m_FontIndex);
			return false;
		}

		// Send written note data to server to save + sync to other clients
		if (m_Paper)
		{
			ZenNoteData note_data = new ZenNoteData;
			note_data.m_FontIndex = m_FontIndex;
			note_data.m_NoteText = msgTxt;
			note_data.m_DateText = DATE_TEXT;
			note_data.m_ARGBColour = m_PenColour;

			Param1<ref ZenNoteData> params = new Param1<ref ZenNoteData>(note_data);

			if (msgTxt != "" && GetGame().GetPlayer())
			{
				m_Paper.RPCSingleParam(ZENNOTERPCs.SEND_WRITTEN_NOTE, params, true, NULL);
			}
		}

		UIManager uiManager = GetGame().GetUIManager();

		if (!uiManager)
			return true;

		// Exit menu and restore player controls
		UIScriptedMenu menu = uiManager.GetMenu();
		if (menu)
		{
			ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
			if (noteMenu)
			{
				uiManager.HideScriptedMenu(noteMenu);

				Mission mission = GetGame().GetMission();
				if (mission)
				{
					mission.PlayerControlEnable(true);
					mission.GetHud().Show(true);
				}
			}
		}

		return true;
	}

	// Display an error message
	private void ErrorMsg(string s)
	{
		Print("[ZenNotesGUI] Error - " + s);
		ZenNote_DebugMsg("[ZenNotesGUI] Error - " + s + " Please tell the server admin to contact Zenarchist");
	}

	// Used only for debugging
	private void ZenNote_DebugMsg(string msg)
	{
		GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", msg, ""));
	}
}