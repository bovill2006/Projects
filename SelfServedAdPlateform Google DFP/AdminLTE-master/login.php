<?php
session_start();

$conn = mysql_connect("localhost", "root", "password");
mysql_select_db("test");

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
echo "Connected successfully, \n";


//create and issue the query
$sql = "SELECT type FROM users WHERE username = '".$_POST["username"]."' AND password = '".$_POST["password"]."'";

$result = mysql_query($sql);

//get the number of rows in the result set; should be 1 if a match
if (mysql_num_rows($result) == 1) {
   
	//if authorized, get the values of f_name l_name
      while ($info = mysql_fetch_array($result)) {
	$id =$info['id'];
	}
      echo $id;
    $_SESSION['id'] = $id; 
    header ("refresh:3; url=OrderTest.html");
      
      }  else {
	//redirect back to login form if not authorized
	  echo "incorrect login";
         

}
?>


