#include "MediaLibraryServer.hpp"

MediaLibraryServer::MediaLibraryServer() : configs(), help(false) {}

void MediaLibraryServer::initialize(Application &self) {
    loadConfiguration();
    logger().information(fmt::format("Configs: {}", configs.size()));
    for (const auto &c : configs) {
        try {
            loadConfiguration(c);
        } catch (const Poco::InvalidArgumentException &e) {
            logger().warning(
                fmt::format("Poco::InvalidArgumentException: {}", e.what()));
        }
    }
    Poco::Util::ServerApplication::initialize(self);
}

void MediaLibraryServer::uninitialize() {
    Poco::Util::ServerApplication::uninitialize();
}

void MediaLibraryServer::defineOptions(Poco::Util::OptionSet &options) {
    ServerApplication::defineOptions(options);

    options.addOption(
        Poco::Util::Option("help", "h", "display argument help information")
            .required(false)
            .repeatable(false)
            .callback(Poco::Util::OptionCallback<MediaLibraryServer>(
                this, &MediaLibraryServer::handleHelp)));

    options.addOption(
        Poco::Util::Option("config", "c", "add a path to a configuration")
            .required(false)
            .repeatable(true)
            .argument("path", true)
            .callback(Poco::Util::OptionCallback<MediaLibraryServer>(
                this, &MediaLibraryServer::addConfig)));
}

void MediaLibraryServer::handleHelp(const std::string &, const std::string &) {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader(
        "A web server that serves the current date and time.");
    helpFormatter.format(std::cout);
    help = true;
    stopOptionsProcessing();
}

void MediaLibraryServer::addConfig(
        const std::string &,
        const std::string &value) {
    if (std::find(configs.begin(), configs.end(), value) == configs.end()) {
        configs.emplace_back(value);
    }
}

int MediaLibraryServer::main(const std::vector<std::string> &) {
    if (help) {
        return Application::EXIT_OK;
    }
    if (!config().has(MEDIA_LIBRARY_SERVER__WEBROOT)) {
        logger().error("Can't initialize server. Webroot is not set");
        return Application::EXIT_USAGE;
    }
    unsigned short port = static_cast<unsigned short>(
        config().getInt(MEDIA_LIBRARY_SERVER__PORT, 8080));

    Poco::Net::ServerSocket svs(port);
    Poco::Net::HTTPServer srv(new HttpRequestHandlerFactory(), svs,
                                new Poco::Net::HTTPServerParams);
    srv.start();
    waitForTerminationRequest();
    srv.stop();

    return Application::EXIT_OK;
}
