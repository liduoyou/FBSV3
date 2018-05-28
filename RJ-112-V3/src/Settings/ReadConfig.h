#ifndef READCONFIG_H
#define READCONFIG_H
#include <QFile>
#include <QDomDocument>

class SettingsManager;
class ReadConfig
{
public:

  /**
   * 构造函数
   *
   */
  ReadConfig();

  /**
   * 析构函数
   *
   */
  ~ReadConfig();

  /**
   * 获取配置文件中的值
   *
   * @param key 配置的键
   * @param type 类型标签
   *
   * @return 配置项对应的值
   */


  bool parseXML();
  void parseXMLToCreateIni();

private:
  void parseChannelItems(const QString& Ac_PortNo, QDomNode channelItemsNode);
  QString parseCollector(QDomNode collectorNode);

  QFile *file;
  QDomDocument *dom;
  SettingsManager* _msettings;

};

#endif // READCONFIG_H
