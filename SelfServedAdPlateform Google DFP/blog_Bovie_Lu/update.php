<?php
include("dbconnect.php");
$con = new dbconnect();
$con->connect();

if(isset($_POST['submit'])) {
         $author = $_POST['author'];
         $pt = $_POST['post_title'];
         $bt = $_POST['book_title'];
         $po = $_POST['post'];

         $id = $_POST['id'];
         $sSql="UPDATE bookposts SET author =\"$author\" , post_title=\"$pt\",
         book_title= \"$bt\", post= \"$po\" WHERE post_id =\"$id\"";
         mysql_query($sSql);

         echo "Submission Successful, you will be redirected back to the home page in 5 Seconds";
         header("refresh:5 ; url= blogphaseI.php");
}

if(isset($_GET['id'])) {

        $sSql = "SELECT * FROM bookposts WHERE post_id='". $_GET['id']."'";

        $oResult = mysql_query($sSql);

        $aRow = mysql_fetch_assoc($oResult);
}
?>
<form method="POST" action="<?php echo $_SERVER['PHP_SELF'].'?id='.$_GET['id']; ?>" >
		<input type="hidden" name="id" value="<?php echo $_GET['id']; ?>" />
        Author:<input type="text" name="author" value="<?php echo $aRow['author']; ?>" /><br />
        Post Title:<input type="text" name="post_title" value="<?php echo $aRow['post_title']; ?>" /><br />
        Book Title:<input type="text" name="book_title" value="<?php echo $aRow['book_title']; ?>" /><br />
        Post:<br/> <textarea rows= "5" cols ="40" type="text" name="post" value="<?php echo $aRow['post']; ?>" /></textarea><br />

        <input type="submit" name="submit" value="Update Item" />
</form>
<a href="blogphaseI.php">Home</a>
