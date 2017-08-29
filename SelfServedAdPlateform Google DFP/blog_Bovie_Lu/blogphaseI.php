<html>
<body>
<center>
<h2> Book Posts </h2>

<?php
include("dbconnect.php");
include("manageblog.php");
$con = new dbconnect();
$con->connect();
error_reporting(E_ALL);
$result = mysql_query("SELECT date_published, post_title, author, post, post_id FROM bookposts ORDER BY date_published DESC");

$man= new Manageblog();
$man->createTableDisplay();

while($row = mysql_fetch_array($result))
{
	$man->displayRow($row[0],$row[1],$row[2], $row[3], $row[4]);
}
?>
</table>
</center>
<br><br>
<form action=insertPosts.php>
<input type = "submit" value = "Add a Post"/></form>
</body>
</html>