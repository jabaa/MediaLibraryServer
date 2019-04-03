ROOT="$( cd "$(dirname "$0")" ; pwd -P )"
BIN="$ROOT/server/build/bin/MediaLibraryServer"

$BIN -c"$ROOT/res/MediaLibraryServer.properties"

