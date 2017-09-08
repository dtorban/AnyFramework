# AnyFramework

AnyFramework is a light weight plugin framework.

## Getting Started

#### Download Repository

  ```
  git clone http://github.com/dtorban/AnyFramework
  cd AnyFramework
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

#### Use Library in Another Project

* Build the install target for AnyFramework
* In your project's CMakeLists.txt add the following:

```cmake
# Find AnyFramework Package
find_package(AnyFW REQUIRED)
include_directories (${AnyFW_INCLUDE_DIRS})
link_directories(${AnyFW_LIB_DIRS})

# ...

# create library or executable
add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${AnyFW_LIBRARIES})
```

* When configuring your project, be sure to set the AnyFW_DIR variable

```bash
cd your_project/build
cmake .. -DAnyFW_DIR=/full/path/to/AnyFramework/build/install
```
