![ZeGrapher logo with name](ZeGrapher_named_logo.svg)

[![Build Status](https://travis-ci.org/AdelKS/ZeGrapher.svg?branch=master)](https://travis-ci.org/AdelKS/ZeGrapher)
[![Gitter](https://badges.gitter.im/ZeGrapher/community.svg)](https://gitter.im/ZeGrapher/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

![ZeGrapher example](https://zegrapher.com/screenshots/index.png)

ZeGrapher is a free, open source and easy to use software for plotting mathematical objects. It can plot functions, sequences, parametric equations and data on the plane.

#### Official website: [https://zegrapher.com/](https://zegrapher.com/)

------------------------------------
### Features
- Visualize up to six functions simultaneously, they currently have fixed names: `f` `g` `h` `p` `r` `m`. It is planned to implement plotting of an arbitrary number of user named function. 
    - All the standard mathematical functions (`cos` `cosh` `exp` ...etc) can be called: they're all written on a virtual keyboard that can be displayed with a button. 
    - On a given function, other functions be called, so it is possible to associate or compose functions.
    - Using the uppercase letter of a user-defined function, _e.g_ `F` makes ZeGrapher compute its antiderivative.
    - Using the primed version of a user-defined function, _e.g_ `f'` makes ZeGrapher compute its derivative.
- Visualize up to six numerical sequence simultaneously, they currently have fixed names: `u` `v` `l` `w` `q` `t`.
    - Sequences can be defined by a recurrent relation, _e.g_ `u(n) = u(n-1) + u(n-2)` in which case initial values should be given in the corresponding input widget, separated by `;`, _e.g._ `1;1`
    - Sequences can be defined explicitly, _e.g_ `u(n) = 2*n + 1`.
- Parametric equation plotting. The curves can be animated, with adjustable framerate and speed.
- Experimental data plot and polynomial fit (regression). Data can be imported/exported from a CSV file.
- Parametric plot for functions, sequences and parametric equations: the parameter name to use is fixed to `k`. This will be overheauled in the upcoming version.
- Plot tangents: they can be moved and resized simply with the mouse.
- Plot derivatives and antiderviatives.
- Print the graph, with these options :
    -   Choose the size and the position of the graph on the sheet.
    -   Print in color or gray-scale.
    -   Export on a PDF file.
- Export to all common image formats (png, jpeg, tiff, gif...).
- Display a table of values with different options.
- Navigate on the graph :
    -   Select a curve to display the coordinates of its points.
    -   Zoom/unzoom on each axis separately, around the mouse (with the scroll wheel), or fit on a mouse drawn rectangle.
    -   Move the graph.
- Customize the presentation :
    -   Change colors: axes, background, functions...
    -   Adjust the plotting precision. Note that it will also affect rendering speed.
    -   Show/hide a grid.
    -   Activate/deactivate curves\' smoothing.
    -   Plot the graph on an orthonormal basis.
------------------------------------------
### Install

#### Ready to use binaries
ZeGrapher is available in the official repositories of Debian, Fedora, Ubuntu, FreeBSD. In the Archlinux (AUR). An [AppImage](https://appimage.org/) is otherwise available, along with Windows and Mac versions in Zegrapher's [Github releases page](https://github.com/AdelKS/ZeGrapher/releases) or at [zegrapher.com](https://zegrapher.com/).

#### Compile from sources
To compile from sources, ZeGrapher needs a C++ compiler and the following libraries:
- [boost](https://www.boost.org/)
- [Qt](https://www.qt.io)

For Windows, one also needs to edit the following line in `ZeGrapher.pro` to where the boost folder has been extracted:
```
win32 {
# Modify this line in Windows to boost's folder to be able to compile
    INCLUDEPATH += C:/boost_1_72_0
}
```
To compile from the command line:
```shell
$ git clone https://github.com/AdelKS/ZeGrapher.git
$ cd ZeGrapher
$ qmake ZeGrapher.pro
$ make
```
It is also possible to use `Qt Creator` as a GUI software to compile ZeGrapher by opening with it the `ZeGrapher.pro` file then pressing the "play" button, after configuring the project.
