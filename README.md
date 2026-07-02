# Spiraling Out
## Spiral Chess Simulator by Mx. M

Congrats on finding the repository! If you're confused, I urge you to check out the [website](https://mx-m29.github.io/spiraling-out) first, open the help menu by clicking the button on the bottom left, and read the explanations. And also play around a little! It's really fun!

Here you'll find the guts of the website, as well as the original C++ source code I wrote to run the simulations. \
I'm freshly out of college and inexperienced in writing READMEs so forgive me if this one sucks.

## Contents

The `code/` folder contains a copy of the original C++ project I wrote before deciding to make a website. `code/include/` and `code/src/` contain the headers and implementation files for the custom libraries, respectively. You know what C++ projects look like. \
The file `code/simulation.cpp` is explained in the next section.

Anything outside the `code/` folder is website-related. `index.html`, the icon, and the `assets/` folder are all your standard static site affair. \
Because the simulation logic code is written in C++, I used [Emscripten](https://github.com/emscripten-core/emsdk) to compile it into Wasm and JS in order to use it on a static webpage. The compiled files are `knights_module.wasm` and `knights_module.js`. (The original project name was "Knights," hence those names)

## Usage

This section does not detail how to use the website. For that, I direct you once again to the website's help menu accessed by clicking the button on the bottom left.

Instead, this section describes how to use `code/simulation.cpp` to run your very own spiral chess experiments. Do you want to set parameters outside the arbitrary limits I chose for the website? Do you want to create a custom piece with more than 50 movement points? Do you want to break my shoddy code by abusing edge cases I purposefully left unattended? Now's your chance to do all that and less.

Changing the simulation parameters is trivial. Adding new pieces is a bit trickier. Every piece needs a Color object, an enemies integer, and some object that describes its movement. 

### Color
The color is simple. It's just RGB values ranging from 0 to 255.

### Enemies
A given piece's enemies are defined by a single 32-bit integer, and every bit determines whether or not the piece is "attacked by" another. This is why in the examples the enemy ints are written in binary, though obviously they don't have to. \
For example, if a given piece's enemy integer is set to `0b110`, this means that if either piece #2 or #3 in the turn order target a certain cell, this piece cannot be placed on that cell. Yes, pieces can attack themselves too. \
I understand this may seem a bit confusing and upside down but it made the code a lot easier (and faster!). This also means there's a limit of 32 pieces in a single simulation.

### Movement
The way each piece moves is explained in depth in the website's help menu and using the website itself will help make sense of the following. \
A Knight takes an XY object for movement, analogous to the way the website lets you input two numbers for dx and dy. A Custom piece takes a vector of XYs, each representing a relative movement point. All the other pieces (King, Queen, Bishop, Rook, Taxi) just take one integer as their range.

### Examples
A black Knight with normal chess movement (2, 1) that is attacked by piece #3: 
```cpp
pieces.push_back(new Knight(Color{0, 0, 0}, 0b100, XY{2, 1}));
```

A cyan King of range 3 that is attacked by pieces #1 and #2: 
```cpp
pieces.push_back(new Knight(Color{0, 255, 255}, 0b11, 3));
```

A yellow Taxi of range 4 that is attacked by every piece except itself, it being piece #3 of 4: 
```cpp
pieces.push_back(new Taxi(Color{255, 255, 0}, 0b1011, 4));
```

A Custom piece with a random color and some crazy movement that is attacked by pieces #2 and #5: 
```cpp
pieces.push_back(new Custom(Color{40, 178, 201}, 0b10010, std::vector<XY>{{2, 1}, {-1, 3}, {0, -3}, {-3, -2}}));
```

### Compiling

"Hey hold on, does that mean that you have to recompile the code every single time you want to make a change to the simulation?" Yup. Sorry about that. \
I actually made a version that takes a (path to a) JSON file as a command line argument and interprets its contents to run a new custom simulation. However, I didn't make that version public because I don't know what I'm doing and I'm scared of messing up the dependencies and attribution to nlohmann::json. Maybe some other day.

## Ok that's it bye
