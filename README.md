Welcome to Ben's OpenGL Assignment!

To run the assignment ...
1) In terminal, navigate to the folder "OpenGL 3.3 (COMP2004)".
2) Inside this folder, contains another folder called "build", navigate to the build folder.
3) Within build, type the command "cmake .." to compile the vs/vf files, and then type "make" to compile the source code.
4) Once the files have been compiled, navigate to the folder "CG_Assignment".
5) Within "CG_Assignment", run the program by typing "./CG_Assignment__assignment".
6) Good luck escaping the Slenderman!

Source code can be found within OpenGL 3.3 (COMP2004) -> src -> CG_Assignment -> assignment -> sample2.cpp

***NOTE*** might be easy to miss, but the animation after player triggering it is the rotation of the tree
	   trunk after picking up dagger and gun

~~~ WIN CONDITION ~~~

In order to escape the Slenderman, two specific objects must be picked up. The dagger and the gun.

The dagger is found near the northwest corner of the map (north being where the camera is facing upon spawning in the game).

The gun is found near the southeast corner of the map.

Once both of these objects have been picked up, the winning area which the player must go through is in the northeast corner of the map. 
Go through this area and you win!
For a visual guide on where these objects are, refer to the PDF "Object Locations Guide".

~~~ LOSE CONDITION ~~~

The game ends when the Slenderman catches up to you, make sure this doesn't happen!

~~~ PROGRAM REQUIREMENT CHECKLIST ~~~

INITIAL ANIMATION
- tree leaves rotating

ANIMATION AFTER PLAYER TRIGGERS IT (this animation only occurs when the player picks up both items)
- tree trunk rotating opposite way to tree leaves

6 COMPOSITE OBJECTS
- tree
- slenderman
- table
- graves
- gun
- tagger
- torch
- winning area

6 IMAGE TEXTURES
- grass (floor)
- wood (tree)
- greenleaves (tree leaves)
- brick (wall)
- metal (dagger, torch)
- red (hilt of dagger)
- marble (graves)
- white (slenderman head)
- black (slenderman body)

===========================================================================================================================
===========================================================================================================================
===========================================================================================================================


# learnopengl.com code repository
Contains code samples for all tutorials of [https://learnopengl.com](https://learnopengl.com). 

## Windows building
All relevant libraries are found in /libs and all DLLs found in /dlls (pre-)compiled for Windows. 
The CMake script knows where to find the libraries so just run CMake script and generate project of choice.
Note that you still have to manually copy the required .DLL files from the /dlls folder to your binary folder for the binaries to run.

Keep in mind the supplied libraries were generated with a specific compiler version which may or may not work on your system (generating a large batch of link errors). In that case it's advised to build the libraries yourself from the source.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev  libxi-dev` .
Next, run CMake (preferably CMake-gui). The source directory is LearnOpenGL and specify the build directory as LearnOpenGL/build. Creating the build directory within LearnOpenGL is important for linking to the resource files (it also will be ignored by Git). Hit configure and specify your compiler files (Unix Makefiles are recommended), resolve any missing directories or libraries, and then hit generate. Navigate to the build directory (`cd LearnOpenGL/build`) and type `make` in the terminal. This should generate the executables in the respective chapter folders.

Note that CodeBlocks or other IDEs may have issues running the programs due to problems finding the shader and resource files, however it should still be able to generate the exectuables. To work around this problem it is possible to set an environment variable to tell the tutorials where the resource files can be found. The environment variable is named LOGL_ROOT_PATH and may be set to the path to the root of the LearnOpenGL directory tree. For example:

    `export LOGL_ROOT_PATH=/home/user/tutorials/LearnOpenGL`

Running `ls $LOGL_ROOT_PATH` should list, among other things, this README file and the resources direcory.

## Mac OS X building
Building on Mac OS X is fairly simple (thanks [@hyperknot](https://github.com/hyperknot)):
```
brew install cmake assimp glm glfw
mkdir build
cd build
cmake ../.
make -j8
```

## Glitter
Polytonic created a project called [Glitter](https://github.com/Polytonic/Glitter) that is a dead-simple boilerplate for OpenGL. 
Everything you need to run a single LearnOpenGL Project (including all libraries) and just that; nothing more. 
Perfect if you want to follow along with the tutorials, without the hassle of having to manually compile and link all third party libraries!
