using System;
using System.Collections;
using System.Data;
using System.Xml;
using System.IO;
using System.Xml.XPath;
using System.Diagnostics;

namespace DBClassCodeUtility
{
  /// <summary>
  /// Summary description for CData.
  /// </summary>
  public class CData
  {
    //Singleton class
    private string m_DBVersion = "DBClassCodeUtility BETA 0.6.3";
    private string m_ClassVersion = "(DB)ClassCodeUtility BETA 0.6.2";
    private string m_WorkingDirectory = null;
    private string m_OutPutPath;
    private XmlDocument m_Doc;
    private XmlDocument m_NewDoc;
    private string m_MethodSummary;
    private DataTable m_TableData;
    private string IniFile = null;
    private ArrayList m_Comments;
    private ArrayList m_TablesInPath;
  
    private static CData instance;

    public enum dbType {CDATETIME=23, LONG=0  , DBTYPE};

    public enum MethodType {MISSING=1, OLD, BOTH};

    private CData() 
    {
//      string sProdName = "Widget";
//      int iUnitQty = 100;
//      double  dUnitCost = 1.03;
//
//      string TraceLogFile = CData.Instance.getWorkingDirectory() + "TraceLogFile.log";
//
//      // Create a file for output named TestFile.txt.
//      Stream traceLogFile = File.CreateText(TraceLogFile);
// 
//      /* Create a new text writer using the output stream, and add it to
//       * the trace listeners. */
//      TextWriterTraceListener myLogListener = new  TextWriterTraceListener(File);
//      Trace.Listeners.Add(myLogListener);
// 
//      Trace.WriteLine("Trace Information-Product Starting ");
//      Trace.Indent();
//
//      Trace.WriteLine("The product name is "+ sProdName);
//      Trace.WriteLine("The product name is"+ sProdName, "Field" );
//      Trace.WriteLineIf(iUnitQty > 50, "This message WILL appear");
//      Trace.Assert(dUnitCost > 1, "Message will NOT appear");
//        
//
//      Trace.Unindent();
//      Trace.WriteLine("Trace Information-Product Ending");
//
//      Trace.Flush();
// 
//      traceLogFile.Flush();
//      traceLogFile.Close(); 

    }

    public static CData Instance
    {
      get 
      {
        if (instance == null)
        {
          instance = new CData();
        }
        return instance;
      }
    }
  
    public string getVersionOfDBClassCodeUtility()
    {
      return m_DBVersion;
    }

    public string getVersionOfClassCodeUtility()
    {
      return m_ClassVersion;
    }

  
    public void setWorkingDirectory (string WorkingDirectory)
    {
      m_WorkingDirectory = WorkingDirectory;
      // clean Arraylist when directory is changed
      resetTablesInPath();
    }

    public string getWorkingDirectory ()
    {
      string WD;

      if ( m_WorkingDirectory != null && !m_WorkingDirectory.Equals("") )
      {
        WD = m_WorkingDirectory;
      }
      else
      {
        WD = System.Environment.CurrentDirectory;
      }

      return WD;
    }

    public void setTablesInPath (ArrayList TablesInPath)
    {
      m_TablesInPath = TablesInPath;
    }

    public void resetTablesInPath()
    {
      m_TablesInPath = null;
    }

    public ArrayList getTablesInPath(bool ToUpper)
    {
      string sFileName = null;
      int typePos;
        
      m_TablesInPath = new ArrayList();
      DirectoryInfo d = new DirectoryInfo(m_WorkingDirectory);
      FileInfo[] fileInfo = d.GetFiles("*.h");

      foreach(FileInfo fi in fileInfo)
      {
        // fi.Name is read only
        sFileName = fi.Name;
        if ( (typePos = sFileName.IndexOf(".h"))!= -1)
        {
          // remove ".h"
          sFileName = sFileName.Remove(typePos,2);
          // remove "C"
          if (ToUpper)
          {
            sFileName = sFileName.Remove(0, 1).ToUpper();
          }
          else 
          {
            sFileName = sFileName.Remove(0, 1);
          }
        }

        m_TablesInPath.Add(sFileName);
      }
      m_TablesInPath.Sort();
 
      return m_TablesInPath;
    }

    public ArrayList getMethodRuleSet()
    {
      ArrayList MethodRuleSet = new ArrayList();

      string ManualMethodRuleSet = ReadSetting("UserSettings", "ManualMethodRuleSet");

      if (ManualMethodRuleSet.Length != 0)
      {
        string[] parts = ManualMethodRuleSet.Split(',');

        foreach (string part in parts)
        {
          MethodRuleSet.Add(part);
        }
      }

      return MethodRuleSet;
    }


    public void setOutPutPath (string OutPutPath)
    {
      m_OutPutPath  = OutPutPath ;
    }

