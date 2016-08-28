#Mario Paint Composer DS

A historical archive for a project I created prior to any formal programming education.

![Alt text](/screenshots/mariopaintcomposer.png?raw=true "Mario Paint Composer DS")

##Original Readme:

----Mario Paint Composer DS----
    ---Bullet Bill Release---

Created by:
	BassAceGold

Graphics by:
	Reluttr
	Lord Toon
	Dino340

Mario Paint Composer DS is an indirect remake of the music composer tool found in the Super Nintendo game "Mario Paint" with a few new adaptations which I added in from the PC version created by unFun Games (http://www.unfungames.com/). Please note, I am not responsible for the pc version, these two programs merely share the same name and that is all. This is not a direct port of any version, it is completely coded by myself.

Features: These are new features continueing from the ones already in the snes version

-Saving and Loading of songs
-Sharp and Flat notes
-more lower ranged notes
-5 new note types
-5 notes per can be played at once rather then the 3 limit
-Longer songs
-Different Tempo's per page



The forum can be found here: http://nds-help.com/mpcforum/

--Installation--

-Copy "mpcsongs" folder to anywhere on your card
-DLDI Patch the rom
-Copy rom to card
-copy mpcds.ini file to same directory as rom
-edit mpcds.ini to point to your mpcsongs folder and enjoy!

--Errors--

"Failed to initialize filesystem"
Your flashcards firmware must support the argv in order for the file system to work correctly. If your card does not support argv, then you will need to use Homebrew menu to launch it.

http://wiki.devkitpro.org/index.php/Homebrew_Menu

"Ini file not found"
The ini file must be in the same folder as the rom file is and named "mpcds.ini" with no quotes.

"Failed to find songs folder"
Make sure the ini file contains something like this:

SongDir = /folder1/folder2/songfolder/

-Check for missing '/' at the beginning and end of the directory in the ini
-ensure correct spelling and capitalization is used
-do not exceed 256 characters


--Controls--

=Main Screen=
-Using the touch screen you can select what note type you want at the top bar, then you can drag it where ever you want on the music staff.

-While dragging it, if you press Up (or X) you can change the note to a Sharp. Pressing Down (or B) will make the note Flat. 

-Releasing the stylus on the staff will place the note, which you can remove by double tapping the note with the stylus

-Left and Right (or Y and A) will move between pages, this program supports up to 257 pages which hold 35 notes each. 
   
-When you have more then one page, you can drag the scroll bar to move quickly between pages, the rewind button (RR) will send you right back to the first page.

-L and R buttons can be used to control the top screen. Pressing them will switch between pages and holding them will make it switch faster.

-Pressing Select will allow you to delete a page which will remove it from the song rather than just clearing the page

-Pressing Start will ask to insert a blank page into the song

=File Browser=
-In the loading screen, you can select the file you want to load with the stylus or d-pad. 

-You can open files with a double tap, pressing A, or tapping the folder icon in the bottom. 

-Exiting is done by taping the X next to the folder icon. 

-To scroll through the files, use the arrow icons in the bottom right.


Everything else is pretty self explanitory	

--Bullet Bill Release July 28 2010
-Compiled with latest libraries, may fix card compatibilities
-Uses NitroFS for argv support, results in much faster startup time
-can now change the song directory via mpcds.ini file which must be in the same directory as the rom
-removed outdated splash screens
-removed wifi news feature
-fixed scrolling issue in the filebrowser using the bottom right arrows
-updated keyboard
-updated installation instructions and controls. Also added error faq to readme.



--Paratroopa Release March 18 2009--
-tweaked stylus locations for note placement
-amplified pig sound
-added ledger bars
-amplified heart sound
-added turtle shell sound
-updated text font
-tempo control icons enlarged
-added Delete Page to Select button
-tweaked note sign controls (makes it easier to place a continuous line of sharp or flat notes)
-fixed a filebrowser bug
-increased max tempo
-Dynamic Tempos (can set an individual tempo per page)
-added insert blank page to Start button
-fixed brief graphical glitches on page switching
-fixed tunings of mushroom notes
-tweaked the page slider
-re-arranged the song information displayed & removed tempo due to dynamic tempo
-fixed game icon transparency
-fixed last note detection for looping

--Koopa Release Oct 28 2008--

-Fixed the D sharp note to play the right sound
-Fixed end of song detection
-Removed the appearance of being able to place notes while a song is playing
-Last song saved/loaded's file name will be remembered in the save menu so you don't have to retype it out
-Can now cycle through all note states with the D-pad (meaning you can make the note natural,sharp or flat rather then just sharp and flat)
-More error checking for FAT operations (Checks if mpcsongs folder is on card, if not then will create the folder. Also detects if FAT was initialized properly)
-Better eraser controls (Double Tap note to delete it)
-can now save author name in file
-When loop is turned on, will loop from last note played rather then the end of the last page
-increased max tempo and tweaked the tempo slider a bit
-Added High A, High A Sharp, High B and High C notes
-prevents users from typing restricted symbols in filename (while saving)
-Can view other pages on top screen using L and R to scroll through pages (hold L or R to scroll faster)
-News system! Click the envelope button (make sure wifi is configured)
-Note type selection tweaks
-saving compatibility hopefully fixed
-new graphics
-Running/jumping mario at the top now :P



--Goomba Release Sept 28 2008--
 Initial Release






