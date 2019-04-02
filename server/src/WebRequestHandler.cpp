#include "ConfigKeys.hpp"
#include "WebRequestHandler.hpp"
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/Util/Application.h>
#include <boost/algorithm/string/trim_all.hpp>
#include <exception>
#include <fmt/format.h>

void WebRequestHandler::handleRequest(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) {
    Poco::Util::Application &app = Poco::Util::Application::instance();
    app.logger().information(fmt::format("WebRequest from {}: {}",
                                        request.clientAddress().toString(),
                                        request.getURI()));

    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    Poco::Path webrootPath(Poco::Path::forDirectory(
        app.config().getString(MEDIA_LIBRARY_SERVER__WEBROOT)));
    Poco::File indexFile(Poco::Path(webrootPath, Poco::Path("index.html")));
    Poco::File requestedFile(
        request.getURI() == "/"
            ? indexFile
            : Poco::Path(webrootPath, boost::algorithm::trim_left_copy_if(
                                            Poco::Path(request.getURI()).toString(),
                                            [](char c) { return c == '/'; })));

    try {
        if (!requestedFile.exists() || !requestedFile.isFile())
        throw std::exception();
        response.sendFile(requestedFile.path(),
                        getMediaType(requestedFile.path()).toString());
    } catch (...) {
        app.logger().warning(fmt::format("{} not found", requestedFile.path()));
        try {
        if (!indexFile.exists() || !indexFile.isFile())
            throw std::exception();
        response.sendFile(indexFile.path(),
                            getMediaType(indexFile.path()).toString());
        } catch (...) {
        app.logger().warning(fmt::format("{} not found", indexFile.path()));
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.send() << "<html><head><title>404 - File not "
                            "found</title></head><body><h1>404 - File not "
                            "found</h1></body></html>";
        }
    }
}
