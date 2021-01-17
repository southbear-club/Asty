#!/bin/bash

TOP_DIR=`pwd`

cd thirdparty

wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz && tar -xf libevent-2.1.12-stable.tar.gz && rm libevent-2.1.12-stable.tar.gz
cd libevent-2.1.12-stable && ./configure --prefix=/usr --enable-static --enable-shared
make -j4 && sudo make install
cd .. && rm -rf libevent-2.1.12-stable

wget https://github.com/apache/thrift/archive/v0.13.0.tar.gz && tar -xf v0.13.0.tar.gz && rm v0.13.0.tar.gz
cd thrift-0.13.0 && ./bootstrap.sh && ./configure --prefix=/usr --with-ruby=no --with-java=no --with-perl=no \
    --with-php=no --with-csharp=no --with-erlang=no --with-lua=no --with-qt5=no \
    --with-php_extension=no --with-dart=no --with-haskell=no --with-cl=no --with-haxe=no --with-netstd=no --with-d=no \
    --with-rs=no --with-python=no --with-nodejs=no
make CPPFLAGS=-DFORCE_BOOST_SMART_PTR -j4 -s && sudo make install
cd .. && rm -rf thrift-0.13.0

wget https://github.com/google/glog/archive/v0.4.0.tar.gz && tar -xf v0.4.0.tar.gz && rm v0.4.0.tar.gz
cd glog-0.4.0 && cmake -H. -Bbuild -G "Unix Makefiles" && cmake --build build && sudo cmake --build build --target install
cd .. && rm -rf glog-0.4.0

sudo apt-get install -y cmake libgtest-dev && cd /usr/src/googletest && sudo cmake . && sudo make && sudo make install && sudo rm /usr/src/googletest -rf && cd -

# wget https://github.com/DaveGamble/cJSON/archive/v1.7.14.tar.gz && tar -xf v1.7.14.tar.gz && rm v1.7.14.tar.gz 
# cd cJSON-1.7.14 && make && sudo make install
# cd .. && rm -rf cJSON-1.7.14
# wget https://github.com/eclipse/mosquitto/archive/v2.0.4.tar.gz && tar -xf v2.0.4.tar.gz && rm v2.0.4.tar.gz
# cd mosquitto-2.0.4 && make -j4 && sudo make install
# cd .. && rm -rf mosquitto-2.0.4

wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
cd /etc/apt/sources.list.d/
# 根据你的系统版本选一个
sudo wget http://repo.mosquitto.org/debian/mosquitto-jessie.list
sudo wget http://repo.mosquitto.org/debian/mosquitto-stretch.list
sudo wget http://repo.mosquitto.org/debian/mosquitto-buster.list
sudo apt-get update && sudo apt-get install mosquitto
cd ..