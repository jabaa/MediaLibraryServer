#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/Application.h>
#include <fmt/format.h>

class ApiRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    ApiRequestHandler();

    void handleRequest(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) override;

private:
    void login(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) const;
    void error(
        Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) const;

    void dbInit();
};
