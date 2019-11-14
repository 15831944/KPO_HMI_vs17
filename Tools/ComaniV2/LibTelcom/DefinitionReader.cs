/*
 * Erstellt mit SharpDevelop.
 * Benutzer: Christian
 * Datum: 08.03.2009
 * Zeit: 18:50
 */
using System;
using System.Xml;
using System.Collections.Generic;

namespace LibTelcom
{
  /// <summary>
  /// Description of DefinitionReader.
  /// </summary>
  public class TelegramDefinitionReader
  {
    private XmlDocument xmlDoc;
    private Dictionary<string, XmlNode> userDefinedNodesDict;

    public TelegramDefinitionReader(string telegramDefinitionFile)
    {
      xmlDoc = new XmlDocument();
      xmlDoc.Load(telegramDefinitionFile);
      userDefinedNodesDict = new Dictionary<string, XmlNode>();
      //now init user defined nodes
      XmlNodeList typeNodeList = xmlDoc.SelectNodes("module/type");
      foreach (XmlNode typeNode in typeNodeList)
      {
        userDefinedNodesDict.Add(typeNode.Attributes["name"].Value, typeNode);
      }
    }
    PrimitiveItem createPrimitiveItem(XmlNode itemNode)
    {
      int count = Convert.ToInt32(itemNode.Attributes["count"].Value);
      string name = itemNode.Attributes["name"].Value;
      string comment = itemNode.SelectSingleNode("comment").InnerText;
      int index = Convert.ToInt32(itemNode.Attributes["index"].Value);
      string dbcol = itemNode.Attributes["dbcol"].Value;
      XmlNode primitiveNode = itemNode.SelectSingleNode("primitive");
      int fieldLen = Convert.ToInt32(primitiveNode.Attributes["len"].Value);
      string appType = primitiveNode.Attributes["appType"].Value;
      string unit = primitiveNode.Attributes["unit"].Value;
      string minVal = primitiveNode.Attributes["min"].Value;
      string maxVal = primitiveNode.Attributes["max"].Value;
      return new PrimitiveItem(name, count, index, comment, fieldLen, typeFromString(appType), unit, minVal, maxVal, dbcol);
    }
    /// <summary>
    /// Create an user defined item from XML
    /// </summary>
    /// <param name="itemNode">the xml node</param>
    /// <returns>an user defined item as specified by XML</returns>
    UserDefinedItem createUserDefinedItem(XmlNode itemNode)
    {
      int count = Convert.ToInt32(itemNode.Attributes["count"].Value);
      string name = itemNode.Attributes["name"].Value;
      int index = Convert.ToInt32(itemNode.Attributes["index"].Value);
      string dbcol = itemNode.Attributes["dbcol"].Value;
      string comment = itemNode.SelectSingleNode("comment").InnerText;
      XmlNode udNode = itemNode.SelectSingleNode("userDefined");
      if (udNode != null)
      {
        string typeName = udNode.Attributes["name"].Value;
        UserDefinedItem udItem = new UserDefinedItem(name, count, index, comment, typeName, dbcol);
        //now add all subItems
        XmlNodeList subNodes = userDefinedNodesDict[typeName].SelectNodes("element");
        foreach (XmlNode subNode in subNodes)
        {
          TelegramItem item = createItem(subNode);
          udItem.SubItems.Add(item);
        }
        return udItem;
      }
      else
      {
        XmlNode recordNode = itemNode.SelectSingleNode("record");
        UserDefinedItem udItem = new UserDefinedItem(name, count, index, comment, "record", "");
        XmlNodeList items = recordNode.SelectNodes("element");
        foreach (XmlNode item in items)
        {
          udItem.SubItems.Add(createItem(item));
        }

      }
      return null;
    }

    TelegramItem createItem(XmlNode itemNode)
    {
      XmlNode primitiveNode = itemNode.SelectSingleNode("primitive");
      if (primitiveNode != null)
      {
        return createPrimitiveItem(itemNode);
      }
      else
      {
        XmlNode udNode = itemNode.SelectSingleNode("userDefined");
        if (udNode != null)
          return createUserDefinedItem(itemNode);
        else
          return null;
      }
    }

    private TelcomDataType typeFromString(string appType)
    {
      if (appType == "number")
        return TelcomDataType.Number;
      else if (appType == "integer")
        return TelcomDataType.Integer;
      else if (appType == "string")
        return TelcomDataType.String;


      return TelcomDataType.String;
    }

    public List<TelegramDefinition> getTelegramDefinitions()
    {
      List<TelegramDefinition> telegramList = new List<TelegramDefinition>();
      XmlNodeList telegramNodeList = xmlDoc.SelectNodes("module/telegram");
      foreach (XmlNode teleNode in telegramNodeList)
      {
        string teleName = teleNode.Attributes["name"].Value;
        string comment = teleNode.SelectSingleNode("comment").InnerText;
        TelegramDefinition tele = new TelegramDefinition(teleName);
        tele.Description = comment;

        XmlNodeList itemNodeList = teleNode.SelectNodes("record/element");
        foreach (XmlNode itemNode in itemNodeList)
        {
          TelegramItem item = createItem(itemNode);
          tele.TelegramItems.Add(item);
        }
        telegramList.Add(tele);
      }
      return telegramList;

    }
  }
}
