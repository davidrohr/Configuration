/// \file FileConfiguration.h
/// \brief Configuration interface for files. Port of Configuration.h & Configuration.cxx
///
/// \author Sylvain Chapeland, CERN
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#ifndef SRC_FILECONFIGURATION_H_
#define SRC_FILECONFIGURATION_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include "ConfigurationBase.h"

namespace AliceO2
{
namespace Configuration
{

class FileConfiguration final : public ConfigurationBase
{
  public:
    FileConfiguration(const std::string& filePath);
    virtual ~FileConfiguration();
    virtual void putString(const std::string& path, const std::string& value) override;
    virtual auto getString(const std::string& path) -> Optional<std::string> override;
    virtual void setPrefix(const std::string& path) override;

  private:
    std::string mFilePath;
    boost::property_tree::ptree mPropertyTree;
};

} // namespace Configuration
} // namespace AliceO2

#endif /* SRC_FILECONFIGURATION_H_ */
