ROOT="$( cd "$(dirname "$0")" ; pwd -P )"
RES_DIR="$ROOT/res"

rm -rf "$RES_DIR"
mkdir "$RES_DIR"

echo -e "MediaLibraryServer.webroot = www_client/www\nMediaLibrarServer.port = 8080\nDatabase.type = sqlite\nDatabase.path = res/MediaLibrarServer.sqlite3" > "$RES_DIR/MediaLibraryServer.properties"