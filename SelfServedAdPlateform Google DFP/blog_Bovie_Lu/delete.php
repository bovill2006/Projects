<?php
include("dbconnect.php");
$con= new dbconnect();
$con->connect();
if(isset($_GET['id'])) {
        $eml= $_GET['id'];
	$sSql = "DELETE FROM bookposts WHERE post_id=\"$eml\"";

	$oResult = mysql_query($sSql);
        $rows=mysql_affected_rows();
	echo "<h2>$rows Record(s) Deleted </h2>";
}
?>
<a href="blogphaseI.php">Home</a>
