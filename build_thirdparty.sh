#!/bin/bash

TOP_DIR=`pwd`

cd thirdparty
wget https://github.com/apache/thrift/archive/v0.13.0.tar.gz
tar -xf v0.13.0.tar.gz
rm v0.13.0.tar.gz
cd thrift-0.13.0
./bootstrap.sh
./configure --prefix=${TOP_DIR} --with-ruby=no --with-java=no --with-perl=no \
    --with-php=no --with-csharp=no --with-erlang=no --with-lua=no --with-qt5=no \
    --with-php_extension=no --with-dart=no --with-haskell=no --with-cl=no --with-haxe=no --with-netstd=no --with-d=no \
    --with-rs=no --with-python=no --with-nodejs=no
make CPPFLAGS=-DFORCE_BOOST_SMART_PTR -j 4 -s
make install
cd ..
rm -rf thrift-0.13.0

wget https://github.com/google/glog/archive/v0.4.0.tar.gz
tar -xf v0.4.0.tar.gz
rm v0.13.0.tar.gz
cd glog-0.4.0
cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=${TOP_DIR}
cmake --build build
cmake --build build --target install
rm -rf glog-0.4.0

cd googletest
cmake -H. -Bbuild -DCMAKE_INSTALL_PREFIX=${TOP_DIR}
cmake --build build
cmake --build build --target install

cd ..