ROOT="$( cd "$(dirname "$0")" ; pwd -P )"
BUILD_DIR="$ROOT/build"
SERVER_DIR="$ROOT/server"

rm -rf "$BUILD_DIR"
mkdir "$BUILD_DIR"

conan install -if "$BUILD_DIR" "$SERVER_DIR"
cd "$BUILD_DIR"; cmake "$SERVER_DIR"; cd "$ROOT"
cmake --build "$BUILD_DIR"

