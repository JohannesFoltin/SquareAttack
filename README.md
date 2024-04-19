# Square Shooter

This game is based on the NES classic Duck Hunt. 
In this game, however, the aim is to shoot the evil square out of the air to save the world. Because alien squares want to take over the world and only you can stop them!
Unfortunately, you don't have much ammunition and the square is getting faster and faster. How far can you make it?
So get ready, pick up your mouse and aim for the high score!


The game was developed as part of the HWR (Hochschule f�r Wirtschaft und Recht) C++ course.

## How to play

1. Extract the windows_x64.zip
2. Run the SquareShooter.exe
3. Shoot the flying square with your left mouseclick out of the air.

## How to build

### Prequisites

- cmake min 3.16

### For Windows:
Make sure to have Visual Studio (e.g. 2022 Community) installed with the C++ development tools. Then run the following
commands in the command prompt:

```bash
cmake -G "Visual Studio 17 2022" -A x64 -S . -B "build64"
cmake --build build64 --config Release
cd build64/bin
mv .\textures\ .\Release\
mv .\font\ .\Release\
```

The game can be run by executing the `SquareShooter.exe` executable in the `build64/bin/Release` directory.

## For Linux

Have a look at the Github Actions Tab ;)

# Used Libarys
- SFML 2.6

# Known Issues
- It's an 1902x1080 window, that means i could be to big for some Screens