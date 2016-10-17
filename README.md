# ColorLightMCUfirmware
firmware

The firmware of te ColorLight

using cc2541, check "Projects/ble/SimpleBLEPeripheral/CC2541DB/SimpleBLEPeripheral.eww" if you have "IAR Embedded Workbench IDE".
Or you can check "Projects/ble/SimpleBLEPeripheral/Source" to get ".c" and ".h" files only.

Under "simpleBLEPeripheral.c", you can see a function named "Code" at the top, and that's the code from TianYu Sun realizing the UNI/O.
Then is the function "SetGRBAll", transfer a char list to LED sequence.
Remember to care of "CB", or, "Callback". That's the function called when messgae is in, whether from BLE or from series.
In this file you can get almost all the information needed.

Good Luck! PKU-Makers!
