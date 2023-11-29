# Void
Void Engine

This project serves as a sandbox to try out the different types of functionality of FMOD.

In this project, we played around with the 3D audio and the doppler effect. Audio Occlusion was also part of the assignment, but I failed to implement this functionaliy.
The wireframes at the gate would function as the barriers/walls, but the effect itself is not there.

To showcase the doppler effect, I implemented a very good camouflaged indian, running left and right behind the starting point.
When walking through the gate, music will play, which will stop when the player is outside the trigger point.

There are foosteps, which are also the user interacted sounds. (these can be hard to hear, so walking away from the scene is advised to listen to them)

The DSP sounds can be found on:
- the footsteps, which shift in pitch every step (1)
- Both guns, which make use of reverb (2)
- The theme song when entering the gate, which makes use of a chorus DSP. (1)

Everything is implemented except for the complete audio occlusion.

Excuses me for the lack of documentation... I was really short on time and did not want to delay another day and taking another penalty...



Building the project is as easy as clicking build. Make sure the absolute path does not contain any spaces. In case the project fails to build, click GenerateFiles in the sln folder.