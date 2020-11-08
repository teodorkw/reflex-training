# Reflex training

Very simple GUI program for improving reaction time and precision with computer mouse. Developed mostly for fun.

## 1. Installation

Program is compiled using Qt Creator's project file in `src` folder. Project was created with Qt version 5.9.1, however [will work with some other versions](https://wiki.qt.io/Qt-Version-Compatibility).

Currently there are no releases, so it must be built on user's machine.

## 2. Features

* Displaying reaction time of hitting the target and distance from previous target for each hit. After clicking the Start button there is one "warm-up round" not included in statictics. 

* Saving results to `*.csv` file,

* Plotting both quantities (time and distance) of current session.

## 3. Feature ideas

* Adjustable target and board size,

* graphic push buttons,

* setting maximal distance to new target position,

* including saved files in statistics,

* tracking excersises (i.e. following target with mouse pointer).
