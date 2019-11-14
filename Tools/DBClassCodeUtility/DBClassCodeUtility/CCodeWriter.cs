using System;
using System.Xml;
using System.IO;
using System.Collections;
using System.Windows.Forms;
using System.Diagnostics;

namespace DBClassCodeUtility
{
  /// <summary>
  /// Summary description for CCodeWriter.
  /// </summary>
  public class CCodeWriter
  {
    private bool IsAutomatic = false;

    public CCodeWriter()
    {
      //
      // TODO: Add constructor logic here
      //
    }

    // generate cpp-file and header-file
    public bool writeCode(string fileName,  XmlDocument doc)
    {
      if (CData.Instance.ReadSetting("UserSettings", "ManualMethodAutomaticGeneration") == "yes")
      {
        IsAutomatic = true;
      }
      else 
      {
        IsAutomatic = false;
      }

      if (writeHeader(fileName, doc)) // generate header-file
        if (writeCPP(fileName, doc)) // generate cpp-file
        {
          return true;
        }
        else
        {
          return false;
        }
      else
      {
        return false;
      }
    }

    // generate DEF-file
    public void writeDefCode(string fileName,  XmlDocument doc)
    {
      if (writeDef(fileName, doc)) // generate header-file
        MessageBox.Show("File DEF_" + fileName +".h is generated.");
    }

