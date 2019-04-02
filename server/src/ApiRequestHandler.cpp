#include "ApiRequestHandler.hpp"
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>

ApiRequestHandler::ApiRequestHandler() = default;

void ApiRequestHandler::handleRequest(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) {

    Poco::Util::Application &app = Poco::Util::Application::instance();
    app
        .logger()
        .information(fmt::format(
            "ApiRequest from {}: {}",
            request.clientAddress().toString(),
            request.getURI()));

    if (request.getMethod() == "POST" && request.getURI() == "/api/login") {
        login(request, response);
    } else {
        error(request, response);
    }
}

void ApiRequestHandler::login(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) const {

    Poco::Util::Application &app = Poco::Util::Application::instance();
    app.logger().information(
        fmt::format("Login from {}", request.clientAddress().toString()));
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &ostr = response.send();
    ostr << "{}";
}

void ApiRequestHandler::error(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) const {

    Poco::Util::Application &app = Poco::Util::Application::instance();
    app.logger().information(
        fmt::format("Error from {}", request.clientAddress().toString()));
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &ostr = response.send();
    ostr << "{}";
}

void ApiRequestHandler::dbInit() {
    Poco::Data::SQLite::Connector::registerConnector();
    Poco::Data::Session session("SQLite", "sample.db");
}