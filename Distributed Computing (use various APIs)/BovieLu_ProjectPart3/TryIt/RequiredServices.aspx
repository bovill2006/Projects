<%@ Page Language="C#" AutoEventWireup="true" CodeFile="RequiredServices.aspx.cs" Inherits="RequiredServices" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .auto-style1 {
            text-align: justify;
            line-height: 13.0pt;
            text-indent: -27.35pt;
            font-size: 12.0pt;
            font-family: "Times New Roman", serif;
            margin-left: 27.35pt;
            margin-right: 0in;
            margin-top: 12.0pt;
            margin-bottom: .0001pt;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
<H1> TryIt (Required Services)</H1>
        <asp:HyperLink ID="HyperLink2" NavigateUrl="http://10.1.11.159:81/TryIt.aspx" runat="server"><h3>HOME PAGE</h3></asp:HyperLink>
        <b><H3>Method : public string Stemming(string str):</H3>
        </b>
        </span>

        <p> 
            <asp:Button ID="StemButton" runat="server" Text="Stem Words" OnClick="StemButton_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="StemText" runat="server" Width="342px"></asp:TextBox>
        </p>
        <p>
            <asp:Label ID="StemLabel" runat="server" Text="Stem Output"></asp:Label>
        </p>
        <p>
            &nbsp;</p>
        <b><H3>Method : public string[] NewsFocus(string[] str):</H3></b>
        <p>
            <asp:Button ID="NewsButton" runat="server" Text="Retrieve URLs" OnClick="NewsButton_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="NewsText" runat="server" Width="340px"></asp:TextBox>
        </p>
        <p>
            <asp:Label ID="NewsLabel" runat="server" Text="URLs related to the topic"></asp:Label>
        </p>
    </form>
    </body>
</html>

