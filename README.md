# quang-advCG-raytracer
Ray tracer built from the ground up as part of the Advanced Computer Graphcis course taught by Prof. Justin Vasselli at Bennington College, Spring 2019 using the book "The Ray Tracer Challenge" by Jamis Buck from The Pragmatic Bookshelf.

Build instruction: It probably works with `clang++` too. Last i checked, it works by compiling all .cpp files with g++ and an fopenmp flag: `g++ -fopenmp baseclass/*.cpp mainInteractive.cpp`. The executable will be an `a.out` by default. Outputs have the .ppm file extension in the `output` folder.

## Finals Samples
Refraction (&transparency)
![](https://i.imgur.com/uS7cs5k.png)

Depth of Field and Anti-aliasing demo
![](https://i.imgur.com/opdN5A9.png)

Soft shadowing demo
![](https://i.imgur.com/286VyZz.png)

## 1 Month Left From Finals!
Reflection works now. (Also transparency works but the image is still on my computer)

![](https://i.imgur.com/DKWpiaM.png) ![](https://i.imgur.com/jiNxUQw.png)

And also the above image was built with the interactive executable. Other stuffs built pre-reflection:

![](https://i.imgur.com/OfKMzQ9.png) ![](https://i.imgur.com/rd2rNE9.png)

## Midterm+1 Progress

Multiple Lights work now.

![](https://i.imgur.com/F0OlDuZ.png)

## Midterm Progress

Shadows are done, but right now only supports 1 light source. Things get weird when I try to add a second one.

Right Light

![](https://i.imgur.com/zcGEOZo.png)


Left Light

![](https://i.imgur.com/zdU65lJ.png)


Two Lights (right is Red)

![](https://i.imgur.com/pIhi4j0.png)
