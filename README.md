# DIYWolf3D v0.2

DIYWold3D is a simple ray cast engine, this is the second revision of the ray cast engine implementation  
* The older revision of the code can be found in [v0.1](https://github.com/amroibrahim/SimpleRayCast/tree/v0.1) branch  
* All dependencies are included in the project  

## Reference
* [Game Engine Black Book: Wolfenstein 3D by Fabien Sanglard](https://fabiensanglard.net/gebbwolf3d/)  
* [Raycasting Engine Programming by Gustavo Pezzi](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript)  
* [Raycasting by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)  
* [Ray-Casting Tutorial for Game Development And Other Purposes by F. Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)  

## Build / Compile  
### Windows  
Download and install Visual Studio 2022
* Open `./src/DIYWolf3D.sln` in visual studio 2022 and click build  
* Click Play 

### Linux / Ubuntu  
* Insall SDL2 and SDL_Image  
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
```
under the `src` directory run  
```
make
```

Navigate to `external/workdir/bin` and run  
```
DIYWolf3D
```

## Screenshots  

![Screen1](https://github.com/amroibrahim/DIYWolf3D/blob/master/img/Screen1.png)  

![Screen2](https://github.com/amroibrahim/DIYWolf3D/blob/master/img/Screen2.png)  

## Assets  
Currently using some of [Retro Texture Pack](https://little-martian.itch.io/retro-texture-pack) for walls texturing  

## TODO: Future updates (v0.3)  
* A closer implementation to IDs Wolfenstein 3D.  
* Read/Use Wolfenstein 3D Shareware assets / full release assets  
