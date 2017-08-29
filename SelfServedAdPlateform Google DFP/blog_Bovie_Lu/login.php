<?php
session_start();
include("dbconnect.php");
$con= new dbconnect();
$con->connect();

//create and issue the query
$sql = "SELECT type FROM users WHERE username = '".$_POST["username"]."' AND password = '".$_POST["password"]."'";

$result = mysql_query($sql);

//get the number of rows in the result set; should be 1 if a match
if (mysql_num_rows($result) == 1) {
   $type="author";
	//if authorized, get the values of f_name l_name
      while ($info = mysql_fetch_array($result)) {
	$type =$info['type'];
	}
      echo $type;
       if($type == "admin")
        {
         $_SESSION['type']=$type; // type of user (admin or regular)
         $_SESSION['status']=100; // indicate that the login is successful
         echo " Login success, you will be directed to the  welcome page in 5 seconds";
         header("refresh: 5; url= welcome.php");
        }
        elseif($type == "author")
        {
          $_SESSION['type']=$type;
          $_SESSION['status']=100;
          echo "Login success, you will be directed to the  welcome page in 5 seconds";
          header("refresh:5 ; url= welcome.php");
        }
      
      }  else {
	//redirect back to login form if not authorized
	  echo "incorrect login";
         header("refresh:5; url=loginfailed.php");

}
?>


