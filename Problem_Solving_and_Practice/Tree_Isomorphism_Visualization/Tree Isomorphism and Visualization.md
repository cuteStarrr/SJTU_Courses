# Tree Isomorphism and Visualization

**Xin Xu	519021910726 **

## Environment

- Ubuntu 20.04
- FLTK 1.3.8

## Get started

Simply run the command to compile files:

```
g++ -I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I./revised-gui -L/usr/local/lib -fvisibility-inlines-hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'main' './main.cpp' ./Tree_Isomorphism.cpp -lXrender -lXcursor -lXfixes -lXext -lXinerama -lpthread -ldl -lm -lX11 -luuid -lfltk_images -lfltk
```

And run ```./main``` to start the program.

## Other Tips

You can change the parameters ```win_length``` and ```win_height``` in file ```main.cpp``` to change the window size. Also, you can change the file name of the tree in the same ```main.cpp``` file.

Some useful information are print out in the terminal.