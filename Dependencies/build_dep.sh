echo Building dependencies...

# extract mysql libs
echo Extract mysql libs
unzip -o mysql_libs.zip -d ./

echo Extract mysql++ libs
unzip -o mysqlpp_libs.zip -d ./

echo Copy mysql libs to Debug directory
cp -r -f ./lib/Release/libmysql.dll ./lib/Debug/
cp -r -f ./lib/Release/libmysql.lib ./lib/Debug/
cp -r -f ./lib/Release/libmysqlclient.a ./lib/Debug/
cp -r -f ./lib/Release/libmysqlclient.so ./lib/Debug/
cp -r -f ./lib/Release/mysqlclient.lib ./lib/Debug/
cp -r -f ./lib/Release/libmysqlpp.a ./lib/Debug

echo Copy mysql libs to lib directory
cp -r -f ./lib/Release/libmysql.dll ./lib/
cp -r -f ./lib/Release/libmysql.lib ./lib/
cp -r -f ./lib/Release/libmysqlclient.a ./lib/
cp -r -f ./lib/Release/libmysqlclient.so ./lib/
cp -r -f ./lib/Release/mysqlclient.lib ./lib/
cp -r -f ./lib/Release/libmysqlpp.a ./lib/

# extract libevent libs
echo Extract libevent libs
tar -xzvf libevent-2.0.22-stable.tar.gz
if [ -d ./libevent ]; then
 rm -rf ./libevent
fi

mv libevent-2.0.22-stable libevent

# compiling libevent
cd libevent
chmod -R 755 *
./configure CPPFLAGS=-fPIC --disable-shared
make
cp -r -f .libs/*.a ../lib/Debug/
cp -r -f .libs/*.a ../lib/
cp -r -f .libs/*.a ../lib/Release/
cd ../

# extract curl libs
# echo Extract curl libs
# if [ -d ./curl ]; then
#  rm -rf ./curl
# fi

# unzip -o curl-7.37.1.zip -d ./
# mv curl-7.37.1 curl
# unzip -o curl_libs.zip -d ./

# compiling protobuf
cd protobuf
chmod -R 755 *
./configure CXXFLAGS=-fPIC
make

if [ ! -d ../../_Out/Comm/ ]; then
 mkdir ../../_Out/Comm/
fi
if [ ! -d ../../_Out/Comm/Debug/ ]; then
 mkdir ../../_Out/Comm/Debug/
fi
if [ ! -d ../../_Out/Comm/Release/ ]; then
 mkdir ../../_Out/Comm/Release/
fi

cp -r -f ./src/.libs/*.so ../lib/Debug/
cp -r -f ./src/.libs/*.so.* ../lib/Debug/
cp -r -f ./src/.libs/*.so ../lib/Release/
cp -r -f ./src/.libs/*.so.* ../lib/Release/
cp -r -f ./src/.libs/*.so ../../_Out/Comm/Debug/
cp -r -f ./src/.libs/*.so.* ../../_Out/Comm/Debug/
cp -r -f ./src/.libs/*.so ../../_Out/Comm/Release/
cp -r -f ./src/.libs/*.so.* ../../_Out/Comm/Release/

cp -r -f ./src/.libs/*.so ../lib/
cp -r -f ./src/.libs/*.so.* ../lib/
cd ../

# compiling Theron
cd Theron
chmod -R 755 *
make library mode=debug boost=off c++11=on posix=on shared=on
cp -r -f ./Lib/libtherond.a ../lib/Debug/
cp -r -f ./Lib/libtherond.a ../lib/
make clean
make library mode=release boost=off c++11=on posix=on shared=on
cp -r -f ./Lib/libtheron.a ../lib/Release/
cp -r -f ./Lib/libtheron.a ../lib/
make clean
cd ../

# TODO: other libs

# back to main dir
pwd

