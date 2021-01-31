# Asty

```shell
sudo apt-get install -y git g++ make libssl-dev libgflags-dev libprotobuf-dev libprotoc-dev protobuf-compiler libleveldb-dev
sudo apt-get install -y libsnappy-dev
sudo apt-get install -y libgoogle-perftools-dev
sudo apt-get install -y libtool
sudo apt-get install -y bison byacc flex
sudo apt-get install -y libboost-dev
sudo apt-get install -y cmake libgtest-dev && cd /usr/src/googletest && sudo cmake . && sudo make && sudo make install && sudo rm /usr/src/googletest -rf && cd -

wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz && tar -xf libevent-2.1.12-stable.tar.gz && rm libevent-2.1.12-stable.tar.gz

cd libevent-2.1.12-stable && ./configure --prefix=/usr --enable-static --enable-shared
make && sudo make install
cd .. && rm -rf libevent-2.1.12-stable

wget https://github.com/apache/thrift/archive/v0.13.0.tar.gz && tar -xf v0.13.0.tar.gz && rm v0.13.0.tar.gz
cd thrift-0.13.0 && ./bootstrap.sh && ./configure --prefix=/usr --with-ruby=no --with-java=no --with-perl=no \
--with-php=no --with-csharp=no --with-erlang=no --with-lua=no --with-qt5=no \
--with-php_extension=no --with-dart=no --with-haskell=no --with-cl=no --with-haxe=no --with-netstd=no --with-d=no \
--with-rs=no --with-python=no --with-nodejs=no
make CPPFLAGS=-DFORCE_BOOST_SMART_PTR -j8 -s
sudo make install
cd .. && rm -rf thrift-0.13.0

wget https://github.com/google/glog/archive/v0.4.0.tar.gz && tar -xf v0.4.0.tar.gz && rm v0.4.0.tar.gz
cd glog-0.4.0 && cmake -H. -Bbuildd -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/usr && cmake --build buildd -j8 && sudo cmake --build buildd --target install
cd .. && rm -rf glog-0.4.0

cd thirdparty/incubator-brpc
cmake -B build -DWITH_GLOG=ON -DWITH_THRIFT=ON -DCMAKE_INSTALL_PREFIX=/mnt/e/ormosiaVM/github/Asty/Asty-platform-server && cmake --build build -j8 && cmake --build build --target install

# sh config_brpc.sh --with-glog --with-thrift --headers=/usr/include --libs=/usr/lib
# sh config_brpc.sh --with-glog --headers=/usr/include --libs=/usr/lib
cmake -H. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DWITH_GLOG=ON -DCMAKE_INSTALL_PREFIX=`pwd`/../../ && cmake --build build -j8 && cmake --build build --taget install
```

## `mqtt`搭建

[查看使用](https://www.cnblogs.com/lulipro/p/10914482.html)

```shell
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install -y mosquitto
```
