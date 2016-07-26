/// \file ConfigurationFactory.h
/// \brief Factory for instantiating specialized configuration interfaces
///
/// \author Pascal Boeschoten, CERN

#include <stdexcept>
#include <Configuration/ConfigurationFactory.h>
#include <Configuration/UriParser/UriParser.hpp>
#include <Configuration/FileConfiguration.h>
#ifdef FLP_CONFIGURATION_BACKEND_ETCD_ENABLED
#include <Configuration/EtcdConfiguration.h>
#endif

std::unique_ptr<ConfigurationInterface> ConfigurationFactory::getConfiguration(std::string uri)
{
  http::url parsed = http::ParseHttpUrl(uri);

  if (parsed.protocol == "file") {
    // If the "authority" part of the URI is missing (host, port, etc), the parser
    // will consider the thing before the first delimiter ('/') of the path as authority,
    // so we have to include that in the path we use.
    auto path = parsed.host + parsed.path;
    return std::unique_ptr<FileConfiguration>(new FileConfiguration(path));
  } else if (parsed.protocol == "etcd") {
#ifdef FLP_CONFIGURATION_BACKEND_ETCD_ENABLED
    return std::unique_ptr<EtcdConfiguration>(new EtcdConfiguration(parsed.host, parsed.port));
#else
    throw std::runtime_error("Back-end 'etcd' not enabled");
#endif
  } else {
    throw std::runtime_error("Unrecognized URI scheme");
  }
}
