# $1 should be Debug or Release

# building in the cmakebuild directory because if "build" is used and added to .Rbuildignore then there are other problems

if [ "$(uname -s)" == "MSYS_NT-10.0-WOW" ]; then
  echo Windows Build
  cmake . -Bcmakebuild -G "Visual Studio 15 2017 Win64"
  # cmake --build cmakebuild --target ALL_BUILD --config $1 # Compiler not supported
else
  echo Linux Build
  cmake . -Bcmakebuild -DCMAKE_BUILD_TYPE=$1
  cmake --build cmakebuild
fi
