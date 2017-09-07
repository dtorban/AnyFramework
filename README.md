# AnyFramework

AnyFramework is a light weight plugin framework.

## Getting Started

#### Download Repository

  ```
  git clone http://github.umn.edu/ivlab/Spatialize
  cd Spatialize
  ```
  
#### Configure and build

* Linux and Mac (command line)

    ```
    mkdir build
    cd build
    cmake ..
    make
    ```
    
* Mac (Xcode)

    ```
    mkdir build
    cd build
    cmake .. -G Xcode
    # Open project in Xcode and build
    ```
    
* Windows (Visual Studio)

    ```
    mkdir build
    cd build
    cmake .. -G "Visual Studio 12 Win64"
    # Open project in Visual Studio and build
    ```

#### Run Examples

* Simple plugin loading examples

```
cd build
bin/FactoryExample
bin/ParseExample
bin/GraphicsExample
```
