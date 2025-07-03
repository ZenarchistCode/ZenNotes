What Is This?

This is another notes mod.

The main advantage of this one is that it's open-source and I allow repacking so you have full control over it as a server admin, and it also allows you to select from several different font styles and colors (and you can easily add your own).

It also allows you to blacklist certain words that you don't want on your server. It will log all player notes to a logs folder including player names, SteamIDs and note locations to make it easy to moderate.

Here is a video showing how the notes work: https://youtu.be/UiiRnS5Zehs

And here's a video guide on how to add/change fonts: https://youtu.be/KSwArPgOcwA

Installation Instructions:

Install this mod like any other mod - copy it into your server folder and add it to your mods list. It must be run on both server and client. Make sure to copy the .bikey into your server keys.

Also don't forget to copy over the types.xml into your server types. You can either import my types.xml separately (here's a guide: https://www.youtube.com/watch?v=PAAEhdiQ_vE) - OR make sure to only copy & paste lines 3-36 into your vanilla types.xml file.

ZenNote is the written note object - you'll want to set that to be persistent for at least a day, by default it's set to 2 weeks. The pens are all optional and you should adjust their spawn numbers according to your preference (remove any colors you don't want, and set the nominal/min/max values to whatever is appropriate for your map & server setup).

Repack & Source Code:

You can repack this mod if you like, and do anything else you want with it for that matter. Just keep in mind my future updates won't be applied so make sure to check back for new versions if you notice any bugs. The source code is on my GitHub at www.zenarchist.io

Enjoy!

-----------------------------------------------------------------------------------

JSON CONFIG:

ConfigVersion - Don't touch this or it will reset your config settings
PenConsumeQuantity - Pens have a max quantity of 100 and each use consumes this quantity. Set this to 0 to disable pen ink consumption
Format - Options are 0 to 5. 0 = no date, 1 = 3rd September 2022, 2 = 03/09/2022, 3 = 3/9/2022, 4 = 09/03/2022, 5 = 9/3/2022
DaySuffix - Only applies to date format #1. Sets the day suffix (eg. "3rd", "1st" etc)
MonthName - Only applies to date format #1. Name of the current month.
WordBlacklist - A list of blacklisted words. Separate each line like this:
"badword1",
"bad word 2",
"bad word 3"

No comma on the last line. These words are NOT case-sensitive.

SendPlayerWarning - This is the message sent to the player if they write a blacklisted word. Set to blank "" to disable warnings.