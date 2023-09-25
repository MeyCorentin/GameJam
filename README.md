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
./r-type_client <host> <port>

EXEMPLE : ./r-type_client 127.0.0.1 8001

##### Build server:

cd server/build
cmake ..
make
./r-type_server <port>

EXEMPLE : ./r-type_server 8001