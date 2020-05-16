# Roadmap

Currently, I plan on having the following features:

### 1. Improved Workflow

I'd like to improve the workflow for mappers, artists and programmers. This isn't exactly easy however.

### 2. Better CI Integration

Source has no CI integration out of the box (I dont think many projects come with CI config scripts). 

I'd like to have good CI integration for:

1. Building the source-code itself

2. Building maps and other things that need to be compiled

3. Assembling the completed products into distributable packages

The map compilation might be a bit tricky, as it can take quite a while, and I don't think many CI services would allow you to run custom executables.

### 3. Cross Compile Support

Since I use Linux as my daily driver, it would be ideal to be able to cross compile to other platforms.

For Linux -> Windows compilation, WINE's MSVC can probably be used. Mingw likely won't work due to ABI issues.

### 4. Various Open-Source Reimplementations

I'd also like to incorporate various Open-Source reimplementations into this project, such as Bullet vphysics. 

On top of this, I personally want to rewrite various parts of Source, such as inputsystem, networksystem, soundsystem, etc. Just since those are easy to rewrite.
