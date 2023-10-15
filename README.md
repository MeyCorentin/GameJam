[![Engine Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/engine_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/engine_compilation.yml)
[![Server Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/server_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/server_compilation.yml)
[![Client Compil](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/client_compilation.yml/badge.svg)](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq/actions/workflows/client_compilation.yml)
# R-Type Project

### How to build project ?

git clone git@github.com:EpitechPromo2026/B-CPP-500-LYN-5-1-rtype-keziah.picq.git
cd B-CPP-500-LYN-5-1-rtype-keziah.picq

sudo pacman -Syu cmake

mkdir client/build server/build

##### Build client:

cd client/build
cmake ..
make
./r-type_client

##### Build server:

cd server/build
cmake ..
make
./r-type_server