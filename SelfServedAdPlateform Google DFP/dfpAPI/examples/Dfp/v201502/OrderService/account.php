<html>
<head>
<title>User Account</title>
</head>
<body>
<center><h1>Welcome To UFree Ads</h1>
<form action="OrderTest.html">
    <input type="submit" value="New Order">
</form>

<?php

include("TableCreation.php");
session_start();

error_reporting(E_STRICT | E_ALL);

$path = dirname(__FILE__) . '/../../../../src';
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

require_once 'Google/Api/Ads/Dfp/Lib/DfpUser.php';
require_once dirname(__FILE__) . '/../../../Common/ExampleUtils.php';
require_once 'Google/Api/Ads/Dfp/Util/StatementBuilder.php';
require_once 'Google/Api/Ads/Common/Util/MapUtils.php';

$create = new TableLayout();
$create->createTable();

try {
    $user = new DfpUser();
    $user->LogDefaults();

    $orderService = $user->GetService('OrderService', 'v201405');
    $lineItemService = $user->GetService('LineItemService', 'v201405');

    $advertiserId = $_SESSION['id'];

  
    $sb = new StatementBuilder(); 
    
    $sb 
        ->Where('advertiserId =: advertiserId')
        ->OrderBy('StartDateTime DESC')
        ->Limit(10)
        ->WithBindVariableValue('advertiserId', $advertiserId);

    $page = $orderService->getOrdersByStatement($sb->ToStatement());

  // Display results.
  if (isset($page->results)) {
    $i = $page->startIndex;
        
    foreach ($page->results as $order) {
    
        $month = $order->startDateTime -> date -> month;
        $day = $order->startDateTime -> date -> day ;
        $year = $order->startDateTime -> date -> year ;
        $date = "On "."$month"."/"."$day"."/"."$year" ;
        $hour = $order->startDateTime -> hour; 
        $min = $order->startDateTime -> minute; 
        $time = "$hour".":"."$min";
        $start = $date."\nAt ".$time; // <------------------------Start date and time
    
        $month = $order->endDateTime -> date -> month;
        $day = $order->endDateTime -> date -> day ;
        $year = $order->endDateTime -> date -> year ;
        $date = "On "."$month"."/"."$day"."/"."$year" ;
        $hour = $order->endDateTime -> hour; 
        $min = $order->endDateTime -> minute; 
        $time = "$hour".":"."$min";
        $end = $date."\nAt ".$time; // <--------------------------End Date and time
        
        $impressions = $order -> totalImpressionsDelivered;
        $clicks = $order -> totalClicksDelivered; 
        $ICCount = "$impressions"."/"."$clicks"; //<---------------- impressions and click counts
        
        $currency = $order->totalBudget->currencyCode; 
        $microAmount = ($order -> totalBudget->microAmount) / 1000000;
        $microAmount = number_format($microAmount , 2, '.', ',');
        $totalBudget = $currency." "."$microAmount"; //<---------------------total budget
        
        //Im using PQL to get line item that matches orderid 
        /*$statementBuilder = new StatementBuilder();
        $statementBuilder->Where('orderid = :orderid')
            ->OrderBy('StartDateTime DESC')
            ->Limit(StatementBuilder::SUGGESTED_PAGE_LIMIT)
            ->WithBindVariableValue('orderid', $order->id);
        
        $results = $lineItemService->getLineItemsByStatement(
        $statementBuilder->ToStatement())->results; 
        */
        if(isset($results[0])){
        $lineItemNames = $results[0]->name;
        }else {$lineItemNames = "N/A";}
        
        //Print the Table
        $create -> displayRow($order->id, $order->status, $order->name, 
                              $totalBudget, $ICCount, $lineItemNames, $start, $end);            
        $i++;
    }
  }
} 

catch (OAuth2Exception $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (ValidationException $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (Exception $e) {
  print $e->getMessage() . "\n";
}
?>

    </center>
</body>
</html>