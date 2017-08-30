<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<asp:Content runat="server" ID="FeaturedContent" ContentPlaceHolderID="FeaturedContent">
    <section class="featured">
        <div class="content-wrapper">
            <hgroup class="title">
                <h1><%: Title %>.</h1>
                <h2>Temperature Convert.</h2>
            </hgroup>
            <p>
                <asp:Button ID="Button1" runat="server" Text="C to F" />
                <asp:Button ID="Button2" runat="server" Text="F to C" />
                <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
                <asp:Label ID="Label1" runat="server" Text="Output"></asp:Label>

            </p>
            
        </div>
    </section>
</asp:Content>

