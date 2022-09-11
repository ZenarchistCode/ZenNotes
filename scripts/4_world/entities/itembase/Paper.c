modded class Paper
{
    // Prepare required paper note variables
    private int m_NotePickupTries = 0;
    Pen_ColorBase m_Pen;

    // Delete paper object - clear pen reference
    void ~Paper()
    {
        m_Pen = NULL;
    }

    // Set note actions
    override void SetActions()
	{
		super.SetActions();
		RemoveAction(ActionWritePaper);
		AddAction(ActionZenWritePaper);
	}

    // Set the pen object used to write with
    void SetPen(Pen_ColorBase pen)
    {
        m_Pen = pen;
    }

    // Receive note data from client, then convert paper to written note
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        // Client-side receiver for server-formatted date
        if (rpc_type == ZENNOTERPCs.RECEIVE_NOTE_DATE)
        {
            string serverDateData;
            Param1<string> client_params = new Param1<string>(serverDateData);

            if (ctx.Read(client_params))
            {
                if (client_params.param1 && client_params.param1 != "")
                {
                    ZenNoteGUI.DATE_TEXT = client_params.param1;
                    m_UpdateTries = 0;
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateDateText, 250, false, client_params.param1);
                }
            }

            return;
        }

        // Server-side receiver for note data written by client/player
        if (rpc_type == ZENNOTERPCs.SEND_WRITTEN_NOTE)
        {
            int highBits, lowBits;
            GetGame().GetPlayerNetworkIDByIdentityID(sender.GetPlayerId(), lowBits, highBits);
            PlayerBase player = PlayerBase.Cast(GetGame().GetObjectByNetworkId(lowBits, highBits));

            if (!player) // If we can't identify the player who sent this note data, stop here.
                return;

            ZenNoteData clientNoteData;
            Param1<ref ZenNoteData> server_params = new Param1<ref ZenNoteData>(clientNoteData);

            if (ctx.Read(server_params))
            {
                if (server_params.param1)
                {
                    // Check if the note contains any blacklisted words
                    if (GetZenNotesConfig().IsBlacklisted(server_params.param1.m_NoteText))
                    {
                        // Log the blacklisted note for server admins
                        ZenNotesLogger.Log("Blacklist", "[BLACKLIST] " + sender.GetName() + " (" + sender.GetPlainId() + ") @ " + this.GetPosition() + " tried to write: " + server_params.param1.m_NoteText);

                        // If player warning is set, send it
                        if (GetZenNotesConfig().SendPlayerWarning != "")
                        {
                            Zen_NoteSendMessage(player, GetZenNotesConfig().SendPlayerWarning);
                        }

                        return;
                    }

                    // Convert to written note item
                    ZenNoteData noteData = new ZenNoteData;
                    noteData.m_FontIndex = server_params.param1.m_FontIndex;
                    noteData.m_DateText = server_params.param1.m_DateText; // Server date
                    noteData.m_NoteText = server_params.param1.m_NoteText;
                    noteData.m_ARGBColour = server_params.param1.m_ARGBColour;

                    // If quantity of this paper is 1, swap the actual item
                    if (this.GetQuantity() == 1)
                    {
                        // Prepare item replacement lambda
                        ReplacePaperWithNoteLambda lambda = new ReplacePaperWithNoteLambda(this, "ZenNote", noteData);

                        // If player is holding the note, replace it in their hands - otherwise replace the item elsewhere
                        if (player.GetItemInHands() == this)
                            player.ServerReplaceItemInHandsWithNew(lambda);
                        else
                            player.ServerReplaceItemWithNew(lambda);
                    }
                    else
                    {
                        this.SetQuantity(this.GetQuantity() - 1);

                        // Spawn a note on the ground
                        ZenNote noteGround = ZenNote.Cast(GetGame().CreateObjectEx("ZenNote", this.GetPosition(), ECE_PLACE_ON_SURFACE));

                        // If note did not spawn, stop here.
                        if (!noteGround)
                            return;

                        // Copy note data to the written note object
                        noteGround.SetNoteData(noteData);

                        // If player is holding the paper stack, replace it in their hands with a note and put paper back in inventory
                        if (player.GetItemInHands() == this && noteGround)
                        {
                            // Put the paper stack back in its reserved location, and place note into player's hands
                            HumanInventory inventory = player.GetHumanInventory();

                            if (!inventory)
                                return;

                            // Get reserved paper location in inventory (dst)
                            InventoryLocation loc_dst = new InventoryLocation;
                            int reservedIndex = inventory.FindUserReservedLocationIndex(this);
                            inventory.GetUserReservedLocation(reservedIndex, loc_dst);

                            // Get current paper inventory location (src)
                            InventoryLocation loc_src = new InventoryLocation;
                            this.GetInventory().GetCurrentInventoryLocation(loc_src);

                            // If player has moved an item into the paper's reserved slot, or ServerTakeToDst fails, just take paper to anywhere in inventory.
                            if (reservedIndex == -1 || !player.ServerTakeToDst(loc_src, loc_dst))
                            {
                                // If we can't take the paper stack to inventory for whatever reason, do nothing, leave it in player's hands and spawn note on ground
                                player.ServerTakeEntityToInventory(FindInventoryLocationType.ANY_CARGO, this);
                            }

                            // Used to loop & try to take note to hands a few times (necessary because it takes a moment to update hand state when paper is put away)
                            m_NotePickupTries = 0;

                            // Attempt to pick up the note from the ground
                            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TakeNoteToHands, 200, true, player, noteGround);
                        } 
                    }

                    // Consume pen quantity
                    if (GetZenNotesConfig().PenConsumeQuantity > 0 && m_Pen)
                    {
                        m_Pen.SetQuantity(m_Pen.GetQuantity() - GetZenNotesConfig().PenConsumeQuantity);
                    }

                    // Log note for server admins
                    ZenNotesLogger.Log("General", sender.GetName() + " (" + sender.GetPlainId() + ") @ " + this.GetPosition() + " wrote: " + noteData.m_NoteText);
                }
            }
        }
    }

    // Pick up the note from the ground (TODO: Convoluted, there must be a better/more efficient way to do this!)
    private void TakeNoteToHands(PlayerBase player, EntityAI item)
    {
        if (item && player && player.IsAlive() && !player.IsUnconscious() && !player.IsPlayerDisconnected())
        {
            // For some reason this approach bugs the player's hands?? Seems to work in my other mods though, not sure what I'm doing wrong...
            //EntityAI note;
            //note = player.GetHumanInventory().CreateInHands("ZenNote");

            // Get inventory location of note (should be ground)
            InventoryLocation loc_src = new InventoryLocation;
            item.GetInventory().GetCurrentInventoryLocation(loc_src);

            // Create new inventory location with note (but set it to Hands location)
            InventoryLocation loc_dst = new InventoryLocation;
            loc_dst.Copy(loc_src);
            loc_dst.SetHands(player, item);

            // Take the ground note item to hands
            player.ServerTakeToDst(loc_src, loc_dst);

            // Increment pickup tries
            m_NotePickupTries++;

            // Try to pick up note for ~1 second, if failed just abandon picking up the note and leave it on the ground
            if (m_NotePickupTries >= 5)
            {
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.TakeNoteToHands);
            }
        }
        else
        {
            // If there is no note, no player object, or they're dead, or they're uncon, or they're disconnected, stop trying to pick it up and leave note on ground.
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.TakeNoteToHands);
        }
    }

    // Updates the text GUI if it's visible
    int m_UpdateTries = 0;
    void UpdateDateText(string txt)
    {
        m_UpdateTries++;
        UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
        if (menu)
        {
            ZenNoteGUI noteMenu = ZenNoteGUI.Cast(menu);
            if (noteMenu)
            {
                noteMenu.SetDate(txt);
            }
        }
        else
        if (m_UpdateTries < 10) // Try 10 times (2.5secs) to update the date, then give up.
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateDateText, 250, false, txt);
        }
    }

    // For debug purposes / to send blacklist warnings
    void Zen_NoteSendMessage(PlayerBase player, string message)
    {
        Param1<string> m_MessageParam = new Param1<string>("");
        if (GetGame().IsServer() && m_MessageParam && player.IsAlive() && !player.IsPlayerDisconnected() && message != "")
        {
            m_MessageParam.param1 = message;
            GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
        }
    }
}

// Lambda for replacing paper with written note object
class ReplacePaperWithNoteLambda extends ReplaceItemWithNewLambdaBase
{
    ref ZenNoteData m_NoteData;

    void ~ReplacePaperWithNoteLambda()
    {
        m_NoteData = NULL;
        delete m_NoteData;
    }

    void ReplacePaperWithNoteLambda(EntityAI old_item, string new_item_type, ZenNoteData data)
    {
        m_NoteData = data;
    }

    override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
    {
        super.CopyOldPropertiesToNew(old_item, new_item);

        ZenNote note = ZenNote.Cast(new_item);
        note.SetNoteData(m_NoteData);

        if (!note.GetParent()) // If not in player's hands, copy paper location & orientation to new object
        {
            note.SetOrientation(old_item.GetOrientation());
            note.SetPosition(old_item.GetPosition());
        }

        m_NoteData = NULL;
    }
}