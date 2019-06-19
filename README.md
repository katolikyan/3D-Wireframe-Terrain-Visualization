## WIREFRAME MAP GENERATOR
Program creates 3d wireframe map representation based on specific 2D map input.

Check out an amazing art motion graphics project made with this program.
https://www.behance.net/gallery/81671933/The-Art-of-Code

## Usage

### Compile and run
```bash
$> Make
$> ./fdf [source_file]
```
![](https://github.com/katolikyan/Wireframe-map-generator/blob/master/media/make_demo.gif?raw=true)
***
### Map example

Map is any 2 demential array with numbers.
Each number represents Z high of the current point.
Numbers are divided by spaces. (Do not use tubs).

Simple map example:
```bash
$> cat -e map_example
9 2 5 -1 5 -32$
-1 2 5 -2 15 0$
14 -3 0 -3 5 2$
$>
```
#### Map generator

 You can use special generator which takes coordinates of any place on the Earth using API from Marine Geoscience Data System.
 It also allows to build the Moon and the Venus Maps based on SGS Astrogeology Science Center data.

<https://github.com/jgigault/42MapGenerator>
***
### Basic demo

![](https://github.com/katolikyan/Wireframe-map-generator/blob/master/media/basic_demo.gif?raw=true)

**Some functionality**:
* *Orthographic and perspective projections.*
* *Rotations and zoom.*
* *Altitude (vertical) scale.*
* *Depth/fog effect.*
* *Motion blur.*
* *Camera focal length change (perspective).*

For all options press `h` to open help page.

Resolution and colors (background, gradient, text) can be changed in `fdf.h` file.

```C
// resolution:
# define RES_X      1920
# define RES_Y      1080

# define DEF_BACK_C 0x2a2a2a    // background color;
# define DEF_BS_C   0xe8e8e8    // altitude min color;
# define DEF_BS_C_2 0x0f0f0f    // altitude min inverse color;
# define DEF_TOP_C  0xff0043    // altitude max color;
# define DEF_TXT_C  0xe0e0e0    // text color;
# define DEF_TXT_2  0x191919    // text inverse color;
```

#### image examples:
###### *The Venus*
![Venus](https://github.com/katolikyan/Wireframe-map-generator/blob/master/media/Venus.png?raw=true)

###### *The Moon*
![Moon](https://github.com/katolikyan/Wireframe-map-generator/blob/master/media/Moon.png?raw=true)

###### *Gulf of California*
![Gulf_of_CA](https://github.com/katolikyan/Wireframe-map-generator/blob/master/media/Gulf_of_california.gif?raw=true)

***

#### Plans and ideas to improve the project someday(probably never):

* *Refactor the code.*
* *Optimize calculations.*
* *Create multicolor map.*
* *Run program on GPU.*
* *Export image.*
* *Export 16 bit image as a displacement map for 3D software.*
* *Integrate program as a script for 3Ds max.*

***

#### Special thanks to [Stepan Nikitin](https://github.com/nikitinste)
