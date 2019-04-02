#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/MediaType.h>
#include <boost/algorithm/string/predicate.hpp>

class WebRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
  WebRequestHandler() = default;

  void handleRequest(Poco::Net::HTTPServerRequest &request,
                     Poco::Net::HTTPServerResponse &response) override;

private:
    static Poco::Net::MediaType getMediaType(const std::string &path) {
        if (boost::algorithm::ends_with(path, ".html"))
            return Poco::Net::MediaType("text/html");
        if (boost::algorithm::ends_with(path, ".css"))
            return Poco::Net::MediaType("text/css");
        if (boost::algorithm::ends_with(path, ".js"))
            return Poco::Net::MediaType("application/javascript");
        return Poco::Net::MediaType("text/plain");
    }
};
