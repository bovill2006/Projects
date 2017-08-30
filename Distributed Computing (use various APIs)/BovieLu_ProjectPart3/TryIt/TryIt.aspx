<%@ Page Language="C#" AutoEventWireup="true" CodeFile="TryIt.aspx.cs" Inherits="TryIt" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">

table.MsoTableGrid
	{border:solid windowtext 1.0pt;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;
	}
 p.MsoNormal
	{margin-top:0in;
	margin-right:0in;
	margin-bottom:10.0pt;
	margin-left:0in;
	line-height:115%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;
	}
        .auto-style1 {
            width: 203pt;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
       <h1> TryIt Home Page</h1>
        <p> Name: Bovie Lu</p>
        <p> ASUID:&nbsp; 1203898184</p>
        </div>
        <table border="1" cellpadding="0" cellspacing="0" class="MsoTableGrid">
            <tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes">
                <td style="width:53.75pt;border:solid windowtext 1.0pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="72">
                    <p class="MsoNormal">
                        Bovie</p>
                </td>
                <td class="auto-style1" style="border-right: 1.0pt solid windowtext; border-top: 1.0pt solid windowtext; border-bottom: 1.0pt solid windowtext; mso-border-left-alt: solid windowtext .5pt; mso-border-alt: solid windowtext .5pt; padding: 0in 5.4pt 0in 5.4pt; border-left-style: none; border-left-color: inherit; border-left-width: medium;" valign="top">
                    <p class="MsoNormal">
                        Stemming (Required Service)</p>
                    <p class="MsoNormal">
                        Input: String</p>
                    <p class="MsoNormal">
                        Output: String</p>
                </td>
                <td style="width:35.95pt;border:solid windowtext 1.0pt;
  border-left:none;mso-border-left-alt:solid windowtext .5pt;mso-border-alt:
  solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="48">
                    <p class="MsoNormal">
                        <asp:HyperLink ID="stemLink" NavigateUrl="http://10.1.11.159:81/RequiredServices.aspx"  runat="server" >TryIt</asp:HyperLink>
                    </p>
                </td>
                <td style="width:2.25in;border:solid windowtext 1.0pt;
  border-left:none;mso-border-left-alt:solid windowtext .5pt;mso-border-alt:
  solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="216">
                    <p class="MsoNormal">
                        Stems words</p>
                </td>
            </tr>
            <tr style="mso-yfti-irow:1">
                <td style="width:53.75pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="72">
                    <p class="MsoNormal">
                        Bovie</p>
                </td>
                <td class="auto-style1" style="border-bottom: solid windowtext 1.0pt; border-right: solid windowtext 1.0pt; mso-border-top-alt: solid windowtext .5pt; mso-border-left-alt: solid windowtext .5pt; mso-border-alt: solid windowtext .5pt; padding: 0in 5.4pt 0in 5.4pt; border-left-style: none; border-left-color: inherit; border-left-width: medium; border-top-style: none; border-top-color: inherit; border-top-width: medium;" valign="top">
                    <p class="MsoNormal">
                        NewsFocus(Required Service)</p>
                    <p class="MsoNormal">
                        Input: String Array</p>
                    <p class="MsoNormal">
                        Output: String Array</p>
                </td>
                <td style="width:35.95pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="48">
                    <p class="MsoNormal">
                        <asp:HyperLink ID="NewsFocusLink" NavigateUrl="http://10.1.11.159:81/RequiredServices.aspx" runat="server" >TryIt</asp:HyperLink>
                    </p>
                </td>
                <td style="width:2.25in;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="216">
                    <p class="MsoNormal">
                        Finds News articles on google news&nbsp; using google api and a custom search engine . then returns ten URLS</p>
                </td>
            </tr>
            <tr style="mso-yfti-irow:2">
                <td style="width:53.75pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="72">
                    <p class="MsoNormal">
                        Bovie</p>
                </td>
                <td class="auto-style1" style="border-bottom: solid windowtext 1.0pt; border-right: solid windowtext 1.0pt; mso-border-top-alt: solid windowtext .5pt; mso-border-left-alt: solid windowtext .5pt; mso-border-alt: solid windowtext .5pt; padding: 0in 5.4pt 0in 5.4pt; border-left-style: none; border-left-color: inherit; border-left-width: medium; border-top-style: none; border-top-color: inherit; border-top-width: medium;" valign="top">
                    <p class="MsoNormal">
                        BankService(Elective Service ; RESTful)</p>
                    <p class="MsoNormal">
                        Input: String</p>
                    <p class="MsoNormal">
                        Output: Json File</p>
                </td>
                <td style="width:35.95pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="48">
                    <p class="MsoNormal">
                        <asp:HyperLink ID="BankLink" runat="server" NavigateUrl="http://10.1.11.159:81/BankService.aspx" >TryIt</asp:HyperLink>
                    </p>
                </td>
                <td style="width:2.25in;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="216">
                    <p class="MsoNormal">
                        The Bank service creates a credit card for user linked to their name</p>
                </td>
            </tr>
            <tr style="mso-yfti-irow:3;mso-yfti-lastrow:yes">
                <td style="width:53.75pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="72">
                    <p class="MsoNormal">
                        Bovie</p>
                </td>
                <td class="auto-style1" style="border-bottom: solid windowtext 1.0pt; border-right: solid windowtext 1.0pt; mso-border-top-alt: solid windowtext .5pt; mso-border-left-alt: solid windowtext .5pt; mso-border-alt: solid windowtext .5pt; padding: 0in 5.4pt 0in 5.4pt; border-left-style: none; border-left-color: inherit; border-left-width: medium; border-top-style: none; border-top-color: inherit; border-top-width: medium;" valign="top">
                    <p class="MsoNormal">
                        Encryption/Decryption (Elective Service)</p>
                    <p class="MsoNormal">
                        Input: String,int ,int
                    </p>
                    <p class="MsoNormal">
                        Output: EncryptedObject
                    </p>
                </td>
                <td style="width:35.95pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="48">
                    <p class="MsoNormal">
                        <asp:HyperLink ID="EncryptLink" runat="server" NavigateUrl="http://10.1.11.159:81/EncodeDecode.aspx">TryIt</asp:HyperLink>
                    </p>
                </td>
                <td style="width:2.25in;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="216">
                    <p class="MsoNormal">
                        Cipher encryption/decryption</p>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
