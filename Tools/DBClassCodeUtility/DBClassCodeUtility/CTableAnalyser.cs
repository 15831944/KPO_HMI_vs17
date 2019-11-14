using System;
using System.Windows.Forms;
using System.Data;
using System.Data.Odbc;
using System.Collections;

namespace DBClassCodeUtility
{
	/// <summary>
	/// Summary description for CTableAnalyser.
	/// </summary>
	public class CTableAnalyser
	{
		public CTableAnalyser()
		{
			//
			// TODO: Add constructor logic here
			//
		}

    // read tablenames from DB
    public bool readTables(ArrayList _tables, ref OdbcConnection conn, bool IsWildCardFilterOn)
    {
      bool RetValue = true;
      try 
      {
        #region get User Id from connection string
        int start = conn.ConnectionString.IndexOf("UID=") + 4;
        int end  =  conn.ConnectionString.IndexOf(";",start);
        string uID = conn.ConnectionString.Substring((start),(end - start));// User ID
        #endregion

        OdbcCommand selectCommand = new OdbcCommand();
        if (IsWildCardFilterOn)
        {
          //string selectQuery = "select object_name from user_objects where object_type = 'TABLE' or object_type = 'SYNONYM'  or object_type = 'VIEW' order by object_name";
          string selectQuery = "SELECT DISTINCT TABLE_NAME FROM ALL_TAB_COLUMNS WHERE OWNER like '" + uID.ToUpper() + "%' AND TABLE_NAME IN (SELECT object_name FROM user_objects WHERE object_type = 'TABLE' OR object_type = 'SYNONYM' OR object_type = 'VIEW') ORDER BY TABLE_NAME";
          selectCommand.CommandText = selectQuery;
        }
        else 
        {
          //string selectQuery = "select object_name from user_objects where object_type = 'TABLE' or object_type = 'SYNONYM'  or object_type = 'VIEW' order by object_name";
          string selectQuery = "SELECT DISTINCT TABLE_NAME FROM ALL_TAB_COLUMNS WHERE OWNER like '" + uID.ToUpper() + "' AND TABLE_NAME IN (SELECT object_name FROM user_objects WHERE object_type = 'TABLE' OR object_type = 'SYNONYM' OR object_type = 'VIEW') ORDER BY TABLE_NAME";
          selectCommand.CommandText = selectQuery;
        }

        selectCommand.Connection = conn;
        //int rows = selectCommand.ExecuteNonQuery();
        OdbcDataReader myReader = selectCommand.ExecuteReader();

        while (myReader.Read())
        {
          string tn = myReader.GetString(myReader.GetOrdinal("TABLE_NAME"));
          _tables.Add(tn);
        }
        _tables.Sort();
        myReader.Close(); // close to be able to read again
      }
      catch(OdbcException ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message,
          "OdbcException", MessageBoxButtons.OK, MessageBoxIcon.Error);
        RetValue = false;
      }
      return RetValue;
    }// read tablenames from DB