    public string getOutPutPath()
    {
      return m_OutPutPath;
    }

    public void setTableContent (DataTable TableData)
    {
      m_TableData = TableData;
    }

    public DataTable getTableData()
    {
      return m_TableData;
    }

    public void setComments(ArrayList comments)
    {
      m_Comments = comments;
    }

    public ArrayList getComments()
    {
      return m_Comments;
    }

    public void setNewSummary(string methodSummary)
    {
      m_MethodSummary = methodSummary;
    }

    // XML describe new class
    public XmlDocument getXmlDocument()
    {
      if (m_Doc == null)
      {
        m_Doc = new XmlDocument();
      }    
      return m_Doc;
    }

    // XML describe new class
    public void setXmlDocument(XmlDocument doc)
    {
      m_Doc = doc;
    }

    public XmlDocument getNewXmlDocument()
    {
      if (m_NewDoc == null)
      {
        m_NewDoc = new XmlDocument();
      }    
      return m_NewDoc;
    }

    // copy into the new xml file
    public void setNewXmlDocument (XmlDocument newDoc)
    {
      //Create a deep clone.  The cloned node 
      m_NewDoc = (XmlDocument) newDoc.Clone();
    }

    public string getMethodSummary()
    {
      return m_MethodSummary;
    }

    public XmlNodeList getPersonalMethods()
    {     
      if ( m_NewDoc != null )
      {
        XmlNodeList PersonalMethodList;
        XmlElement root = m_NewDoc.DocumentElement;
        PersonalMethodList = root.SelectNodes("/class/METHOD[@GENERATEDBY='MANUAL']");
        return PersonalMethodList;
      }
      else
        return null;  
    }

    public XmlNodeList getPersonalMethodsToGenerate()
    {     
      if ( m_NewDoc != null )
      {
        XmlNodeList PersonalMethodList;
        XmlElement root = m_NewDoc.DocumentElement;
        PersonalMethodList = root.SelectNodes("/class/METHOD[@GENERATEDBY='MANUAL'and @GENERATE='YES']");
        return PersonalMethodList;
      }
      else
        return null;  
    }

    //get missing and old generated methods
    public XmlNodeList getGeneratedMethodsToMerge(int methodType)
    {  
      // new missing 
      // old one
      // both

      XmlNodeList OldGeneratedMethoddList = null, tempOldGeneratedMethoddList;  
      
      if (methodType == (int)MethodType.BOTH)
      {
        // use new XML file with updated information
        if ( m_NewDoc != null )
        {
          XmlElement root = m_NewDoc.DocumentElement;
          tempOldGeneratedMethoddList = root.SelectNodes("/class/METHOD[@COLUMNEXISTS='YES' and @GENERATEDBY='DBClassCodeUtility']");

          //minus pre defined values de/construktor = higher than 2
          if( tempOldGeneratedMethoddList.Count > 2)
          {
            //only when method and column in DB or/and File not exist, otherwise COLUMNEXISTS is YES
            OldGeneratedMethoddList = root.SelectNodes("/class/METHOD[@COLUMNEXISTS='NO' and @GENERATEDBY='DBClassCodeUtility']");
          }
          else
          {
            // to return 0 Elements
            OldGeneratedMethoddList = root.SelectNodes("/class/METHOD[@COLUMNEXISTS='NOTHING']");
          }
        }
      }
      // missing in file
      else if (methodType == (int)MethodType.MISSING)
      {
        // use new XML file with updated information
        if ( m_NewDoc != null )
        {
          XmlElement root = m_NewDoc.DocumentElement;
   
          //column in DB exist
          OldGeneratedMethoddList = root.SelectNodes("/class/METHOD[@GENERATEDBY='DBClassCodeUtility' and @COLUMNEXISTS='NO' and @FROM='DB']");
        }
      }
      // old one in files
      else if (methodType == (int)MethodType.OLD)
      {
        // use new XML file with updated information
        if ( m_NewDoc != null )
        {
          XmlElement root = m_NewDoc.DocumentElement;
   
          //only when method in File exist
          OldGeneratedMethoddList = root.SelectNodes("/class/METHOD[@COLUMNEXISTS='NO' and @FROM='FILE' and @GENERATEDBY='DBClassCodeUtility']");
        }
      }

      return OldGeneratedMethoddList;
    }

    public XmlNodeList getDifferentGeneratedMethods()
    {     
      if ( m_NewDoc != null )
      {
        XmlNodeList DiffMethods;
        XmlElement root = m_NewDoc.DocumentElement;

        DiffMethods = root.SelectNodes("/class/METHOD[@COLUMNEXISTS='YES' and @GENERATEDBY='DBClassCodeUtility' and @BODYIDENTICAL='NO']");
      
        return DiffMethods;
      }
      else
        return null;  
    }

