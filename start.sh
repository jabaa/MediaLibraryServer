ROOT="$( cd "$(dirname "$0")" ; pwd -P )"
BIN="$ROOT/build/bin/MediaLibraryServer"

$BIN -c"$ROOT/res/MediaLibraryServer.properties"

