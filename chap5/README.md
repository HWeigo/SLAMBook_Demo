To run the defects detection, please do the following:  
```
$ mkdir build && cd build
$ cmake ..
$ make
$ make test OR $ ./defectsDetection PATH_TO_THE_IMAGE
```

The scipts will do the detection and save the result as .jpg file in your current folder. To enable image display, go CMakeLists.txt and uncomment **add_definitions(-DDEBUG_IMAGEDISPLAY)**.  