    public void makeIniFile(string OutPutPath, string service)
    {
      setOutPutPath(OutPutPath);
      IniFile = getOutPutPath() + "\\DBClassCodeUtility.ini";
      
      if(!File.Exists(IniFile))
      {
        StreamWriter file = File.CreateText((IniFile));
        file.WriteLine(";DBClassCodeUtility.ini");

        file.WriteLine(";Settings");
        file.WriteLine("[UserSettings]");       
        file.WriteLine("SelectedDataBase=");
        file.WriteLine("WorkingDirectory="  + Environment.CurrentDirectory);
        file.WriteLine("OutPutPath=" + m_OutPutPath);
        file.WriteLine("Gen=GEN_CLASS");
        file.WriteLine("ManualMethodSort=yes");
        file.WriteLine("WildCardFilter=yes");
        file.WriteLine("ManualMethodRuleSet=init,select,copy");
        file.WriteLine("ManualMethodAutomaticGeneration=no");
        file.WriteLine("StaticMembers=yes");
        file.WriteLine(";Default: cCBS_StdConnection; Older Versions: cCBS_Connection");
        file.WriteLine("ConstructorArgumentType=cCBS_StdConnection,cCBS_Connection");
        file.WriteLine("DefaultConstructor=yes");
        file.WriteLine("");

        file.WriteLine("[" + service + "]");             
        file.WriteLine("User=");
        file.WriteLine("Password=");
        file.WriteLine("");       
        //        file.WriteLine("[Sektion]");
        //        file.WriteLine("key=Datum");
        file.Close();
      }
      else
      {
        WriteSetting("UserSettings", "OutPutPath", m_OutPutPath);
      }    
    }    

    public String ReadSetting(String Section, String Entry) 
    {
      if (File.Exists(IniFile)) 
      {
        StreamReader reader = new StreamReader(IniFile);
        String line = "";
        // default return
        String toreturn = "";
        bool section = false;
        while ((line = reader.ReadLine()) != null) 
        {
          if (!line.StartsWith(";")) 
          {
            if (line.StartsWith("[") && line.EndsWith("]")) 
            {
              if (line == ("[" + Section + "]"))
                section = true;
              else
                section = false;
            }
            if (section) 
            {
              if (line.StartsWith(Entry + "=")) 
              {
                if (line.Length >= Entry.Length + 2) 
                {
                  toreturn = line.Substring(Entry.Length + 1);
                  break;
                }
                else 
                {
                  toreturn = "";
                  break;
                }
              }// if (line.StartsWith(Entry + "=")) 
            }// if (section) 
          }// if (!line.StartsWith(";"))
        } // while ((line = reader.ReadLine()) != null)
        reader.Close();
        return toreturn;
      } //   if (File.Exists(Filename)) 
      else 
      {
        throw new IOException("Try again");
      }
    }//public static String ReadSetting(String Filename, String Section, String Entry, String Default) 

    public void WriteSetting(String Section, String Entry, String Value) 
    {
      int i = (IniFile.Length-20);
      string IniFile2 = IniFile.Insert(i, "~");
      StreamWriter writer = new StreamWriter(IniFile2, false);
      bool section = false;
      bool found = false;
      if (File.Exists(IniFile)) 
      {
        String line = "";
        StreamReader reader = new StreamReader(IniFile);
        while ((line = reader.ReadLine()) != null) 
        {
          if (!line.StartsWith(";")) 
          {
            if (line.StartsWith("[") && line.EndsWith("]")) 
            {
              if (section && !found) 
              {
                writer.WriteLine(Entry + "=" + Value);
                found = true;
              }
              writer.WriteLine(line);
              if (!section && line == "[" + Section + "]") 
              {
                section = true;
              }
              else 
              {
                section = false;
              }
            }// if (line.StartsWith("[") && line.EndsWith("]")) 
            else 
            {
              if (!found) 
              {
                if (section && line.StartsWith(Entry + "=")) 
                {
                  writer.WriteLine(Entry + "=" + Value);
                  found = true;
                }
                else 
                {
                  writer.WriteLine(line);
                }
              }// if (!found) 
              else 
              {
                writer.WriteLine(line);
              }
            }
          }//if (!line.StartsWith(";")) 
          else 
          {
            writer.WriteLine(line);
          }
        }// while ((line = reader.ReadLine()) != null) 
        reader.Close();
      }// if (File.Exists(Filename)) 
      if (!found) 
      {
        // new section
        if (!section)
        {
          // new line
          writer.WriteLine("");
          writer.WriteLine("[" + Section + "]");
        }

        writer.WriteLine(Entry + "=" + Value);
      }
      writer.Close();
      try 
      { 
        File.Delete(IniFile); 
      } 
      catch {}
      File.Move(IniFile2, IniFile);
    }  
  }
}

