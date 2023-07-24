# README

## Configure

1. Debug build

```
mkdir build
cd build
cmake ..
```

2. Release build

```
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
```


## Steps

1. copy the necessary files from the imgui library.
2. the necessary files are the ones in the ./backends and ./imgui folder
3. copy an example (glfw, opengl3), modify the Makefile so that the paths are correct
4. install the following:
    - sudo apt-get install libglfw3
    - sudo apt-get install libglfw3-dev

