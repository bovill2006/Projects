<%@ Page Language="C#" AutoEventWireup="true" CodeFile="TryIt.aspx.cs" Inherits="TryIt" %>

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
        <p style="height: 16px"> 
            <b><H3>Method : public string Stemming(string str):</H3></b>
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:
normal"><span style="color:red">Description</span></b><span style="color:red">: Analyze a string containing a word or multiple words and replace each of the inflected or derived words to their stem or root word. For example, “information”, “informed”, “informs”, “informative” will be replaced by the tem word “inform”. This service can help find useful keywords or index words in information processing and retrieval.<o:p></o:p></span></p>
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:
normal"><span style="color:red">Input</span></b><span style="color:red">: A string type of a word or words.<o:p></o:p></span></p>
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:
normal"><span style="color:red">Output</span></b><span style="color:red">: The string of the inflected or derived words replaced by their stem words.<o:p></o:p></span></p>
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
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:
normal"><span style="color:red">Description: </span></b><span style="color:
red">Find news about specific topics, for example, find all (as many as possible) news articles about ASU (Arizona State University). <o:p></o:p></span>
        </p>
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:
normal"><span style="color:red">Input</span></b><span style="color:red">: a list of topics or key words<o:p></o:p></span></p>
        <p align="left" class="auto-style1" style="tab-stops: right 513.0pt; text-justify: inter-ideograph;">
            <b style="mso-bidi-font-weight:normal"><span style="color:red">Output</span></b>
            <span style="color:red">: A list of URLs in which the given topics are reported.<o:p></o:p></span></p>
        <p>
            <asp:Button ID="NewsButton" runat="server" Text="Retrieve URLs" OnClick="NewsButton_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="NewsText" runat="server" Width="340px"></asp:TextBox>
        </p>
        <p>
            <asp:Label ID="NewsLabel" runat="server" Text="URLs related to the topic"></asp:Label>
        </p>
        <p>
            &nbsp;</p>
    </form>
    </body>
</html>

