<?php
session_start();

$conn = mysqli_connect("localhost", "root", "password", "test") or die("Error" . mysqli_error($conn));


echo "Connected successfully, \n";


//create and issue the query
$sql = "SELECT id FROM users WHERE username = '".$_POST['username']."' AND password = '".sha1(mysqli_real_escape_string($conn,$_POST['password']))."'" or die ("Error in query" . mysqli_error($conn));

$result = $conn->query($sql);

//get the number of rows in the result set; should be 1 if a match
if (mysqli_num_rows($result) == 1) {
	
	//if authorized, get the values of f_name l_name
      while ($info = mysqli_fetch_array($result)) {
	$id =$info['id'];
	}
      echo $id;
    $_SESSION['id'] = $id; 
    header ("refresh:0; url=account.php");
      
      }  else {
	//redirect back to login form if not authorized
	  echo "incorrect login";
         

}
?>


