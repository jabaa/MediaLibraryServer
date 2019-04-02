#pragma once

#include "ConfigKeys.hpp"
#include "HttpRequestHandlerFactory.hpp"
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>
#include <fmt/format.h>
#include <iostream>

class MediaLibraryServer : public Poco::Util::ServerApplication {
public:
    MediaLibraryServer();
    virtual ~MediaLibraryServer() = default;

protected:
    void initialize(Application &self) override;
    void uninitialize() override;
    void defineOptions(Poco::Util::OptionSet &options) override;
    void handleHelp(const std::string &name, const std::string &value);
    void addConfig(const std::string &name, const std::string &value);

    int main(const std::vector<std::string> &) override;

private:
    using Configs = std::vector<std::string>;
    Configs configs;

    bool help;
};
