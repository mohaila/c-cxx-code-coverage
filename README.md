# C/C++ Code coverage

This is an example for unit testing C/C++ code. 

## Project
this project is developed using Visual Studio Code, Docker and Dev Containers.

Tools used:
- Make for running cmake commands
- CMake to manage this project
- Ninja for project build
- lcov for C/C++ code coverage
- Visual Studio code with Dev Containers plugin
- Docker 

Libraries used:
- gtest and gmock for unit testing

## Sub projects:
- libSystem: library for a dummy system with connect/disconnect, resource open/close, lock/unlock and process functions.
- app1: simple application using libSystem
- app2: app1 can't be tested because all code is in main, app1 is refactored as app2 and libApp
- libApp: all logic from app1, used by app2
- libMock: to test libApp code without linking with libSystem, this library will be used to mock libSystem functions
- app2-test: unit testing libApp using libMock as libSystem dropin
- libWrapper: C++ wrapper for libSystem (abstract class) with an implementation that can be used to call libSystem
- libWapp: libApp refactored to use libSystem wrapper
- app3: app2 refactored to use libWapp
- app3-test: unit testing libWapp using libSystem Wrapper

### Testing
```sh
make clean test
```

### Code coverage
```sh
make clean coverage 
cd buildir
ninja coverage
```
### Screenshoots
![Code coverage 3](/images/Screenshot3.png)
![Code coverage 1](/images/Screenshot1.png)
![Code coverage 2](/images/Screenshot2.png)
