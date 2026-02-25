# Keypress Visualizer

A graphical application that allows you to visualize the keys pressed on your keyboard.

![Screenshot of program working](/assets/image.png)

## Table of Contents

- [Description](#description)
- [Getting Started](#getting-started)
  - [Dependencies](#dependencies)
  - [Executing Program](#executing-program)
- [Authors](#authors)
- [Version History](#version-history)
- [License](#license)
- [Acknowledgements](#acknowledgments)

## Description

Keypress Visualizer is a real-time graphical desktop application built in C++ using the SFML multimedia library. The program visually represents keyboard input by rendering a partial QWERTY layout (only alphabet letters and space key) and dynamically highlighting keys as they are pressed.

Keypress Visualizer uses scancode-based input detection to ensure accurate mapping. The key sprites are pulled from a spritesheet that has 26 identical key "frames" that only contain the frame (actual key print coming in future versions), and an unique frame for the space key (as it takes more space than regular keys).

When a key is pressed is pressed:

- A randomly generated highlight color is assigned (this is the color the key is going to turn into)
- The key snaps from its base color to the highlight color, then slowly fades back to its base color based on time-based interpolation.

This project has a `KeypressVisualizer` class that inherits from `sf::Drawable` class so that it can have its own draw method, which allowed me to module exactly how I wanted the keys to be drawn to the screen (although the only thing I'm really doing in the overriden `draw()` is iterating from the keylist and drawing them to the screen while also applying a scale to the full picture).

## Getting Started

### Dependencies

- gcc: Since this is a c++ project you need gcc to compile the code. You can follow the tutorial for [downloading, installing and configuring gcc here](https://gcc.gnu.org/install/).
**Note:** You may use a different compiler, but you would have to modify the Makefile or manually compile in order to run the program.
- sfml: This project uses SFML as the bulk of it, as it handles essentially all the events, inputs, and drawing.
- make: I used Makefiles to automate the compiling process. If you wish to utilize them as well, you can [download, install, and configure make here](https://www.gnu.org/software/make/#download).

### Executing program

- You may choose to either clone the repo, or download the project as a zip. In whichever case you can run the program the same way:
  - Cloning the repo: You can clone the repo by doing the following command on the target directory:

```shell
  git clone https://github.com/rhuangsaragioto/KeypressVisualizer.git
```

**Note** that this will also create a copy of the repository in your machine. If you only  wish to have a copy of the directory, you can [download the project's zip here](https://github.com/rhuangsaragioto/KeypressVisualizer/archive/refs/heads/main.zip).

When you have the directory on your local machine, along with gcc and make configured, you can run the project with the following command:

```zsh
make
```

and

```zsh
./KeypressVisualizer
```

## Authors

I am the sole author of this project, you can find some of my information below.

- LeetCode - [@rhuangsaragioto](https://leetcode.com/u/rhuangsaragioto/)
- GitHub - [@rhuangsaragioto](https://github.com/rhuangsaragioto)
- LinkedIn - [@rhuansaragioto](https://www.linkedin.com/in/rhuan-saragioto-4043662aa/)

## Version History

- 0.3
  - Made colors random for each new keypress.
- 0.2
  - Added the Naoya background
  - See [commit history](https://github.com/rhuangsaragioto/KeypressVisualizer/commits/main/).
- 0.1
  - Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments

- [README-Template.md](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc) - The README file's template you're currently reading came from this legend's  gist. Go show them some support.
- [SFML Documentation](https://www.sfml-dev.org/documentation/3.0.2/) - SFML has pretty good documentation, I'd recommend checking it out in case you don't understand something from the source code.
