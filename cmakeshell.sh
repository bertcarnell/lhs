# $1 should be Debug or Release

if [ "$(uname -s)" == "MSYS_NT-10.0-WOW" ]; then
  echo Windows Build
  cmake . -Bbuild -G "Visual Studio 15 2017 Win64"
  # cmake --build build --target ALL_BUILD --config $1 # Compiler not supported
else
  echo Linux Build
  cmake . -Bbuild -DCMAKE_BUILD_TYPE=$1
  cmake --build build
fi
