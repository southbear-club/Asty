# Asty

## 依赖安装

1. `thrift`；

  该`RPC`相对轻量级，不过依赖于`boost`和`libevent`，所以需要先安装`boost`。

  安装`thrift`：

  ```shell
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
  ```

2. `glog`；

  ```shell
  wget https://github.com/google/glog/archive/v0.4.0.tar.gz && tar -xf v0.4.0.tar.gz && rm v0.4.0.tar.gz
  cd glog-0.4.0 && cmake -H. -Bbuild -G "Unix Makefiles" && cmake --build build && sudo cmake --build build --target install
  cd .. && rm -rf glog-0.4.0
  ```

3. `googeltest`；

  ```shell
  sudo apt-get install -y cmake libgtest-dev && cd /usr/src/googletest && sudo cmake . && sudo make && sudo make install && sudo rm /usr/src/googletest -rf && cd -
  ```
