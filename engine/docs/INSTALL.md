# INSTALL

## Documentation Menu
- [Documentation Menu](DOCUMENTATION.md)

### How to install from repository


To install the game, you have to execute the installation script corresponding to your OS :


**For Linux**<br>

**For Mac**<br>

You need to install Conan on your computer. Once installed, run the following command :
conan profile detect --force
Next, to build the project, for instance to build the engine, navigate to the 'engine' folder, delete the 'build' directory, and recreate it. Then, use this command to install the dependencies
conan install . --output-folder=build --build=missing
Afterwards, execute these commands to build:
- cd build && cmake ..
- DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
- DCMAKE_BUILD_TYPE=Release
- make

**For Windows**<br>
(To fill)
This should successfully build the binary. Repeat these steps for each folder (engine, server, client).
Everything should install correctly, and you should be able to launch the game.

First, you have to launch the server. To do so, you have to execute the server executable with the port you want to use as an argument with this command:

```
./rtype-server 4242
```

Then, you can launch the client. To do so, you have to execute the client executable. It takes two arguments:
The IP address of the server
The port of the server
```
./client address port (example : ./r-type_client 172.20.10.4 800)
```

### Dependencies

-[SFML](https://github.com/SFML/SFML) : Graphic library supported by this engine

-[Doxygen](https://github.com/doxygen/doxygen): Library to generate in-code documentation

-[Nlohmann](https://github.com/nlohmann/json): library to manage json.file with cpp language

