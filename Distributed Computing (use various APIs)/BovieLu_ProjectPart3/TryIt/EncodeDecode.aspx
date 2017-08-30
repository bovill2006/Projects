<%@ Page Language="C#" AutoEventWireup="true" CodeFile="EncodeDecode.aspx.cs" Inherits="TryIt" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <h1>TryIt (Encoding/Decoding)</h1>
        <asp:HyperLink ID="HyperLink1" NavigateUrl="http://10.1.11.159:81/TryIt.aspx" runat="server"><h3>HOME PAGE</h3></asp:HyperLink>
        <br />
        Amount :
        <asp:TextBox ID="AmountText" runat="server"></asp:TextBox>
        (Only can enter int)<br />
        <br />
        ID:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <asp:TextBox ID="IdText" runat="server"></asp:TextBox>
        (Only can enter string)<br />
        <br />
        CardNo:
        <asp:TextBox ID="CardText" runat="server"></asp:TextBox>
        (Only can enter int)<br />
        <br />
        <asp:Button ID="EncodeBut" runat="server" Text="Encrypt" OnClick="EncodeBut_Click" />
        <br />
        <br />
        <asp:Label ID="EncryptedLabel" runat="server" Text="Output of the Encrypted"></asp:Label>
        <br />
        <br />
        <br />
        <br />
        <br />
        <asp:Button ID="DecodeBut" runat="server" Text="Decrypt" OnClick="DecodeBut_Click" />
        <br />
        <br />
        <asp:Label ID="DecodeLabel" runat="server" Text="Output of the Decrypted"></asp:Label>
        <br />
        <br />
    
    </div>
    </form>
</body>
</html>
