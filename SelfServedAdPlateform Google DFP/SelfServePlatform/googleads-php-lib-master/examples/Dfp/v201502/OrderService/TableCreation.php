<?php
class TableLayout
{

function createTable()
{
    echo "<table border=1>";
    echo "<tr>";
      echo "<th> Approval Status </th>";
      echo "<th> Order Name </th>";
      echo "<th> Total Budget</th>";
      echo "<th> Impression/Clicks </th>";
      echo "<th> Line Items</th>";
      echo "<th> Date Published</th>";
      echo "<th> End Date </th>";
      echo "<th> UPDATE </th>";
    echo "</tr>";

}



function displayRow($id, $status, $name, $cost, $ICCount, $LineItems, $date_published, $end_date)
{
	echo "<tr>";
	echo "<td> $status </td>";
	echo "<td> $name </td>";
	echo "<td> $cost </td>";
	echo "<td> $ICCount </td>";
	echo "<td> $LineItems </td>";
	echo "<td> $date_published </td>";
	echo "<td> $end_date </td>";

	echo "<td> <form action=\"update.php?orderid=$id\" method=\"post\">";
	echo "<input type=\"submit\" value=\"UPDATE\"> </form></th>";

	echo "</tr>";
}
}

?>
