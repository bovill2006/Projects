<a href="blogphaseI.php">Home</a>
<?php
include("dbconnect.php");
$con= new dbconnect();
$con->connect();
if(isset($_GET['id'])) {
	$display= $_GET['id'];
	$sSql = "SELECT * FROM bookposts WHERE post_id=\"$display\"";
	$oResult = mysql_query($sSql);
	$row = mysql_fetch_array($oResult);
	printf("<h2> Post info: </h2>");
	printf("<table border = 2>");
	printf("<tr><td><b>Post Id</td><td><b>Author</td><td><b>Post Title</td><td><b>Book Title</td>
			<td><b>Post</td><td><b>Date Published</td></tr>");
	printf("<tr>"."<td>".$row['post_id']."</td>"."<td>".$row['author']."</td>".
			"<td>".$row['post_title']."</td>"."<td>".$row['book_title']."</td>".
			"<td>".$row['post']."</td>"."<td>".$row['date_published']."</td>"."</tr>");
	printf("</table>");
	printf("<h3> Comments on <i>" .$row['post_title']." </i></h3>");	
	
	$sSql2 = "SELECT * FROM bookcomments WHERE post_id=\"$display\"";
	$results = mysql_query($sSql2);
	while($row2 = mysql_fetch_array($results))
	{
		echo"by <b>$row2[2]</b> on <b>$row2[4]</b> <br><br>";
		$text = wordwrap($row2[3], 100, "<br />\n");
		echo $text ;
		echo"<br><br><br>"; 
	}
	
}
?>

<form method="POST" action="<?php echo $_SERVER['PHP_SELF'];?>">
<br>
<br>
<h4>Add a Comment:</h4>
Name:  <input type="text" name="author"/><br/>
Comment:<br/>  <textarea name ="comment" rows="5" cols="40"/></textarea><br/>
<input type="submit" name="submit" value="Add Comment"/>