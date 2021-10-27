# TrafficControlSystem

# Content

This repository contains the sources for the workshop series "Object Oriented
Analysis with UML" and the series "Object Oriented Design and Design Patterns".

There is a separate description for each component.

- [CrossRoad](./CrossRoadLib/CrossRoad.md)
- [Sensor](./Sensor/Sensor.md)
- [TrafficControlSystem](./TrafficControlSystem/TrafficControlSystem.md)

## Models

to download the EA model for the libraries choose:
`<_projectname_>/Model/<_libname_>.xmi` right click on Raw -> save link as.. and
import the xmi file into EA

## Build the examples

Prerequisites:

- CMake 3.12 (or greater)
- A recent C++ compiler

Create a buildfolder, configure the project and build:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Have a look at different CMake Generators for generating your desired project
files. E.g. for Eclipse or VisualStudio. You can get a list by running `cmake
--help`.