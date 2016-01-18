========================================================================
    CONSOLE APPLICATION : ROFLcopter Project Overview
========================================================================
Please install Visual C++ Redistributable to run this game on a PC which does not have
Visual Studio 2015 installed. You can find it in the appdir/debug/vs_redist.x86-64/


ROFLcopter was created as a homework project for my 1st year introducting to C++
class.

It is similar to Flappy Bird, although it stretched more horizontally than vertically. 
The real inspiration is the flash game "Chopper".

The gameplay is simple: press any key for the ROFLcopter to go up and do not crash into the wall of WTF.




========================================================================
CHANGELOG
========================================================================
v1.2.2:

-minor changes in the code, deleted unnecessary files

v1.2.1:

- removed text files from "Art" folder, replaced them with .dat files for release
- changed the height of :WTF: walls and "Score" for better compatibility with 1080p screens 
(still not compatible with lower resolutions[?])

v1.2:

- fixed some minor ghosting issues
- reworked the main menu so that it does not crash while viewing the Scoreboard
- reworked the collision system to be more accurate
- removed unnecessarry ASCII art files

v1.1:

- changed splash screen animation to use gotoxy() function instead of
reading from text file
- started the implementation of a struct type scoreboard for easier
sorting

v1.0:

- changed the propeller animation from :LOL: to :ROFL: 
- added menu number options
- added credits