# a-maze-gl
Computer Graphics Project #4 Realtime OpenGL Maze Game

A simple yet pretty-looking interactive 3D first-person Maze Game built using OpenGL.
>It's **a maze** game made with Open**GL**. Geddit? ( ͡° ͜ʖ ͡°)

## GAMEPLAY SNAPSHOT
![Game Snapshot](res/game.png)

## GAMEPLAY VIDEO
[![Gameplay Video](https://imgur.com/fDrZ3SX.png)](https://www.youtube.com/watch?v=xQQIzod7fCU)

## MAP FORMAT
The map stores the world as a `rectilinear` map. The first row is `width` and
`height`. The player will begin at the `start` point marked **S** and must reach the `goal` point marked
**G** to finish the level. The player’s progress may be hindered by `walls` (marked **W**) and
`doors` (marked with a capital letter **A-E**). Throughout the environment will be `keys`
(marked with a lowercase **a-e**). A player may not cross through a door unless they
have picked up the corresponding key. A player may never cross a wall.
<br><br>

No Doors | Door w/ Key
---| ---
5 5<br>0000G<br>WW0W0<br>0W0W0<br>0W0WW<br>S0000 | 5 5<br>0000G<br>WW0W0<br>0WAW0<br>0W0WW<br>S000a

## BASIC FEATURES
* `Walls & Doors`: Each map element type has a unique rendering. Walls look different than doors,
and each of the five doors and keys look different than each other.
* `Keys`: Each key is rendered as a physical object (key model). Whenever a player moves,
the key is rendered in front of them moving with the character.
* `User Input`: Users are able to move around the map with keyboard input.
Rotate with the **left** and **right** keys, and move forward and back with the **up** and **down** keys.
* `Collision Detection`: Users are not able to move through walls or locked
doors.
* `Lighting`: Ambient and diffuse lighting.

## ADVANCED FEATURES - EXTRA CREDIT
* Multiple point lights on the maze corners and an overhead directional light.
* Soft-edged Flashlight that moves with the player.
* Textured walls, floor, door, keys and goal.
* Original models to represent keys, doors, walls, floor made with [Wings3D](http://www.wings3d.com).
* Models can be loaded in the [OBJ 3D models format](http://enwp.org/Wavefront_.obj_file). Supports v, vt, vn, f tags.
* ENTER can be used to pick up a key or switch the key held by you.
* The held key is always rendered pointing away from the user for a true first-person experience.
* Holding SHIFT while moving or turning, does it faster.

## CHALLENGES
* `Modelling and Texturing` - Learning to model and texture my own 3D objects was a challenge but Prof. Guy's quick intro to
Wings3D encouraged me to try it out.
* `Reading OBJ Files` - I used the OBJ loader created by [bennybox](https://github.com/BennyQBD) and augmented it to be able to read in OBJs
with all or any of normal, texture and vertex data.
* `Reading MTL Files` - I also added code to read in Material properties from MTL files which can be attached to any Entity.
* `Normalizing OBJ Files` - I had to normalize the OBJ 3D models in Wings3D by using a unit bounding box
so that all objects had a comparable size.
* `Collision Detection` - I went with the easy way of doing this by using a grid to denote my map and marking cells with walls, doors and
empty space as invalid areas where a player cannot step. I also added a slight offset while checking if my position is invalid, which helped
me avoid seeing inside of walls.
* `Animation` - I figured it would be better to have some of the interactive items move around a bit so that it
looks attractive and catches the player's attention.
* `Lighting` - I drew from the LearnOpenGL tutorial and used 3 kinds of lights in my game with the Phong Lighting Model - point, directional and spot lights.
To have soft edges on the spotlight, I had to define two angles for falloff calculation.
* `Updating Uniforms` - I realized the light positions/directions had to be updated according to the View and preferred to update it in CPU code once
and update it as a uniform instead of doing it in the shaders. Also, using structs and functions in the shader helped me make the code more readable and modular.
* `Moving the Key with User` - While moving the key was easy, rotating it was challenging as the dot product doesn't preserve the sign
of the angle. So if we turn a 360, the object turns the other way around when we hit 180. To solve this problem, I used the cross product
of view direction and key direction and checked to see if it was in the direction of the up vector.
* `Key Switch`: In order to enable more complex mazes in which a key and door pair are not both accessible initially, I let the user
switch his held key with another lying around.