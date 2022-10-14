# Open Street Map Route Planner
This is the first project of Udacity C++ Nano Degree program. The main goal is to use A* search algorithm to find a path between two points in a real 2D map. The data used in this project is taken from the open-source [OpenStreetMap](https://www.openstreetmap.org/#map=12/51.4499/5.5622) project. The map used in this project is renedered using the 2D graphic library [IO2D](https://github.com/cpp-io2d/P0267_RefImpl) and the [map rendering example](https://github.com/cpp-io2d/P0267_RefImpl/tree/master/P0267_RefImpl/Samples/maps) provided in this library repository.


<p align="center">
<img align="center" src="https://user-images.githubusercontent.com/45536639/195708959-e855066a-b15c-41df-9c90-f914ed576def.png"> 
</p>

## Dependencies (Linux)
1. Cmake and GCC:
```
    sudo apt update
    sudo apt install build-essential
    sudo apt install cmake
```

2. IO2D Library [README.md](https://github.com/cpp-io2d/P0267_RefImpl)
```
	sudo apt install libcairo2-dev
	sudo apt install libgraphicsmagick1-dev
	sudo apt install libpng-dev

	git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
	cd P0267_RefImpl
	mkdir Debug
	cd Debug
	cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
	cmake --build .
	sudo make install
```

## Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
    mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
    cmake ..
    make
```
## Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
    ./OSM_A_star_search
```
Or to specify a map file:
```
    ./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
    ./test
```

## Authors

* **Fedi Salhi** [FediSalhi](https://www.linkedin.com/in/fedisalhi/)

