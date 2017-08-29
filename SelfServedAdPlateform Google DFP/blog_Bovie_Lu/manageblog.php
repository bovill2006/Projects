<?php
class Manageblog
{

function createTable()
{
    echo "<table border=1>";
    echo "<tr>";
      echo "<th> Post id </th>";
      echo "<th> Author</th>";
      echo "<th> Post Title</th>";
      echo "<th> Book Title </th>";
      echo "<th> Post</th>";
      echo "<th> Date Published</th>";
      echo "<th> DELETE </th>";
      echo "<th> UPDATE </th>";
    echo "</tr>";

}

function createTableDisplay()
{
echo "<table border=1>";
    echo "<tr>";
    echo "<th> Post Title</th>";
    echo "<th> Author</th>";
    echo "<th> Post</th>";
    echo "<th> Date Published</th>";
    echo "</tr>";

}

function displayRowEdit($post_id, $author, $post_title, $book_title, $post, $date_published)
{
	echo "<tr>";
	echo "<td> $post_id </td>";
	echo "<td> $author </td>";
	echo "<td> $post_title </td>";
	echo "<td> $book_title </td>";
	echo "<td> $post </td>";
	echo "<td> $date_published </td>";
	echo "<td> <form action=\"delete.php?id=$post_id\" method=\"post\">";
	echo "<input type=\"submit\" value=\"DELETE\"> </form></th>";

	echo "<td> <form action=\"update.php?id=$post_id\" method=\"post\">";
	echo "<input type=\"submit\" value=\"UPDATE\"> </form></th>";

	echo "</tr>";
}

function displayRow($date, $post_title, $author, $post, $post_id )
{	$post = substr($post, 0 , 20);
	echo "<tr>";	
		echo "<td> <a href='bookcomments.php?id=$post_id'>$post_title</a></td>";
		echo "<td> $author </td>";
		echo "<td> $post ...</td>"; 
		echo "<td> $date </td>";
	echo "</tr>";
}

}
?>
