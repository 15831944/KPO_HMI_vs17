using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Mail; 
using Outlook = Microsoft.Office.Interop.Outlook;
using Oracle.DataAccess.Client;
//using EASendMail; //SARS

namespace SendEmailOutlookSmtp
{
    public class SendEmail
    {
        public void SendemailOutLook(string mailreci, string subj, string Body)
        {
            //Outlook.Application oApp = new Outlook.Application();
            //Outlook.MailItem oMsg = (Outlook.MailItem)oApp.CreateItem(Outlook.OlItemType.olMailItem);
            //oMsg.Body = Body;
            //oMsg.Subject = subj;
            //oMsg.To = mailreci;

            //oMsg.Attachments.Add(@"D:\SMS_Siemag\X-Pact\SMC\Reports\HMD Daily Reports\Daily_Report__2014_06_06_12_20_00.pdf",Outlook.OlAttachmentType.olByValue,Type.Missing,Type.Missing);
            //oMsg.Send();
            

        }


        public void SendMail(string mailreci, string subj, string Body, string userid, string pwd,string filePath,string fileName,bool fileAttached)
        {
            //SmtpMail oMail = new SmtpMail("TryIt");
            //SmtpClient oSmtp = new SmtpClient();

            //Console.WriteLine("start to send email over SSL ..."); 
            //try
            //{
            //    SmtpServer oServer = new SmtpServer("smtp.gmail.com"); //smtp.live.com - for hotmail, smtp.gmail.com - for gmail
                
            //    //oServer.SocksProxyServer = "10.182.1.101";
            //    //oServer.SocksProxyPort = 8101;
            //    // if your proxy doesn't requires user authentication, please don't assign any value to 
            //    // SocksProxyUser and SocksProxyPassword properties 
            //    //oServer.SocksProxyUser = "sars";
            //    //oServer.SocksProxyPassword = "sana3456";
            //    //oServer.ProxyProtocol = SocksProxyProtocol.Socks5;
                 

            //    //set user authentication
            //    oServer.User = userid;
            //    oServer.Password = pwd;
            //    oServer.ConnectType = SmtpConnectType.ConnectSSLAuto; 

            //    //specifies the authentication mechanism.
            //    //oSmtp.AuthType = SmtpAuthType.AuthAuto;

            //    //set SSL connection
            //    //oServer.ConnectType = SmtpConnectType.ConnectSSLAuto;

            //    //set smtp server port
            //    //oServer.Port = 465;

            //    //set helo domain
            //    //oServer.HeloDomain = "mymachine.com";

            //    //set delivery-report address
            //    //oServer.MailFrom = "report@adminsystem.com";


            //    oMail.From = new MailAddress(userid);
            //    oMail.To.Add(new MailAddress(mailreci)); 
            //    oMail.Subject = subj;
            //    oMail.TextBody = Body;

            //    if (fileAttached)
            //    {
            //        Console.WriteLine(" filePath : " + filePath);
            //        Console.WriteLine(" fileName : " + fileName);
            //        filePath = filePath + fileName;
            //        Console.WriteLine(" Combined filePath : " + filePath);

            //        oMail.AddAttachment(filePath);
            //    }

            //    oSmtp.SendMail(oServer, oMail);
            //    Console.WriteLine("email was sent successfully!"); 
            //}
            //catch (SmtpTerminatedException exp)
            //{
            //    Console.WriteLine(exp.Message);
            //}
            //catch (SmtpServerException exp)
            //{
            //    Console.WriteLine("Exception: Server Respond: {0}", exp.ErrorMessage);
            //}
            //catch (System.Net.Sockets.SocketException exp)
            //{
            //    Console.WriteLine("Exception: Networking Error: {0} {1}", exp.ErrorCode, exp.Message);
            //}
            //catch (System.ComponentModel.Win32Exception exp)
            //{
            //    Console.WriteLine("Exception: System Error: {0} {1}", exp.ErrorCode, exp.Message);
            //}
            //catch (System.Exception exp)
            //{
            //    Console.WriteLine("Exception: Common: {0}", exp.Message);
            //}
        }

        public void SendemailSmtp(string mailreci, string subj, string Body, string userid, string pwd, string filePath, string fileName, bool fileAttached)
        {
            MailMessage mail = new MailMessage();
            SmtpClient SmtpServer = new SmtpClient("smtp.gmail.com");

            mail.From = new MailAddress(userid);
            mail.To.Add(mailreci);
            mail.Subject = subj;
            mail.Body = Body;
            mail.IsBodyHtml = false;

            if (fileAttached)
            {
                Console.WriteLine(" filePath : " + filePath);
                Console.WriteLine(" fileName : " + fileName);
                filePath = filePath + fileName;
                Console.WriteLine(" Combined filePath : " + filePath);

                mail.Attachments.Add(new Attachment(filePath));
            }

            SmtpServer.Port = 587;
            SmtpServer.Credentials = new System.Net.NetworkCredential(userid, pwd);
            SmtpServer.EnableSsl = true;
            SmtpServer.Send(mail);
            
        }
    }
}
