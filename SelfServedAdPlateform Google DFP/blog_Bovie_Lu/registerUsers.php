<?php
include("dbconnect.php");
$con=new dbconnect();
$con->connect();
if(isset($_POST['submit'])) {
		$type = "author";

        if($_POST[type] =="admin")
        $type = "admin";
       else
        $type = "author";

	$sSql = "INSERT INTO users
		(first_name, last_name, email, username, password, type)
		 VALUES ('$_POST[first_name]', '$_POST[last_name]', '$_POST[email]', '$_POST[username]', '$_POST[password]', '$type')";
      echo $sSql;
	mysql_query($sSql);

	echo '<h2>USER REGISRERED</h2><br />';
}
?>
