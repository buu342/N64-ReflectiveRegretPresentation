# Reflective Regret

This repository contains a lot of stuff regarding the "Reflective Regret: Adventures in N64 Homebrew Development" presentation I gave at [Inércia 2021](http://inercia.pt). The presentation was given at the Demoparty halls while simultaneously livestreamed to Twitch. In case you missed it, however, you can watch this recording:

[![Reflective Regret: Adventures in N64 Development (Inércia 2021 Talk)](https://i.ytimg.com/vi/ZgPWE0Wkg7g/hqdefault.jpg)](https://www.youtube.com/watch?v=ZgPWE0Wkg7g "Reflective Regret: Adventures in N64 Development (Inércia 2021 Talk)")

This repository is split into a bunch of folders, like so:
* `Images` - The source files for images and sprites used in the presentation
* `Models` - The source files for models (and their textures) used in the presentation
* `Presentation` - A (backup) PowerPoint of the presentation, a rough draft of the script that was used, and a collection of addendums + clarifications. Be aware that the script is not final nor a transcript, it was just written to help me structure the presentation. Captions are also available in this folder (in SRT format). If you wish to help in translating this presentation to other languages, feel free to open a Pull Request with more captions!
* `ROM` - The source code for the presentation ROM (IE the one that you actually see in the video, which was meant to run on the console (but unfortunately had to be run on an Emulator due to hardware issues)).

Regarding the ROM itself, it was finished about 5 hours before the actual presentation was given, so the code's structure is nowhere near optimal. I've since then have updated it with a fix or two and with a documentation pass, but the overall structure remains (albeit with a few comments regarding design decisions). If you're using the WindowsXP setup, compiling the ROM is just a matter of executing `makeme.bat`. Compiling with the ModernSDK, however, requires a rewrite of the makefile and the replacement of the Spec file with a linker script. 

The ROM allows for compiling with USB output via [UNFLoader](https://github.com/buu342/N64-UNFLoader), and utilizes [Sausage64](https://github.com/buu342/Blender-Sausage64) for character animation. There exists a macro in `config.h` called `EMULATOR` that modifies the handling of Catherine's speed in `slide01.c`, which differs between emulator and console due to clock speeds. If I had more time, I would have fixed this properly by making Catherine's position update between game ticks, rather than as soon as the CPU was available.