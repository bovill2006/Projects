<?php
include("dbconnect.php");
$con=new dbconnect();
$con->connect();
if(isset($_POST['submit']))
{
	$query1= "INSERT INTO bookposts
		   (author, post_title, book_title, post)
		   VALUES
		   ('".$_POST['author']."', '".$_POST['post_title']."', '".$_POST['book_title']."', '".$_POST['post']."')";

	 mysql_query($query1);
	 $update=mysql_affected_rows();
	 echo"<h2>$update record Inserted </h2><br/>";

	 echo "Submission Successful, you will be redirected back to the home page in 5 Seconds";
         header("refresh:5 ; url= blogphaseI.php");
}
?>

<form method="POST" action="<?php echo $_SERVER['PHP_SELF'];?>">
Author Name:  <input type="text" name="author"/><br/>
Post Title:  <input type="text" name="post_title"/><br/>
Book Title:  <input type="text" name="book_title"/><br/>
Post:<br/>  <textarea name ="post" rows="5" cols="40"/></textarea><br/>
<input type="submit" name="submit" value="Add Record"/>
</form>

<a href="blogphaseI.php">Home</a>