    public bool readTableDetails(string TableName, ref DataTable TableDesc, OdbcConnection conn, bool IsWildCardFilterOn)
    {
      bool RetValue = true;
      try
      {
        #region get User Id from connection string
        int start = conn.ConnectionString.IndexOf("UID=") + 4;
        int end  =  conn.ConnectionString.IndexOf(";",start);
        string uID = conn.ConnectionString.Substring((start),(end - start));// User ID
        #endregion

        string SemanticLenght = "BYTE";
        try
        {
          // dependent on V_$NLS_PARAMETERS.NLS_LENGTH_SEMANTICS (CHAR or BYTE)
          // the select statement is different

          OdbcCommand odbcCommandSemantic = new OdbcCommand();
          odbcCommandSemantic.CommandText = "SELECT VALUE FROM SYS.V_$NLS_PARAMETERS WHERE PARAMETER = 'NLS_LENGTH_SEMANTICS';";
          odbcCommandSemantic.Connection = conn;
          DataTable SemanticTable = new DataTable();
          System.Data.Odbc.OdbcDataAdapter ODBC_ADAPT_SEMANTIC = new System.Data.Odbc.OdbcDataAdapter(odbcCommandSemantic);
          ODBC_ADAPT_SEMANTIC.Fill(SemanticTable);
          SemanticLenght = SemanticTable.Rows[0]["VALUE"].ToString();
        }
        catch(OdbcException ex)
        {
          MessageBox.Show(ex.Message,
            "*** ERROR GETTING PARAMETER 'NLS_LENGTH_SEMANTICS'. DEFAULT WILL BE 'BYTE' ***", MessageBoxButtons.OK, MessageBoxIcon.Error);

          SemanticLenght = "BYTE";
        }

        OdbcCommand odbcCommand1 = new OdbcCommand();

        if (IsWildCardFilterOn)
        {
          if (SemanticLenght.Equals("BYTE") || SemanticLenght.Equals("CHAR"))
            odbcCommand1.CommandText = "SELECT COLUMN_NAME, COLUMN_ID, DATA_TYPE, decode(CHAR_LENGTH, 0, DATA_PRECISION, CHAR_LENGTH) as DATA_LENGTH, NULLABLE, DATA_SCALE, OWNER FROM ALL_TAB_COLUMNS WHERE owner like '" + uID.ToUpper() + "%' and TABLE_NAME = '" + TableName + "' ORDER BY COLUMN_ID;";
          else// BYTE
            odbcCommand1.CommandText = "SELECT COLUMN_NAME, COLUMN_ID, DATA_TYPE, DATA_LENGTH, NULLABLE, DATA_SCALE FROM ALL_TAB_COLUMNS WHERE owner like '" + uID.ToUpper() + "%' and TABLE_NAME = '" + TableName + "' ORDER BY COLUMN_ID;"; 
        }
        else
        {
          if (SemanticLenght.Equals("BYTE") || SemanticLenght.Equals("CHAR"))
            odbcCommand1.CommandText = "SELECT COLUMN_NAME, COLUMN_ID, DATA_TYPE, decode(CHAR_LENGTH, 0, DATA_PRECISION, CHAR_LENGTH) as DATA_LENGTH, NULLABLE, DATA_SCALE, OWNER FROM ALL_TAB_COLUMNS WHERE owner like '" + uID.ToUpper() + "' and TABLE_NAME = '" + TableName + "' ORDER BY COLUMN_ID;";
          else// BYTE
            odbcCommand1.CommandText = "SELECT COLUMN_NAME, COLUMN_ID, DATA_TYPE, DATA_LENGTH, NULLABLE, DATA_SCALE FROM ALL_TAB_COLUMNS WHERE owner like '" + uID.ToUpper() + "' and TABLE_NAME = '" + TableName + "' ORDER BY COLUMN_ID;";
        }

        odbcCommand1.Connection = conn;
        System.Data.Odbc.OdbcDataAdapter adapt = new System.Data.Odbc.OdbcDataAdapter(odbcCommand1);
        adapt.Fill(TableDesc);
      
        DataTable all_constraints_tab = new DataTable(); // table for PK select
        odbcCommand1.CommandText = "SELECT cols.column_name FROM all_constraints cons, all_cons_columns cols WHERE cols.table_name = '"
          + TableName.ToUpper() + "' AND cons.constraint_type = 'P' AND cons.constraint_name = cols.constraint_name AND cons.owner = cols.owner AND cons.owner like '" + uID.ToUpper() + "%' ORDER BY cols.POSITION;";
        
        //odbcCommand1.CommandText = "SELECT cols.column_name FROM all_constraints cons, all_cons_columns cols WHERE cols.table_name = '"
        //  + TableName.ToUpper() + "' AND cons.constraint_type = 'P' AND cons.constraint_name = cols.constraint_name AND cons.owner = cols.owner ORDER BY cols.POSITION;";

        adapt.SelectCommand = odbcCommand1;
        adapt.Fill(all_constraints_tab);

        // comments
        DataTable user_comment_tab = new DataTable(); // table for comments select
        odbcCommand1.CommandText = "select column_name, comments from user_col_comments where table_name like '" + TableName.ToUpper() + "%';";
        adapt.SelectCommand = odbcCommand1;
        adapt.Fill(user_comment_tab);

        // NEW Columns for DataTable
        DataColumn PK = new DataColumn("PK");// column for PK identification
        TableDesc.Columns.Add(PK);
        DataColumn COLUMN_COMMENT = new DataColumn("COLUMN_COMMENT");// column for comment
        TableDesc.Columns.Add(COLUMN_COMMENT);

        int PKNO = 1;
       
        for(int j = 0; j < TableDesc.Rows.Count; j++)
        {
          TableDesc.Rows[j]["PK"] = "";
          TableDesc.Rows[j]["COLUMN_COMMENT"] = "";

          for (int i = 0; i < all_constraints_tab.Rows.Count; i++)
          {
            if (TableDesc.Rows[j]["COLUMN_NAME"].ToString() == all_constraints_tab.Rows[i][0].ToString())
            {
              TableDesc.Rows[j]["PK"] = "PK " + (PKNO++);
              break;
            }
          }

          // comments          
          for (int i = 0; i < user_comment_tab.Rows.Count; i++)
          {
            if (TableDesc.Rows[j]["COLUMN_NAME"].ToString() == user_comment_tab.Rows[i][0].ToString())
            {
              TableDesc.Rows[j]["COLUMN_COMMENT"] = user_comment_tab.Rows[i][1].ToString();
              break;
            }
          }// for (int i = 0; i < user_comment_tab.Rows.Count; i++)
        }
      }
      catch(OdbcException ex)
      {
        MessageBox.Show(ex.StackTrace + " : \r\n\r\n"  + ex.Message,
          "OdbcException", MessageBoxButtons.OK, MessageBoxIcon.Error);
        RetValue = false;
      }
      return RetValue;
    }// readTableDetails

