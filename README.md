# pchlists to reabank

Simple tool to import the patch list from a Nord Modular G2 synth into Reaper's ReaControlMIDI plugin.

## Workflow

- Power on the synthesizer, and make sure it is connected to the computer via USB
- Create a directory on your filesystem where all the patch data will be uploaded
- Open the Nord Modular G2 Editor, and check that it communicates with the synth
- In the menu, select Synth/Bank upload
- Upload all the banks, one by one, to the directory you created before
- Launch this tool with this directory path as first parameter, and a destination file path as second parameter

  Example (Windows): pchList2reabank.exe "D:\Studio\Patches\G2X\2025-01-19 bank uploads" "C:\Users\zeebyezon\AppData\Roaming\REAPER\Data\G2X.reabank"
- The load the file G2X.reabank in ReaControlMIDI
