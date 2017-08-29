<?php
class dbconnect
{
	function connect()
	{
		$con = mysql_connect("localhost", "syao5", "syao5");
		if(!$con)
		{
			die('Could not connect: '.mysql_error());
		}
		mysql_select_db("syao5", $con);
	}
}
?>