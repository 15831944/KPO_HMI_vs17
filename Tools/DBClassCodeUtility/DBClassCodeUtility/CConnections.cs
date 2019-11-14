using System;
using System.Windows.Forms;
using System.Data.Odbc;
using System.Collections;

namespace DBClassCodeUtility
{
	/// <summary>
	/// Summary description for CConnections.
	/// </summary>
	public class CConnections
	{
    private string m_UID;
    private string m_Password;
    private string m_Service;
    
    private Hashtable AllConnections;

		public CConnections()
		{
      AllConnections = new Hashtable();
		}

    public string getUserAuthentication(string service)
    {
      this.m_UID = CData.Instance.ReadSetting(service, "User");
      return this.m_UID;
    }

    public void setUserAuthentication(string User, string service)
    {
      CData.Instance.WriteSetting(service,"User",User);
      this.m_UID = User;
    }

    public string getPasswordAuthentication(string service)
    {
      this.m_Password = CData.Instance.ReadSetting(service, "Password");
      return this.m_Password;
    }

    public void setPasswordAuthentication(string Password, string service)
    {
      CData.Instance.WriteSetting(service,"Password",Password);
      this.m_Password = Password;
    }

    public string getDataBaseAuthentication(string service)
    {
      this.m_Service = CData.Instance.ReadSetting(service, "DataBase");
      return this.m_Service;
    }

    public bool makeConnection(string user, string passwd, string service, string exten)
    {
      bool RetValue = false;

      try
      {
        System.Data.Odbc.OdbcConnection odbcConnection;
        odbcConnection = new System.Data.Odbc.OdbcConnection();
        odbcConnection.ConnectionTimeout = 60;
        odbcConnection.ConnectionString = "DSN=" + service + ";UID=" + user + ";PWD=" +passwd;
        odbcConnection.Open();
        if (odbcConnection.State.Equals(System.Data.ConnectionState.Open))
        {
          //map for connection with identification "service + extention"
          AllConnections.Add(service+exten, odbcConnection);
         
          setUserAuthentication(user,service);
          setPasswordAuthentication(passwd,service);
          
          RetValue = true;
        }
      }
      catch(OdbcException ex)
      {
        MessageBox.Show("CConnections::makeConnection: "+ ex.Message,
          "OdbcException", MessageBoxButtons.OK, MessageBoxIcon.Error);
        RetValue = false;
      }
      return RetValue;
    }


    public bool getConnection(string service, ref OdbcConnection con_, string exten)
    {
      bool RetValue = false;

      IDictionaryEnumerator Enumerator = AllConnections.GetEnumerator();
      // search for connection with identification "service + extention"
      while ( Enumerator.MoveNext() )
      {
        if (Enumerator.Key.Equals(service+exten))
        {
          con_ = (OdbcConnection)Enumerator.Value;
          int index =0;
            
          if ( (index=con_.ConnectionString.IndexOf("UID=")) != -1)
          {
            // + 4 letters
            index += 4; 

            m_UID = con_.ConnectionString.Substring(index, con_.ConnectionString.Length-index-1);
            
            m_Service = service;
          }

          if (System.Data.ConnectionState.Closed == con_.State)
          {
            con_.Open();
          }

          if (System.Data.ConnectionState.Open != con_.State)
          {
            RetValue = false;
          }
          else
          {
            RetValue = true;
          }
        }
      }
      return RetValue;
    }

    public string getDBName()
    {
      return m_UID;  
    }

    public string getDBService()
    {
      return m_Service;  
    }

    public bool closeConnection(string service, string exten)
    {
      bool RetValue = false;

      IDictionaryEnumerator Enumerator = AllConnections.GetEnumerator();
      // search for connection with identification "service + extention" and close that
      while ( Enumerator.MoveNext() )
      {
        if (Enumerator.Key.Equals(service+exten))
        {
          ((OdbcConnection)Enumerator.Value).Close();
          AllConnections.Remove(service+exten);
          RetValue = true;
          break;
        }
      }
      return RetValue;
    }
  }
}
