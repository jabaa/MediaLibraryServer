#pragma once

#include "ApiRequestHandler.hpp"
#include "WebRequestHandler.hpp"
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <boost/algorithm/string/predicate.hpp>

class HttpRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    HttpRequestHandlerFactory() = default;

    Poco::Net::HTTPRequestHandler *
    createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
        if (boost::algorithm::starts_with(request.getURI(), "/api"))
            return new ApiRequestHandler();
        else
            return new WebRequestHandler();
    }
};