    // generate Def-file
    bool writeDef(string fileName,  XmlDocument doc)
    {
      bool RetValue = true;
      try
      {
        XmlNode root;
        root = doc.FirstChild;

        XmlNodeList DBDataList;
        DBDataList = root.SelectNodes("/CLASS/DEF/DATA");

        string defName;
        string defValue;
        
        ArrayList def = new ArrayList();

        //        if(File.Exists("DEF_" + fileName + ".h"))
        //          File.Copy("DEF_" + fileName + ".h","DEF_" + fileName + ".h.bak",true);

        StreamWriter sw = File.CreateText(("DEF_" + fileName + ".h"));
        sw.Write("/* Generated name space, using column ");
        sw.Write(root.ChildNodes[0].Attributes["NAME"].InnerText.ToString());
        sw.Write(" */ \r\n");

        sw.WriteLine(root.Attributes["BODY_HEADER"].InnerText);
        
        sw.Write("/* \r\n");
        // header comment
        sw.WriteLine(root.FirstChild.Attributes["DEF_COMMENT"].InnerText.Trim());
        sw.Write("*/ \r\n\r\n");

        for(int arg = 0 ; arg < DBDataList.Count; arg++)//if more as on argument
        {
          defName = DBDataList[arg].Attributes["DEFNAME"].InnerText.Trim();
          defValue = DBDataList[arg].Attributes["DEFVALUE"].InnerText.Trim();
          defName = defName.Replace(" ", "");
          defValue = defValue.Replace(" ", "");
          
          //Um Duplikate zu vermeiden
          if(!def.Contains(defName)) 
          {
            sw.Write(" const ");
            
            if(root.FirstChild.Attributes["TYPE"].InnerText.Equals("string")) 
              sw.Write("std::");          
            
            sw.Write(root.FirstChild.Attributes["TYPE"].InnerText + " ");            
            sw.Write(defName);
            sw.Write(" = ");

            if(root.FirstChild.Attributes["TYPE"].InnerText.Equals("string")) 
              sw.Write("\"" + defValue + "\"" );
            else 
              sw.Write(defValue);

            sw.Write(";\r\n");
            //Um Duplikate zu vermeiden
            def.Add(defName);        
          }
          
        }//  for(int arg = 0 ; arg < root.FirstChild.ChildNodes.Count; arg++)
        sw.Write("\r\n");
        sw.WriteLine("};");
        sw.Write("\r\n");
        sw.Write("#endif /* _INC_CDEF_" + fileName + "_INCLUDED */");

        // Normalize line ending
        sw.Write(Environment.NewLine);
        sw.Close();
      }
      catch( System.UnauthorizedAccessException e )
      {
        RetValue = false;

        System.Diagnostics.Process process = System.Diagnostics.Process.Start("cleardlg.exe", "/checkout \"" + CData.Instance.getWorkingDirectory() + "\\DEF_" + fileName + ".h\"");

        process.WaitForExit();

        if (process.ExitCode != 1)
        {
          DialogResult dr = MessageBox.Show(e.StackTrace + " : \r\n\r\n" + e.Message + " \r\n Press OK to open file dialog, CANCEL to skip generating",
            "UnauthorizedAccess", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);

          //if (dr == DialogResult.OK)
          //{
          //}
        }

        writeDef(fileName, doc);
      }
      catch(Exception ex)
      {
        RetValue = false;
        MessageBox.Show(ex.StackTrace + ": \r\n\r\n"  
          + ex.Message,
          "Exception", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      return RetValue;
    }

    // generate header-file
    bool writeHeader(string fileName,  XmlDocument doc)
    {
      bool RetValue = true;
      try
      {
        XmlNode root;
        root = doc.FirstChild;

        XmlNodeList DBMemberCodeMethodList = root.SelectNodes("/class/MEMBER");
        XmlNodeList DBClassCodeMethodList  = root.SelectNodes("/class/METHOD[@GENERATE='YES']");
        int DBGeneratedMethodCount         = root.SelectNodes("/class/METHOD[@GENERATE='YES' and @GENERATEDBY='DBClassCodeUtility']").Count;
   
        string accessibility_key = "";// contains "public:", "protected:" or "private:"

        StreamWriter sw = File.CreateText(("C" + fileName + ".h"));

        // header comment
        sw.Write(root.Attributes["SMS_COPYRIGHT"].InnerText);
        sw.Write(root.Attributes["HEADER_COMMENT"].InnerText);
        sw.Write(root.Attributes["HEADER_MACRO"].InnerText);
        sw.WriteLine(root.Attributes["HEADER_INCLUDE_MANUAL"].InnerText);
        sw.Write(root.Attributes["HEADER_INCLUDE"].InnerText);

        if (root.Attributes["HEADER_CLASS_MANUAL"].InnerText != "")
        {
          sw.WriteLine(root.Attributes["HEADER_CLASS_MANUAL"].InnerText);
        }

        if (root.Attributes["HEADER_OUTER_UNDETECTEDCODE"].InnerText != "")
        {
          sw.WriteLine(root.Attributes["HEADER_OUTER_UNDETECTEDCODE"].InnerText);
        }

        if ( root.Attributes["HEADER_CLASS"].InnerText != "")
        {
          sw.WriteLine(root.Attributes["HEADER_CLASS"].InnerText);
        }

        sw.WriteLine(root.Attributes["HEADER_BODY"].InnerText);
        
        if (root.Attributes["HEADER_INNER_UNDETECTEDCODE"].InnerText != "")
        {
          if (accessibility_key != "public:\r\n")// only if accessibility was changed
          {
            accessibility_key = "public:\r\n";
            sw.Write(accessibility_key);
          }
          sw.WriteLine(root.Attributes["HEADER_INNER_UNDETECTEDCODE"].InnerText);
        }

        for (int i = 0; i < DBMemberCodeMethodList.Count; i++)// loop for each static member
        {
          if (DBMemberCodeMethodList[i].Attributes["HEADER_STATIC_MEMBER"] != null)
          {
            if ( i == 0 )
            {
              if (accessibility_key != "public:\r\n")// only if accessibility was changed
              {
                accessibility_key = "public:\r\n";
                sw.Write(accessibility_key);
              }
            }

            // mark as generated
            if (root.Attributes["GENERATED_COMMENT"] != null)
            {
              // generated comment         
              sw.Write("  " + root.Attributes["GENERATED_COMMENT"].InnerText + "\r\n");
            }

            string staticMember = DBMemberCodeMethodList[i].Attributes["HEADER_STATIC_MEMBER"].InnerText;
            sw.WriteLine("  " + staticMember);

            if ( i == DBMemberCodeMethodList.Count-1 )
            {
              sw.Write("\r\n");
            }
          }
        }

        for(int i = 0 ; i < DBClassCodeMethodList.Count ; i++)// loop for each method
        {
          if (accessibility_key != DBClassCodeMethodList[i].Attributes["ACCESSIBILITY"].InnerText)// only if accessibility was changed
          {
            accessibility_key = DBClassCodeMethodList[i].Attributes["ACCESSIBILITY"].InnerText;
            sw.Write(accessibility_key);
          }

          Debug.WriteLine(DBClassCodeMethodList[i].Attributes["NAME"].InnerText);
          Debug.WriteLine(DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText);

          if (DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText.Equals("DBClassCodeUtility"))
          {
            // mark as generated
            if (root.Attributes["GENERATED_COMMENT"] != null)
            {
              // generated comment         
              sw.Write("  " + root.Attributes["GENERATED_COMMENT"].InnerText + "\r\n");

              if (DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"] != null)
              {
                if (DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"].InnerText != "")
                {
                  sw.Write("  //##" + DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"].InnerText + "\r\n");
                }        
              }
            }
          }
          else if (DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText.Equals("MANUAL"))
          {
            if (DBClassCodeMethodList[i].Attributes["HEADER_COMMENT"] != null)
            {
              // personal comment
              if (!DBClassCodeMethodList[i].Attributes["HEADER_COMMENT"].InnerText.Equals(""))
                sw.Write(DBClassCodeMethodList[i].Attributes["HEADER_COMMENT"].InnerText);
            }
          }

          if (DBClassCodeMethodList[i].Attributes["LINESAVE"] != null)
          {
            string headerSignature = DBClassCodeMethodList[i].Attributes["HEADER_SIGNATURE"].InnerText;
            if (headerSignature  == "")
            {
              // its read from cpp file and the class must be removed
              headerSignature = DBClassCodeMethodList[i].Attributes["SIGNATURE"].InnerText;
              headerSignature = headerSignature.Replace(DBClassCodeMethodList[i].Attributes["CLASS"].InnerText + "::", "");

              // frag only for doOnConstruct and doOnDestruct  .. better parse header (not yet implemented
              if (DBClassCodeMethodList[i].Attributes["NAME"].InnerText.Equals("doOnConstruct")
                || DBClassCodeMethodList[i].Attributes["NAME"].InnerText.Equals("doOnDestruct"))
              {
                headerSignature = "  virtual " + headerSignature;         
              }
  
              headerSignature += ";";
            }

            if (DBClassCodeMethodList[i].Attributes["LINESAVE"].InnerText.Equals("YES"))
            {
              sw.Write("  " + headerSignature);
              sw.Write("\r\n\r\n");
            }
          }
          else
          {
            sw.Write("  " + DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText);

            if (DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText != "")
            {
              sw.Write(" ");
            }

            if (DBClassCodeMethodList[i].Attributes["CLASS"].InnerText == "")
            {
              sw.Write(DBClassCodeMethodList[i].Attributes["NAME"].InnerText + ";\r\n\r\n");
            }
            else
            {
              sw.Write((DBClassCodeMethodList[i].Attributes["NAME"].InnerText + "("));
              for (int arg = 0; arg < DBClassCodeMethodList[i].ChildNodes.Count; arg++)//if more as on argument
              {
                sw.Write(DBClassCodeMethodList[i].ChildNodes[arg].Attributes["ARG_TYPE"].InnerText + " ");
                sw.Write(DBClassCodeMethodList[i].ChildNodes[arg].Attributes["NAME"].InnerText);
                if (arg < DBClassCodeMethodList[i].ChildNodes.Count - 1)
                  sw.Write(", ");
              }// for(int i = 0 ; i < DBClassCodeMethodList.Count ; i++)
              sw.Write(");\r\n\r\n");
            }
          }

          if ( DBGeneratedMethodCount.Equals(i + 1) )
          {
            //              sw.Write("  //## ----------------END-GENERATED CODE-(DO NOT EDIT )---------------------------- \r\n\r\n");

            //              // initialize your members
            //              sw.Write("  //##" + DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText + " \r\n");
            //              sw.Write("   virtual void doOnConstruct(); \r\n");
            //              sw.Write("   \r\n");
            //
            //              // destruct your members
            //              sw.Write("  //##" + DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText + " \r\n");     
            //              sw.Write("   virtual void doOnDestruct(); \r\n");

            //              sw.Write("  //## ----------------YOUR-CODE---------------------------------------------------- \r\n");
            //              sw.Write("   \r\n");

            sw.WriteLine("  //## ----------------------------------END-GENERATED-CODE--------------------- \r\n");
            sw.WriteLine("  //## ----------------------------------YOUR-CODE------------------------------ \r\n");
          }
        }// for(int i = 0 ; i < DBClassCodeMethodList.Count ; i++)// loop for each method

        if (root.Attributes["HEADER_MEMBER"].InnerText != "")
        {
          sw.Write(root.Attributes["HEADER_MEMBER"].InnerText);
          sw.Write("\r\n");
        }

        sw.Write(root.Attributes["ENDBODY"].InnerText);
        // Normalize line ending
        sw.Write(Environment.NewLine);
        sw.Close();
      }
      catch( System.UnauthorizedAccessException e )
      {
        RetValue = false;

        string fullName = CData.Instance.getWorkingDirectory() + "\\C" + fileName + ".h";

        System.Diagnostics.Process process;

        int ExitCode = 0;

        if (IsAutomatic)
        {
          string Version = "File generated by " + CData.Instance.getVersionOfDBClassCodeUtility();
          process = System.Diagnostics.Process.Start("cleartool.exe", "checkout -c \"" + Version + "\" \"" + fullName);
        }
        else
        {
          process = System.Diagnostics.Process.Start("cleardlg.exe", "/checkout \"" + fullName);
          ExitCode = process.ExitCode;
        }

        process.WaitForExit();

        if (ExitCode != 1)
        {
          DialogResult dr   = DialogResult.OK;
          FileInfo filePath = new FileInfo(fullName);
          FileAttributes attribute;

          if ((File.GetAttributes(fullName) & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
          {
            dr = MessageBox.Show("UnauthorizedAccess" + " : \r\n\r\n"
                   + e.Message + " \r\n"
                   + "Press OK to modify file, CANCEL to skip generating",
                   "UnauthorizedAccess", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);

            if (dr == DialogResult.OK)
            {
              //set to read
              attribute = (FileAttributes)(filePath.Attributes - FileAttributes.ReadOnly);
              File.SetAttributes(filePath.FullName, attribute);
            }
          }

          if (dr == DialogResult.OK)
          {
            writeCode(fileName, doc);
          }
        }// if (ExitCode != 1)
      }
      catch(Exception ex)
      {
        RetValue = false;
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  
          + ex.Message,
          "Error: " + fileName, MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
      return RetValue;
    }

    // generate cpp-file
    bool writeCPP(string fileName,  XmlDocument doc)
    {
      bool RetValue = true;
      try
      {
        XmlNode root;
        root = doc.FirstChild;
        
        XmlNodeList DBMemberCodeMethodList = root.SelectNodes("/class/MEMBER");
        XmlNodeList DBClassCodeMethodList = root.SelectNodes("/class/METHOD[@GENERATE='YES']");
        int DBGeneratedMethodCount        = root.SelectNodes("/class/METHOD[@GENERATE='YES' and @GENERATEDBY='DBClassCodeUtility']").Count;
   
        //        if(File.Exists("C" + fileName + ".cpp"))
        //          File.Copy("C" + fileName + ".cpp","C" + fileName + ".cpp.bak",true);

        StreamWriter sw = File.CreateText(("C" + fileName + ".cpp"));

        // header comment
        sw.Write(root.Attributes["SMS_COPYRIGHT"].InnerText);
        sw.WriteLine(root.Attributes["CPP_COMMENT"].InnerText);
        sw.WriteLine(root.Attributes["CPP_INCLUDE_MANUAL"].InnerText);
        sw.WriteLine(root.Attributes["CPP_INCLUDE"].InnerText);

        for (int i = 0; i < DBMemberCodeMethodList.Count; i++)// loop for each static member
        {
          if (DBMemberCodeMethodList[i].Attributes["CPP_STATIC_MEMBER"] != null)
          {
            // mark as generated
            if (root.Attributes["GENERATED_COMMENT"] != null)
            {
              // generated comment         
              sw.Write(root.Attributes["GENERATED_COMMENT"].InnerText + "\r\n");
            }

            string staticMember = DBMemberCodeMethodList[i].Attributes["CPP_STATIC_MEMBER"].InnerText;
            sw.WriteLine(staticMember);

            if (i == DBMemberCodeMethodList.Count - 1)
            {
              sw.Write("\r\n");
            }
          }
        }
   
        for(int i = 0 ; i < DBClassCodeMethodList.Count ; i++)// loop for each method
        {
          if (DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText.Equals("DBClassCodeUtility"))
          {
            // mark as generated
            if (root.Attributes["GENERATED_COMMENT"] != null)
            {
              // generated comment         
              sw.Write(root.Attributes["GENERATED_COMMENT"].InnerText + "\r\n");

              if (DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"] != null )
              {
                if (DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"].InnerText != "")
                {
                  sw.Write("//##" + DBClassCodeMethodList[i].Attributes["COLUMN_COMMENT"].InnerText + "\r\n");
                }
              }
            }
          }
          else if (DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText.Equals("MANUAL"))
          {
            if (DBClassCodeMethodList[i].Attributes["CPP_COMMENT"] != null)
            {
              // personal comment
              if (!DBClassCodeMethodList[i].Attributes["CPP_COMMENT"].InnerText.Equals(""))
                sw.Write(DBClassCodeMethodList[i].Attributes["CPP_COMMENT"].InnerText);
            }
          }

          if (DBClassCodeMethodList[i].Attributes["LINESAVE"] != null)
          {
            if (DBClassCodeMethodList[i].Attributes["LINESAVE"].InnerText.Equals("YES"))
            {          
              sw.Write(DBClassCodeMethodList[i].Attributes["SIGNATURE"].InnerText);
              sw.Write("\r\n");
            }
          }
          else
          {
            sw.Write(DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText);
            if (DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText != "")
              sw.Write(" ");

            Debug.WriteLine(DBClassCodeMethodList[i].Attributes["NAME"].InnerText);
            Debug.WriteLine(DBClassCodeMethodList[i].Attributes["RET_TYPE"].InnerText);

            if (DBClassCodeMethodList[i].Attributes["CLASS"].InnerText == "")
            {
              sw.Write((DBClassCodeMethodList[i].Attributes["NAME"].InnerText));
              sw.Write("\r\n");
            }
            else
            {
              sw.Write(DBClassCodeMethodList[i].Attributes["CLASS"].InnerText + "::");
              sw.Write((DBClassCodeMethodList[i].Attributes["NAME"].InnerText + "("));
              for (int arg = 0; arg < DBClassCodeMethodList[i].ChildNodes.Count; arg++)//if more as on argument
              {
                sw.Write(DBClassCodeMethodList[i].ChildNodes[arg].Attributes["ARG_TYPE"].InnerText + " ");
                sw.Write(DBClassCodeMethodList[i].ChildNodes[arg].Attributes["NAME"].InnerText);
                if (arg < DBClassCodeMethodList[i].ChildNodes.Count - 1)
                  sw.Write(", ");
              }
              sw.Write(")\r\n");
            }
          }

          sw.Write(DBClassCodeMethodList[i].Attributes["BODY"].InnerText);

          if ( DBGeneratedMethodCount.Equals(i + 1) )
          {
            //              sw.Write("//## ----------------END-GENERATED CODE-(DO NOT EDIT )---------------------------- \r\n\r\n");

            //              // initialize your members
            //              sw.Write("/##" + DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText + " \r\n");
            //              sw.Write("virtual void doOnConstruct(); \r\n");
            //              sw.Write("\r\n");
            //
            //              // destruct your members
            //              sw.Write("//##" + DBClassCodeMethodList[i].Attributes["GENERATEDBY"].InnerText + " \r\n");     
            //              sw.Write("virtual void doOnDestruct(); \r\n");

            //              sw.Write("//## ----------------YOUR-CODE---------------------------------------------------- \r\n");
            //              sw.Write("\r\n");

            sw.WriteLine("//## ------------------------------------END-GENERATED-CODE---------------------- \r\n");
            sw.WriteLine("//## ------------------------------------YOUR-CODE------------------------------- \r\n");
          }
        }// for(int i = 0 ; i < DBClassCodeMethodList.Count ; i++)

        // Normalize line ending vs2005
        sw.Write(Environment.NewLine);
        sw.Close();
      }
      catch( System.UnauthorizedAccessException e )
      {
        RetValue = false;

        string fullName = CData.Instance.getWorkingDirectory() + "\\C" + fileName + ".cpp";

        System.Diagnostics.Process process;

        int ExitCode = 0;

        if (IsAutomatic)
        {
          //process = System.Diagnostics.Process.Start("cleartool.exe", "checkout -nc \"" + fullName);
          string Version = "File generated by " + CData.Instance.getVersionOfDBClassCodeUtility();
          process = System.Diagnostics.Process.Start("cleartool.exe", "checkout -c \"" + Version + "\" \"" + fullName);
        }
        else
        {
          process = System.Diagnostics.Process.Start("cleardlg.exe", "/checkout \"" + fullName);
          ExitCode = process.ExitCode;
        }

        process.WaitForExit();

        if (ExitCode != 1)
        {
          DialogResult dr = DialogResult.OK;
          FileInfo filePath = new FileInfo(fullName);
          FileAttributes attribute;

          if ((File.GetAttributes(fullName) & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
          {
            dr = MessageBox.Show("UnauthorizedAccess" + " : \r\n\r\n"
                   + e.Message + " \r\n"
                   + "Press OK to modify file, CANCEL to skip generating",
                   "UnauthorizedAccess", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);

            if (dr == DialogResult.OK)
            {
              //set to read
              attribute = (FileAttributes)(filePath.Attributes - FileAttributes.ReadOnly);
              File.SetAttributes(filePath.FullName, attribute);
            }
          }

          if (dr == DialogResult.OK)
          {
            writeCode(fileName, doc);
          }
        }// if (ExitCode != 1)
      }
      catch(Exception ex)
      {
        RetValue = false;
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  
          + ex.Message,
          "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);;
      }
      return RetValue;
    }
  }
}
