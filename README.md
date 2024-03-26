# fwm
tiling window manager for windows
like i3wm or suckless dwm but much simpler, this is just a proof of concept


# HOW TO RUN: FOLLOW IN ORDER
LAUNCH X64 VS NATIVE TOOLS 
"cl wm.c user32.lib"
"cl /c wm_dll.c"
"link wm_dll.obj user32.lib /dll"
"wm.exe"