    public bool readTableContent(string TableName,ref DataTable TableData, OdbcConnection conn)
    {
      bool RetValue = true;
      try
      {
        OdbcCommand odbcCommand1 = new OdbcCommand();
        odbcCommand1.CommandText = "SELECT * FROM " + TableName + ";";
        odbcCommand1.Connection = conn;
        //odbcCommand1.
        System.Data.Odbc.OdbcDataAdapter adapt = new System.Data.Odbc.OdbcDataAdapter(odbcCommand1);
        adapt.SelectCommand = odbcCommand1;
        adapt.Fill(TableData);

        // to verify its existence 
        // odbcCommand1.CommandText = "SELECT * FROM all_objects WHERE object_type in ('TABLE', 'VIEW') and object_name = '"+ TableName +"';";

        //System.Data.Odbc.OdbcDataAdapter adapt = new System.Data.Odbc.OdbcDataAdapter("SELECT * FROM " + TableName, conn);
        //adapt.ContinueUpdateOnError = true;
        //adapt.Fill(TableData);
      }
      catch(OdbcException odbcEx)
      {
        MessageBox.Show(
          "Message:          " + odbcEx.Message + ""
          + "Source:         " + odbcEx.Source + "\r\n"
          + "InnerException: " + odbcEx.InnerException + "\r\n"
          + "TargetSite:     " + odbcEx.TargetSite + "\r\n"
          + "StackTrace:     " + odbcEx.StackTrace,
          "OdbcException", MessageBoxButtons.OK, MessageBoxIcon.Error);
        RetValue = false;
      }
      catch(System.FormatException formatEx)
      {
        MessageBox.Show(
          "Message:          " + formatEx.Message + ""
          + "Source:         " + formatEx.Source + "\r\n"
          + "InnerException: " + formatEx.InnerException + "\r\n"
          + "TargetSite:     " + formatEx.TargetSite + "\r\n"
          + "StackTrace:     " + formatEx.StackTrace,
          "FormatException", MessageBoxButtons.OK, MessageBoxIcon.Error);
        RetValue = false;
      }
      catch(Exception ex)
      {
        MessageBox.Show(
            "Message:        " + ex.Message + ""
          + "Source:         " + ex.Source + "\r\n"
          + "InnerException: " + ex.InnerException + "\r\n"
          + "TargetSite:     " + ex.TargetSite + "\r\n"
          + "StackTrace:     " + ex.StackTrace,
          "Exception", MessageBoxButtons.OK, MessageBoxIcon.Error);        
        RetValue = false;
      }
      return RetValue;
    }// readTableDetails

//    public bool readColumn(string TableName, string column ,string where_str ,ref DataTable TableData, OdbcConnection conn)
//    {
//      bool RetValue = true;
//      try
//      {
//        OdbcCommand odbcCommand1 = new OdbcCommand();
//        odbcCommand1.CommandText = "SELECT " + column + " FROM " + TableName + " WHERE " + where_str + ";";
//        odbcCommand1.CommandText = "SELECT comments FROM user_col_comments WHERE table_name='" + TableName + "' and and column_name ='" + ColumnName+ "';";
        
	}
}
