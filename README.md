# MAZE Granular ARP MIDI controller

**The winner project in "MaKE IT" innovation grants project 2023.**

I demonstrate how this works in [this video](https://youtu.be/gfWn8kauTtI). I explain the experience and the roots of the idea in my [blog](https://notdevkey.github.io/maze-midi/). We also got in on our local [newsletter](https://www.ventasbalss.lv/zinas/sabiedriba/49566-vatp-komanda-izveido-muzikas-instrumentu-video) :D

## Repo structure

- `src/main.cpp` - the core functionality of the Arduino Uno MIDI controller.
- `schema` - contains KiCad schematica files for the MIDI controller final version.

If you really want to try recreating this and don't have an Arduino that supports MIDI output natively, you will need to follow the workaround I found:

- Get [HairlessMIDI](https://projectgus.github.io/hairless-midiserial/?source=post_page---------------------------). This emulates the MIDI signal by creating a bridge on the serial port the Arduino is attached to. Keep in mind that this means sending specific bytes instead of straight-forward MIDI messages, but I created a function in my code that simplifies this.
- Get [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html). It creates a "virtual MIDI cable" that can be recognized by other applications. In my case, I needed to wire up the MIDI signal to Ableton, where I have synths that can read the incoming MIDI signal to play a note.

![IMG-1561](https://github.com/notdevkey/maze-midi/assets/66126144/ab0fcac6-b26c-493f-b9e7-71d19ba59b3d)
