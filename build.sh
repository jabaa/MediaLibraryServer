ROOT="$( cd "$(dirname "$0")" ; pwd -P )"
SERVER_DIR="$ROOT/server"
SERVER_BUILD_DIR="$SERVER_DIR/build"

rm -rf "$SERVER_BUILD_DIR"
mkdir "$SERVER_BUILD_DIR"

conan install -if "$SERVER_BUILD_DIR" "$SERVER_DIR"
cd "$SERVER_BUILD_DIR"; cmake "$SERVER_DIR"; cd "$ROOT"
cmake --build "$SERVER_BUILD_DIR"

