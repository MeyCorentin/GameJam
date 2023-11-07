[![Engine Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/engine_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/engine_compilation.yml)
[![Server Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/server_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/server_compilation.yml)
[![Client Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/client_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/client_compilation.yml)
# R-Type Project


## Documentation

- [Engine Documentation](engine/docs/DOCUMENTATION.md)
- [Client Documentation](client/docs/DOCUMENTATION.md)
- [Server Documentation](server/docs/DOCUMENTATION.md)
- [RFC Documentation](RFC-doc.md)

## How to build project ?

git clone git@github.com:EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq.git
cd B-CPP-500-LYN-5-1-rtype-keziah.picq

sudo pacman -Syu cmake

mkdir client/build server/build engine/build


### Build Engine:

```
cd engine/build
cmake ..
make
```

### Build client:

```
cd client/build
cmake ..
make

Run Game Solo:

./r-type_client {GAME_PATH}


Run Game Multiplayer:

./r-type_client {SERVER_IP} {PORT} {GAME_PATH}
```

### Build server:

```
cd server/build
cmake ..
make
./r-type_server {PORT} {GAME_PATG}
```
