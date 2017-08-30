<%@ Page Language="C#" AutoEventWireup="true" CodeFile="BankService.aspx.cs" Inherits="BankService" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <h1>TryIt BankService</h1>
        <asp:HyperLink ID="HyperLink3" NavigateUrl="http://10.1.11.159:81/TryIt.aspx" runat="server"><h3>HOME PAGE</h3></asp:HyperLink>
        <br />
        <asp:Button ID="createBut" runat="server" Text="Generate Card" OnClick="createBut_Click" />
        <asp:TextBox ID="nameText" runat="server" Width="284px"></asp:TextBox>
&nbsp;(Input the Owner Name: String )<br />
        <br />
        <asp:Label ID="cardLabel" runat="server" Text="Newly Crated Card"></asp:Label>
    </form>
</body>
</html>
