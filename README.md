
# Cub3D

My first RayCaster with miniLibX


## Installation

To install Cub3D, clone the project with

```bash
  git clone https://github.com/DinoMalin/cub3d.git
  cd cub3d
```
Then compile the executable using

```bash
  make
```
Finally, launch the game with

```bash
  ./cub3D <your_map>
```

    
## Play

You can play the game using the keys **W**, **A**, **S**, **D**.  
Use your **mouse** to rotate the point of view.  
By using **M**, you can enable and disable the minimap.  
You can **right-click** to place block et **left-click** to destroy them.
## Map Requirement

A map is a *.cub* file that **must** have a texture associated to each direction.  
**'0'** : Tile  
**'1'** : Wall  
**'N'**, **'S'**, **'E'**, **'W'** : Starting position / direction  

Here is an example of a working map :
```
NO ./textures/north.png

SO ./textures/south.png

EA ./textures/east.png

WE ./textures/west.png

F ./texture/floor.png

C ./textures/sky.png

111111
10000111111111111111111111111111111111111
100E000D0000000000000000D0000000000000001
10001001001001111111111111111001111111111
10001001001001000000000001000001
1111111111100111100100111111100111111
      1001000000001000001001001000001
      1001111001001001001001001001001
      1000000001001001001000001001001
      1001001111111111001111001111001
      1001000000001000001000001001001
      1111111001001111001111111001001
      1000000001000001000000000001001
      1111001111001001111001111001001
      1000001000001001001000001001001
      1001111001111111001001111111001
      10010010010010010010000010000011111111111
      10010010010010010011110011110000000000001
      10000010000000010000010000000011111111111
      1001001001111001001001111111001
      100100100100000000100000000000111111111
      100111100111111111111111111100000000D01
      1001  1001                 111111111111
      1001  1001
      1001111001
      1000000001
      1001111001
      1111  1111
```

